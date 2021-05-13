/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 10:08:32 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/12 09:26:24 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		moving_forward(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' || (str[i] == '"' && is_escaped(str, i - 1) == 1))
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	else if (ft_isredir(str, i) == 2)
		i++;
	else if (ft_isredir(str, i) == 1)
		return (i);
	else
	{
		i++;
		while ((str[i] != ' ' || (str[i] == ' ' && is_escaped(str, i - 1) == 1))
		&& (db_quotes(str, i) == 1) && (sp_quote(str, i) == 1) && str[i])
			i++;
		i--;
	}
	return (i);
}

int		count_word_next(int i, int *j, int k, int num)
{
	*j = i - k;
	if (num == 1)
		return (*j);
	return (-1);
}

int		count_word(char *str, int i, int count, int num)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1 && is_escaped(str, i - 1) == 0)
		{
			if (count_word_next(i, &j, k, num) != -1)
				return (j);
			count++;
		}
		else
			i = moving_forward(str, i);
		i++;
		if ((str[i] == '\0' && ft_isspace(str[i - 1]) == 1 && is_escaped(
		str, i - 2) == 1) || (str[i] == '\0' && ft_isspace(str[i - 1]) == 0))
		{
			if (count_word_next(i, &j, k, num) != -1)
				return (j);
			count += 2;
		}
	}
	return (count);
}

char	*new_str(char *str, int i, int size)
{
	char	*tmp;
	int		count;

	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	count = -1;
	while (++count < size)
	{
		tmp[count] = str[i];
		i++;
	}
	tmp[count] = '\0';
	return (tmp);
}

char	**my_split(char *str, int j)
{
	int		nb_word;
	int		nb_char;
	char	**split;
	int		i;

	nb_word = count_word(str, 0, 0, 0);
	split = malloc(sizeof(char *) * nb_word);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (++j < (nb_word - 1))
	{
		nb_char = count_word(str, i, 1, 1);
		split[j] = new_str(str, i, nb_char);
		if (split[j] == NULL)
		{
			split = ft_free_tab(split, j);
			return (split);
		}
		i = i + nb_char + 1;
	}
	split[j] = NULL;
	return (split);
}
