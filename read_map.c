#include "fdf.h"
#define MAR_W 201

static void	free_array_split(char **arr)
{
	size_t	i;

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

	alt_coord = (t_altitudes *)malloc(sizeof(t_altitudes));
	if (!alt_coord)
		error_message("Memory Allocation Error!\n");
	parts = ft_split(s, ',');
	if (!parts)
		error_message("Memory Allocation Error!\n");
	if (parts[1] && !ft_isnumber(parts[1], 16))
		error_message("Error! Wrong Map Data in Map File\n");
	alt_coord->height = ft_atoi_base(parts[0], 10);
	if (parts[1])
		alt_coord->color = ft_atoi_base(parts[1], 16);
	else
		alt_coord->color = -1;
	alt_coord->next = NULL;
	free_array_split(parts);
	return (alt_coord);
}

static void	line_check(char **row, t_altitudes **alt_stack, t_map *map)
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
	else if (map->width != width && width != MAR_W)
		error_message("Error. Wrong Map File Format\n");
}

int	read_map(char *path, t_map **map, t_altitudes **alt_stack)
{
	int		fd;
	char	*maprow;
	char	**row;

	fd = open(path, O_RDONLY);
	while (fd != -1)
	{
		maprow = get_next_line(fd);
		if (maprow)
		{
			row = ft_split(maprow, ' ');
			if (!row)
				error_message("Reading Map Error! Exit program\n");
			line_check(row, alt_stack, *map);
			(*map)->height++;
			free_array_split(row);
			free(maprow);
		}
		else
			break ;
	}
	if (fd == -1)
		return (-1);
	return (0);
}
