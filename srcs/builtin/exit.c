/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:13:05 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/11 15:43:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value_arg(char *str)
{
	int	i;

	i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

unsigned long long	long_long_atoi(const char *str)
{
	int i;
	unsigned long long res;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}
int	ft_exit(char **arg, t_env **env, int fork)
{
	unsigned long long	val;

	if (fork == 0)
		printf("exit\n");
	val = 0;
	if (arg[1] != NULL)
	{
		val = long_long_atoi(arg[1]);
		if (check_value_arg(arg[1]) != 0 || (val > LL_LIMIT_MAX
		&& ft_strncmp(arg[1], LL_LIMIT_MIN, 21) != 0))
		{
			(*env)->exit = error_msg_with_string(4, arg[1]);
			(*env)->return_value = 2;
			return (1);
		}
		if (check_nb_arg(arg, 0) > 2)
			return ((*env)->return_value = error_msg_with_string(3, arg[0]));
		val = ft_atoi(arg[1]) % 256;
	}
	else if (arg[1] == NULL && (*env)->return_value == 127 && fork == 0)
		(*env)->return_value = 127;
	if (arg[1] != NULL || (arg[1] == NULL && fork == 1))
		(*env)->return_value = val;
	(*env)->exit = 1;
	return (0);
}
