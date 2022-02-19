all:	cliente	balcao medico clean

cliente: cliente.o
	gcc cliente.o -o cliente

cliente.o: cliente.c cliente.h
	gcc cliente.c -c

balcao: balcao.o
	gcc balcao.o -o balcao -lpthread

balcao.o: balcao.c balcao.h
	gcc balcao.c -c

medico: medico.o
	gcc medico.o -o medico

medico.o: medico.c medico.h
	gcc medico.c -c

clean:
	rm balc rm balcmed rm espec* rm utente*
