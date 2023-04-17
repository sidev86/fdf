#include "fdf.h"

void		push_to_stack(t_altitudes **alt_stack, t_altitudes *new)
{
	if (alt_stack)
	{
		if (new)
			new->next = *alt_stack;
		*alt_stack = new;
	}
}

t_altitudes	*get_from_stack(t_altitudes **alt_stack)
{
	t_altitudes *head;

	head = NULL;
	if (alt_stack && *alt_stack)
	{
		head = *alt_stack;
		*alt_stack = (*alt_stack)->next;
	}
	return (head);
}

void	free_stack(t_altitudes **alt_stack)
{
	t_altitudes	*tmp;

	while (*alt_stack)
	{
		tmp = *alt_stack;
		(*alt_stack) = (*alt_stack)->next;
		free(tmp);
	}
	
}

void		stack_to_arrays(t_altitudes **alt_stack, t_map *map)
{
	t_altitudes    *alt_coord;
	ssize_t		i;
	size_t		arr_size;

	arr_size = map->width * map->height * sizeof(int);
	if (!(map->alt_arr = (int *)malloc(arr_size)))
		error_message();
	if (!(map->color_arr = (int *)malloc(arr_size)))
		error_message();
	i = map->width * map->height - 1;
	while ((alt_coord = get_from_stack(alt_stack)) && i >= 0)
	{
		map->alt_arr[i] = alt_coord->height;
		map->color_arr[i] = alt_coord->color;
		if (alt_coord->height > map->z_max)
			map->z_max = alt_coord->height;
		if (alt_coord->height < map->z_min)
			map->z_min = alt_coord->height;
		i--;
		free(alt_coord);
	}
	free_stack(alt_stack);
}