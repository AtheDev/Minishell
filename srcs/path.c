/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:20:22 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/20 12:20:27 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_path(char **path, char **arg, char *bin, int ret)
{
	free_tab_string(path);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		free(arg[0]);
		arg[0] = bin;
	}
	return (ret);
}

int	search_path(char **arg, t_env **env, int i, int ret)
{
	char		**path;
	char		*bin;
	struct stat	file_status;

	if (arg[0][0] != '/' && ft_strncmp(arg[0], "./", 2) != 0
	&& ft_strncmp(arg[0], "../", 3) != 0)
	{
		path = ft_split(get_value_var_env(get_var_env(env, "PATH")), ':');
		if (path == NULL)
			return (-1);
		if ((arg[0] = ft_strjoin("/", arg[0])) == NULL)
			ret = -1;
		while (path[++i] != NULL && ret != -1)
		{
			bin = NULL;
			if ((bin = ft_strjoin(path[i], arg[0])) == NULL)
				ret = -1;
			if (stat(bin, &file_status) == 0)
				ret = 0;
			if (ret == -1 || ret == 0)
				break ;
			free(bin);
		}
		return (save_path(path, arg, bin, ret));
	}
	return (0);
}
