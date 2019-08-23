# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 17:33:15 by kbatz             #+#    #+#              #
#    Updated: 2019/03/03 16:59:17 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

# **************************************************************************** #

HDRDIR	=	include/
SRCDIR	=	src/
FLAG	=	-Wall -Wextra -Werror

# **************************************************************************** #

SRCS	=	$(wildcard $(SRCDIR)*)
HDR 	=	$(wildcard $(HDRDIR)*.h)
SRC		=

$(foreach S,$(SRCS), \
	$(eval SRC += $(wildcard $(S)/*.c)) \
)

OBJ		=	$(SRC:%.c=%.o)

# **************************************************************************** #

#ifeq "$(wildcard ./*.a)" ""
all: $(NAME)
#else
#all:
#endif

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): %.o: %.c $(HDR)
	gcc $(FLAG) -I$(HDRDIR) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC) $(HDR)
