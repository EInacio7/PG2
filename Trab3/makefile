CFLAGS = -g -std=c99 -c 
LFLAGS = -g

app: app.o file.o fileTerm.o strCol.o aref.o scanTree.o
	gcc $(LFLAGS) app.o file.o fileTerm.o strCol.o aref.o scanTree.o
	
app.o: app.c aref.h file.h strCol.h scanTree.h
	gcc $(CFLAGS) app.c 
	
file.o: file.c file.h strCol.h
	gcc $(CFLAGS) file.c 
	
fileTerm.o: fileTerm.c strCol.h 
	gcc $(CFLAGS) fileTerm.c
	
strCol.o: strCol.c strCol.h
	gcc $(CFLAGS) strCol.c
	
aref.o: aref.c aref.h strCol.h
	gcc $(CFLAGS) aref.c 
	
scanTree.o: scanTree.c scanTree.h file.h strCol.h aref.h
	gcc $(CFLAGS) scanTree.c 
	
binTree.o: binTree.c binTree.h aref.h file.h
	gcc $(CFLAGS) binTree.c 

clean:
	rm -rf *.o
