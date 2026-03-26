NAME	= malloc

SRCS	= malloc.c

OPATH	= obj/

OBJS	= ${addprefix ${OPATH}, ${SRCS:.c=.o}}

DEPS	= ${addprefix ${OPATH}, ${SRCS:.c=.d}}

RM		= rm -rf

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

all:		dir ${NAME}

dir:
				mkdir -p obj

obj/%.o:	src/%.c Makefile includes/malloc.h
				${CC} ${CFLAGS} -c $< -MMD -o $@

${NAME}:	${OBJS} dir
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

test:		${NAME}
				./${NAME} ${NAME} > a
				nm ${NAME} > b
				diff a b

clean:
				${RM} ${OPATH}

fclean:		clean
				${RM} ${NAME} a b

re:			fclean all

.PHONY:		all clean fclean re
