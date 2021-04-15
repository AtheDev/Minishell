/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:36:48 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/15 23:38:38 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	if ((size = ft_strlen(s)) < start)
	{
		if (!(str = malloc(sizeof(char))))
			return (NULL);
		str[0] = '\0';
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (len + 1))))
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		str[i] = '\0';
	}
	free(s);
	return (str);
}
