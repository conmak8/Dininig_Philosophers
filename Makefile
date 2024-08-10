# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 16:25:24 by mevangel          #+#    #+#              #
#    Updated: 2024/08/10 02:25:57 by cmakario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

SRC_DIR	=	./
OBJ_DIR	=	./objs/

SRC		=	$(SRC_DIR)main.c \
			$(SRC_DIR)routines.c \
			$(SRC_DIR)supervisor.c \
			$(SRC_DIR)threads.c \
			$(SRC_DIR)utils.c \
			$(SRC_DIR)utils2.c 


OBJ		=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)philo compiled!$(CLEAR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)object files cleaned!$(CLEAR)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@echo "$(CYAN)Philo executable and object files cleaned!$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re