/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:41:45 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/06 23:40:41 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*edit_arg_db_quotes(char *str, int *i, t_env *env, int *ret)
{
	int res;

	res = 0;
	str = delete_char(str, i);
	(*i)++;
	while (str[*i] != '"' || (str[*i] == '"' && is_escaped(str, *i - 1) == 1))
	{
		if (str[*i] == '\\' && str[*i + 1] == 'n')
			(*i)++;
		else if (str[*i] == '\\' && is_char(str[*i + 1], CHAR_PROTEC) == 0)
		{
			str = delete_char(str, i);
			(*i)++;
			if (str[*i + 1] == '"')
				break ;
		}
		else if (str[*i] == '$' && str[*i + 1] != '"' && str[*i + 1] != '$')
		{
			if ((res = replace_variable(&str, i, env, 1)) == -1)
				return (NULL);
			if (res == 2)
			{
				*ret = 1;
				return (NULL);
			}
		}
		if (str == NULL)
			return (NULL);
		(*i)++;
	}
//	if (str[*i + 1] == '"')
//		(*i)++;
	str = delete_char(str, i);
	(*i)++;
	//if ((*i) != -1)
	//	(*i)--;
	return (str);
}

char	*edit_arg_other(char *str, int *i, t_env *env)
{
	while (((str[*i] != '"' && str[*i] != '\'') ||
	(str[*i] == '"' && is_escaped(str, *i - 1) == 1) ||
	(str[*i] == '\'' && is_escaped(str, *i - 1) == 1)) && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\\')
		{
			if ((str = delete_char(str, i)) == NULL)
				return (NULL);
			(*i)++;
		}
		else if (str[*i] == '\\' && str[*i + 1] != '\\')
		{
			if ((str = delete_char(str, i)) == NULL)
				return (NULL);
			(*i)++;
		}
		else if (str[*i] == '$' && str[*i + 1] != '\0' && str[*i + 1] != '\\' && str[*i + 1] != '$')
		{
			if (replace_variable(&str, i, env, 0) == -1)
				return (NULL);
		}
		(*i)++;
	}
	(*i)--;
	return (str);
}

char	*edit_arg(char *str, t_env *env, int *ret)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			if (ft_strlen(str) == 2 && i == 0)
			{
				*ret = 1;
				str = ft_free(str);
				break;
			}
			str = edit_arg_db_quotes(str, &i, env, ret);
			if (*ret == 1 || str[0] == '\0' || str[i] == '\0')
				break;
			i--;
		}
		else if (str[i] == '\'')
		{
			if (ft_strlen(str) == 2 && i == 0)
			{
				*ret = 1;
				str = ft_free(str);
				break;
			}	
			if ((str = delete_char(str, &i)) == NULL)
				return (NULL);
			i++;
			while (str[i] != '\'')
				i++;
			str = delete_char(str, &i);
		}
		else
			str = edit_arg_other(str, &i, env);
		if (str == NULL)
			return (NULL);
		i++;
		if (str[i] == '\0' || str[i + 1] == '\0')
			break;
	}
	return (str);
}

int		dvlpmt_arg(char **arg, t_env *env, t_list_cmd **cmd)
{
	int	i;
	int	ret;

	i = -1;
	(*cmd)->nb_arg = check_nb_arg(arg, 0);
	while (arg[++i] != NULL)
	{
		ret = 0;
		arg[i] = edit_arg(arg[i], env, &ret);
		if (arg[i] == NULL && ret == 0)
			return (error_msg(2, ' '));
		if (i == 0)
		{
			if (arg[i] == NULL && ret == 1)
			{
				if ((arg[i] = malloc(sizeof(char) * 1)) == NULL)
					return (error_msg(2, ' '));
				arg[i][0] = '\0';
			}
		}
	}
	return (0);
}
