/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:03:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 18:50:42 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	*cmd_tmp;
	char	*line;
	int	ret;

	(void)argc;
	(void)argv;
	env = copy_env(envp, 1, 0);
	if (env.var_env == NULL)
		return (EXIT_FAILURE);
	line = NULL;
	cmd_tmp = NULL;
	prompt();
	ret = get_next_line(0, &line);
	if (ret == -1)
		return (process_end(&env, EXIT_FAILURE, cmd_tmp));
	if (ret > 0)
		ret = analysis_input(&line, -1, &cmd_tmp);
	if (ret == -1 )
		return (process_end(&env, EXIT_FAILURE, cmd_tmp));
	if (ret == 0)
		
	print_lst(cmd_tmp);
	free(line);	
	return (process_end(&env, EXIT_SUCCESS, cmd_tmp));
}
