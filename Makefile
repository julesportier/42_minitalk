CC := cc
CFLAGS := -Wall -Werror -Wextra

SERVER := server
CLIENT := client
NAME := $(SERVER)\
	$(CLIENT)

HEADER := minitalk.h

SRC_SRV := server.c
SRC_CLI := client.c
SRC_UTILS := bit_stream.c

#OBJ := $(SRC:%.c=%.o)
OBJ_SRV := $(SRC_SRV:%.c=%.o)
OBJ_CLI := $(SRC_CLI:%.c=%.o)
OBJ_UTILS := $(SRC_UTILS:%.c=%.o)

#FT_PRINTF_DIR := ft_printf/
LIBFT := ft
LIBFT_DIR := ./libft/

all: libft $(NAME)
srv: libft $(SERVER)
cli: libft $(CLIENT)
libft:
	make -C $(LIBFT_DIR)

$(SERVER): $(OBJ_SRV) $(OBJ_UTILS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -l$(LIBFT)

$(CLIENT): $(OBJ_CLI) $(OBJ_UTILS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -l$(LIBFT)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SRV) $(OBJ_CLI) $(OBJ_UTILS)
	make clean -C $(LIBFT_DIR)
#cleansrv:
#	rm -f $(OBJ_SRV)
#cleancli:
#	rm -f $(OBJ_CLI)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all srv cli libft clean fclean re
