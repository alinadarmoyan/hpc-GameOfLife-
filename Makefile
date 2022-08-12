CC = mpic++
CFLAGS=	-O3 -fopenmp
LFLAGS=	-lm

# System independent definitions

#MF=	Makefile

EXE=	main

INC= main.h program.h

SRC= main.cpp program.cpp

#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .cpp .o

OBJ=	$(SRC:.cpp=.o)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(OBJ):	$(INC)

$(EXE):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)	

clean:
	rm -f $(OBJ) $(EXE) $(OUT) core *~
