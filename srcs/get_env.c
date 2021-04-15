/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:26:13 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/15 22:13:07 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr_rev(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*get_value_var_env(char *str)
{
	char	*value;

	if (str == NULL)
		return (NULL);
	value = ft_strrchr_rev(str, '=') + 1;
	return (value);
}

char	*get_var_env(t_env **env, char *str)
{
	int	i;

	i = 0;
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_strncmp((*env)->var_env[i], str, ft_strlen(str)) == 0)
			return ((*env)->var_env[i]);
		i++;
	}
	return (NULL);
}
