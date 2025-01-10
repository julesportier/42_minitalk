CC := cc
CFLAGS := -Wall -Werror -Wextra

SERVER := server
CLIENT := client
NAME := $(SERVER)\
		$(CLIENT)

#HEADER := minitalk.h

#SRC := server.c\
#	   client.c
SRC_SRV := server.c
SRC_CLI := client.c

#OBJ := $(SRC:%.c=%.o)
OBJ_SRV := $(SRC_SRV:%.c=%.o)
OBJ_CLI := $(SRC_CLI:%.c=%.o)

all: $(NAME)
srv: $(SERVER)
cli: $(CLIENT)

$(SERVER): $(OBJ_SRV)
	$(CC) $(CFLAGS) $< -o $@
$(CLIENT): $(OBJ_CLI)
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SRV) $(OBJ_CLI)
#cleansrv:
#	rm -f $(OBJ_SRV)
#cleancli:
#	rm -f $(OBJ_CLI)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all srv cli clean fclean re
