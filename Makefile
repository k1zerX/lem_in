# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/25 21:10:51 by kbatz             #+#    #+#              #
#    Updated: 2019/10/31 08:56:34 by kbatz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
LIB		=	libft

# **************************************************************************** #

SRCDIR	=	src/
OBJDIR	=	.obj/
HDRDIR	=	include/
TESTDIR	=	test/

# **************************************************************************** #

LIBDIR	=	$(addsuffix /,$(LIB))
SRC		=	avl_int_balance.c\
			avl_int_bfs.c\
			avl_int_find.c\
			avl_int_infix.c\
			avl_int_insert.c\
			avl_int_remove.c\
			avl_str_balance.c\
			avl_str_bfs.c\
			avl_str_find.c\
			avl_str_infix.c\
			avl_str_insert.c\
			avl_str_remove.c\
			ctnr_clear.c\
			ctnr_new.c\
			ctnr_pop_bot.c\
			ctnr_pop_top.c\
			ctnr_push_bot.c\
			ctnr_push_top.c\
			main.c\
			tools1.c\
			tools2.c\
			tools3.c\
			tools4.c\
			tools5.c\
			tools6.c\
			tools7.c\
			tools8.c\
			validation.c\
			validation2.c\
			validation3.c
OBJ		=	$(SRC:%.c=%.o)
HDR		=	$(wildcard $(HDRDIR)*.h)
TEST	=	$(patsubst $(TESTDIR)%,%,$(wildcard $(TESTDIR)*))
LFLAG	=	$(addprefix -L,$(LIBDIR)) $(addprefix -,$(patsubst lib%,l%,$(LIB)))
IFLAG	=	$(addprefix -I,$(HDRDIR)) $(addprefix -I,$(LIBDIR))
CFLAG	=	-Wall -Wextra -Werror
CC		=	gcc

# **************************************************************************** #

vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

# **************************************************************************** #

all: lib.all $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(addprefix $(OBJDIR), $(OBJ)) -o $(NAME) $(IFLAG) $(LFLAG)

$(OBJ): %.o: %.c $(HDR)
	$(CC) $(CFLAG) $(IFLAG) -c $< -o $(OBJDIR)$@

$(OBJDIR):
	mkdir $(OBJDIR)

clean: lib.fclean
	rm -Rf $(OBJDIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

lib%:
	$(foreach C,$(LIBDIR),\
		make -C $(C) $(patsubst lib.%,%,$@) \
	)

norm:
	norminette $(addprefix $(SRCDIR),$(SRC))
	norminette $(HDR)

g: $(OBJDIR) $(OBJ)
	$(CC) -g $(addprefix $(SRCDIR),$(SRC)) -o debug_$(NAME) $(IFLAG) $(LFLAG)

gclean:
	rm -Rf debug_$(NAME)
	rm -Rf debug_$(NAME).dSYM

t: all $(TEST)

$(TEST): %:
	@echo "--------------------------------------------------"
	@echo "| >>>>> TEST \""$@"\" START >>>>> |"
	@echo ""
	@./$(NAME) $(TESTDIR)$@
	@echo ""
	@echo "| <<<<< TEST \""$@"\" END <<<<< |"
	@echo "--------------------------------------------------"
