#include "get_next_line.h"

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
	double alpha;
	double beta;
	double gamma; 
	int iso_active; 
}				t_camera; 

typedef struct s_img
{
	void	*mlx_img; 
	int		bpp; 
	int		line_width; 
	int		endian; 
}				t_img; 

typedef struct s_fdf
{
	void *mlx; 
	void *win; 
	char *data_addr;
	struct s_point **points_map;
	struct s_camera *cam; 
	struct s_map *map; 
	struct s_img *img; 
	
}			t_fdf; 

char	**ft_split(char const *s, char c);