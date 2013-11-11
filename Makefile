INCLUDE = -I src/
OUTPUT = ./bin/planet.run
LINKS = -fopenmp

CFLAG = -c -w

main: build/main.o
	@ printf "Building modules..."
	@ gcc -o $(OUTPUT) build/*.o $(LINKS)
	@ printf "[OK]\nDone here is the program "
	@ printf $(OUTPUT)
	@ printf "\n"

build/main.o: src/main.c
	@ echo "  cc src/main.c"
	@ gcc $(CFLAG) -o build/main.o src/main.c $(INCLUDE) $(LINKS)

clean:
	@ clear
	@ echo "Cleanning"
	@ rm -r build/*.o
	@ rm -r bin/*.run