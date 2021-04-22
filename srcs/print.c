/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:41:32 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/20 14:04:12 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		ft_putstr_fd("1 => lst = ", 2);
		ft_putstr_fd(lst->content, 2);
		ft_putstr_fd("\n", 2);
		lst = lst->next;
	}
	printf("2 => lst = %s\n", lst->content);
	lst = tmp;
}

void	print_arg_cmd(char **arg_cmd)
{
	int	i;

	i = -1;
	while (arg_cmd[++i] != NULL)
	{
		ft_putstr_fd("arg_cmd[", 2);
		ft_putnbr_fd(i, 2);
		ft_putstr_fd("] = ", 2);
		ft_putstr_fd(arg_cmd[i], 2);
		ft_putstr_fd("\n", 2);
	}
	ft_putstr_fd("arg_cmd[", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("] = ", 2);
	ft_putstr_fd(arg_cmd[i], 2);
	ft_putstr_fd("\n", 2);
}

void	print_struct(t_list_cmd *lst)
{
	t_list_cmd	*tmp;

	tmp = lst;
	ft_putstr_fd("\nlst->cmd = ", 2);
	ft_putstr_fd(lst->cmd, 2);
	ft_putstr_fd("\nlst->semicolon = ", 2);
	ft_putnbr_fd(lst->semicolon, 2);
	ft_putstr_fd("\nlst->pipe = ", 2);
	ft_putnbr_fd(lst->pipe, 2);
	ft_putstr_fd("\nlst->nb_redir = ", 2);
	ft_putnbr_fd(lst->nb_redir, 2);
	ft_putstr_fd("\n", 2);
	print_arg_cmd(lst->arg_cmd);
}

void	print_struct_complete(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;

	tmp = *cmd;
	ft_putstr_fd("\033[31m***** PRINT_STRUCT_COMPLETE *****\033[37m\n", 2);
	while ((*cmd)->next_cmd != NULL)
	{
		print_struct(*cmd);
		(*cmd) = (*cmd)->next_cmd;
	}
	print_struct(*cmd);
	(*cmd) = tmp;
	ft_putstr_fd("\033[31m***** FIN *****\033[37m\n", 2);
}
