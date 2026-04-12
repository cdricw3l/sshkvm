CC		:= 	gcc
GFLAGS	:= 	#-Werror -Wall -Wextra
NAME	:= 	vm_auto
SRCS	:= 	srcs/getnextline/get_next_line.c \
			srcs/getnextline/get_next_line_utils.c \
			srcs/vm_auto.c 
COM := default commentaire
SRCS_OBJS:= $(SRCS:.c=.o)
LIB_FT	:= -Llibft_v2 -lft
LIB_SQL := -lsqlite3

%.o:%.c
	$(CC) $(GFLAGS) -c  $^ -o $@


$(NAME): $(SRCS_OBJS)
	$(CC) $(GFLAGS) $(SRCS_OBJS) $(LIB_FT) $(LIB_SQL) -o $(NAME)

r: 
	@./$(NAME)

clean:
	rm -f $(SRCS_OBJS)
	rm -f *.log

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

git:
	git add .
	git commit -m $(COM)
	git push origin $(shell git branch --show-current)