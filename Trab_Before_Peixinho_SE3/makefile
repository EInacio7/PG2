CFLAGS=-std=c99 -W -Wall
all: app
app: app.o tag.o setdata.o listfiles.o lists.o trees.o strset.o
	gcc -o app app.o tag.o setdata.o listfiles.o lists.o trees.o strset.o
app.o: app.c listfiles.h
	gcc $(CFLAGS) -o app.o -c app.c 
tag.o: tag.c tagtype.h tag.h strset.h
	gcc $(CFLAGS) -o tag.o -c tag.c
setdata.o: setdata.c setdata.h tagtype.h tag.h trees.h lists.h
	gcc $(CFLAGS) -o setdata.o -c setdata.c
listfiles.o: listfiles.c tagtype.h tag.h setdata.h strset.h
	gcc $(CFLAGS) -o listfiles.o -c listfiles.c
trees.o: trees.c trees.h lists.h tagtype.h
	gcc $(CFLAGS) -o trees.o -c trees.c
lists.o: lists.c lists.h tagtype.h
	gcc $(CFLAGS) -o lists.o -c lists.c
strset.o: strset.c strset.h
	gcc $(CFLAGS) -o strset.o -c strset.c
clean:
	rm -rf *.o app