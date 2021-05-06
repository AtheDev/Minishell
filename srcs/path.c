/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:20:22 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/03 11:03:45 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_in_var_env_path(t_env **env, char **arg)
{
	char	**path;
	DIR	*rep;
	struct dirent *file;
	int	i;
	char	*tmp;

	if ((tmp = get_value_var_env(get_var_env(env, "PATH"))) == NULL)
	{
		error_msg_with_string(9, arg[0]);
		return (2);
	}
	if ((path = ft_split(tmp, ':')) == NULL)
		return (error_msg(2, ' '));
	i = -1;
	tmp = NULL;
	while (path[++i] != NULL)
	{
		if ((rep = opendir(path[i])) == NULL)
			continue;
		while (((file = readdir(rep))) != NULL)
		{
			if (ft_strncmp(file->d_name, arg[0], ft_strlen(arg[0]) + 1) == 0)
			{
				if ((tmp = ft_strjoin("/", *arg)) == NULL)
				{
					path = free_tab_string(path);
					closedir(rep);
					return (error_msg(2, ' '));
				}
				*arg = ft_free(*arg);
				*arg = ft_strjoin(path[i], tmp);
				tmp = ft_free(tmp);
				path = free_tab_string(path);
				closedir(rep);
				if (*arg == NULL)
					return (error_msg(2, ' '));
				return (0);		
			}
		}
		closedir(rep);	
	}
	path = free_tab_string(path);
	return (1);
}

int	check_with_stat(t_env **env, char *arg)
{
	struct stat	file_status;

	errno = 0;
	if (stat(arg, &file_status) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (-1);
	}
	if (S_ISDIR(file_status.st_mode) != 0)
	{
		error_stat_and_path(1, arg);
		(*env)->return_value = 126;
		return (1);
	}
	else if ((file_status.st_mode & S_IXUSR) == 0)
	{
		error_stat_and_path(2, arg);
		(*env)->return_value = 126;
		return (1);
	}
	return (0);
}

int	search_path(char **arg, t_env **env, int ret)
{
	if (arg[0][0] == '\0')
	{
		error_stat_and_path(3, " ");
		return ((*env)->return_value = 127);
	}
	if (ft_strchr(*arg, '/') == NULL)
	{
		ret = search_in_var_env_path(env, arg);
		if (ret == 1 || ret == 2)
		{
			if (ret == 1)
				error_stat_and_path(3, *arg);
			(*env)->return_value = 127;
			return (1);
		}
		else if (ret == -1)
		{
			(*env)->return_value = 1;
			return (-1);
		}
		else if (ret == 0)
			return (0);
	}

	if (ft_strchr(*arg, '/') != NULL)
	{
		ret = check_with_stat(env, *arg);
		if (ret == 1)
			return (1);
		else if (ret == -1)
		{
			(*env)->return_value = 127;
			return (-1);
		}
		else if (ret == 0)
			return (0);

	}
	return (0);
}
