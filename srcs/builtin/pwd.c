/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:16:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/19 20:49:34 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **arg, t_env *env)
{
	char	*pwd;

	(void)arg;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	env->return_value = 0;
	return (0);
}
