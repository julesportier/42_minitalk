CC := cc
CFLAGS := -Wall -Werror -Wextra

SERVER := server
CLIENT := client
NAME := $(SERVER)\
		$(CLIENT)

#HEADER := minitalk.h

SRC_SRV := server.c
SRC_CLI := client.c

#OBJ := $(SRC:%.c=%.o)
OBJ_SRV := $(SRC_SRV:%.c=%.o)
OBJ_CLI := $(SRC_CLI:%.c=%.o)

#FT_PRINTF_DIR := ft_printf/
LIB := ftprintf
LIB_DIR := lib/ft_printf/

all: lib $(NAME)
srv: lib $(SERVER)
cli: lib $(CLIENT)
lib:
	make -C $(LIB_DIR)

$(SERVER): $(OBJ_SRV)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -l$(LIB)
$(CLIENT): $(OBJ_CLI)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -l$(LIB)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LIB_DIR)

clean:
	rm -f $(OBJ_SRV) $(OBJ_CLI)
	make clean -C $(LIB_DIR)
#cleansrv:
#	rm -f $(OBJ_SRV)
#cleancli:
#	rm -f $(OBJ_CLI)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all srv cli lib clean fclean re
