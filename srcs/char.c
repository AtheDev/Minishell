/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 00:47:49 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/27 16:58:34 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *line, int i)
{
	int	nb_backslash;

	nb_backslash = 0;
	if (i == -1)
		return (0);
	if (line[i] != '\\')
		return (0);
	if (line[i] == '\\' && i == 0)
		return (1);
	while (line[i] == '\\' && i-- >= 0)
		nb_backslash++;
	if (nb_backslash % 2 == 0)
		return (0);
	return (1);
}

int		before_char(char *line, int i, char c)
{
	if (i == 0 && ((c == ';' && line[i + 1] == c) || (c == '|' && line[i + 1] == c)))
		return (error_msg(5, c));
	if (i == 0 && (c == ';' || c == '|'))
		return (error_msg(1, c));
	while (--i >= 0)
	{
		if (line[i] != ' ' &&
		((line[i] == ';' && is_escaped(line, i - 1) == 0)
		|| (line[i] == '|' && is_escaped(line, i - 1) == 0)
		|| (line[i] == '<' && is_escaped(line, i - 1) == 0)
		|| (line[i] == '>' && is_escaped(line, i - 1) == 0)
		|| (line[i] == '`' && is_escaped(line, i - 1) == 0)
		|| (line[i] == '&' && is_escaped(line, i - 1) == 0)))
		{
			if (c == ';' || c == '|')
				return (error_msg(1, c));
			return (error_msg(1, line[i]));
		}
		else if (line[i] != ' ' &&
		((line[i] == '(' && is_escaped(line, i - 1) == 0)
		|| (line[i] == ')' && is_escaped(line, i - 1) == 0)))
			return (error_msg(1, line[i]));
		if (line[i] != ' ')
			return (0);
	}
	return (1);
}

char	*add_char(char *line, int *pos, char c, int space)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, 0, *pos);
	tmp2 = ft_substr(line, *pos + space, (ft_strlen(line) - (*pos + space)));
	free(line);
	if (tmp == NULL || tmp2 == NULL)
		return (process_free(tmp, tmp2));
	tmp = strjoin_char(tmp, c, space, 0);
	if (tmp == NULL)
		return (process_free(tmp, tmp2));
	line = ft_strjoin(tmp, tmp2);
	process_free(tmp, tmp2);
	if (line == NULL)
		return (process_free(tmp, tmp2));
	*pos += 2;
	return (line);
}

char	*delete_char(char *line, int *pos)
{
	int		size;
	char	*tmp;
	char	*tmp2;

	size = ft_strlen(line);
	tmp = ft_substr(line, 0, *pos);
	tmp2 = ft_substr(line, *pos + 1, size - *pos - 1);
	free(line);
	if (tmp == NULL || tmp2 == NULL)
		return (process_free(tmp, tmp2));
	line = ft_strjoin(tmp, tmp2);
	process_free(tmp, tmp2);
	if (line == NULL)
		return (process_free(tmp, tmp2));
	*pos = *pos - 1;
	return (line);
}

char	*strjoin_char(char *s1, char c, int space, int j)
{
	char	*str;
	int		i;
	int		size;

	i = j;
	if (!s1 || !c)
		return (NULL);
	size = 2;
	space == 1 ? size += 2 : 2;
	space == 2 ? size += 3 : 2;
	str = malloc(sizeof(char) * (ft_strlen(s1) + size));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	if (space > 0)
		str[j++] = ' ';
	str[j++] = c;
	if (space == 2)
		str[j++] = c;
	if (space > 0)
		str[j++] = ' ';
	str[j] = '\0';
	free(s1);
	return (str);
}
