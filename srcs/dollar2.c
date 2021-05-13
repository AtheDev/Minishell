/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:37:57 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 19:38:54 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_next(char *tmp, char *tmp2, char **line, char *num)
{
	if ((tmp = ft_my_strjoin(tmp, num)) != NULL)
	{
		*line = ft_free(*line);
		*line = ft_strjoin(tmp, tmp2);
		process_free(tmp, tmp2);
		if (num != NULL)
			num = ft_free(num);
		if (*line != NULL)
			return (0);
	}
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
			if ((num = ft_itoa(env->return_value)) != NULL)
				if (var_next(tmp, tmp2, line, num) == 0)
					return (0);
		process_free(tmp, tmp2);
		if (num != NULL)
			num = ft_free(num);
		return (error_msg(2, ' '));
	}
	return (1);
}
