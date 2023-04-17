#include "fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



static void			free_array_split(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
		
	free(arr);
}

static t_altitudes	*add_coordinate(char *s)
{
	t_altitudes	*alt_coord;
	char		**parts;

	if (!(alt_coord = (t_altitudes *) malloc(sizeof(t_altitudes))))
		error_message();
	if (!(parts = ft_split(s, ',')))
		error_message();
	/*if (!ft_isnumber(parts[0], 10))
		error_message();*/
	/*if (parts[1])
		error_message();*/
	alt_coord->height = atoi(parts[0]);
	alt_coord->color = parts[1] ? ft_atoi_base(parts[1], 16) : -1;
	alt_coord->next = NULL;
	free_array_split(parts);
	return (alt_coord);
}

static void		line_check(char **row, t_altitudes **alt_stack, t_map *map)
{
	int	width;

	width = 0;
	while (*row)
	{
		push_to_stack(alt_stack, add_coordinate(*(row++)));
		width++;
	}
	if (map->height == 0)
		map->width = width;
	else if (map->width != width)
		error_message();
}


int read_map(char *path, t_map **map, t_altitudes **alt_stack)
{
	int	fd;
	char *maprow;
	char **row;
	
	fd = open(path, O_RDONLY);
	if(fd != -1)
	{
		while(1)
		{
			maprow = get_next_line(fd);
			if (maprow)
			{
				if (!(row = ft_split(maprow, ' ')))
					error_message();
				line_check(row, alt_stack, *map);
				(*map)->height++;
				free_array_split(row);
			}
			else
				break;
		}
	}
	else
		return (-1);
	return (0);
}