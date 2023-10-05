CC = gcc
CFLAGS = -ansi -Wall -g
OBJS = analyze.o instructions.o machinecode.o assembler.o symbols.o macro.o utilities.o
HDRS = analyze.h instructions.h machinecode.h symbols.h utilities.h macro.h data.h

assembler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o assembler -lm

analyze.o: analyze.c $(HDRS)
	$(CC) -c $(CFLAGS) analyze.c -o analyze.o

instructions.o: instructions.c $(HDRS)
	$(CC) -c $(CFLAGS) instructions.c -o instructions.o

machinecode.o: machinecode.c $(HDRS)
	$(CC) -c $(CFLAGS) machinecode.c -o machinecode.o

assembler.o: assembler.c $(HDRS)
	$(CC) -c $(CFLAGS) assembler.c -o assembler.o

symbols.o: symbols.c $(HDRS)
	$(CC) -c $(CFLAGS) symbols.c -o symbols.o

macro.o: macro.c $(HDRS)
	$(CC) -c $(CFLAGS) macro.c -o macro.o

utilities.o: utilities.c $(HDRS)
	$(CC) -c $(CFLAGS) utilities.c -o utilities.o

clean:
	rm -f assembler $(OBJS)

