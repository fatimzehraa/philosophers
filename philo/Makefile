# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fael-bou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 13:52:25 by fael-bou          #+#    #+#              #
#    Updated: 2022/07/02 20:01:25 by fael-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUILD_DIR = build

MANDATORY_OBJ = main.o

M_OBJ = $(addprefix $(BUILD_DIR)/, $(MANDATORY_OBJ))

test :
	echo $(M_OBG)

NAME = philosophers

all : $(NAME)

$(NAME) : $(M_OBJ)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 
