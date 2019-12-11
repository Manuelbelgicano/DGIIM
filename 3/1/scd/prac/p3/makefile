RUN:=prodcons
TIMES:=10
SRC:=$(RUN).cpp
EXECUTABLE:=$(RUN)_exe

all: $(RUN)

$(RUN): $(EXECUTABLE)
	mpirun --oversubscribe -np $(TIMES) $<

$(EXECUTABLE): $(SRC)
	mpicxx -o $@ $<

clean:
	rm *_exe
