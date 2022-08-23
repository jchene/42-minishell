/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:27:27 by anguinau          #+#    #+#             */
/*   Updated: 2022/02/04 10:27:28 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>

// ANSI COLOR CODES

# define RED_CODE		"\033[38;5;1m"
# define GREEN_CODE		"\033[38;5;2m"
# define YELLOW_CODE	"\033[38;5;3m"
# define BLUE_CODE		"\033[38;5;4m"
# define PURPLE_CODE	"\033[38;5;5m"
# define CYAN_CODE		"\033[38;5;6m"
# define RESET_CODE		"\033[0m"

// PIPE ENDS

# define P_RD		0	//	READ END
# define P_WR		1	//	WRITE END

// UPDATE FUNCTIONS

# define NO_UP		0	//	NO UPDATE
# define UP			1	//	UPDATE

// ASCII CODES

# define D_QUOTE	34	//	DOUBLE QUOTE
# define S_QUOTE	39	//	SIMPLE QUOTE

// FLAGGING CODES

# define INV		-1	//	INVALID
# define INF		0	//	INFILE
# define HRD		1	//	HEREDOC
# define ROF		2	//	REPLACE OUTFILE
# define AOF		3	//	APPEND OUTFILE
# define FLN		4	//	FILENAME
# define HDL		5	//	HEREDOC DELIMITER
# define CMD		6	//	COMMAND
# define ARG		7	//	ARGUMENT
# define PIP		8	//	PIPE
# define NWL		9	//	NEWLINE

// BASH EXIT CODES

# define GNRL_ERR	1	//	GENERAL ERROR
# define SHELL_BT	2	//	SHELL BUILTIN MISUSE
# define CMD_NO_X	126	//	COMMAND NOT EXECUTED
# define CMD_NO_F	127	//	COMMAND NOT FOUND
# define FATL_ERR	128	//	FATAL ERROR

// MINISHELL ERROR CODES

# define ER_CMD_PA	1	// BAD CMD PATH
# define ER_CMD_FO	2	// BAD CMD
# define ER_CMD_PE	3	// NO CMD PERMS
# define ER_CMD_DI	4	// CMD IS DIRECTORY

typedef struct s_export
{
	char				*str;
	struct s_export		*next;
	struct s_export		*prev;
}						t_export;

typedef struct s_history
{
	char				*str;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct s_quotes
{
	int				quoted_from;
	int				quoted_to;
	int				quote;
	struct s_quotes	*next;
}					t_quotes;

typedef struct s_dollars
{
	int					from;
	int					to;
	struct s_dollars	*next;
}						t_dollars;

typedef struct s_parsing
{
	char				*str;
	int					flag;
	int					was_quoted;
	int					no_extend;
	t_quotes			*quotes;
	t_dollars			*dollars;
	struct s_parsing	*next;
	struct s_parsing	*prev;
}						t_parsing;

typedef struct s_exec
{
	int					input;
	int					output;
	int					to_close[2];
	int					out_pipe[2];
	int					exit_code;
	char				*path;
	char				**args;
}						t_exec;

typedef struct s_line
{
	char				c;
	struct s_line		*next;
}						t_line;

typedef struct s_data
{
	t_export	*exp_index;
	t_export	*exp_start;
	t_export	*exp_end;
	t_history	*h_start;
	t_history	*h_index;
	t_parsing	*p_start;
	t_parsing	*p_index;
	t_parsing	*he_start;
	t_parsing	*he_index;
	t_parsing	*lines;
	t_exec		*exec_struc;
	t_line		*line_start;
	t_line		*line_index;
	int			shlvl;
	int			in_hrd;
	int			passif_mode;
	int			envp_size;
	char		**old_envp;
	char		**envp;
	char		**path;
	char		*line;
	int			lines_executed;
	int			stop;
	int			exit_code;
	int			got_from_builtsin;
	int			error_occured;
	pid_t		*child_ids;
	int			he_read;
	int			he_pipe[2];
	int			old_pipe[2];
	int			new_pipe[2];
	int			temp_pipe[2];
	pid_t		temp_pid;
	int			in_child;
	int			skip_exec;
	int			last_skip;
	char		*temp;
	char		*temp2;
	int			i;
	int			j;
	int			old;
	int			offset;
}				t_data;

//				ENV MANAGEMENT

int				create_envp(char **envp);
char			**add_to_envp(char *new, char **dst);
int				update_env(char *new);
int				create_exp_struct(void);
int				add_to_exp_struct(char *str);
int				free_exp_struct(void);
int				is_in_env(char *to_find);
char			*envp_to_export(char *s, int founded);

//				INIT

int				init_data(char **envp);

//				SIGNALS

int				ft_signal(void);

//				EXIT

int				exit_properly(int ret);

//				HISTORY

int				init_history(char *str);
int				add_in_history(char *str);
int				create_history_file(void);
int				ft_clear_history(void);

//				PARSING

int				read_input(void);
int				split_line(void);
int				check_input(void);
int				rm_dollars(t_parsing *start, t_parsing *temp, int from_hrd);
int				rm_quotes(void);
int				replace_it(int finded, char **old, char **buff);
int				is_quoted(int k, int quote);
void			init_p_struct_member(t_parsing *index);
int				was_quoted(t_quotes *index, int i);
int				split_ret(void);
int				convert_it(int size, int k, int finded);
int				return_it(int ret, char **old, char **buff, int diff);
int				dollar_finded(int ret);
int				from_dollar(t_dollars *index, int i);

//				FLAGGING

int				is_redir(char *word, int *flag);
int				get_flag(void);
void			check_symbols(char *first_wrong_char);
int				check_invalids(char *first_wrong_char);
int				flag_words(void);

//				EXECUTION

int				first_init(void);
int				fd_update(int *fd_ptr, int value);
int				nb_cmds(int reset);
int				nb_pipes(int flag);
int				wait_all(void);
int				init_exec(void);
int				pipe_at_end(t_parsing *cursor);
int				fill_e_struc(t_exec *struc, char **envp);
char			*get_path(char *string, t_exec *struc, char **envp);
int				is_builtin(char *str);
int				start_exec(char **envp, int i, int ret);
int				child_process(t_exec *struc, char **envp);
int				free_exec(void);
int				exit_exec(int ret);
void			apply_builtin(t_exec *struc, int ret, int is_last);
int				exec_builtin(t_exec *struc);
int				is_directory(char *string);
int				free_that_line(void);
unsigned long	display_error(int err_code, char *name, int bash_code);
const char		*get_err_str(int err_code);
int				is_directory(char *string);
int				next_word(void);
int				child_process(t_exec *struc, char **envp);
int				is_builtin(char *str);

//				HEREDOCS

int				init_heredocs(void);
int				end_of_hrd(char **str, int ret);
int				get_new_line(int ret);

//				PATH

int				get_env_index(char *env_name, char **envp);
char			*get_path(char *string, t_exec *struc, char **envp);
char			*add_arg(char *str, t_exec *struc);
char			**get_args(t_parsing *tmp, t_exec *struc, char **envp);

//				REDIRECTIONS

void			*get_infiles(t_parsing *tmp, t_exec *struc);
void			*get_outfiles(t_parsing *tmp, t_exec *struc);
int				count_block_flags(t_parsing *cursor, int flag);
int				count_list_flags(int flag);

//				BUILTS IN

int				ft_pwd(int fd);
void			ft_exit(char **args);
int				ft_echo(char **str, int fd);
int				ft_cd(char **dir, char *str);
int				ft_export(char **str, int fd);
int				ft_env(int fd);
int				ft_unset(char **name);

//				STRUCTURE MANAGEMENT

int				new_p_struct_member(void);
int				free_p_struct(t_parsing **start);
int				fill_p_struct_str(void);
int				join_p_struc(t_parsing *member1, t_parsing *member2);

//				NORM HELPING - RETURNS

int				iperror(const char *str, int ret);
void			*pperror(const char *str);
int				ifree(void *ptr, int ret);
void			*pfree(void *ptr, void *ret);

//				NORM HELPING - SET

int				set_int(int	*dst, int src, int ret);
int				set_char(char *dst, char c, int ret);
int				set_ptr(void **dst, void *src, int ret);
int				fill_char(char *dst, char c, int ret);

//				NORM HELPING - MEMORY

int				free_ptab(void **tab, size_t size);
int				free_ptabn(void **tab);
void			*ft_calloc(size_t size);
void			*ft_memset(void *s, int c, size_t n);

//				NORM HELPING - SINGLETONS

t_data			*data(void);
int				*seen_cmd(void);
int				*is_d_quoted(void);
int				*is_s_quoted(void);

//				NORM HELPING - TERNARIES

int				itern(int exp, int ret1, int ret2);
void			*ptern(int exp, void *ret1, void *ret2);
int				is_equal(int nbr, int to_find, int ret_true, int ret_false);

//				NORM HELPING - COPY

void			ft_strcpy(char *src, char *dst);
int				ft_strmcpy(char *src, char **dst);
int				strict_cmp(char *s1, char *s2);

//				NORM HELPING - TMF
int				new_quotes(int quote);

#endif
