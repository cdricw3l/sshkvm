CC		:= 	gcc
GFLAGS	:= 	
NAME	:= 	vm_auto
SRCS	:= 	getnextline/get_next_line.c \
			getnextline/get_next_line_utils.c \
			srcs/dispatcher.c \
			srcs/ssh_identification.c \
			srcs/db_managment.c
SRCS_SQ	:= srcs/db_managment.c
COM := default commentaire
SRCS_OBJS:= $(SRCS:.c=.o)
SQL_OBJS:= $(SRCS_SQ:.c=.o)
LIB_FT	:= -Llibft_v2 -lft
LIB_SQL := -lsqlite3

%.o:%.c
	$(CC) $(GFLAGS) -c  $^ -o $@


$(NAME): $(SRCS_OBJS)
	$(CC) $(GFLAGS) $(SRCS_OBJS) $(LIB_FT) $(LIB_SQL) -o $(NAME)

sq: $(SQL_OBJS)
	$(CC) $(GFLAGS) $(SQL_OBJS) $(LIB_FT) $(LIB_SQL) -o sql_test

r: 
	@./$(NAME)

clean:
	rm -f $(SRCS_OBJS) $(SQL_OBJS)
	rm -f *.log

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

git: fclean
	cd libft_v2 && make clean && cd ..
	git add .
	git commit -m $(COM)
	git push origin $(shell git branch --show-current)