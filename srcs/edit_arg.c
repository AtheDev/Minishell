/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:39:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 19:11:44 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*edit_arg_other(char *str, int *i, t_env *env, int *quote)
{
	while (((str[*i] != '"' && str[*i] != '\'') ||
	(str[*i] == '"' && is_escaped(str, *i - 1) == 1) ||
	(str[*i] == '\'' && is_escaped(str, *i - 1) == 1)) && str[*i] != '\0')
	{
		if (str[*i] == '\\')
		{
			if ((str = delete_char(str, i)) == NULL)
				return (NULL);
			(*i)++;
		}
		else if (str[*i] == '$' && str[*i + 1] != '\0' &&
		(ft_isalnum(str[*i + 1]) == 1 || str[*i + 1] == '_' ||
		str[*i + 1] == '?'))
		{
			if (replace_variable(&str, i, env) == -1)
				return (NULL);
			if (str[0] == '\0')
				*quote = 0;
		}
		(*i)++;
	}
	(*i)--;
	return (str);
}

char	*edit_arg(char *str, t_env *env, int i, int *quote)
{
	int	ret;

	ret = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '"' && ((str = edit_arg_db_quotes(str, &i, env))))
		{
			if (str == NULL || str[0] == '\0' || str[i] == '\0')
				break ;
			i--;
		}
		else if (str[i] == '\'' && (ret = edit_arg_sp_quote(&i, &str)) <= 0)
		{
			if (ret == -1)
				return (NULL);
			break ;
		}
		else
		{
			if ((str = edit_arg_other(str, &i, env, quote)) == NULL)
				return (NULL);
		}
	}
	return (str);
}

char	**dvlpmt_arg(char **arg, t_env *env)
{
	int	i;
	int	quote;

	i = -1;
	while (arg[++i] != NULL)
	{
		quote = 1;
		arg[i] = edit_arg(arg[i], env, -1, &quote);
		if (arg[i] == NULL)
		{
			error_msg(2, ' ');
			return (NULL);
		}
		if (arg[i][0] == '\0' && quote == 0)
		{
			if ((arg =
			delete_var_env(arg, i, check_nb_arg(arg, 0) - 1)) == NULL)
			{
				error_msg(2, ' ');
				return (NULL);
			}
			i--;
		}
	}
	return (arg);
}
