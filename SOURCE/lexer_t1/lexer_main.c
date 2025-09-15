/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:53:46 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 13:04:36 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Token types matching bash behavior
// typedef enum e_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIRECT_IN,
// 	TOKEN_REDIRECT_OUT,
// 	TOKEN_REDIRECT_APPEND,
// 	TOKEN_REDIRECT_HEREDOC,
// 	TOKEN_AND,
// 	TOKEN_OR,
// 	TOKEN_SEMICOLON,
// 	TOKEN_LPAREN,
// 	TOKEN_RPAREN,
// 	TOKEN_AMPERSAND,
// 	TOKEN_EOF,
// 	TOKEN_NEWLINE
// }	t_token_type;

// typedef enum e_quote
// {
// 	NA,
// 	SINGLE,
// 	DOUBLE
// }	t_quote;

// typedef struct s_token
// {
// 	t_token_type				type;
// 	t_quote						quote;
// 	char						*token_value;
// 	struct s_token				*next_token;
// }								t_token;

// Helper function to create a new token
static t_token *create_token(t_token_type type, char *value, t_quote quote)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	
	token->type = type;
	token->quote = quote;
	token->token_value = value ? strdup(value) : NULL;
	token->next_token = NULL;
	return (token);
}

// Helper function to append token to list
static void append_token(t_token **head, t_token *new_token)
{
	t_token *current;
	
	if (!*head)
	{
		*head = new_token;
		return;
	}
	
	current = *head;
	while (current->next_token)
		current = current->next_token;
	current->next_token = new_token;
}

// Check if character is a metacharacter in bash
static int is_metachar(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' || 
			c == '<' || c == '>' || c == ' ' || c == '\t' || c == '\n');
}

// Skip whitespace (space and tab)
static char *skip_whitespace(char *input)
{
	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

// Parse operator tokens
static char *parse_operator(char *input, t_token **tokens)
{
	if (strncmp(input, "&&", 2) == 0)
	{
		append_token(tokens, create_token(TOKEN_AND, "&&", NA));
		return (input + 2);
	}
	else if (strncmp(input, "||", 2) == 0)
	{
		append_token(tokens, create_token(TOKEN_OR, "||", NA));
		return (input + 2);
	}
	else if (strncmp(input, "<<", 2) == 0)
	{
		append_token(tokens, create_token(TOKEN_HEREDOC, "<<", NA));
		return (input + 2);
	}
	else if (strncmp(input, ">>", 2) == 0)
	{
		append_token(tokens, create_token(TOKEN_APPEND, ">>", NA));
		return (input + 2);
	}
	else if (*input == '|')
	{
		append_token(tokens, create_token(TOKEN_PIPE, "|", NA));
		return (input + 1);
	}
	else if (*input == '<')
	{
		append_token(tokens, create_token(TOKEN_REDIRECT_IN, "<", NA));
		return (input + 1);
	}
	else if (*input == '>')
	{
		append_token(tokens, create_token(TOKEN_REDIRECT_OUT, ">", NA));
		return (input + 1);
	}
	else if (*input == ';')
	{
		append_token(tokens, create_token(TOKEN_SEMICOLON, ";", NA));
		return (input + 1);
	}
	else if (*input == '(')
	{
		append_token(tokens, create_token(TOKEN_LPAREN, "(", NA));
		return (input + 1);
	}
	else if (*input == ')')
	{
		append_token(tokens, create_token(TOKEN_RPAREN, ")", NA));
		return (input + 1);
	}
	else if (*input == '&')
	{
		append_token(tokens, create_token(TOKEN_AMPERSAND, "&", NA));
		return (input + 1);
	}
	else if (*input == '\n')
	{
		append_token(tokens, create_token(TOKEN_NEWLINE, "\n", NA));
		return (input + 1);
	}
	return (input);
}

// Handle single quoted strings
static char *parse_single_quote(char *input, char **word, int *len, int *capacity)
{
	input++; // skip opening quote
	
	while (*input && *input != '\'')
	{
		if (*len >= *capacity - 1)
		{
			*capacity *= 2;
			*word = realloc(*word, *capacity);
		}
		(*word)[(*len)++] = *input++;
	}
	
	if (*input == '\'')
		input++; // skip closing quote
	
	return (input);
}

// Handle double quoted strings with variable expansion and escape sequences
static char *parse_double_quote(char *input, char **word, int *len, int *capacity)
{
	input++; // skip opening quote
	
	while (*input && *input != '"')
	{
		if (*len >= *capacity - 1)
		{
			*capacity *= 2;
			*word = realloc(*word, *capacity);
		}
		
		if (*input == '\\' && *(input + 1))
		{
			input++; // skip backslash
			// Handle escape sequences in double quotes
			switch (*input)
			{
				case '"':
				case '\\':
				case '$':
				case '`':
				case '\n':
					(*word)[(*len)++] = *input;
					break;
				default:
					(*word)[(*len)++] = '\\';
					(*word)[(*len)++] = *input;
					break;
			}
			input++;
		}
		else
		{
			(*word)[(*len)++] = *input++;
		}
	}
	
	if (*input == '"')
		input++; // skip closing quote
	
	return (input);
}

// Parse word tokens (including quoted strings)
static char *parse_word(char *input, t_token **tokens)
{
	int capacity = 64;
	char *word = malloc(capacity);
	int len = 0;
	t_quote quote_type = NA;
	int has_quotes = 0;
	
	if (!word)
		return (input);
	
	while (*input && !is_metachar(*input))
	{
		if (*input == '\'' && quote_type != DOUBLE)
		{
			has_quotes = 1;
			if (quote_type == NA)
				quote_type = SINGLE;
			input = parse_single_quote(input, &word, &len, &capacity);
		}
		else if (*input == '"' && quote_type != SINGLE)
		{
			has_quotes = 1;
			if (quote_type == NA)
				quote_type = DOUBLE;
			input = parse_double_quote(input, &word, &len, &capacity);
		}
		else if (*input == '\\' && quote_type == NA && *(input + 1))
		{
			// Handle escape sequences outside quotes
			if (len >= capacity - 1)
			{
				capacity *= 2;
				word = realloc(word, capacity);
			}
			input++; // skip backslash
			word[len++] = *input++;
		}
		else
		{
			if (len >= capacity - 1)
			{
				capacity *= 2;
				word = realloc(word, capacity);
			}
			word[len++] = *input++;
		}
	}
	
	if (len > 0)
	{
		word[len] = '\0';
		// If no quotes were encountered, reset quote_type
		if (!has_quotes)
			quote_type = NA;
		append_token(tokens, create_token(TOKEN_WORD, word, quote_type));
	}
	
	free(word);
	return (input);
}

// Main lexer function
t_token *ft_lexer_main(char *input)
{
	t_token *tokens = NULL;
	
	if (!input)
		return (NULL);
	
	while (*input)
	{
		// Skip whitespace
		input = skip_whitespace(input);
		
		if (!*input)
			break;
		
		// Try to parse operators first
		char *prev_input = input;
		input = parse_operator(input, &tokens);
		
		// If no operator was parsed, parse as word
		if (input == prev_input)
		{
			input = parse_word(input, &tokens);
		}
	}
	
	// Add EOF token
	append_token(&tokens, create_token(TOKEN_EOF, NULL, NA));
	
	return (tokens);
}

// Helper function to free token list
// void free_tokens(t_token *tokens)
// {
// 	t_token *current;
	
// 	while (tokens)
// 	{
// 		current = tokens;
// 		tokens = tokens->next_token;
// 		free(current->token_value);
// 		free(current);
// 	}
// }

// Helper function to print tokens (for debugging)
void print_tokens(t_token *tokens)
{
	const char *type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "REDIRECT_APPEND",
		"REDIRECT_HEREDOC", "AND", "OR", "SEMICOLON", "LPAREN", "RPAREN",
		"AMPERSAND", "EOF", "NEWLINE"
	};
	
	const char *quote_names[] = {"NONE", "SINGLE", "DOUBLE"};
	
	while (tokens)
	{
		printf("Type: %-15s Quote: %-6s Value: [%s]\n",
			   type_names[tokens->type],
			   quote_names[tokens->quote],
			   tokens->token_value ? tokens->token_value : "NULL");
		tokens = tokens->next_token;
	}
}

// Example usage
// #ifdef TEST_LEXER
// int main(void)
// {
// 	char *test_inputs[] = {
// 		"ls -la | grep test",
// 		"echo \"hello world\" > file.txt",
// 		"cat file.txt && echo 'done'",
// 		"echo $USER || echo \"not found\"",
// 		"(ls; pwd) | wc -l",
// 		"echo \"quotes \\\"inside\\\" quotes\"",
// 		"echo 'single quotes'",
// 		NULL
// 	};
	
// 	for (int i = 0; test_inputs[i]; i++)
// 	{
// 		printf("\n=== Input: %s ===\n", test_inputs[i]);
// 		t_token *tokens = ft_lexer_main(test_inputs[i]);
// 		print_tokens(tokens);
// 		free_tokens(tokens);
// 	}
	
// 	return (0);
// }
// #endif