# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/03 13:50:56 by ddela-cr          #+#    #+#              #
#    Updated: 2016/08/09 14:02:02 by ddela-cr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

NAMEBASE    =   $(shell basename $(NAME))

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRCDIR		=	srcs/

OBJDIR		=	objs/

INCDIR		=	includes/

LIBFT_DIR	=	libft/

LIBFT_LIB	=	libft/libft.a

LIBFTPRINTF	=	libftprintf/libftprintf.a

SRCBASE		=	\
				ants.c														\
				error.c														\
				get_data.c													\
				link.c														\
				main.c														\
				print.c														\
				rooms.c														\
				utils.c

INCBASE		=	\
				ft_printf.h													\
				lem_in.h													\
				libft.h

SRCS		=	$(addprefix $(SRCDIR), $(SRCBASE))

INCS		=	$(addprefix $(INCDIR), $(INCBASE))

OBJS		=	$(addprefix $(OBJDIR), $(SRCBASE:.c=.o))

.SILENT:

all:		$(NAME)
	echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K"

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(LIBFTPRINTF)
	echo -en "\r\033[38;5;22m☑️  MAKE   $(NAMEBASE)\033[0m\033[K"
	echo "\r\033[38;5;184m👥  GROUP MEMBER(S):\033[0m\033[K"
	echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K"

$(OBJS):	$(SRCS) $(INCS)
	printf "\r\033[38;5;11m⌛  MAKE   $(NAMEBASE) please wait ...\033[0m\033[K"
	mkdir -p $(OBJDIR)
	make -C $(LIBFT_DIR)
	(cd $(OBJDIR);															\
	$(CC) $(FLAGS) -c $(addprefix ../, $(SRCS))								\
	-I $(addprefix ../, $(LIBFT_DIR)/$(INCDIR))								\
	-I $(addprefix ../, $(INCDIR)))

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAMEBASE) please wait ...\033[0m\033[K"
	make -C $(LIBFT_DIR) clean
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo -en "\r\033[38;5;124m🔘  CLEAN  $(NAMEBASE)\033[0m\033[K";		\
	else																	\
		printf "\r";														\
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAMEBASE) please wait ...\033[0m\033[K"
	make -C $(LIBFT_DIR) fclean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\r\033[38;5;124m🔘  FCLEAN $(NAMEBASE)\033[0m\033[K";		\
	else																	\
		printf "\r";														\
	fi

re:			fclean all

.PHONY:		fclean clean re
