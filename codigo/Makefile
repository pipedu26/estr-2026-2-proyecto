# Compilación del proyecto.
CC       = g++
CFLAGS   = -Wall -Wextra -O2
PROGRAMA = proyecto
MEDIDOR  = medicion
HEADERS  = inventario_lista.h inventario_hash.h inventario_map.h

all: $(PROGRAMA) proyecto_hash proyecto_map $(MEDIDOR)

$(PROGRAMA): principal.cpp inventario_lista.h
	$(CC) $(CFLAGS) principal.cpp -o $(PROGRAMA)

proyecto_hash: principal.cpp inventario_hash.h
	$(CC) $(CFLAGS) -DUSAR_HASH principal.cpp -o proyecto_hash

proyecto_map: principal.cpp inventario_map.h
	$(CC) $(CFLAGS) -DUSAR_MAP principal.cpp -o proyecto_map

$(MEDIDOR): medicion.cpp $(HEADERS)
	$(CC) $(CFLAGS) medicion.cpp -o $(MEDIDOR)

# Corre cada entrada de ../datos/ con las tres estructuras
pruebas: $(PROGRAMA) proyecto_hash proyecto_map
	@for programa in $(PROGRAMA) proyecto_hash proyecto_map; do \
	  echo "== $$programa"; \
	  for entrada in ../datos/*.in; do \
	    esperada="$${entrada%.in}.out"; \
	    if [ -f "$$esperada" ]; then \
	      ./$$programa < "$$entrada" > /tmp/salida.txt; \
	      if diff -q /tmp/salida.txt "$$esperada" > /dev/null; then \
	        echo "  OK   $$(basename $$entrada)"; \
	      else \
	        echo "  FALLA $$(basename $$entrada)"; \
	        diff /tmp/salida.txt "$$esperada" | head -5; \
	      fi; \
	    fi; \
	  done; \
	done

# Corre las mediciones
medir: $(MEDIDOR)
	./$(MEDIDOR) > ../datos/resultados.csv

clean:
	rm -f $(PROGRAMA) proyecto_hash proyecto_map $(MEDIDOR) *.o

.PHONY: all pruebas medir clean
