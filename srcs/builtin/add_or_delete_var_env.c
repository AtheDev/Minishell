/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_delete_var_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:03:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/20 15:20:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_var_env(char **var_env, int num, size_t size)
{
	char	**tmp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if ((tmp = malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (var_env[i] != NULL)
	{
		if (j == num)
			i++;
		if (var_env[i] == NULL)
			break ;
		tmp[j] = ft_strdup(var_env[i]);
		free(var_env[i]);
		if (tmp[j] == NULL)
			return (free_tab_string(tmp));
		j++;
		i++;
	}
	free(var_env[num]);
	tmp[j] = NULL;
	free(var_env);
	return (tmp);
}

int		process_delete_var_env(char *arg, t_env **env)
{
	int	i;

	i = 0;
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_my_strncmp((*env)->var_env[i], arg, ft_strlen(arg)) == 0)
		{
			(*env)->size--;
			(*env)->var_env = delete_var_env((*env)->var_env, i, (*env)->size);
			if ((*env)->var_env == NULL)
				return (-1);
			return (0);
		}
		i++;
	}
	return (0);
}

char	**add_var_env(char *arg, char **var_env, size_t size)
{
	char	**tmp;
	int		i;

	i = 0;
	if ((tmp = malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (i < ((int)size - 3))
	{
		tmp[i] = ft_strdup(var_env[i]);
		free(var_env[i]);
		if (tmp[i] == NULL)
			return (free_tab_string(tmp));
		i++;
	}
	if ((tmp[i] = ft_strdup(arg)) == NULL)
		return (free_tab_string(tmp));
	tmp[i + 1] = ft_strdup(var_env[i]);
	free(var_env[i]);
	if (tmp[i + 1] == NULL)
		return (free_tab_string(tmp));
	tmp[i + 2] = NULL;
	free(var_env);
	return (tmp);
}

int		process_add_var_env(char *arg, t_env **env)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] != '=')
		i++;
	if ((key = ft_substr(arg, 0, i)) == NULL)
		return (-1);
	i = 0;
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_my_strncmp((*env)->var_env[i], key, ft_strlen(key)) == 0)
		{
			free((*env)->var_env[i]);
			(*env)->var_env[i] = ft_strdup(arg);
			process_free(arg, key);
			if ((*env)->var_env[i] == NULL)
				return (-1);
			return (0);
		}
		i++;
	}
	if ((*env)->var_env[i] == NULL)
	{
		(*env)->size++;
		(*env)->var_env = add_var_env(arg, (*env)->var_env, (*env)->size);
		free(key);
		if ((*env)->var_env == NULL)
			return (-1);
	}
	return (0);
}
