/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 22:47:51 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/15 23:06:21 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_end_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		if (!(s1 = malloc(sizeof(char))))
			return (NULL);
		s1[0] = '\0';
	}
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (i + j + 1))))
	{
		free(s1);
		return (NULL);
	}
	str[i + j] = '\0';
	while (--j >= 0)
		str[i + j] = s2[j];
	while (--i >= 0)
		str[i] = s1[i];
	if (s1)
		free(s1);
	return (str);
}

int		save_line(char **line, char *str, int ret)
{
	*line = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (*line == NULL)
	{
		free(str);
		return (-1);
	}
	ft_strlcpy(*line, str, ft_strlen(str));
	free(str);
	str = NULL;
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	char		*str;
	int			count;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (-1);
	str = NULL;
	ret = 1;
	while ((ret > 0) && ((count = ft_is_end_line(str)) == 0))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (!(str = ft_my_strjoin(str, buf)))
			return (-1);
	}
	return (save_line(line, str, ret));
}
