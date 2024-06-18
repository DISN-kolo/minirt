# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 11:52:48 by akozin            #+#    #+#              #
#    Updated: 2024/06/18 17:42:26 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		 ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		 ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		 ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		 ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		 ft_strlen.c ft_strslen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		 ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		 ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		 ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
		 ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
		 ft_strjoin3.c

OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(OFILES): %.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

-include $(DFILES)

clean:
	$(RM) $(OFILES) $(DFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
