CC = cc
SRC = nfck.c
OUT = nfck
FLAGS = -Wall -pedantic -std=c11

nfck:
	$(CC) $(FLAGS) $(SRC) -o $(OUT)
