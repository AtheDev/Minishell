/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:59:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/13 14:26:51 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_next(int *num, t_list_cmd **cmd, int i)
{
	int	fd;

	fd = 0;
	if (ft_strncmp((*cmd)->arg_cmd[i - 1], "<", 2) == 0)
	{
		if (ft_strncmp((*cmd)->arg_cmd[i], ">", 2) == 0 ||
		ft_strncmp((*cmd)->arg_cmd[i], ">>", 3) == 0)
		{
			*num = 1;
			(*cmd)->nb_redir--;
			return (0);
		}
		else
			fd = open((*cmd)->arg_cmd[i], O_RDONLY);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[i - 1], ">", 2) == 0)
		fd = open((*cmd)->arg_cmd[i], O_WRONLY | O_CREAT |
		O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	else if (ft_strncmp((*cmd)->arg_cmd[i - 1], ">>", 3) == 0)
		fd = open((*cmd)->arg_cmd[i], O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	return (fd);
}

int	open_file(t_list_cmd **cmd, int i, int *index, char **tmp)
{
	int	fd;
	int	num;

	fd = 0;
	num = 0;
	errno = 0;
	if ((*cmd)->arg_cmd[i] == NULL || (*cmd)->arg_cmd[i][0] == '\0')
		return (error_redirect(*tmp, cmd, "redirection ambiguë", 0));
	fd = open_file_next(&num, cmd, i);
	if (fd == -1)
	{
		if (*tmp != NULL)
			*tmp = ft_free(*tmp);
		return (error_redirect((*cmd)->arg_cmd[i], cmd, strerror(errno), 1));
	}
	if (num == 1)
		return (0);
	if (ft_strncmp((*cmd)->arg_cmd[i - 1], "<", 2) == 0)
		(*cmd)->fd[0] = fd;
	else
		(*cmd)->fd[1] = fd;
	(*cmd)->fd_redir[(*index)++] = fd;
	if (*tmp != NULL)
		*tmp = ft_free(*tmp);
	return (0);
}

int	loop_redir(t_list_cmd **cmd, int *i, int *quote, char **tmp)
{
	while ((ft_strncmp((*cmd)->arg_cmd[*i], ">", 2) != 0 &&
	ft_strncmp((*cmd)->arg_cmd[*i], "<", 2) != 0 &&
	ft_strncmp((*cmd)->arg_cmd[*i], ">>", 3) != 0) &&
	(*cmd)->arg_cmd[*i] != NULL)
	{
		(*i)++;
		if (((*cmd)->arg_cmd[*i] = edit_arg((*cmd)->arg_cmd[*i],
		&g_sig.env, -1, quote)) == NULL)
			return (error_msg(2, ' '));
	}
	if ((*cmd)->arg_cmd[*i] != NULL)
	{
		(*i)++;
		*tmp = ft_strdup((*cmd)->arg_cmd[*i]);
		if (*tmp == NULL || ((*cmd)->arg_cmd[*i] =
		edit_arg((*cmd)->arg_cmd[*i], &g_sig.env, -1, quote)) == NULL)
		{
			if (*tmp != NULL)
				*tmp = ft_free(*tmp);
			return (error_msg(2, ' '));
		}
	}
	return (0);
}

int	process_redir_cmd(t_list_cmd **cmd, int nb_redir, int i, int index)
{
	int		nb;
	int		ret;
	int		quote;
	char	*tmp;

	tmp = NULL;
	if (init_redir(&ret, &quote, cmd, &nb) == -1)
		return (-1);
	while (nb_redir > 0)
	{
		if (((*cmd)->arg_cmd[i] = edit_arg((*cmd)->arg_cmd[i],
		&g_sig.env, -1, &quote)) == NULL)
			return (error_msg(2, ' '));
		if (loop_redir(cmd, &i, &quote, &tmp) != 0)
			return (-1);
		if ((ret = open_file(cmd, i, &index, &tmp)) == 1)
		{
			(*cmd)->nb_redir = (*cmd)->nb_redir - nb_redir;
			return (1);
		}
		i++;
		nb_redir--;
	}
	return (clean_redir(cmd, nb));
}
