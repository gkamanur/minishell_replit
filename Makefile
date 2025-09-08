# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 12:35:46 by gkamanur          #+#    #+#              #
#    Updated: 2025/09/02 11:15:14 by gkamanur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BONUS_NAME = minishell_bonus

CC = cc -g -O0

LIBFT_DIR       	:= SOURCE/libft
GET_NEXT_LINE_DIR 	:= SOURCE/gnl
BUILT_DIR 			:= SOURCE/built
EXEC_DIR      		:= SOURCE/execute
EXPAN_DIR   		:= SOURCE/expansion
LEXER_DIR 			:= SOURCE/lexer
PIPE_DIR     		:= SOURCE/pipe
PARSE_DIR     		:= SOURCE/parser
MAIN_DIR     		:= SOURCE/main

CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(GET_NEXT_LINE_DIR)

SRC_DIR = src
BONUS_SRC_DIR = src_bonus

include src.mk

OBJ_DIR = obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
BONUS_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@printf "$(GREEN)***** MINISHELL PROGRAM CREATED SUCCESSFULLY *****$(RESET)\n"

$(BONUS_NAME): $(BONUS_OBJ) | $(LIBFT)
	@$(CC) $(CFLAGS) -DBONUS $(BONUS_OBJ) $(LIBFT) -lreadline -o $@
	@printf "$(GREEN)***** MINISHELL BONUS PROGRAM CREATED SUCCESSFULLY *****$(RESET)\n"

# Create obj directory structure
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

$(LIBFT):
	@echo "Building libft with bonus..."
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "LIBFT built with Bonus."

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "--Cleaned all .o files--"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "--Fully Cleaned Successfully--"

re: fclean all
bonus: $(BONUS_NAME)

# VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind.log

val: $(NAME)
	@echo "=== Running $(NAME) under Valgrind ==="
	@$(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re bonus
