CC=gcc
SANITY_FLAGS=-Wall -Wextra -fstack-protector-all -pedantic -Wno-unused -Wfloat-equal -Wshadow -Wpointer-arith -Wstrict-overflow=5 -Wformat=2
LFLAGS= -lfl

comp: Makefile main.o lexico.o sintactico.tab.o listaSimbolos.o listaCodigo.o generacionCodigo.o
	$(CC) $(SANITY_FLAGS) main.o lexico.o sintactico.tab.o listaSimbolos.o listaCodigo.o generacionCodigo.o $(LFLAGS) -o comp

main.o: main.c lexico.c sintactico.tab.h
	$(CC) $(SANITY_FLAGS) $(LFLAGS) -c main.c

lexico.o: lexico.c sintactico.tab.h
	$(CC) $(SANITY_FLAGS) -c lexico.c

lexico.c: lexico.l sintactico.tab.h
	flex lexico.l

sintactico.tab.o: sintactico.tab.c sintactico.tab.h
	$(CC) $(SANITY_FLAGS) -c sintactico.tab.c

sintactico.tab.h sintactico.tab.c: sintactico.y
	bison -d $(BISON_DEBUG) sintactico.y

listaSimbolos.o: listaSimbolos.c listaSimbolos.h
	$(CC) $(SANITY_FLAGS) -c listaSimbolos.c

generacionCodigo.o: generacionCodigo.c generacionCodigo.h
	$(CC) $(SANITY_FLAGS) -c generacionCodigo.c

listaCodigo.o: listaCodigo.c listaCodigo.h
	$(CC) $(SANITY_FLAGS) -c listaCodigo.c


debug: SANITY_FLAGS += -g
debug: BISON_DEBUG += -v
debug: comp

clean:
	rm *.o comp lexico.c sintactico.tab.h sintactico.tab.c prog.ll
