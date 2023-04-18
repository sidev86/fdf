#include "fdf.h"

static size_t	ft_message_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	error_message(char *str)
{
	write(2, str, ft_message_len(str));
	exit(1);
}
