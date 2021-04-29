/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 09:56:23 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/29 14:07:40 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar(char **line, int index, int *i, t_env *env)
{
	int	size_tot;

	size_tot = 0;
	while ((*line)[index] != '"' && !is_escaped(*line, index - 1))
	{
		if ((*line)[index] == '$')
		{
			*i = index;
			if (replace_variable(line, i, env) < 0)
				return (0);
			index = ++(*i);
			index--;
		}
		index++;
	}
	*i += 1;
	return (1);
}

int	var_is_digit_or_interrogation_point
	(char **line, int *i, char *tmp, t_env *env)
{
	char	*tmp2;
	char	*num;

	tmp2 = NULL;
	num = NULL;
	if ((ft_isdigit((*line)[*i + 1]) == 1))
		return (delete_two_char(line, i));
	if ((*line)[*i + 1] == '?')
	{
		if (delete_two_char(line, i) == -1)
			return (-1);
		tmp = ft_substr(*line, 0, *i + 1);
		tmp2 = ft_substr(*line, *i + 1, ft_strlen(*line) - *i);
		if (tmp != NULL && tmp2 != NULL)
		{
			if ((num = ft_itoa(env->return_value)) != NULL)
			{
				tmp = ft_my_strjoin(tmp, num);
				if (tmp != NULL)
				{
					*line = ft_free(*line);
					*line = ft_strjoin(tmp, tmp2);
					process_free(tmp, tmp2);
					if (num != NULL)
						num = ft_free(num);
					if (*line != NULL)
						return (0);
				}
			}
		}
		process_free(tmp, tmp2);
		if (num != NULL)
			num = ft_free(num);
		return (error_msg(2, ' '));
	}
	return (1);
}

int	variable_not_found(char **line, char *tmp, int pos_dollar, int size_var)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp = ft_substr(*line, 0, pos_dollar);
	tmp2 = ft_substr(*line, pos_dollar + size_var + 1, ft_strlen(*line)
	- (pos_dollar + size_var + 1));
	if (tmp != NULL && tmp2 != NULL)
	{
		*line = ft_strjoin(tmp, tmp2);
		if (*line != NULL)
			return (0);
	}
	*line = process_free(tmp, tmp2);
	return (-1);
}

int	recover_variable(char **line, int *i, int *size_var, int *index, t_env *env)
{
	int		j;
	char	*tmp;
	int		ret;
	int		pos_dollar;

	pos_dollar = *index;
	while ((*line)[++*i] != '\0' && (ft_isalnum((*line)[*i]) == 1
	|| (*line)[*i] == '_'))
		(*size_var)++;
	if ((tmp = malloc(sizeof(char) * (*size_var + 1))) == NULL)
		return (-1);
	j = 0;
	while (++(*index) < *i)
		tmp[j++] = (*line)[*index];
	tmp[j] = '\0';
	*index = ft_strlen(tmp);
	ret = search_var_env(&tmp, env, *size_var);
	if (ret == -1)
		free(tmp);
	else if (ret == 1)
		return (variable_not_found(line, tmp, pos_dollar, *size_var));
	else if (ret == 0)
		return (swap_var_env(&tmp, line, pos_dollar, *size_var));
	return (ret);
}

int	replace_variable(char **line, int *i, t_env *env)
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
	ret = recover_variable(line, i, &size_var, &index, env);
	process_free(tmp, NULL);
	if (ret == 0)
		*i = pos_dollar - 1;
	else if (ret == -1)
		return (error_msg(2, ' '));
	else
		*i = --(*i) + index - size_var - 2;
	return (0);
}
