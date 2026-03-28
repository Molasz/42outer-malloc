ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so
LINK_NAME	= libft_malloc.so

SRCS_FILES	= malloc.c free.c realloc.c
INC_FILES	= malloc.h types.h

SPATH		= src/
OPATH		= obj/
IPATH		= includes/

SRCS		= $(addprefix $(SPATH), $(SRCS_FILES))
OBJS		= $(addprefix $(OPATH), $(SRCS_FILES:.c=.o))
DEPS		= $(addprefix $(OPATH), $(SRCS_FILES:.c=.d))
INCS		= $(addprefix $(IPATH), $(INC_FILES))

RM			= rm -rf
CC			= gcc
CFLAGS      = -Wall -Wextra -Werror -fPIC -Iincludes

all:        dir $(NAME)

dir:
	mkdir -p $(OPATH)

$(OPATH)%.o:	$(SPATH)%.c Makefile $(INCS)
	$(CC) $(CFLAGS) -c $< -MMD -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -shared $(OBJS) -o $(NAME)
	ln -sf $(NAME) $(LINK_NAME)

test: all
	@chmod +x test_malloc.sh
	@./test_malloc.sh

clean:
	$(RM) $(OPATH)

fclean:     clean
	$(RM) $(NAME) $(LINK_NAME)

re:         fclean all

.PHONY:     all clean fclean re dir
