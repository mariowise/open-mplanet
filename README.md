A gravitatory simulation of planets over OpenMP
===============================================

This works aims to simulate the solar system in `C language` and `OpenMP` routines. To achieve this, we build a quadtree in each frame and map the planets positions to a quadtree node. In the etc folder you'll find some examples for execution.


Running
-------

To run the program you'll need to compile the sources. You can run the `clean` option over make to achieve a clean complilation instance.

	cd open-mplanet
	make clean
	make

To run the simulation just type

	make run

Or you can indicate the input file to load the universe

	./bin/planet <path_to_input_file>


Bugs
----

The program it's not currently checking the integrity of the `input` file. So you'll need to indicate the right number of planets in the first line.