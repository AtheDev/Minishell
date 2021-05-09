/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:59:17 by adupuy            #+#    #+#             */
/*   Updated: 2021/05/07 18:44:08 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_redir_and_file(char **cmd, int nb, int nb2/*, int nb_arg*/)
{
	char	**new;
	int		i;
	int		j;

//	new = malloc(sizeof(char *) * (nb_arg - (2 * nb2) + (nb - nb2) + 1));
	new = malloc(sizeof(char *) * (check_nb_arg(cmd, 0) - (2 * nb2) + (nb - nb2) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (cmd[i] != NULL/*i < nb_arg*/)
	{
		if (/*cmd[i] != NULL && */ft_strncmp(cmd[i], "<", 2) == 0 && 
		(ft_strncmp(cmd[i + 1], ">", 2) == 0 ||
		ft_strncmp(cmd[i + 1], ">>", 3) == 0))
			i = i + 1;
		else if (/*cmd[i] != NULL && */(ft_strncmp(cmd[i], ">", 2) == 0
		|| ft_strncmp(cmd[i], "<", 2) == 0 || ft_strncmp(cmd[i], ">>", 3) == 0))
			i = i + 2;
		else if (cmd[i] != NULL)
		{
			new[++j] = ft_strdup(cmd[i]);
			if (new[j] == NULL)
				return (new = ft_free_tab(new, i));
			i++;
		}
		//else if (cmd[i] == NULL)
		//	i++;
	}
	new[++j] = NULL;
	ft_free_tab(cmd, check_nb_arg(cmd, 0)/*nb_arg*/);
	return (new);
}

int		close_redir(t_list_cmd **cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->nb_redir)
	{
		if (close((*cmd)->fd_redir[i]) == -1)
			return (1);
		i++;
	}
	free((*cmd)->fd_redir);
	return (0);
}

int		open_file(t_list_cmd **cmd, int i, int *index)
{
	int	fd;
	int	num;

	fd = 0;
	num = 0;
	errno = 0;
	if (ft_strncmp((*cmd)->arg_cmd[i], "<", 2) == 0)
	{
		if (ft_strncmp((*cmd)->arg_cmd[i + 1], ">", 2) == 0 ||
		ft_strncmp((*cmd)->arg_cmd[i + 1], ">>", 3) == 0)
		{
			num = 1;
			(*cmd)->nb_redir--;
		}
		else
			fd = open((*cmd)->arg_cmd[i + 1], O_RDONLY);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[i], ">", 2) == 0)
		fd = open((*cmd)->arg_cmd[i + 1], O_WRONLY | O_CREAT |
		O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	else if (ft_strncmp((*cmd)->arg_cmd[i], ">>", 3) == 0)
		fd = open((*cmd)->arg_cmd[i + 1], O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	if (num == 0)
	{
		if (ft_strncmp((*cmd)->arg_cmd[i], "<", 2) == 0)
			(*cmd)->fd[0] = fd;
		else
			(*cmd)->fd[1] = fd;
		(*cmd)->fd_redir[(*index)++] = fd;
	}
	return (0);
}

int		process_redir_cmd(t_list_cmd **cmd, int nb_redir)
{
	int	i;
	int	nb;
	int	index;
	int	ret;

	i = 0;
	index = 0;
	ret = 0;
	nb = nb_redir;
	(*cmd)->fd_redir = malloc(sizeof(int) * (*cmd)->nb_redir);
	if ((*cmd)->fd_redir == NULL)
		return (error_msg(2, ' '));
	while (nb_redir > 0)
	{
		while ((ft_strncmp((*cmd)->arg_cmd[i], ">", 2) != 0 &&
		ft_strncmp((*cmd)->arg_cmd[i], "<", 2) != 0 &&
		ft_strncmp((*cmd)->arg_cmd[i], ">>", 3) != 0) &&
		(*cmd)->arg_cmd[i] != NULL)
			i++;
		if ((ret = open_file(cmd, i, &index)) == 1)
			return (1);
		i++;
		nb_redir--;
	}
	if (((*cmd)->arg_cmd = delete_redir_and_file((*cmd)->arg_cmd, nb, (*cmd)->nb_redir/*, (*cmd)->nb_arg*/)) == NULL)
		return (error_msg(2, ' '));
//	(*cmd)->nb_arg = check_nb_arg((*cmd)->arg_cmd, 0);
	return (0);
}
