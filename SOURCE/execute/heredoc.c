/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:08:32 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/10 18:40:25 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_heredoc_eof(char *line, t_shell *shell, char *delimiter)
{
	write(STDOUT_FILENO, "\n", 1);
	printf("minishell: warning: here-document at line %d "
		"delimited by end-of-file (wanted `%s')\n",
		shell->line_cnt, delimiter);
	free(line);
	return (-1);
}

static int	is_heredoc_delimiter(char *line, char *delimiter)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& (line[ft_strlen(delimiter)] == '\n'
			|| line[ft_strlen(delimiter)] == '\0'))
		return (1);
	return (0);
}

int	ft_heredoc_read_loop(int pipe_write_fd, char *delimiter, t_shell *shell)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_gb.last_sig == SIGINT)
		{
			if (g_gb.last_sig != SIGINT)
				return (handle_heredoc_eof(line, shell, delimiter));
			free(line);
			return (-1);
		}
		if (is_heredoc_delimiter(line, delimiter))
		{
			shell->line_cnt++;
			free(line);
			break ;
		}
		if (!(ft_strcmp (line, "\n") == 0))
			shell->line_cnt++;
		write(pipe_write_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

void	ft_heredoc(t_comnd *cmds, t_shell *shell)
{
	int		pipe_fd[2];

	if (!cmds->delimiter)
	{
		ft_putstr_fd("minishell: heredoc: missing delimiter\n", 2);
		return ;
	}
	if (pipe(pipe_fd) < 0)
		ft_error_exit("pipe");
	//g_gb.last_sig = SIGINT_HEREDOC;
	if (ft_heredoc_read_loop(pipe_fd[1], cmds->delimiter, shell) == -1)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		cmds->infile = -1;
		g_gb.last_sig = 0;
		return ;
	}
	close(pipe_fd[1]);
	cmds->infile = pipe_fd[0];
	
	ft_pipe_up_bonus(cmds, shell);
	get_next_line(-1);
	g_gb.last_sig = 0;
}

int	ft_start_execution(t_comnd *cmds, t_shell *shell)
{
	t_comnd	*cmd;

	cmd = cmds;
	if (!cmds)
	{
		ft_putstr_fd("minishell: missing commands\n", 2);
		return (1);
	}
	if (cmd->av_cmd[0] && (strcmp(cmd->av_cmd[0], "minishell") == 0
		|| strcmp(cmd->av_cmd[0], "./minishell") == 0))
    	return (handle_nested_minishell(cmd->av_cmd, shell->envp));
	while (cmd)
	{
		if (cmd->delimiter)
		{
			ft_heredoc(cmd, shell);
			return (0);
		}
		cmd = cmd->next;
	}
	// Open redirection files before executing pipeline
	//ft_open_main(cmds, 0);
	ft_pipe_up_bonus(cmds, shell);
	get_next_line(-1);
	return (0);
}
