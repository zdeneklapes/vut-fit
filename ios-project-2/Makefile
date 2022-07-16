###############################################################################
# Makefile
# Řešení IOS_PROJEKT 2, 29.4.2021
# Autor: Zdenek Lapes <xlapes02>, FIT
# Přeloženo: gcc 9.3.0
###############################################################################
##
# @file Makefile
# @brief Makefile + shell SEM, SHM and Process commands
# @author Zdenek Lapes <xlapes02>, FIT
#


###############################################################################
###                             MAKEFILE VARIABLES                          ###
###############################################################################
PROGRAM = proj2

CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -pedantic -pthread
#CFLAGS += -O0

RM = rm -f

###############################################################################
###                            PROGRAM COMPILING                            ###
###############################################################################
### ALL ###
all: $(PROGRAM)

### PROGRAM.(exe) - create exec. proj2 ###
$(PROGRAM): $(PROGRAM).o santa_problem.o arguments.o error.o helper.o processes.o shm.o sem.o
#here is default setting from make, which will do this: $(CC) $(CFLAGS) $^ -o $@

### PROGRAM.o - create all needed dependencies for exec. proj2 ###
%.o: %.c %h
#here is default setting from make, which will do this: $(CC) $(CFLAGS) -c $< -o $@
#and will do that for all modules which is given as dependencies in the exec. proj2

###############################################################################
###                                  DELETE                                 ###
###############################################################################
.PHONY: clean
clean:
	$(RM) *.o
	$(RM) $(PROGRAM)
	$(RM) -r xlapes02.zip

###############################################################################
###                                    RUN                                  ###
###############################################################################
.PHONY: run
run: $(PROGRAM)
	@$(MAKE) -s sem-clean
	@$(MAKE) -s shm-clean
	@$(MAKE) -s clean
	@$(MAKE) -s all
	./proj2 3 2 100 100

###############################################################################
###                                   ZIP                                   ###
###############################################################################
.PHONY: zip
zip:
	zip $(PROGRAM).zip *.c *.h Makefile





# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# # #   Below this line are only commands for easier                      # # #
# # #   CLEANING (SHM, SEM, PROC) CREATED BY MY PROGRAM                   # # #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
###############################################################################
###                                 CLEAN                                   ###
###############################################################################
### CLEAN ALL ###
clean-all:
	@$(MAKE) -s shm-clean
	@$(MAKE) -s sem-clean
	@$(MAKE) -s proc-clean
clean-all-linux:
	@$(MAKE) -s shm-clean-linux
	@$(MAKE) -s sem-clean-linux
	@$(MAKE) -s proc-clean
### SHM ###
shm-clean:
	ipcs -tm | grep "$$(whoami)" | awk '{print $$2};' | xargs -L1 -t ipcrm -m
### SHM LINUX ###
shm-clean-linux:
	ipcs -tm | grep "$$(whoami)" | awk '{print $$1};' | xargs -L1 -t ipcrm -m
### SEM ###
sem-clean:
	ipcs -ts | grep "$$(whoami)" | awk '{print $$2};' | xargs -L1 -t ipcrm -s
### SEM LINUX ###
sem-clean-linux:
	ipcs -ts | grep "$$(whoami)" | awk '{print $$1};' | xargs -L1 -t ipcrm -s
### FILES SEM ###
find-del:
	find /dev/shm -user "$$(whoami)" -delete
### PROCESSES ###
proc-clean:
	killall $(PROGRAM)

###############################################################################
###                                  FIND                                   ###
###############################################################################
### FIND ALL ###
find-all:
	@$(MAKE) -s shm-find
	@$(MAKE) -s sem-find
	@$(MAKE) -s proc-find
### SHM ###
shm-find:
	ipcs -tm | grep "$$(whoami)"
### SEM ###
sem-find:
	ipcs -ts | grep "$$(whoami)"
### FILES SHM ###
s-find:
	find /dev/shm -user "$$(whoami)"
### PROCESSES ###
proc-find:
	ps ux | grep "$(PROGRAM)"
