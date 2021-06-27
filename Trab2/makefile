CFLAGS=-std=c99 -W -Wall
all: app
app: app.o fileManip.o fileTerm.o sharedStringManager.o aref.o scanTree.o
	gcc -o app app.o fileManip.o fileTerm.o sharedStringManager.o aref.o scanTree.o
app.o: app.c strCol.h aref.h scanTree.h
	gcc $(CFLAGS) -o app.o -c app.c 
fileManip.o: fileManip.c file.h strCol.h
	gcc $(CFLAGS) -o fileManip.o -c fileManip.c
fileTerm.o: fileTerm.c strCol.h 
	gcc $(CFLAGS) -o fileTerm.o -c fileTerm.c
sharedStringManager.o: sharedStringManager.c strCol.h
	gcc $(CFLAGS) -o sharedStringManager.o -c sharedStringManager.c
aref.o: aref.c  aref.h
	gcc $(CFLAGS) -o aref.o -c aref.c
scanTree.o: scanTree.c strCol.h file.h aref.h
	gcc $(CFLAGS) -o scanTree.o -c scanTree.c
clean:
	rm -rf *.o app
