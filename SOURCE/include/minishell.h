/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:38:07 by robello           #+#    #+#             */
/*   Updated: 2025/09/15 13:00:44 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "../gnl/get_next_line_bonus.h"
# include "libft.h"
# include <limits.h>
# include <sys/select.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define HEREDOC_TMP "/tmp/minishell_heredoc"
# define SIGINT_HEREDOC -1
# define COLOR_USERHOST "\001\033[1;33m\002"
# define COLOR_SHELL "\001\033[1;31m\002"
# define COLOR_PATH "\001\033[1;36m\002"
# define COLOR_RESET "\001\033[1;30m\002"
# define PROMPT " $ "


typedef struct s_gb
{
        volatile sig_atomic_t   last_sig;
        int last_status_code;
} t_gb ;

// extern volatile sig_atomic_t g_gb.last_sig;
// extern int status;
extern t_gb g_gb;

typedef struct s_env_var
{
        char                                            *envar_name;
        char                                            *envar_value;
        struct s_env_var                        *next_envar;
}                                                               t_env_var;

typedef struct s_array_var
{
        char                                            *array_name;
        char                                            **elements;
        int                                                     element_count;
        int                                                     capacity;
        struct s_array_var                      *next_array;
}                                                               t_array_var;

// typedef enum e_token
// {
//      TOKEN_WORD,
//      TOKEN_PIPE,
//      TOKEN_REDIRECT_IN,
//      TOKEN_REDIRECT_OUT,
//      TOKEN_HEREDOC,
//      TOKEN_APPEND,
//      TOKEN_COMMAND,
//      TOKEN_EOF,
// }                                                            t_token_type;
typedef enum e_token_type
{
        TOKEN_WORD,
        TOKEN_PIPE,
        TOKEN_REDIRECT_IN,
        TOKEN_REDIRECT_OUT,
        TOKEN_APPEND,
        TOKEN_HEREDOC,
        TOKEN_AND,
        TOKEN_OR,
        TOKEN_SEMICOLON,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_AMPERSAND,
        TOKEN_EOF,
        TOKEN_NEWLINE
}       t_token_type;

typedef enum e_quote
{
        NA,
        SINGLE,
        DOUBLE,
}                                                               t_quote;



typedef struct s_token
{
        t_token_type                            type;
        t_quote                                         quote;
        char                                            *token_value;
        int                                                     join_with_next;
        struct s_token                          *next_token;
}                                                               t_token;

typedef struct s_command
{
        char                                            **av_cmd;
        t_token                                         *av_cmd_lst;
        char                                            *infile_name;
        char                                            *outfile_name;
        char                                            *delimiter;
        int                                                     infile;
        int                                                     outfile;
        int                                                     redirec_type;
        int                                                     quote;
        struct s_command                        *next;
}                                                               t_comnd;

typedef struct s_shell
{
        t_env_var                                       *env_list;
        t_comnd                                         *cmd_list;
        t_array_var                                     *array_list;
        char                                            **envp;
        int                                                     last_status;
        int                                                     line_cnt;
}                                                               t_shell;



typedef struct s_command_args
{
        char                                            **argv;
        t_token                                         **arg_tokens;
        int                                                     argc;
        int                                                     capacity;
}                                                               t_cmd_args;

typedef struct s_pipe
{
        t_comnd                                         *cmd;
        t_shell                                         *shell;
        pid_t                                           *pids;
        int                                                     i;
        int                                                     prev;
        int                                                     pfd[2];
        char                                            **envp;
}                                                               t_pipe;

typedef struct s_export_state
{
        char    *last_name;
        int             last_was_assignment;
        int             status;
}                       t_export_state;

// prompt

int handle_nested_minishell(char **argv, char **envp);
                                                                        void print_command_list(const t_comnd *cmd);
void    quotes_tokens(t_token *tokens);
// void                                                 build_prompt(char *prompt, size_t size);
char                                                    *ft_build_prompt(void);
char                                                    *read_input_with_quotes(const char *prompt,
                                                                        const char *secondary_prompt);
int     ft_append_char_to_expand(char **expand_string, char c);
void    ft_put_bash_error_with_arg(const char *command, const char *arg, const char *error);
void    ft_put_bash_error(const char *command, const char *error);
void    ft_put_syntax_error(const char *token);
int     ft_validate_redirect_syntax(t_token *tokens);
int     ft_validate_pipe_syntax(t_token *tokens);
// lexer
int                                                             ft_is_space(char x);
int                                                             ft_is_single_quote(char x);
int                                                             ft_is_double_quote(char x);
int                                                             ft_is_quote(char x);
int                                                             ft_is_redirect_char(char x);

int                                                             ft_is_pipe(char x);
int                                                             ft_is_metacharacter(char x);
int                                                             ft_is_word_char(char x);

void                                                    print_tokens(t_token *tokens);
const char                                              *token_type_to_str(t_token_type type);
void                                                    print_array(char **av);

t_token                                                 *lex_double_redirect(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *lex_redirect(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *lex_single_quote(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *lex_double_quote(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *lex_metacharacter(const char *input_line,
                                                                        int *input_ptr);

t_token                                                 *lex_word(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *get_next_token(const char *input_line,
                                                                        int *input_ptr);
t_token                                                 *ft_lexer_main(char *input_line);

// parser

int                                                             is_redirection(t_token_type type);
void                                                    init_command_args(t_cmd_args *args);
void                                                    cleanup_command_parsing(t_cmd_args *args,
                                                                        t_comnd *cmd);
t_comnd                                                 *setup_command_parsing(void);

int                                                             process_redirection(t_token *token,
                                                                        t_comnd *cmd);
int                                                             parse_redirection(t_token **tok_ptr,
                                                                        t_comnd *cmd);
int     add_argument(t_cmd_args *args, t_token *token);
int                                                             process_token(t_token **token_ptr, t_comnd *cmd,
                                                                        t_cmd_args *args);
t_comnd                                                 *ft_parse_command(t_token **tok_ptr);

t_comnd                                                 *ft_build_cmdline(t_comnd **first,
                                                                        t_comnd **last, t_token **current);
t_token                                                 *handle_pipe_token(t_token *current);
t_comnd                                                 *ft_parser_main(t_token *tokens);

// pipe
int                                                             setup_allocations(t_comnd *cmds, t_shell *shell,
                                                                        pid_t **pids, char ***envp);
int                                                             handle_parent_builtin(t_comnd *cmds,
                                                                        t_shell *shell, char **envp, pid_t *pids);
void                                                    setup_pipe(int pfd[2], t_comnd *current);
void                                                    launch_child(t_pipe *ctx);
void                                                    close_parent_fds(int *prev, int pfd[2]);
void                                                    ft_pipe_up_bonus(t_comnd *cmds, t_shell *shell);
// built

int                                                             is_builtin_argv(char **av_cmd);
int     ft_dispatch_builtin(char **av_cmd, t_env_var **env_list, t_shell *shell);

char                                                    *ft_get_cd(char **av_cmd, t_env_var **env_list);
int                                                             builtin_cd(char **av_cmd, t_env_var **env_list);

int                                                             builtin_echo(char **av_cmd,
                                                                        t_env_var **env_list);

char                                                    *get_env_value(char *name, t_env_var *env_list);
int                                                             ft_update_env_var(t_env_var *current,
                                                                        const char *value);
int                                                             ft_create_env_var(const char *name,
                                                                        const char *value, t_env_var **env_list);
int                                                             ft_set_env_var(const char *name,
                                                                        const char *value, t_env_var **env_list);
void                                                    unset_env_variable(const char *name,
                                                                        t_env_var **env_list);

int                                                             builtin_env(char **av_cmd,
                                                                        t_env_var **env_list);

int                                                             is_numeric(const char *str);
int                     builtin_exit(char **av_cmd, t_shell *shell);

// static int   is_valid_identifier(const char *str);
void    print_export_error(const char *name);
int     is_valid_export_arg(const char *arg);
void                                                    print_export_list(t_env_var *env_list);
int                                                             ft_process_export(char *arg,
                                                                        t_env_var **env_list);
int     builtin_export(char **av_cmd, t_env_var **env_list, char *arg, char *equals);

int                                                             builtin_pwd(char **av_cmd,
                                                                        t_env_var **env_list);

int                                                             is_valid_unset_identifier(const char *str);
int                                                             builtin_unset(char **av_cmd,
                                                                        t_env_var **env_list);

// expansion
int                                                             is_valid_var_char(char c, int start);
char                                                    *ft_dup_env_value(char *var_name,
                                                                        t_shell *shell);
char                                                    *ft_get_lastcmd_string(int status);
char                                                    *ft_char_to_str(char x);
int                                                             ft_append_piece(char **expand_string,
                                                                        char *piece);
char    *ft_process_quote(const char *input, size_t *idx_ptr, t_shell *shell);
char                                                    *ft_process_dollar(const char *input,
                                                                        size_t *idx_ptr, t_shell *shell);
char    *ft_create_expansion_main(const char *input, t_token *token, t_shell *shell);
void                                                    ft_expand_cmds(t_comnd *cmds, t_shell *shell);

// execute

void                                                    exec_command(t_comnd *current, char **envp);
void                                                    fork_and_exec(t_comnd *curre, int prev_fd,
                                                                        int pipe_fd[2], char **envp);
void                                                    ft_parent_cleanup(int *prev_fd, int pipe_fd[2]);
void                                                    print_commands(t_comnd *cmds);

void                                                    free_env_array(char **envp);
void                                                    ft_trim_newline(char *str);
int                                                             free_partial_envp(char **envp, int i);
int                                                             fill_envp_array(char **envp,
                                                                        t_env_var *env_list);
char                                                    **ft_env_list_to_array(t_env_var *env_list);

int                                                             count_cmds(t_comnd *cmd);
int                                                             is_parent_builtin(t_comnd *cmd);
void                                                    run_child(t_pipe *ctx);
void                                                    ft_wait_all(pid_t *pids, int count,
                                                                        t_shell *shell);

void                                                    ft_execve_cmd_flat(char **av_cmd,
                                                                        t_env_var *env_list);
void                                                    ft_execve_shell_cmd(char *cmd_str, char **env);
void                                                    ft_execve_cmd(char **av_cmd, char **env);

void                                                    redirect_input(t_comnd *c, int prev, int is_first_cmd);
void                                                    redirect_output(t_comnd *c, int *pfd);
void                                                    cleanup_all_fds(t_comnd *cmds);
void                                                    cleanup_command_fds(t_comnd *cmd);
void                                                    ft_put_exec_error(char *cmd, char **cmd_array,
                                                                        char *fullpath);

void                                                    ft_child_proxs(int infile, int out_fd,
                                                                        t_comnd *cmd, t_shell *shell);
void                                                    ft_frk_chld(t_comnd *cmd, int pipe_fd[2],
                                                                        int prev_infi, t_shell *shell);

void                                                    ft_put_cmd_not_found(char *cmd,
                                                                        char **cmd_array);
char                                                    *ft_create_path(char *cmd, char **dirs);
char                                                    *ft_get_path_env(char *var, char **env);
char                                                    *ft_get_cmd_path(char *cmd, char **env);
void                                                    ft_execve_normal_cmd_array(char **cmd_array,
                                                                        char **env);

// static size_t        calc_total_len(char **av_cmd);
void                                                    ft_check_fork(pid_t child_pid);
char                                                    *ft_join_arguments(char **av_cmd);
void                                                    ft_error_exit(char *error);
void                                                    ft_free_strings(char **cmd_array);

int                                                             ft_heredoc_read_loop(int pipe_write_fd,
                                                                        char *delimiter, t_shell *shell);
void                                                    ft_heredoc(t_comnd *cmds, t_shell *shell);
int                                                             ft_start_execution(t_comnd *cmds,
                                                                        t_shell *shell);

int                                                             ft_open_file(char *filename, int mode,
                                                                        int permis);
int                                                             ft_open_outfile(char *filename, int here_flag);
void                                                    open_infile(t_comnd *cmd, int in_child);
void                                                    open_outfile(t_comnd *last, int here_flag,
                                                                        int infile_fd);

void                                                    ft_open_main(t_comnd *cmds, int here_flag);
void                                                    ft_open_last_outfile(t_comnd *cmds);
int                                                             devnull_open(int fd);
void                                                    ft_child_setup(t_comnd *current, int prev_fd,
                                                                        int pipe_write);

// main

void                                                    sigint_handler(int signo);
void                                                    ft_setup_signals(void);

void                                                    ft_clean_shell_setup(t_shell *shell);
void                                                    ft_free_env_list(t_env_var **env_list);
void                                                    free_tokens(t_token *tokens);
void                                                    ft_free_command_redirn_fds(t_comnd *cmd);
void                                                    ft_free_commands(t_comnd **cmd_list);

void                                                    ft_free_env_node(t_env_var *node);
void                                                    ft_add_back(t_comnd **list, t_comnd *new_node);
t_token                                                 *ft_new_token(t_token_type type, char *value, int quote);
t_comnd                                                 *ft_create_command_node(void);
t_env_var                                               *ft_create_env_list(const char *env_line);

t_env_var                                               *ft_build_env_list(char **env_vars);

// t_shell                                                      *ft_init_shell(void);
// t_shell                                                      *ft_shell_setup(char **env_vars);
// int                                                          ft_manage_inputline(char *input_line,
//                                                                      t_shell *shell);
// void                                                 shell_loop(t_shell *shell);

// arrays
t_array_var                                             *ft_create_array_node(const char *name);
int                                                             ft_add_array_element(t_array_var *array, const char *element);
t_array_var                                             *ft_find_array(const char *name, t_array_var *array_list);
char                                                    *ft_get_array_first_element(const char *name, t_array_var *array_list);
void                                                    ft_free_array(t_array_var *array);
void                                                    ft_free_array_list(t_array_var **array_list);
int                                                             ft_is_array_assignment(const char *arg);
char                                                    *ft_extract_array_name(const char *arg);
int                                                             ft_set_array_var(const char *name, const char *value, t_array_var **array_list);
void                                                    ft_remove_array(const char *name, t_array_var **array_list);
int                                                             ft_builtin_export_with_arrays(char **av_cmd, t_env_var **env_list, t_array_var **array_list);
char                                                    *ft_get_variable_value(const char *name, t_env_var *env_list, t_array_var *array_list);
int                                                             ft_dispatch_builtin_with_arrays(char **av_cmd, t_env_var **env_list, t_shell *shell);
char                                                    *ft_get_expanded_variable_value(const char *name, t_shell *shell);
void                                                    ft_init_shell_arrays(t_shell *shell);
void                                                    ft_clean_shell_arrays(t_shell *shell);
#endif
