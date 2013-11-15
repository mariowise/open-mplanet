INCLUDE = -I src/
OUTPUT = ./bin/planet.run
LINKS = -fopenmp -lm -lX11

CFLAG = -c -w

main: build/main.o build/getpar.o build/point2D.o build/universe.o build/quadtree.o build/arraylist.o build/visu.o
	@ gcc -o $(OUTPUT) build/*.o $(LINKS)
	@ printf "Done here is the program "
	@ printf $(OUTPUT)
	@ printf "\n"

build/main.o: src/main.c
	@ printf "  cc src/main.c "
	@ gcc $(CFLAG) -o build/main.o src/main.c $(INCLUDE)
	@ printf "OK\n"

build/getpar.o: src/getpar.c
	@ printf "  cc src/getpar.c "
	@ gcc $(CFLAG) -o build/getpar.o src/getpar.c $(INCLUDE)
	@ printf "OK\n"

build/point2D.o: src/point2D.c
	@ printf "  cc src/point2D.c "
	@ gcc $(CFLAG) -o build/point2D.o src/point2D.c $(INCLUDE)
	@ printf "OK\n"

build/universe.o: src/universe.c
	@ printf "  cc src/universe.c "
	@ gcc $(CFLAG) -o build/universe.o src/universe.c $(INCLUDE)
	@ printf "OK\n"

build/quadtree.o: src/quadtree.c
	@ printf "  cc src/quadtree.c "
	@ gcc $(CFLAG) -o build/quadtree.o src/quadtree.c $(INCLUDE)
	@ printf "OK\n"

build/arraylist.o: src/arraylist.c
	@ printf "  cc src/arraylist.c "
	@ gcc $(CFLAG) -o build/arraylist.o src/arraylist.c $(INCLUDE)
	@ printf "OK\n"

build/visu.o: src/visu.c
	@ printf "  cc src/visu.c "
	@ gcc $(CFLAG) -o build/visu.o src/visu.c $(INCLUDE)
	@ printf "OK\n"

clean:
	@ clear
	@ echo "Cleanning"
	@ rm -r build/*.o
	@ rm -r bin/*.run

run:
	@ clear
	@ $(OUTPUT) -i etc/input.dat -o output.dat -T 4.0E+12 -t 10000 -h 4

me: clean main run
