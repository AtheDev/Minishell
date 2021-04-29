/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:04:11 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/29 14:03:29 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_variable(char *line, int *i, int quote)
{
	*i += 1;
	while (line[*i] != '\0' && (ft_isalnum(line[*i]) == 1 || line[*i] == '_'))
		(*i)++;
	if (line[*i] == '`')
		return (error_msg(3, ' '));
	if (line[*i] == '\\' && line[*i + 1] == '\0')
		return (error_msg(3, ' '));
	if (line[*i] == '|' && empty_line(&line, *i + 1) == 1 && quote == 0)
		return (error_msg(3, ' '));
	if (quote == 0 &&
	((line[*i] == '(' && empty_line(&line, *i + 1) == 1) ||
	(line[*i] == ')' && empty_line(&line, *i + 1) == 1) ||
	(line[*i] == '>' && empty_line(&line, *i + 1) == 1) ||
	(line[*i] == '<' && empty_line(&line, *i + 1) == 1) ||
	(line[*i] == '<' && line[*i + 1] == '<'
	&& empty_line(&line, *i + 2) == 1) ||
	(line[*i] == '>' && empty_line(&line, *i + 1) == 1) ||
	(line[*i] == '>' && line[*i + 1] == '>' && empty_line(&line, *i + 2) == 1)))
		return (error_msg(1, line[*i]));
	if (quote == 0)
		(*i)--;
	return (0);
}

int		save_value(char **tmp, char *env)
{
	int	count;
	int	i;
	int	index;

	i = 0;
	while (env[i] != '=')
		i++;
	index = i + 1;
	count = 0;
	while (env[++i] != '\0')
		count++;
	*tmp = ft_substr(env, index, count);
	if (*tmp == NULL)
		return (-1);
	return (0);
}

char	*add_str(char *str, char *line, int pos)
{
	char	*tmp;
	int		size_line;
	int		size_str;
	int		i;

	size_line = ft_strlen(line) - pos;
	size_str = ft_strlen(str);
	tmp = malloc(sizeof(char) * (size_str + size_line + 1));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
		tmp[i] = str[i];
	while (i < (size_str + size_line))
		tmp[i++] = line[pos++];
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

int		swap_var_env(char **tmp, char **line, int pos, int size_var)
{
	int		size_tmp;
	char	*str;
	char	*tmp2;

	size_tmp = ft_strlen(*tmp);
	tmp2 = ft_substr(*line, 0, pos);
	if (tmp2 == NULL)
		return (-1);
	str = ft_strjoin(tmp2, *tmp);
	free(tmp2);
	free(*tmp);
	if (str == NULL)
		return (-1);
	str = add_str(str, *line, size_var + pos + 1);
	if (str == NULL)
		return (-1);
	*line = ft_free(*line);
	*line = str;
	return (0);
}

int		search_var_env(char **tmp, t_env *env, int size_tmp)
{
	int	i;

	i = 0;
	while (env->var_env[i] != NULL)
	{
		if (ft_my_strncmp(env->var_env[i], *tmp, size_tmp) == 0)
		{
			free(*tmp);
			*tmp = NULL;
			if (save_value(tmp, env->var_env[i]) == -1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}
