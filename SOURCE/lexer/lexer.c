/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:07:52 by robello           #+#    #+#             */
/*   Updated: 2025/09/15 13:16:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int      is_potential_array_assignment(const char *input_line, int start_pos)
{
        int     i;

        i = start_pos;
        // Look for pattern: IDENTIFIER=( but reject IDENTIFIER=((
        while (input_line[i] && (ft_isalnum(input_line[i]) || input_line[i] == '_'))
                i++;
        if (input_line[i] != '=')
                return (0);
        i++;
        if (input_line[i] != '(')
                return (0);
        // Reject double parentheses - this should be a syntax error
        if (input_line[i + 1] == '(')
                return (0);
        return (1);
}

t_token *lex_word(const char *input_line, int *input_ptr)
{
        t_token *token;
        char    *value;
        int             start;
        int             paren_depth;
        int             is_array_assignment;

        paren_depth = 0;
        start = *input_ptr;
        is_array_assignment = is_potential_array_assignment(input_line, start);
        if (is_array_assignment)
        {
                // For array assignments,
                        //include parentheses and spaces in the word token
                while (input_line[*input_ptr])
                {
                        if (input_line[*input_ptr] == '(')
                                paren_depth++;
                        else if (input_line[*input_ptr] == ')')
                        {
                                paren_depth--;
                                (*input_ptr)++;
                                if (paren_depth == 0)
                                        break ;
                                continue ;
                        }
                        // Allow spaces inside parentheses for array assignments
                        else if (ft_is_space(input_line[*input_ptr]) && paren_depth == 0)
                                break ;
                        (*input_ptr)++;
                }
        }
        else
        {
                // Normal word parsing with backslash escape handling
                while (ft_is_word_char(input_line[*input_ptr])
                        || input_line[*input_ptr] == '\\')
                {
                        if (input_line[*input_ptr] == '\\' && input_line[*input_ptr + 1])
                                (*input_ptr) += 2; // Skip escaped character
                        else
                                (*input_ptr)++;
                }
        }
        value = ft_substr(input_line, start, *input_ptr - start);
        if (!value)
                return (NULL);
        token = ft_new_token(TOKEN_WORD, value, 0);
        if (!token)
                free(value);
        return (token);
}

t_token *get_next_token(const char *input_line, int *input_ptr)
{
        char    x;

        while (ft_is_space(input_line[*input_ptr]))
                (*input_ptr)++;
        if (input_line[*input_ptr] == '\0')
                return (NULL);
        x = input_line[*input_ptr];
        if (ft_is_single_quote(x))
                return (lex_single_quote(input_line, input_ptr));
        if (ft_is_double_quote(x))
                return (lex_double_quote(input_line, input_ptr));
        if (ft_is_metacharacter(x))
                return (lex_metacharacter(input_line, input_ptr));
        return (lex_word(input_line, input_ptr));
}

// Helper function to get next token without skipping initial spaces
static t_token  *get_next_token_preserve_space(const char *input_line,
                int *input_ptr, int *had_space)
{
        char    x;

        *had_space = 0;
        while (ft_is_space(input_line[*input_ptr]))
        {
                *had_space = 1;
                (*input_ptr)++;
        }
        if (input_line[*input_ptr] == '\0')
                return (NULL);
        x = input_line[*input_ptr];
        if (ft_is_single_quote(x))
                return (lex_single_quote(input_line, input_ptr));
        if (ft_is_double_quote(x))
                return (lex_double_quote(input_line, input_ptr));
        if (ft_is_metacharacter(x))
                return (lex_metacharacter(input_line, input_ptr));
        return (lex_word(input_line, input_ptr));
}

// Helper function to concatenate two token values
static char     *concat_token_values(const char *val1, const char *val2)
{
        char    *result;

        size_t len1, len2;
        if (!val1)
                val1 = "";
        if (!val2)
                val2 = "";
        len1 = ft_strlen(val1);
        len2 = ft_strlen(val2);
        result = malloc(len1 + len2 + 1);
        if (!result)
                return (NULL);
        ft_strlcpy(result, val1, len1 + 1);
        ft_strlcat(result, val2, len1 + len2 + 1);
        return (result);
}

t_token *ft_lexer_main(char *input_line)
{
        int             input_ptr;
        t_token *first;
        t_token *last;
        t_token *token;
        int             had_space;
        char    *new_value;
        // int          prev_quote;
        // int          curr_quote;

        input_ptr = 0;
        first = NULL;
        last = NULL;
        if (!input_line || !*input_line)
                return (NULL);
        while (input_line[input_ptr])
        {
                token = get_next_token_preserve_space(input_line, &input_ptr,
                                &had_space);
                if (!token)
                {
                        free_tokens(first);
                        return (NULL);
                }

                // Set join_with_next flag for the previous token
                if (last)
                        last->join_with_next = !had_space;

                // Check if we can concatenate with previous token
                // Only concatenate if quote contexts match to preserve expansion semantics
                if (!had_space && last && last->type == TOKEN_WORD
                        && token->type == TOKEN_WORD && last->quote == token->quote)
                {
                        // Concatenate with previous token (same quote context)
                        new_value = concat_token_values(last->token_value,
                                        token->token_value);
                        if (!new_value)
                        {
                                free_tokens(first);
                                free(token->token_value);//added
                                free(token); //added
                                return (NULL);
                        }
                        // Quote context remains the same since both tokens have same quote type
                        last->quote = token->quote;

                        free(last->token_value);
                        last->token_value = new_value;
                        
                        // Free the current token since we merged it
                        free(token->token_value);
                        free(token);
                }
                else
                {
                        // Add as new token
                        token->join_with_next = 0; // Initialize flag
                        if (!first)
                                first = token;
                        else
                                last->next_token = token;
                        last = token;
                }
        }
        return (first);
}

// t_token      *ft_lexer_main(const char *input_line)
// {
//      int             input_ptr;
//      t_token *first;
//      t_token *last;
//      t_token *token;
//      int             had_space;
//      char    *new_value;
        
//      input_ptr = 0;
//      first = NULL;
//      last = NULL;
        
//      if (!input_line || !*input_line)
//              return (NULL);

//      while (input_line[input_ptr])
//      {
//              token = get_next_token_preserve_space(input_line, &input_ptr, &had_space);
//              if (!token)
//              {
//                      free_tokens(first);
//                      return (NULL);
//              }
                
//              // Check if we can concatenate with previous token
//              if (!had_space && last && last->type == TOKEN_WORD && token->type == TOKEN_WORD)
//              {
//                      // Concatenate with previous token
//                      new_value = concat_token_values(last->token_value, token->token_value);
//                      if (!new_value)
//                      {
//                              free_tokens(first);
//                              return (NULL);
//                      }
//                      free(last->token_value);
//                      last->token_value = new_value;
//                      // Free the current token since we merged it
//                      free(token->token_value);
//                      free(token);
//              }
//              else
//              {
//                      // Add as new token
//                      if (!first)
//                              first = token;
//                      else
//                              last->next_token = token;
//                      last = token;
//              }
//      }
//      return (first);
// }
