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

PRINTF_URL  = https://github.com/pdrlrnc/ft_printf.git
PRINTF_DIR  = ft_printf
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a

CC          = cc -g -O0
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR)
RM          = rm -rf

DEF_COLOUR  = \033[0;39m
TURQUOISE   = \033[38;2;64;224;208m

SRC         = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
HDRS        = $(INC_DIR)/pipex.h $(INC_DIR)/printf.h $(INC_DIR)/libft.h

.PHONY: all clean fclean re headers

all: $(PRINTF_LIB) headers $(NAME)
	@echo "$(TURQUOISE)__________.____________________________  ___$(DEF_COLOUR)"
	@echo "$(TURQUOISE)\______   \   \______   \_   _____/\   \/  /$(DEF_COLOUR)"
	@echo "$(TURQUOISE) |     ___/   ||     ___/|    __)_  \     / $(DEF_COLOUR)"
	@echo "$(TURQUOISE) |    |   |   ||    |    |        \ /     \ $(DEF_COLOUR)"
	@echo "$(TURQUOISE) |____|   |___||____|   /_______  //___/\  \ $(DEF_COLOUR)"
	@echo "$(TURQUOISE)                                \/       \_/$(DEF_COLOUR)"
	@echo "$(TURQUOISE)                   🚬Ceci n'est pas une pipe$(DEF_COLOUR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(PRINTF_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -L$(PRINTF_DIR) -lftprintf -o $(NAME)

$(PRINTF_DIR):
	@git clone --depth 1 $(PRINTF_URL) $(PRINTF_DIR)

$(PRINTF_LIB): | $(PRINTF_DIR)
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR)

headers: $(INC_DIR)/printf.h $(INC_DIR)/libft.h

$(INC_DIR)/printf.h: $(PRINTF_LIB)
	@mkdir -p $(INC_DIR)
	@cp $(PRINTF_DIR)/include/printf.h $(INC_DIR)/printf.h

$(INC_DIR)/libft.h: $(PRINTF_LIB)
	@mkdir -p $(INC_DIR)
	@cp $(PRINTF_DIR)/include/libft.h $(INC_DIR)/libft.h

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(INC_DIR)/printf.h $(INC_DIR)/libft.h 
	@$(RM) -r $(PRINTF_DIR)

re: fclean all

