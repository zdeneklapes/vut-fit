LOGIN=xlapes02
EXEC=queens.py
REQ=requirements.txt
QUEENS=queens
PWD := $(shell pwd)
N=4

# idk why minisat returns err code 10
run: $(EXEC)
	source venv/bin/activate && \
	python3 $(EXEC) $(N) > $(QUEENS).in && \
	minisat $(QUEENS).in $(QUEENS).out || \
	deactivate

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
install:
	python3 -m venv venv && \
	source venv/bin/activate && \
	pip3 install -r $(REQ) && \
	deactivate
endif
ifeq ($(UNAME), Linux)
install:
	python3 -m venv venv
	source venv/bin/activate
	pip install -r $(REQ)
	deactivate
endif

requirements:
	pip3 freeze > $(REQ)

zip: $(EXEC) README.md $(REQ) Makefile
	zip $(LOGIN).zip $^

unzip:
	unzip $(LOGIN).zip -d $(LOGIN)

make clean:
	rm -f $(QUEENS).{in,out} *.zip
	rm -rfd venv
	rm -rfd .DS_Store

scp:
	scp $(PWD)/$(LOGIN).zip $(LOGIN)@eva.fit.vutbr.cz://homes/eva/xl/$(LOGIN)/


#hey: one two
#	echo $@ # Outputs "hey", since this is the first target
#	echo $? # Outputs all prerequisites newer than the target
#	echo $^ # Outputs all prerequisites
