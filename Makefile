# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: you <you@42.fr>                             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 09:50:19 by you               #+#    #+#              #
#    Updated: 2025/07/18 10:10:00 by you               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex

SRC_FILES   = main
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

LIBFT_URL   = https://github.com/pdrlrnc/libft.git
CLONE_DIR   = libft
LIBFT_LIB   = $(CLONE_DIR)/libft.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(CLONE_DIR)
RM          = rm -rf

SRC         = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all: $(CLONE_DIR) $(LIBFT_LIB) $(NAME)
	@echo "Pipex ready! Pipe those Xs!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -L$(CLONE_DIR) -lft -o $(NAME)

$(CLONE_DIR):
	@git clone --depth 1 $(LIBFT_URL) $(CLONE_DIR)

$(LIBFT_LIB): | $(CLONE_DIR)
	@make -C $(CLONE_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@if [ -d $(CLONE_DIR) ]; then make clean -C $(CLONE_DIR); fi

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(CLONE_DIR)

re: fclean all

.PHONY: all clean fclean re

