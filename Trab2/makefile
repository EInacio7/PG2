CFLAGS=-std=c99 -W -Wall
all: app
app: app.o fileManip.o fileTerm.o sharedStringManager.o
	gcc -o app app.o fileManip.o fileTerm.o sharedStringManager.o
app.o: app.c 
	gcc $(CFLAGS) -o app.o -c app.c 
fileManip.o: fileManip.c file.h strCol.h
	gcc $(CFLAGS) -o fileManip.o -c fileManip.c
fileTerm.o: fileTerm.c strCol.h 
	gcc $(CFLAGS) -o fileTerm.o -c fileTerm.c
sharedStringManager.o: sharedStringManager.c strCol.h
	gcc $(CFLAGS) -o sharedStringManager.o -c sharedStringManager.c
clean:
	rm -rf *.o app
