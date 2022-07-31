/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:40:32 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 16:38:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**affect(char **tmp, char **line, char **buffer)
{
	char	**ret;

	*tmp = *buffer;
	*buffer = ft_strjoin(*buffer, *line);
	free(*line);
	free(*tmp);
	*tmp = *buffer;
	*buffer = ft_strjoin(*buffer, "\n");
	free(*tmp);
	ret = ft_split(*buffer, '\n');
	free(*buffer);
	return (ret);
}

int	map_check2(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
		{
			if ((*(buffer + 1) == ' ' || *(buffer + 1) == '1'))
			{
				while (*buffer)
				{
					if (ft_comp(buffer, "\n\n"))
						return (-1);
					buffer++;
				}
			}
		}
		if (*buffer == '\0')
			return (1);
		buffer++;
	}
	if (*buffer == '\0')
		return (1);
	buffer++;
	return (1);
}

char	**read_input(char *file)
{
	int		fd1;
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	fd1 = open(file, O_RDONLY);
	if (fd1 < 0)
		return (NULL);
	while (get_next_line(fd1, &line))
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(line);
		free(tmp);
		tmp = buffer;
		buffer = ft_strjoin(buffer, "\n");
		free(tmp);
	}
	if (map_check2(buffer) == -1)
		return (NULL);
	return (affect(&tmp, &line, &buffer));
}

void	skip_digits(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
}

void	skip_digits2(char ***line)
{
	while (ft_isdigit(***line))
		(**line)++;
}
