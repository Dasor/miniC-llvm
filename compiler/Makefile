CC=g++
#SANITY_FLAGS=-Wall -Wextra -fstack-protector-all -pedantic -Wno-unused -Wfloat-equal -Wshadow -Wpointer-arith -Wstrict-overflow=5 -Wformat=2
LFLAGS= -lfl -lLLVM

comp: Makefile main.o lexico.o sintactico.tab.o generacionCodigo.o llvmHelper.o
	$(CC) $(SANITY_FLAGS) main.o lexico.o sintactico.tab.o generacionCodigo.o llvmHelper.o $(LFLAGS) -o comp

main.o: main.cpp lexico.c sintactico.tab.hpp
	$(CC) $(SANITY_FLAGS) $(LFLAGS) -c main.cpp

lexico.o: lexico.cpp sintactico.tab.hpp
	$(CC) $(SANITY_FLAGS) -c lexico.cpp

lexico.cpp: lexico.l sintactico.tab.hpp
	flex -o lexico.cpp lexico.l

sintactico.tab.o: sintactico.tab.c sintactico.tab.h
	$(CC) $(SANITY_FLAGS) -c sintactico.tab.c

sintactico.tab.hpp sintactico.tab.cpp: sintactico.y
	bison -d sintactico.y

generacionCodigo.o: generacionCodigo.cpp generacionCodigo.hpp
	$(CC) $(SANITY_FLAGS) -c generacionCodigo.cpp

llvmHelper.o: llvmHelper.cpp llvmHelper.hpp
	$(CC)  $(SANITY_FLAGS) -c -lLLVM llvmHelper.cpp


debug: SANITY_FLAGS += -g
debug: comp

clean:
	rm *.o comp lexico.cpp sintactico.tab.h sintactico.tab.c
