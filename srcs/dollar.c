/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 09:56:23 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 19:39:12 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		variable_not_found(char **line, char *tmp, int pos_dollar, int size_var)
{
	char	*tmp2;

	tmp2 = NULL;
	if (tmp != NULL)
		tmp = ft_free(tmp);
	tmp = ft_substr(*line, 0, pos_dollar);
	tmp2 = ft_substr(*line, pos_dollar + size_var + 1, ft_strlen(*line)
	- (pos_dollar + size_var + 1));
	if (tmp != NULL && tmp2 != NULL)
	{
		if (*line != NULL)
			*line = ft_free(*line);
		*line = ft_strjoin(tmp, tmp2);
		process_free(tmp, tmp2);
		if (*line != NULL)
			return (0);
	}
	*line = process_free(tmp, tmp2);
	return (-1);
}

char	*init_tmp(char **line, int *i, int *size_var, int *index)
{
	char	*tmp;
	int		j;

	while ((*line)[++*i] != '\0' && (ft_isalnum((*line)[*i]) == 1
	|| (*line)[*i] == '_'))
		(*size_var)++;
	if ((tmp = malloc(sizeof(char) * (*size_var + 1))) == NULL)
		return (NULL);
	j = 0;
	while (++(*index) < *i)
		tmp[j++] = (*line)[*index];
	tmp[j] = '\0';
	return (tmp);
}

int		recover_variable(char **line, int *i, int *size_var, int *index)
{
	char	*tmp;
	int		ret;
	int		pos_dollar;

	pos_dollar = *index;
	if ((tmp = init_tmp(line, i, size_var, index)) == NULL)
		return (-1);
	*index = ft_strlen(tmp);
	ret = search_var_env(&tmp, &g_sig.env, *size_var);
	if (ret == -1)
		free(tmp);
	else if (ret == 1)
	{
		*index = pos_dollar;
		return (variable_not_found(line, tmp, pos_dollar, *size_var));
	}
	else if (ret == 0)
	{
		ret = swap_var_env(&tmp, line, &pos_dollar, *size_var);
		*index = pos_dollar;
		return (ret);
	}
	return (ret);
}

int		replace_variable(char **line, int *i, t_env *env)
{
	char	*tmp;
	int		index;
	int		pos_dollar;
	int		size_var;
	int		ret;

	index = *i;
	pos_dollar = index;
	tmp = NULL;
	size_var = 0;
	ret = var_is_digit_or_interrogation_point(line, i, tmp, env);
	if (ret == 0 || ret == -1)
		return (ret);
	ret = recover_variable(line, i, &size_var, &index);
	process_free(tmp, NULL);
	if (ret == 0)
		*i = index - 1;
	else if (ret == -1)
		return (error_msg(2, ' '));
	return (0);
}
