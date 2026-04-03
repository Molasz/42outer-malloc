ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so
LINK_NAME	= libft_malloc.so

SRCS_FILES	= malloc.c \
				free.c \
				realloc.c \
				zones.c \
				blocks.c \
				sys_calls.c \
				utils.c \
				show_alloc_mem.c

TEST_FILES	= basic.c \
				complete.c \
				stress.c \

INC_FILES	= malloc.h types.h

SPATH		= src/
OPATH		= obj/
IPATH		= includes/
TPATH		= test/
BPATH		= bin/

SRCS		= $(addprefix $(SPATH), $(SRCS_FILES))
OBJS		= $(addprefix $(OPATH), $(SRCS_FILES:.c=.o))
DEPS		= $(addprefix $(OPATH), $(SRCS_FILES:.c=.d))
INCS		= $(addprefix $(IPATH), $(INC_FILES))
TSTS		= $(addprefix $(TPATH), $(TEST_FILES))
TSTB		= $(addprefix $(BPATH), $(TEST_FILES:.c=_test))

RM			= rm -rf
CC			= gcc
CFLAGS      = -Wall -Wextra -Werror -fPIC -Iincludes

all:        dir $(NAME)

dir:
	@mkdir -p $(OPATH)
	@mkdir -p $(BPATH)

$(OPATH)%.o:	$(SPATH)%.c Makefile $(INCS)
	$(CC) $(CFLAGS) -c $< -MMD -o $@

$(BPATH)%_test:	$(TPATH)%.c $(NAME)
	$(CC) $(CFLAGS) $< -L. -lft_malloc -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -shared $(OBJS) -o $(NAME)
	ln -sf $(NAME) $(LINK_NAME)

run: all $(TSTB)
	@for t in $(TSTB); do \
		echo "--- $$t ---"; \
		LD_LIBRARY_PATH=. $$t; \
		echo ""; \
	done

test: all
	./test/test_malloc.sh

clean:
	$(RM) $(OPATH) ./bin

fclean:     clean
	$(RM) $(NAME) $(LINK_NAME)

re:         fclean all

.PHONY:     all clean fclean re dir
