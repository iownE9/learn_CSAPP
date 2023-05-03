CC = gcc
file = snooze
path = ../csapp

$(file): $(file).o $(path).o
	$(CC) $(file).o $(path).o -o $(file) 

$(file).o: $(file).c $(path).h
	$(CC) -c $(file).c -o $(file).o 

clean:
	rm -rf $(file) $(file).o

