all: Programma

Programma: main.o attivita.o mergesortList.o
	gcc main.o attivita.o mergesortList.o -o Programma

main.o: main.c attivita.h
	gcc -c main.c

attivita.o: attivita.c attivita.h mergesortList.h
	gcc -c attivita.c

mergesortList.o: mergesortList.c mergesortList.h attivita.h
	gcc -c mergesortList.c

clean:
	del /Q *.o Programma.exe