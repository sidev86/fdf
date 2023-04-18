#ifndef FDF_H
# define FDF_H

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define M_WIDTH  250
# define COLOR_1  0X009387
# define COLOR_2 0XB5EBFD
# define KEYB_ESC 53
# define KEYB_I 34
# define KEYB_P 35
# define KEYB_Q 12
# define KEYB_E 14
# define KEYB_A 0
# define KEYB_D 2 
# define KEYB_Z 6
# define KEYB_C 8
# define KEYB_J 38 
# define KEYB_L_ARROW 123 
# define KEYB_R_ARROW 124 
# define KEYB_U_ARROW 126 
# define KEYB_D_ARROW 125 
# define KEYB_MINUS 44 
# define KEYB_PLUS 30
# define TXT_COLOR 0XFFFFFF
# define MENU_COLOR 0X090A2F
# define FT_INT_MAX 2147483647;
# define FT_INT_MIN -2147483648;

# include "get_next_line.h"
# include "mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;

typedef struct s_map
{
	int	width;
	int	height;
	int	z_min;
	int	z_max;
	int	*alt_arr;
	int	*color_arr;
	int	gradient[5];
}		t_map;

typedef struct s_altitudes
{
	int					x;
	int					y;
	int					height;
	int					color;
	struct s_altitudes	*next;
}		t_altitudes;

typedef struct s_camera
{
	int		zoom;
	int		x_off;
	int		y_off;
	int		iso_active;
	double	alpha;
	double	beta;
	double	gamma;
	double	z_div;
}				t_camera;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;	
	int			bpp;
	int			line_width;
	int			endian;
	t_camera	*cam;
	t_map		*map;
	t_altitudes	*alt;
}		t_fdf;

t_point		projection(t_point p, t_fdf *fdf);
t_point		point_init(t_map **map, int x, int y);
t_fdf		*init_fdf(t_map *map);
t_map		*init_map(void);
t_camera	*init_camera(t_fdf *fdf);
char		**ft_split(char const *s, char c);
int			get_altitude_value(t_altitudes **alt, int y, int x);
void		add_altitude_data(t_altitudes **alt, int y, int x, char **map_val);
void		draw_map(t_fdf *fdf, t_map *map);
void		draw_line(t_point a, t_point b, t_fdf *fdf);
void		input_controls(t_fdf **fdf);
void		change_camera_angle(t_fdf **fdf, int key);
void		move_map(t_fdf **fdf, int key);
int			read_map(char *path, t_map **map, t_altitudes **alt);
void		translate_z(t_fdf **fdf, int key);
void		error_message(char *str);
int			ft_atoi_base(const char *str, int base);
void		stack_to_arrays(t_altitudes **alt_stack, t_map *map);
int			ft_isnumber(char *str, int base);
void		push_to_stack(t_altitudes **alt_stack, t_altitudes *new);
int			get_color(t_point current, t_point start, t_point end,
				t_point delta);
void		change_gradient_values(t_fdf **fdf);
int			get_default_color(int z, t_map *map);
void		print_menu(t_fdf *fdf);
void		change_projection(t_fdf **fdf, int key);
int			terminate(t_fdf **fdf);

#endif
