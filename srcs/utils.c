/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:36:48 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 15:52:13 by adupuy           ###   ########.fr       */
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
	size = (int)ft_strlen(s);
	if (size < start)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
	}
	else
	{
		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		str[i] = '\0';
	}
	free(s);
	return (str);
}

char	*process_free(char *s1, char *s2)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (NULL);
}
