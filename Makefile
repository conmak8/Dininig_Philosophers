# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 16:25:24 by mevangel          #+#    #+#              #
#    Updated: 2024/08/10 04:42:10 by cmakario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

SRC_DIR	=	./sources
OBJ_DIR	=	./objs

SRC		=	$(wildcard $(SRC_DIR)/philo_actions/*.c) \
			$(wildcard $(SRC_DIR)/philo_initialize/*.c) \
			$(wildcard $(SRC_DIR)/philo_utils/*.c) \
			$(SRC_DIR)/main.c

OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)philo compiled!$(CLEAR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)object files cleaned!$(CLEAR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)Philo executable and object files cleaned!$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
