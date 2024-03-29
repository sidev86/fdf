/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:24:47 by sibrahim          #+#    #+#             */
/*   Updated: 2023/04/19 12:24:48 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_string_size(char const *str, char c)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != '\n' && str[i])
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
		if (*s != c && *s != '\n')
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
