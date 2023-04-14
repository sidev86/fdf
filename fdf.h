#include "get_next_line.h"
#include "mlx/mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#define		W_WIDTH	1024
#define		W_HEIGHT 768


typedef struct	s_point
{
	int	x;
	int	y;
	int z; 
	int color; 
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
	int		color; 
	struct s_altitudes *next; 
}				t_altitudes;

typedef struct s_camera
{
	int zoom;
	int x_off;
	int y_off;  
	double alpha;
	double beta;
	double gamma; 
	int iso_active; 
}				t_camera; 



typedef struct s_fdf
{
	void *mlx; 
	void *win; 
	void *img;
	char *data_addr;	
	int					bpp;
	int					line_width;
	int					endian;
	t_camera *cam; 
	t_map *map; 
	t_altitudes *alt;
	
}			t_fdf; 

char	**ft_split(char const *s, char c);
int		get_altitude_value(t_altitudes **alt, int y, int x);
void	add_altitude_data(t_altitudes **alt, int y, int x, int height);
t_point     projection(t_point p, t_fdf *fdf);
t_point	point_init(t_altitudes **alt, int x, int y);
t_fdf   *init_fdf(t_map *map);
t_camera    *init_camera(t_fdf *fdf);
void draw_map(t_fdf *fdf, t_map *map);
t_map   *init_map(void);

int read_map(char *path, t_map **map, t_altitudes **alt);
void error_message(void);