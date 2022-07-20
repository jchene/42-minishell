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

typedef struct s_history
{
	char				*str;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct s_export
{
	char				*str;
	struct s_export		*next;
	struct s_export		*prev;
}						t_export;

typedef struct s_parsing
{
	char				*str;
	int					flag;
	struct s_parsing	*next;
	struct s_parsing	*prev;
}						t_parsing;

typedef struct s_hrd_line
{
	char				*line;
	struct s_hrd_line	*next;
}						t_hrd_line;

typedef struct s_heredoc
{
	t_hrd_line			*heredoc;
	char				*delimiter;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_exec
{
	int					input;
	int					output;
	int					to_close[2];
	char				*path;
	char				**args;
}						t_exec;

typedef struct s_data
{
	int			i;
	int			j;
	int			stop;
	int			exit_code;
	int			exit_calls;
	int			*child_ids;
	char		*line;
	char		*temp;
	char		**path;
	char		**envp;
	int			envp_size;
	char		**old_envp;
	t_history	*h_start;
	t_history	*h_index;
	t_parsing	*p_start;
	t_parsing	*p_index;
	t_export	*exp_index;
	t_export	*exp_start;
	t_export	*exp_end;
	t_exec		*exec_struc;
	t_heredoc	*he_start;
	int			old_pipe[2];
	int			new_pipe[2];
	int			skip_exec;
}				t_data;

//				CORE

int				exit_properly(int ret);
int				free_exec(int ret);
int				init_data(char **envp);
int				new_prompt(void);

//				HISTORY

int				init_history(char *str);
int				add_in_history(char *str);
int				create_history_file(void);
int				ft_clear_history(void);

//				PARSING

int				read_input(void);
int				split_line(void);
int				rm_dollars(void);
int				rm_quotes(void);
int				replace_it(int finded, char **old, char **buff);

//				FLAGGING

int				is_redir(char *word, int *flag);
const char		*flag_name(int flag);
int				get_flag(void);
void			check_symbols(char *first_wrong_char);
int				check_invalids(char *first_wrong_char);
int				flag_words(void);

//				EXECUTION

int				first_init(void);
int				fd_update(int *fd_ptr, int value);
int				nb_cmds(int reset);
void			wait_all(void);
int				init_exec(void);
int				pipe_at_end(t_parsing *cursor);
int				new_pipe(void);
int				init_close(t_exec *struc);
int				fill_e_struc(t_exec *struc, char **envp);
int				child_process(t_exec *struc, char **envp);
int				start_exec(char **envp);
int				close_exec(t_exec *struc);

//				PATH

int				env_diff(char *env_name, char *env_value);
int				get_env_index(char *env_name, char **envp);
char			*get_path(char *string, t_exec *struc, char **envp);
char			*add_arg(char *str, t_exec *struc);
char			**get_args(t_parsing *cursor, t_exec *struc, char **envp);

//				HEREDOCS

int				init_heredocs(void);
int				insert_hrd(t_heredoc *heredoc);
void			display_hrd(t_heredoc *heredoc);
int				insert_line(t_heredoc *heredoc, char *line);
int				count_hrd_list(void);
int				count_hrd_lines(t_heredoc *heredoc);
void			display_all_heredocs(void);
void			clear_all_heredocs(t_heredoc *heredoc);
void			clear_heredoc(t_hrd_line *line);

//				REDIRECTIONS

void			*fill_with_infiles(t_parsing *cursor, t_exec *struc);
void			*fill_with_heredocs(t_parsing *cursor, t_exec *struc);
void			*fill_with_outfiles(t_parsing *cursor, t_exec *struc);
void			*get_infiles(t_parsing *cursor, t_exec *struc);
void			*get_outfiles(t_parsing *cursor, t_exec *struc);
int				count_block_flags(t_parsing *cursor, int flag);
int				count_list_flags(int flag);

//				SIGNALS

int				ft_signal(void);

//				BUILT IN

int				ft_pwd(void);
void			ft_exit(int exit_code);
void			ft_echo(int n, char *str);
int				fd_cd(char *dir);
int				ft_export(char *str);

//				ENV MANAGEMENT

char			**add_to_envp(char **src, char *new);
int				update_env(char *new);
int				create_exp_struct(void);
int				add_to_exp_struct(char *str);
int				free_exp_struct(void);
int				is_in_env(char *to_find);

//				STRUCTURE MANAGEMENT

int				new_p_struct_member(void);
int				free_p_struct(void);
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

//				NORM HELPING - COPY

void			ft_strcpy(char *src, char *dst);
int				ft_strmcpy(char *src, char **dst);
int				strict_cmp(char *s1, char *s2);

//				TEMP

void			display_list(void);

#endif
