# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 22:31:22 by fael-bou          #+#    #+#              #
#    Updated: 2022/08/17 18:30:11 by fael-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
BUILD_DIR = build

MANDATORY_OBJ = main_bonus.o libft_bonus.o philo_bonus.o args_control_bonus.o time_bonus.o stop_coditions_bonus.o

M_OBJ = $(addprefix $(BUILD_DIR)/, $(MANDATORY_OBJ))

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(M_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c philosophers_bonus.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 
