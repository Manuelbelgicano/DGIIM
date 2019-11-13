# Compilador & flags
CXX=g++
CXXFLAGS=-std=c++11 -g -pthread

# Ficheros
TEMPLATE_FILES= Semaphore.cpp HoareMonitor.cpp
P1:=fumadores
P2:=barberia
P3:=prodcons
P1_SRC:=$(P1).cpp
P2_SRC:=$(P2).cpp
P3_SRC:=$(P3).cpp

# Variables
define compile =
$(CXX) $(CXXFLAGS) -o $@ $^ $(TEMPLATE_FILES)
endef

all: $(P1) $(P2) $(P3)

$(P1): $(P1_SRC)
	$(compile)

$(P2): $(P2_SRC)
	$(compile)

$(P3): $(P3_SRC)
	$(compile)

clean:
	rm $(P1) $(P2) $(P3)
