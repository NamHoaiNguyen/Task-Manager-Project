CC = gcc
CFLAGS = -I.
INC_FILES = info_sys.h
.PHONY: main info_sys.o main.o

%.o: %.c $(INC_FILES)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o info_sys.o
	$(CC) -o $@ $^ $(CFLAGS)

info_sys.o: info_sys.c 
	$(CC) -c $< $(CFLAGS)

main.o: main.c 
	$(CC) -c $< $(CFLAGS)
clean:
	@rm main main.o info_sys.o 
