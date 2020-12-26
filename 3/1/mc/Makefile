CXX = gcc
CXXFLAGS = -lfl
PROJECT := wikipedia
TEMPLATE := $(PROJECT).l
SOURCES := lex.yy.c
BOLD = `tput bold`
GREEN = `tput setaf 2`
RESET = `tput sgr0`
IN := doc/cannae.txt
OUT := salida.txt

define make_source =
@echo "${GREEN}Creando el archivo $@ ...${RESET}"
flex $^
@echo "${GREEN}HECHO${RESET}"
endef
define compile = 
@echo "${GREEN}Generando el ejecutable $(PROJECT) ...${RESET}"
$(CXX) $(CXXFLAGS) -o $@ $^
@echo "${GREEN}HECHO${RESET}"
endef

all: help exec
.PHONY: ${SOURCES}

$(PROJECT): $(SOURCES)
	$(compile)

$(SOURCES): $(TEMPLATE)
	$(make_source)

clean:
	rm *.c
	rm ${PROJECT}
	-rm *.txt

exec: $(PROJECT)
	@echo "${GREEN}Ejecutando:"
	@echo "    Entrada: ${RESET}${IN}"
	@echo "    ${GREEN}Salida: ${RESET}${OUT}"
	./$(PROJECT) $(IN) $(OUT)

help:
	@echo "Posibles opciones:"
	@echo "		${BOLD}IN=<file>${RESET}	\
	Cambia el fichero a procesar por <file>"
	@echo "		${BOLD}OUT=<file>${RESET}	\
	Cambia el fichero de salida a <file>"
	@echo "		${BOLD}clean${RESET}	\
	Borra el ejecutable y el generado por la plantilla"
	@echo "${GREEN}Archivos de ejemplo:${RESET}"
	@ls doc/ -1