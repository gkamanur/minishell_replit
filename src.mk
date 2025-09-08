# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 12:39:14 by gkamanur          #+#    #+#              #
#    Updated: 2025/08/22 15:01:28 by gkamanur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# sources.mk: explicit list of all source files

SRC =	\
	$(wildcard $(LIBFT_DIR)/*.c) \
	$(wildcard $(GET_NEXT_LINE_DIR)/*.c) \
	$(wildcard $(BUILT_DIR)/*.c) \
	$(wildcard $(EXPAN_DIR)/*.c) \
	$(wildcard $(LEXER_DIR)/*.c) \
	$(wildcard $(PIPE_DIR)/*.c) \
	$(wildcard $(PARSE_DIR)/*.c) \
	$(wildcard $(EXEC_DIR)/*.c) \
	$(wildcard $(PROMPT_DIR)/*.c) \
	$(wildcard $(MAIN_DIR)/*.c) 

BONUS_SRC =	$(BONUS_SRC_DIR)/main_bonus.c \
			$(BONUS_SRC_DIR)/parser_bonus.c \
			$(BONUS_SRC_DIR)/lexer_bonus.c \
			$(BONUS_SRC_DIR)/utils_bonus.c \
			$(BONUS_SRC_DIR)/execute_bonus.c \
			$(GET_NEXT_LINE_DIR)/get_next_line_bonus.c \
			$(GET_NEXT_LINE_DIR)/get_next_line_utils_bonus.c
