/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:39:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/09 22:42:51 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*edit_arg_db_quotes(char *str, int *i, t_env *env)
{
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
			if (str != NULL && str[*i + 1] == '"')
			{
				(*i)++;
				break;
			}
		}
		else if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) == 1 ||
		str[*i + 1] == '_' || str[*i + 1] == '?'))
		{
			if (replace_variable(&str, i, env) == -1)
				return (NULL);
		}
		if (str == NULL)
			return (NULL);
		(*i)++;
	}
	str = delete_char(str, i);
	(*i)++;
	return (str);
}

char	*edit_arg_other(char *str, int *i, t_env *env, int *quote)
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
		else if (str[*i] == '$' && str[*i + 1] != '\0' && (ft_isalnum(str[*i + 1]) == 1 ||
		str[*i + 1] == '_' || str[*i + 1] == '?') /*str[*i + 1] != '\\' && str[*i + 1] != '$'*/)
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
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			if ((str = edit_arg_db_quotes(str, &i, env)) == NULL)
				return (NULL);
			if (str[0] == '\0' || str[i] == '\0')
				break;
			i--;
		}
		else if (str[i] == '\'')
		{
			if ((str = delete_char(str, &i)) == NULL)
				return (NULL);
			i++;
			while (str[i] != '\'')
				i++;
			if ((str = delete_char(str, &i)) == NULL)
				return (NULL);
			if (str[0] == '\0')
				break;
		}
		else
			if ((str = edit_arg_other(str, &i, env, quote)) == NULL)
				return (NULL);
		i++;
	}
	return (str);
}

/*int*/char		**dvlpmt_arg(char **arg, t_env *env)
{
	int	i;
	int	quote;

	i = -1;
	while (arg[++i] != NULL)
	{
		quote = 1;
		arg[i] = edit_arg(arg[i], env, 0, &quote);
		if (arg[i] == NULL)
		{
			/*return (*/error_msg(2, ' ')/*)*/;
			return (NULL);
		}
		if (arg[i][0] == '\0' && quote == 0)
		{
			//if ((arg = delete_arg(arg, i)) == NULL)
			if ((arg = delete_var_env(arg, i, check_nb_arg(arg, 0) - 1)) == NULL)
			{
				/*return (*/error_msg(2, ' ')/*)*/;
				return (NULL);
			}
			i--;
		}
	}
	return (arg);
}
