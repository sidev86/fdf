#ifndef FDF_H
# define FDF_H

# define		W_WIDTH	1024
# define		W_HEIGHT 768
# define		M_WIDTH  250

# define 	COLOR_1  0x009387
# define		COLOR_2	0XB5EBFD

# define		TXT_COLOR 0XFFFFFF
# define		MENU_COLOR 0X090A2F

# define FT_UINT_MAX	((unsigned)(~0L))
# define FT_INT_MAX		((int)(FT_UINT_MAX >> 1))
# define FT_INT_MIN		((int)(~FT_INT_MAX))

# include "get_next_line.h"
# include "mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

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
	int z_min;
	int z_max;
	int *alt_arr;
	int *color_arr;
	int gradient[5];
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
	double z_div;
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
void	add_altitude_data(t_altitudes **alt, int y, int x, char **map_val);
t_point     projection(t_point p, t_fdf *fdf);
t_point	point_init(t_map **map, int x, int y);
t_fdf   *init_fdf(t_map *map);
t_camera    *init_camera(t_fdf *fdf);
void draw_map(t_fdf *fdf, t_map *map);
t_map   *init_map(void);
void    input_controls(t_fdf **fdf);
void change_camera_angle(t_fdf **fdf, int key);
void    move_map(t_fdf **fdf, int key);
int read_map(char *path, t_map **map, t_altitudes **alt);
void    translate_z(t_fdf **fdf, int key);
void error_message(void);
int			ft_atoi_base(const char *str, int base);
void		stack_to_arrays(t_altitudes **alt_stack, t_map *map);
int		ft_isnumber(char *str, int base);
void		push_to_stack(t_altitudes **alt_stack, t_altitudes *new);
int	get_color(t_point current, t_point start, t_point end, t_point delta);
void change_gradient_values(t_fdf **fdf);
int	get_default_color(int z, t_map *map);
void	print_menu(t_fdf *fdf);
void change_projection(t_fdf **fdf, int key);

#endif