/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:41:32 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 17:41:43 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		printf("1 => lst = %s\n", lst->content);
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
	//	printf("arg_cmd[%d] = %s\n", i, arg_cmd[i]);
	}
	ft_putstr_fd("arg_cmd[", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("] = ", 2);
	ft_putstr_fd(arg_cmd[i], 2);
	ft_putstr_fd("\n", 2);
//	printf("arg_cmd[%d] = %s\n", i, arg_cmd[i]);
}

void	print_struct(t_list_cmd *lst)
{
	t_list_cmd	*tmp;

	tmp = lst;
	printf("lst->cmd = %s\n", lst->cmd);
	printf("lst->semicolon = %d\n", lst->semicolon);
	printf("lst->pipe = %d\n", lst->pipe);
	printf("lst->nb_redir = %d\n", lst->nb_redir);
	print_arg_cmd(lst->arg_cmd);
}

void	print_struct_complete(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;

	tmp = *cmd;
	while ((*cmd)->next_cmd != NULL)
	{
		print_struct(*cmd);
		(*cmd) = (*cmd)->next_cmd;
	}
	print_struct(*cmd);
	(*cmd) = tmp;
}

