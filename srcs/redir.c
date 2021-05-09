/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:08:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/07 07:25:05 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_out(char *line, int i)
{
	if (i > 0 && line[--i] == ' ')
	{
		while (line[i] == ' ' && i > 0)
			i--;
		if (line[i] == '>' && redir(line, i) == 0)
			return (1);
	}
	else if (line[i] == '<' && redir(line, i) == 0)
		return (1);
	else if (line[i] == '>' && redir(line, i) == 0 && i > 0)
	{
		if (line[--i] == ' ')
			while (line[i] == ' ' && i > 0)
				i--;
		if ((line[i] == '<' || line[i] == '>') && redir(line, i) == 0)
			return (1);
	}
	return (0);
}

int	check_redir(char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[--i] == ' ')
			while (line[i] == ' ' && i > 0)
				i--;
		if ((line[i] == '<' || line[i] == '>') && redir(line, i) == 0)
			return (1);
	}
	if (line[i] == '>')
		if (check_redir_out(line, i) == 1)
			return (1);
	return (0);
}

int	count_redir(char **arg)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (arg[++i] != NULL)
	{
		if (ft_strncmp(arg[i], ">>", ft_strlen(arg[i])) == 0)
			count++;
		else if (ft_strncmp(arg[i], "<", ft_strlen(arg[i])) == 0)
			count++;
	}
	return (count);
}

int	ft_isredir(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}
