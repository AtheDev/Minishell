/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:12:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/20 10:27:06 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_quotes(char *line, int *i)
{
	int		index;
	char	*tmp;
	int		ret;

	++*i;
	index = *i;
	ret = 0;
	while ((line[*i] != '"' || (line[*i] == '"' &&
		is_escaped(line, *i - 1) == 1)) && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (error_msg(3, ' '));
	tmp = ft_substr(line, index, *i - index);
	ret = check_word(tmp, 0, 1);
	free(tmp);
	return (ret);
}

int	check_simple_quote(char *line, int *i)
{
	++*i;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (error_msg(3, ' '));
	return (0);
}
