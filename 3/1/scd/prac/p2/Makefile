# Compiler & flags
CXX=g++
CXXFLAGS=-std=c++11 -g -pthread

# Files
TEMPLATE_FILES=HoareMonitor.cpp Semaphore.cpp
P1:=fumadores
P2:=barberia
P1_SRC:=$(P1).cpp
P2_SRC:=$(P2).cpp

# Variables
define compile =
$(CXX) $(CXXFLAGS) -o $@ $< $(TEMPLATE_FILES)
endef

all: $(P1) $(P2)

$(P1): $(P1_SRC)
	$(compile)

$(P2): $(P2_SRC)
	$(compile)

clean:
	rm $(P1) $(P2)
