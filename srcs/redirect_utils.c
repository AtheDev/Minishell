/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:21:38 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 14:26:15 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_redir_and_file(char **cmd, int size, int i, int j)
{
	char	**new;

	if ((new = malloc(sizeof(char *) * (size))) == NULL)
		return (NULL);
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "<", 2) == 0 &&
		(ft_strncmp(cmd[i + 1], ">", 2) == 0 ||
		ft_strncmp(cmd[i + 1], ">>", 3) == 0))
			i = i + 1;
		else if ((ft_strncmp(cmd[i], ">", 2) == 0 ||
		ft_strncmp(cmd[i], "<", 2) == 0 || ft_strncmp(cmd[i], ">>", 3) == 0))
			i = i + 2;
		else if (cmd[i] != NULL)
		{
			if ((new[++j] = ft_strdup(cmd[i])) == NULL)
				return (new = ft_free_tab(new, i));
			i++;
		}
	}
	new[++j] = NULL;
	ft_free_tab(cmd, check_nb_arg(cmd, 0));
	return (new);
}

int		error_redirect(char *tmp, t_list_cmd **cmd, char *error, int num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	if (num == 0)
		tmp = ft_free(tmp);
	g_sig.env.return_value = 1;
	(*cmd)->nb_redir--;
	return (1);
}

int		init_redir(int *ret, int *quote, t_list_cmd **cmd, int *nb)
{
	*ret = 0;
	*quote = 1;
	*nb = (*cmd)->nb_redir;
	if (((*cmd)->fd_redir = malloc(sizeof(int) * (*cmd)->nb_redir)) == NULL)
		return (error_msg(2, ' '));
	return (0);
}

int		clean_redir(t_list_cmd **cmd, int nb)
{
	if (((*cmd)->arg_cmd = delete_redir_and_file((*cmd)->arg_cmd,
	check_nb_arg((*cmd)->arg_cmd, 0) - (2 * (*cmd)->nb_redir) +
	(nb - (*cmd)->nb_redir) + 1, 0, -1)) == NULL)
		return (error_msg(2, ' '));
	return (0);
}
