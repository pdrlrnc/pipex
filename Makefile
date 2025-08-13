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

SRC_FILES   = pipex factories parser parser2 parser3 cleaner parent child
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

LIBFT_URL   = https://github.com/pdrlrnc/libft.git
CLONE_DIR   = libft
LIBFT_LIB   = $(CLONE_DIR)/libft.a

CC          = cc -g -O0
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(CLONE_DIR)
RM          = rm -rf

DEF_COLOUR = \033[0;39m
TURQUOISE = \033[38;2;64;224;208m

SRC         = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all: $(CLONE_DIR) $(LIBFT_LIB) $(NAME)
	@echo "$(TURQUOISE)__________.____________________________  ___$(DEF_COLOUR)"
	@echo "$(TURQUOISE)\______   \   \______   \_   _____/\   \/  /$(DEF_COLOUR)"
	@echo "$(TURQUOISE) |     ___/   ||     ___/|    __)_  \     / $(DEF_COLOUR)"
	@echo "$(TURQUOISE) |    |   |   ||    |    |        \ /     \ $(DEF_COLOUR)"
	@echo "$(TURQUOISE) |____|   |___||____|   /_______  //___/\  \ $(DEF_COLOUR)"
	@echo "$(TURQUOISE)                                \/       \_/$(DEF_COLOUR)"
	@echo "$(TURQUOISE)                   🚬Ceci n'est pas une pipe$(DEF_COLOUR)"
	


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -L$(CLONE_DIR) -lft -o $(NAME)

$(CLONE_DIR):
	@git clone --depth 1 $(LIBFT_URL) $(CLONE_DIR)

$(LIBFT_LIB): | $(CLONE_DIR)
	@make debug --no-print-directory -C $(CLONE_DIR)
	@mv $(CLONE_DIR)/libft.h $(INC_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@if [ -d $(CLONE_DIR) ]; then make clean --no-print-directory -C $(CLONE_DIR); fi
	@$(RM) $(INC_DIR)/libft.h

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(CLONE_DIR)

re: fclean all

.PHONY: all clean fclean re

