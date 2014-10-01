
all:
	g++ -Wall -o secvential_bin secvential/main.cpp
	g++ -Wall -o secv_opt_bin secv_opt/main.cpp
	g++ -Wall -fopenmp -o parallel_bin parallel/main.cpp


clean:
	rm parallel_bin
	rm secvential_bin
	rm secv_opt_bin
