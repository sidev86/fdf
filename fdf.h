#include "get_next_line.h"



char	**ft_split(char const *s, char c);
typedef struct	s_point
{
	int	x;
	int	y;
	int	pos[3];
	struct s_point	*next;
}		t_point;
