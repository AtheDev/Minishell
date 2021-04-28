/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:32:58 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/27 19:43:06 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		empty_line(char **line, int i)
{
	while ((*line)[i] != '\0')
	{
		if (ft_isprint((*line)[i]) == 1 && ft_isspace((*line)[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*clean_line(char *str)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	if (ft_isspace(str[i - 1]) == 1)
	{
		while (ft_isspace(str[i - 1]) == 1)
			i--;
	}
	tmp = my_substr(str, 0, i, -1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

int		delete_two_char(char **line, int *i)
{
	if ((*line = delete_char((*line), i)) == NULL)
		return (error_msg(2, ' '));
	(*i)++;
	if ((*line = delete_char((*line), i)) == NULL)
		return (error_msg(2, ' '));
	return (0);
}
