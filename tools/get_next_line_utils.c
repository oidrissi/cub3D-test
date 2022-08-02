/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:09:50 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 02:52:42 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!ft_strlen(s1) && !ft_strlen(s2))
		return (ft_strdup(s2));
	ret = (char *)malloc((sizeof(char)) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(ret))
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	int		lensrc;
	char	*ptr;
	int		i;

	ptr = NULL;
	i = -1;
	if (s1)
	{
		lensrc = (int)ft_strlen(s1);
		ptr = (char *)malloc(lensrc + 1);
		if (!(ptr))
			return (0);
		while (s1[++i])
			ptr[i] = s1[i];
		ptr[i] = '\0';
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!(sub))
		return (NULL);
	while (s[i + start] && len--)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}
