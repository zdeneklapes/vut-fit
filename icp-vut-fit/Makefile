LOGIN=xbinov00-xlapes02
TARGET = diagram_editor
RM=rm -rfd

all: compile

compile:
	qmake -o qMakefile icp-vut-fit.pro
	make -f qMakefile

run: compile
	./$(TARGET)

doxygen:
	doxygen doc/Doxyfile

pack:
	zip -r $(LOGIN).zip *.pro doc/* examples/* src/* Makefile README.txt

clean:
	make -f qMakefile clean
	$(RM) $(TARGET)
	$(RM) qMakefile
	$(RM) .qmake.stash
	$(RM) doc/html
	$(RM) doc/latex
