defaul: sopt_olsTestQuadratic

stochasticTools.o: stochasticTools.cpp stochasticTools.h makefile
	g++ -std=c++11 -c stochasticTools.cpp -framework accelerate

seqols.o: seqols.cpp seqols.h  makefile
	g++ -std=c++11 -c seqols.cpp -framework accelerate

soptolsTestQuadratic.o: soptolsTestQuadratic.cpp seqols.h stochasticTools.h soptolsTestQuadratic.h  makefile
	g++ -std=c++11 -c soptolsTestQuadratic.cpp -framework accelerate

sopt_olsTestQuadratic: soptolsTestQuadratic.o seqols.o stochasticTools.o
	g++ -std=c++11 -o sopt_olsTestQuadratic soptolsTestQuadratic.o seqols.o stochasticTools.o -framework accelerate

