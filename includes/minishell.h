/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:48:30 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/16 01:07:10 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BUFFER_SIZE 1024

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

typedef struct	s_env
{
	char	**var_env;
	char	*tilde;
	int	return_value;
	int	exit;
	size_t	size;
	int	fd[2];
}			t_env;

typedef struct	s_list_cmd
{
	char	*cmd;
	char	**arg_cmd;
	int	semicolon;
	int	pipe;
	int	nb_redir;
	int	*fd_redir;
	int	fd[2];
	struct	s_list_cmd	*next_cmd;
	
}			t_list_cmd;

/*
	***** ENV *****
*/
void	clear_env(t_env *env);
t_env	copy_env(char **env, int init, size_t i);
char	*inc_shlvl(char *str);
void	add_elt_env(t_env *env);
void	clear_env(t_env *env);

/*
	***** GET ENV *****
*/
char	*get_value_var_env(char *str);
char	*get_var_env(t_env **env, char *str);
char	*inc_shlvl(char *str);

/*
	***** GNL *****
*/
int	get_next_line(int fd, char **line);
int	ft_is_end_line(char *str);
char	*ft_my_strjoin(char *s1, char *s2);

/*
	***** ANALYSIS LINE *****
*/
int	analysis_input(char **line, int i, t_list **cmd);

/*
	***** LINE *****
*/
char	*clean_line(char *str);
int	empty_line(char **line, int i);

/*
	***** QUOTE *****
*/
int	check_double_quotes(char *line, int *i);
int	check_simple_quote(char *line, int *i);

/*
	***** CHAR *****
*/
int	is_escaped(char *line, int i);

/*
	***** CHAR ESCAPED *****
*/
int	db_quotes(char *str, int i);
int	sp_quote(char *str, int i);
int	dollar(char *str, int i);
int	sep_cmd(char *str, int i);
int	redir(char *str, int i);

/*
	***** UTILS *****
*/
char	*my_substr(char *s, int start, int len);

/*
	***** PROCESS END *****
*/
int	process_end(t_env *env, int end, t_list *cmd_tmp);
void	clear_cmd(t_list_cmd *cmd);
void	clear_cmd_tmp(t_list *cmd);

/*
	***** PROMPT *****
*/
int	prompt(void);

/*
	***** ERROR *****
*/
int	error_msg(int num, char c);
int	error_msg_with_string(int num, char *str);

#endif
