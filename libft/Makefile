# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 17:33:15 by kbatz             #+#    #+#              #
#    Updated: 2019/09/13 22:39:25 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

# **************************************************************************** #

HDRDIR	= ./
SRCDIR	= src/
OBJDIR	= .obj/

# **************************************************************************** #

SRC		= $(patsubst $(SRCDIR)%,%,$(wildcard $(SRCDIR)*.c))
HDR 	= $(wildcard $(HDRDIR)*.h)
OBJ		= $(SRC:%.c=%.o)
IFLAG	= $(addprefix -I,$(HDRDIR))
CFLAG	= -Wall -Wextra -Werror
CC		= gcc

# **************************************************************************** #

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	ar rc $(NAME) $(addprefix $(OBJDIR),$(OBJ))
	ranlib $(NAME)

$(OBJ): %.o: %.c $(HDR)
	$(CC) $(CFLAG) $(IFLAG) -o $(OBJDIR)$@ -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
