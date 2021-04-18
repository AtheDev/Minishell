/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:48:30 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/18 11:27:55 by adupuy           ###   ########.fr       */
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

# define CHAR_PROTEC "\"\\`$\\n"

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
int	parsing_input(char **line, int *i, t_list **cmd, int *start_cmd);
int	analysis_redir(char **line, int *i);
int	analysis_sep(char **line, int *i, int *start_cmd, t_list **cmd);
int	analysis_quote(char *line, int *i);
/*
	***** LINE *****
*/
char	*clean_line(char *str);
int	empty_line(char **line, int i);
int	delete_two_char(char **line, int *i);

/*
	***** QUOTE *****
*/
int	check_double_quotes(char *line, int *i);
int	check_simple_quote(char *line, int *i);

/*
	***** CHAR *****
*/
int	is_escaped(char *line, int i);
char	*add_char(char *line, int *pos, char c, int space);
char	*delete_char(char *line, int *pos);
char	*strjoin_char(char *s1, char c, int space, int j);
int	before_char(char *line, int i, char c);

/*
	***** CHAR ESCAPED *****
*/
int	db_quotes(char *str, int i);
int	sp_quote(char *str, int i);
int	dollar(char *str, int i);
int	sep_cmd(char *str, int i);
int	redir(char *str, int i);

/*
	***** DOLLAR *****
*/
int	replace_variable(char **line, int *i, t_env *env);
int	check_dollar(char **line, int index, int *i, t_env *env);
int	recover_variable(char **line, int *i, int *size_var, int *index, t_env *env);
int	variable_not_found(char **line, char *tmp, int pos_dollar, int size_var);
int	var_is_digit_or_interrogation_point(char **line, int *i, char *tmp, t_env *env);

/*
	***** DOLLAR UTILS *****
*/
int	search_var_env(char **tmp, t_env *env, int size_tmp);
int	swap_var_env(char **tmp, char **line, int pos, int size_var);
char	*add_str(char *str, char *line, int pos);
int	save_value(char **tmp, char *env);
int	check_variable(char *line, int *i, int quote);

/*
	***** WORD *****
*/
int	check_word(char *line, int i, int quote);
int	delete_space(char **cmd, int i);

/*
	***** REDIR *****
*/
int	check_redir(char *line, int i);
int	count_redir(char **arg);

/*
	***** CMD *****
*/
int	save_cmd_tmp(t_list **cmd, char *line, int start_cmd, int end_cmd);
int	save_cmd(t_list_cmd **cmd, t_list *cmd_tmp);
void	ft_lstadd_back_cmd(t_list_cmd **cmd, t_list_cmd *new);
t_list_cmd	*ft_lstnew_cmd(char *content);
void	complete_struct(char *str, t_list_cmd **new);

/*
	***** SPLIT CMD *****
*/
char	**my_split(char *str, int j);
char	*new_str(char *str, int i, int size);
int		count_word(char *str, int i, int count, int num);
int		moving_forward(char *str, int i);
int		ft_isredir(char *str, int i);

/*
	***** PROCESS SHELL *****
*/
int	process_shell(t_env *env, t_list_cmd **cmd);

/*
	***** EDIT ARG *****
*/
int		dvlpmt_arg(char **arg, t_env *env);
char	*edit_arg(char *str, t_env *env);
char	*edit_arg_other(char *str, int *i, t_env *env);
char	*edit_arg_db_quotes(char *str, int *i, t_env *env);

/*
	***** UTILS *****
*/
char	*my_substr(char *s, int start, int len);
char	*process_free(char *s1, char *s2);
int	is_char(char c, char *str);
int	ft_my_strncmp(char *s1, char *s2, size_t n);

/*
	***** PROCESS END *****
*/
int	process_end(t_env *env, int end, t_list *cmd_tmp, t_list_cmd *tmp);
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

/*
	***** PRINT *****
*/
void	print_lst(t_list *lst);
void	print_arg_cmd(char **arg_cmd);
void	print_struct(t_list_cmd *lst);
void	print_struct_complete(t_list_cmd **cmd);

#endif
