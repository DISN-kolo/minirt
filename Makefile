# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 16:54:33 by akozin            #+#    #+#              #
#    Updated: 2024/07/31 16:18:21 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libs/libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

GNL = libs/gnl/
GNL_A = $(addprefix $(GNL), libgnl.a)

MLX = libs/minilibx-linux/
MLX_A = $(addprefix $(MLX), libmlx.a)

NAME = miniRT

MAKE = make
RM = rm -rf

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# don't use with valgrind lol       !vvvvvvvvvvvvvvvv!
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror

SRCNAMES = main.c \
		   utils/fileprobe.c \
		   utils/inits.c \
		   utils/mlx_utils.c \
		   utils/draw_utils.c \
		   utils/misc.c \
		   utils/vector.c \
		   utils/vector2.c \
		   utils/color_mixing.c \
		   parse/parser_counter.c \
		   parse/parser.c \
		   parse/parse_amb.c \
		   parse/parse_cam.c \
		   parse/parse_lig.c \
		   parse/parse_sp.c \
		   parse/parse_pl.c \
		   parse/parse_cy.c \
		   parse/parse_power.c \
		   parse/parse_rational_positive.c \
		   parse/parse_rgb.c \
		   parse/parse_origin.c \
		   parse/parse_normal.c \
		   parse/parse_fov.c \
		   draw/draw.c \
		   draw/draw_internal_funcs.c \
		   draw/light_calculus.c \
		   draw/light_calculus_sf.c \
		   draw/light_calculus_ignores.c \
		   draw/light_calculus_internal_funcs.c \
		   console/print_usage.c \
		   console/print_errors.c \
		   free_utils/free_utils.c \
		   ray/ray_plane.c \
		   ray/ray_sphere.c \
		   ray/ray_cylinder.c \
		   ray/ray_cylinder_internal.c \
		   ray/ray_cylinder_internal_2.c


SRCS = $(SRCNAMES)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
DEPS = $(addprefix obj/, $(SRCS:.c=.d))

all:		folders make_libs $(NAME)

folders:
	mkdir -p obj/ obj/utils/ obj/parse/ obj/console/ obj/free_utils/ obj/draw/ obj/ray/

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
