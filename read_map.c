#include "fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int read_map(char *path, t_map **map, t_altitudes **alt)
{
	int	fd;
	int r = 0;
	int c = 0; 
	char *maprow;
	char **row;
	
	fd = open(path, O_RDONLY);
	if(fd != -1)
	{
		while(1)
		{
			//printf("leggo la mappa\n");
			maprow = get_next_line(fd);
			if (maprow)
			{
				row = ft_split(maprow, ' ');
				while(row[c] != 0)
				{
					//printf("%s ", row[c]);
					if (alt == NULL || *alt == NULL)
						*alt = malloc(sizeof(t_altitudes));
					add_altitude_data(alt, r, c, atoi(row[c]));
					
					
					c++;
				}
				(*map)->width = c;
				r++;
				c = 0; 
			}
			else
			{
				(*map)->height = r;
				close(fd);
				break ;
			}		
		}
	}
	else
	{
		return (-1);
	}

	printf("aaalt %d\n", (*alt)->height);
	return (0);
}