/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:48:30 by adupuy            #+#    #+#             */
/*   Updated: 2021/04/30 14:00:35 by adupuy           ###   ########.fr       */
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
# include <term.h>
# include <termios.h>
#include <sys/ioctl.h>

# define CHAR_PROTEC "\"\\`$\\n"
# define ULL_LIMIT_MAX 9223372036854775807
# define LL_LIMIT_MIN "-9223372036854775808"

int	g_sig;

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

typedef struct	s_termcap
{
	t_list	*history;
	int	pos_hist;
	int	tot_hist;
	int	rows_cursor;
	int	cols_cursor;
	int	rows_window;
	int	cols_window;
	int	pos_cursor;
	int	tot_cursor;
	int	size_prompt;
	char	*input;
	char	*input_tmp;
	char	*line;
	char	*del_line;
	char	*del_char;
	char	*move_left;
	char	*move_cursor;
}			t_termcap;

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
char	*get_key_var_env(char *str);
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
int	check_redir_out(char *line, int i);
int	count_redir(char **arg);
int	ft_isredir(char *str, int i);

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
int		count_word_next(int i, int *j, int k, int num);
int		moving_forward(char *str, int i);

/*
	***** PROCESS SHELL *****
*/
int	process_shell(t_env *env, t_list_cmd **cmd);

/*
	*******************
	***** BUILTIN *****
	*******************
*/
/*
	--> built.c
*/
int	is_builtin(t_env *env, t_list_cmd **cmd, int fork);

/*
	--> pwd.c
*/
int	ft_pwd(char **arg, t_env *env);

/*
	--> echo.c
*/
int	chech_option_echo(char *str, int i);
int	ft_echo(char **arg, int i, int n);

/*
	--> exit.c
*/
int	ft_exit(char **arg, t_env **env, int fork);
unsigned long long	long_long_atoi(const char *str);
int	check_value_arg(char *str);

/*
	--> env.c
*/
int	ft_env(char **arg, t_env *env);

/*
	--> export.c
*/
int	sort_env(t_env **env, int i);
int	ft_export(char **arg, t_env **env);

/*
	--> unset.c
*/
int	ft_unset(char **arg, t_env **env);
int	check_arg_var(char **arg, int cmd/*, t_env **env*/);

/*
	--> cd.c
*/
int	ft_cd(char **arg, t_env **env);

/*
	--> add_or_delete_var_env.c
*/
int	process_add_var_env(char *arg, t_env **env);
char	**add_var_env(char *arg, char **var_env, size_t size);
int	process_delete_var_env(char *arg, t_env **env);
char	**delete_var_env(char **var_env, int num, size_t size);

/*
	--> utils.c
*/
int	check_nb_arg(char **arg, int count);

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
char	*my_substr(char *s, int start, int len, int i);
char	*process_free(char *s1, char *s2);
int	is_char(char c, char *str);
int	ft_my_strncmp(char *s1, char *s2, size_t n);
char	**free_tab_string(char **tab_string);

/*
	***** PIPE *****
*/
int	count_pipes(t_list_cmd **cmd);
int	create_pipe(t_list_cmd *cmd1, t_list_cmd *cmd2);
void	redirect(int fd1, int fd2);
void	cancel_redirect(t_list_cmd *cmd, t_env *env, int fork);

/*
	***** REDIRECT *****
*/
int	process_redir_cmd(t_list_cmd **cmd, int nb_redir);
int	open_file(t_list_cmd **cmd, int i, int *index);
char	**delete_redir_and_file(char **cmd, int nb);
int	close_redir(t_list_cmd **cmd);

/*
	***** PATH *****
*/
int	search_path(char **arg, t_env **env, int i, int ret);

/*
	***** PROCESS END *****
*/
int	process_end_ko(t_env *env, t_termcap *t, t_list *cmd_tmp, t_list_cmd *tmp);
int	process_end_ok(t_list *cmd_tmp, t_list_cmd *tmp);
void	clear_cmd(t_list_cmd *cmd);
void	clear_cmd_tmp(t_list *cmd);
void	clear_termcap(t_termcap *t);

/*
	***** PROMPT *****
*/
int	prompt(t_termcap *t);

/*
	***** ERROR *****
*/
int	error_msg(int num, char c);
int	error_msg_with_string(int num, char *str);
int	putstr(char *str1, char *str2, char *str3);
int	error_term(int num, char *str);

/*
	***** PRINT *****
*/
void	print_lst(t_list *lst);
void	print_arg_cmd(char **arg_cmd);
void	print_struct(t_list_cmd *lst);
void	print_struct_complete(t_list_cmd **cmd);
void	print_hist(t_list **hist);

/*
	***** INIT *****
*/
void	init(t_list **cmd_tmp, t_list_cmd **cmd, t_termcap *t);
int	init2(t_env *env, char **envp, t_termcap *t);
void	init_read(t_termcap *t);

/*
	***** READ *****
*/
int	process_read(t_termcap *termcap, int ret, int new_line);
int	loop_read(t_termcap *t);

/*
	***** TERMCAP *****
*/
int	init_term(t_env *env);
int	swap_way_icanon_echo(int num);

/*
	***** CURSOR *****
*/
void	get_pos_cursor(t_termcap *t);
int	get_size_window(t_termcap *t);

/*
	***** HISTORY *****
*/
void	print_history(t_list **hist, int index, char **input, t_termcap *t);
int	save_history(char *input, t_list **history, t_termcap *t);
int	up_history(t_termcap *t);
int	down_history(t_termcap *t);

/*
	***** SIGNAL *****
*/
void	handler_sigint(int num);
void	handler_sigquit(int num);

#endif
