#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}



static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len)
	{		
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


static int	ft_string_size(char const *str, char c)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			++len;
			while (str[i] && str[i] != c)
				++i;
		}
		else
			++i;
	}
	return (len);
}

static char	**ft_create_subs(char **spl, char const *s, char c)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (*s)
	{
		if (*s != c)
		{
			size = 0;
			while (*s && *s != c)
			{
				size++;
				s++;
			}
			spl[i++] = ft_substr(s - size, 0, size);
		}
		else
			s++;
	}
	spl[i] = 0;
	return (spl);
}

char	**ft_split(char const *s, char c)
{
	char	**spl;

	if (!s)
		return (0);
	spl = malloc(sizeof(char *) * (ft_string_size(s, c) + 1));
	if (!spl)
		return (0);
	spl = ft_create_subs(spl, s, c);
	return (spl);
}
