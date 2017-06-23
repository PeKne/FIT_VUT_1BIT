ME=proj3
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic -g -DNDEBUG

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -lm -o $(NAME)

clean:
	rm -f $(NAME) $(NAME).o output8 output20 output13 output1

run:
	rm -f output8 output20 output13 output1

	./$(NAME) input 8 > output8

	./$(NAME) input 20 > output20

	./$(NAME) input 13 > output13

	./$(NAME) input > output1

	diff output8 pattern8

	diff output20 pattern20

	diff output13 pattern13

	diff output1 pattern1




