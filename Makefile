# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 16:54:33 by akozin            #+#    #+#              #
#    Updated: 2024/06/18 17:09:35 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libs/libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

GNL = libs/gnl/
GNL_A = $(addprefix $(GNL), libgnl.a)

MLX = libs/mlx/
MLX_A = $(addprefix $(MLX), libmlx.a)

NAME = miniRT

MAKE = make

CC = gcc
CFLAGS = -Wall -Wextra -Werror# -g -fsanitize=address

SRCNAMES = main.c

SRCS = $(SRCNAMES)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
DEPS = $(addprefix obj/, $(SRCS:.c=.d))

all:		folders make_libs $(NAME)

folders:
	mkdir -p obj/

make_libs:
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(GNL)
	$(MAKE) -C $(MLX)

$(NAME):	$(OBJS) $(LIBFT_A) $(GNL_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(GNL_A) $(MLX_A) -lXext -lX11 -lm -lz -o $(NAME)

obj/%.o:	src/%.c Makefile
	$(CC) $(CFLAGS) -Imlx -c $< -MMD -o $@

-include $(DEPS)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(GNL)
	$(MAKE) clean -C $(MLX)
	$(RM) obj

fclean:
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(GNL)
	$(MAKE) clean -C $(MLX)
	$(RM) obj $(NAME)


re:			fclean all

.PHONY: all clean fclean re
