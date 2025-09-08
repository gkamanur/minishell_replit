/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:06:18 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/08 17:44:04 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

int	check_incomplete_syntax(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (1);
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	if (i > 0 && (line[i - 1] == '\\'
			|| line[i - 1] == '&'))
		return (1);
	return (0);
}

char *read_line_interruptible(const char *prompt)
{
    char    *line;
    char    buffer[4096];
    int     i;
    int     c;
    fd_set  readfs;
    struct timeval  timeout;
    int     result;
    
    // Print prompt
    write(STDOUT_FILENO, prompt, strlen(prompt));
    fflush(stdout);
    
    // Reset signal flag
    g_gb.last_sig = 0;
    i = 0;
    
    // Read character by character using select() for proper signal handling
    while (i < (int)(sizeof(buffer) - 1))
    {
        // Check for signal before each iteration
        if (g_gb.last_sig == SIGINT)
            return (NULL);
        
        // Set up select() to monitor stdin
        FD_ZERO(&readfs);
        FD_SET(STDIN_FILENO, &readfs);
        
        // Short timeout to allow signal checking
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100ms timeout
        
        // Use select() to wait for input or timeout
        result = select(STDIN_FILENO + 1, &readfs, NULL, NULL, &timeout);
        
        // Check for signal after select()
        if (g_gb.last_sig == SIGINT)
            return (NULL);
        
        if (result > 0 && FD_ISSET(STDIN_FILENO, &readfs))
        {
            // Input is available, read one character
            c = getchar();
            
            // Check for signal after read
            if (g_gb.last_sig == SIGINT)
                return (NULL);
            
            if (c == EOF)
            {
                if (i == 0)
                    return (NULL); // True EOF
                break; // EOF after some input
            }
            
            if (c == '\n')
                break;
            
            buffer[i++] = c;
        }
        else if (result == -1)
        {
            // select() error, possibly interrupted by signal
            if (g_gb.last_sig == SIGINT)
                return (NULL);
            // Other error, continue
        }
        // result == 0 means timeout, continue the loop to check for signals
    }
    
    buffer[i] = '\0';
    
    // Return a copy of the buffer
    line = ft_strdup(buffer);
    return (line);
}

char	*read_secondary_input(char *line, const char *second_prompt)
{
	char	*next;
	char	*tmp;
	char	*joined;

	next = readline(second_prompt);
	if (g_gb.last_sig == SIGINT)
	{
		free(line);
		free(next);
		return (NULL);
	}
	if (!next)
		return (line);
	tmp = ft_strjoin(line, "\n");
	free(line);
	if (!tmp)
	{
		free(next);
		return (NULL);
	}
	joined = ft_strjoin(tmp, next);
	free(tmp);
	free(next);
	return (joined);
}

char	*read_input_with_quotes(const char *prompt, const char *second_prompt)
{
	char	*line;

	g_gb.last_sig = 0;
	line = readline(prompt);

	// Ctrl+D on first prompt → exit shell
	if (!line)
		return (NULL);

	// Ctrl+C on first prompt → cancel line, return empty
	if (g_gb.last_sig == SIGINT)
	{
		free(line);
		return (NULL);
	}

	while (check_unclosed_quotes(line))
	{
		char *next = readline(second_prompt);

		// Ctrl+C inside continuation → cancel whole line
		if (g_gb.last_sig == SIGINT)
		{
			free(line);
			free(next);
			return (NULL);
		}

		// Ctrl+D inside continuation → stop and return partial input
		if (!next)
			break;

		// Concatenate
		char *tmp = ft_strjoin(line, "\n");
		free(line);
		if (!tmp)
		{
			free(next);
			return (NULL);
		}
		char *joined = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
		if (!joined)
			return (NULL);
		line = joined;
	}
	return (line);
}

