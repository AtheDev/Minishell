/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/17 11:28:12 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	*cmd_tmp;
	t_list_cmd *cmd;
	char	*line;
	int	ret;

	(void)argc;
	(void)argv;
	env = copy_env(envp, 1, 0);
	if (env.var_env == NULL)
		return (EXIT_FAILURE);
	line = NULL;
	cmd_tmp = NULL;
	cmd = NULL;
	prompt();
	ret = get_next_line(0, &line);
	if (ret == -1)
		return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
	if (ret > 0)
		ret = analysis_input(&line, -1, &cmd_tmp);
	free(line);
	//print_lst(cmd_tmp);
	if (ret == -1 )
		return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
	if (ret == -1)
		return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
	if (ret == 0)
		ret = save_cmd(&cmd, cmd_tmp);
	if (ret == -1)
		return (process_end(&env, EXIT_FAILURE, cmd_tmp, cmd));
	//print_struct_complete(&cmd);	
	return (process_end(&env, EXIT_SUCCESS, cmd_tmp, cmd));
}
