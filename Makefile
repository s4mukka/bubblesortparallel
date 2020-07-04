make: compile run
.PHONY: make
	
compile:
	g++ final_project.cpp -o project -fopenmp -O3

run:
	./project