# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 13:52:25 by fael-bou          #+#    #+#              #
#    Updated: 2022/08/17 17:42:51 by fael-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
BUILD_DIR = build

MANDATORY_OBJ = main.o libft.o philosophers.o args_control.o time.o stop_conditions.o

M_OBJ = $(addprefix $(BUILD_DIR)/, $(MANDATORY_OBJ))

NAME = philo

all : $(NAME)

$(NAME) : $(M_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c philosophers.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 
