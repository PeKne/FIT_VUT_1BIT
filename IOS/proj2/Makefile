#AUTHOR : PETR KNETL
### MAKEFILE K SESTAVENI DRUHEHO PROJEKTU IOS ###

CC= gcc
CFLAGS= -std=gnu99 -Wall -Wextra -pedantic #TODO: chybi parametr -Werror
NAME=proj2

make:
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME)
zip:
	zip $(NAME) *.c *.h Makefile
clean:
	rm -f $(NAME) *.zip
