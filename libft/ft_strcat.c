/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:04:00 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/05 16:01:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;
	int k;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	if (dest[i] == '\0')
	{
		k = i;
		j = 0;
		while (src[j] != '\0')
		{
			++k;
			dest[k] = src[j];
			++j;
		}
		dest[k] = '\0';
	}
	return (dest);
}
