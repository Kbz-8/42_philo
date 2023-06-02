# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 17:20:17 by maldavid          #+#    #+#              #
#    Updated: 2023/06/02 17:37:29 by maldavid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= ./philo

SRCS		=	srcs/main.c

OBJ_DIR		= objs
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

DEBUG		?= false
TOOLCHAIN	?= clang

CC			= clang

ifeq ($(TOOLCHAIN), gcc)
	CC = gcc
endif

CLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes
LIBS		= -lpthread

ifeq ($(DEBUG), true)
	CFLAGS += -g -D DEBUG
endif

RM		= rm -f

$(OBJ_DIR)/%.o: %.c
	@echo "\e[1;32m[compiling...   ]\e[1;00m "$<
	@$(CC) $(CFLAGS) $(INCLUDES) $(COPTS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	@echo "\e[1;32m[ linking ...]\e[1;00m "$@
	@$(CC) -o $(NAME) $(OBJS) $(LIBS)
	@echo "\e[1;32m[build finished]\e[1;00m"

$(OBJ_DIR):
	@mkdir -p $(sort $(addprefix $(OBJ_DIR)/, $(dir $(SRCS))))

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re 
