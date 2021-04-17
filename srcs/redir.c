/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:08:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/17 10:03:39 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		if (line[--i] == ' ')
		{
			while (line[i] == ' ' && i > 0)
				i--;
			if (line[i] == '>' && redir(line, i) == 0)
				return (1);
		}
		else if (line[i] == '<' && redir(line, i) == 0)
			return (1);
		else if (line[i] == '>' && redir(line, i) == 0)
		{
			if (line[--i] == ' ')
				while (line[i] == ' ' && i > 0)
					i--;
			if ((line[i] == '<' || line[i] == '>') && redir(line, i) == 0)
				return (1);
		}	
	}
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
