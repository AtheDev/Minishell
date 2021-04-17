/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:08:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 15:39:25 by adupuy           ###   ########.fr       */
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
