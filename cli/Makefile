.PHONY: all clean
CC = gcc
FLAGS = -Wall -Werror -Wextra -pedantic -g -pthread
CRY = -I../crypto -L../crypto -lhblk_crypto
BCHAIN = -I../blockchain/v0.3 -L../blockchain/v0.3 -lhblk_blockchain
LINKER = -lssl -lcrypto

NAME = cli
SRC = $(wildcard *.c)


#default
all:
	$(CC) $(FLAGS) $(CRY) $(SRC) $(LINKER) -o $(NAME)


#clean
clean:
	rm -f $(NAME)
