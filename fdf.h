#include "get_next_line.h"

char	**ft_split(char const *s, char c);

typedef struct s_vars
{
	void	*mlx; 
	void	*win; 
}				t_vars; 


typedef struct	s_point
{
	int	x;
	int	y;
	int	pos[3];
}		t_point;

typedef struct	s_map
{
	int width; 
	int height; 
}				t_map;


typedef struct s_altitudes
{
	int		x;
	int		y; 
	int		height;
	struct s_altitudes *next; 
}				t_altitudes;

typedef struct s_camera
{
	int zoom; 
}				t_camera; 


typedef struct s_fdf
{
	void *mlx; 
	void *win; 
	struct s_camera *cam; 
	struct s_map *map; 
}			t_fdf; 

