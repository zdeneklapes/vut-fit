##
# Makefile
# Řešení IJC-DU2, příklad 2), 15.4.2021
# Autor: Zdenek Lapes <xlapes02>, FIT
# Přeloženo: gcc 9.3.0

CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra
CFLAGS += -O2
#CFLAGS += -pg # -no-pie -fno-builtin # no POS indep code ; don;t replace funcs with inlines
#CFLAGS += -DHASHTEST
#CFLAGS += -DMOVETEST

#CXX = g++
#CXXFLAGS = -g -std=c++11 -O2

LIBS_SRC = htab_bucket_count htab_clear htab_erase htab_find htab_for_each htab_free htab_hash_function htab_init htab_lookup_add htab_move htab_size
LIBS_OBJ_O := $(LIBS_SRC:=.o)
LIBS_OBJ_C := $(LIBS_SRC:=.c)
DEPS = htab.h htab_define.h
PATH_LIB = -L. -lhtab
#PATH_LIB += -Wl,-rpath,.

RM = rm -f

###############################################################################
### ALL ###
###############################################################################
all: tail wordcount wordcount-dynamic

###############################################################################
### COMPILE ###
###############################################################################
### TAIL ###
tail: tail.c

### WORDCOUNT ###
wordcount: wordcount.o libhtab.a io.o
	$(CC) $(CFLAGS) $(PATH_LIB) -static $^ -o $@

### WORDCOUNT-DYNAMIC ###
wordcount-dynamic: wordcount.o libhtab.so io.o
	$(CC) $(CFLAGS) $(PATH_LIB) $^ -o $@

### WORDCOUNT.o ###
wordcount.o: wordcount.c io.o $(DEPS)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

### C++ (predloha) ###
#wordcount-: wordcount-.cc

###############################################################################
### LIBS ###
###############################################################################
### ARCHIVE FILE ###
libhtab.a: $(LIBS_OBJ_O)
	ar rcs $@ $(LIBS_OBJ_O)

### SHARED OBJECT FILE ###
libhtab.so: $(LIBS_OBJ_O)
	$(CC) $(CFLAGS) -shared $(LIBS_OBJ_O) -fPIC -o $@

### IO.O ###
io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

### LIBS FNS ###
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

###############################################################################
### COMMAND ##
###############################################################################
### ZIP ###
.PHONY: zip
zip:
	zip xlapes02.zip *.c *.h Makefile

### VALGRIND ###
.PHONY: valgrind-tail
valgrind-tail: tail
	valgrind --leak-check=full -v --track-origins=yes ./tail data/web2

.PHONY: valgrind-wordcount
valgrind-wordcount: wordcount
	cat data/web2 | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./wordcount

.PHONY: valgrind-wordcount-dynamic
valgrind-wordcount-dynamic: wordcount-dynamic
	cat data/web2 | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./wordcount-dynamic

### SIZE ###
.PHONY: size
size: wordcount wordcount-dynamic
	size wordcount
	size wordcount-dynamic

### CLEAN ###
.PHONY: clean
clean:
	$(RM) *.o
	$(RM) libhtab.a
	$(RM) libhtab.so
	$(RM) tail
	$(RM) wordcount
	$(RM) wordcount-dynamic
	$(RM) -r xlapes02.zip

#$(RM) wordcount-
