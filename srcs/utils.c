/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:36:48 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/28 15:34:09 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_substr(char *s, int start, int len, int i)
{
	char	*str;
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
		while (++i < len)
			str[i] = s[start + i];
		str[i] = '\0';
	}
	free(s);
	s = NULL;
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

int		is_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (0);
		i++;
	}
	return (1);
}

int		ft_my_strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (((unsigned char)*s1) - ((unsigned char)*s2));
	if ((*s1) != '=')
		return (1);
	return (0);
}

char	**free_tab_string(char **tab_string)
{
	int	i;

	i = -1;
	while (tab_string[++i] != NULL)
	{
		free(tab_string[i]);
		tab_string[i] = NULL;
	}
	free(tab_string);
	tab_string = NULL;
	return (NULL);
}
