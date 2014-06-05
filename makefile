defaul: sopt_olsTestQuadratic

soptols.o: soptols.cpp soptols.h makefile
	$(CXX) -std=c++11 -c soptols.cpp -framework accelerate

stochasticTools.o: stochasticTools.cpp stochasticTools.h makefile
	$(CXX) -std=c++11 -c stochasticTools.cpp -framework accelerate

seqols.o: seqols.cpp seqols.h  makefile
	$(CXX) -std=c++11 -c seqols.cpp -framework accelerate

soptolsTestQuadratic.o: soptolsTestQuadratic.cpp seqols.h stochasticTools.h soptolsTestQuadratic.h  soptols.h makefile
	$(CXX) -std=c++11 -c soptolsTestQuadratic.cpp -framework accelerate

sopt_olsTestQuadratic: soptolsTestQuadratic.o seqols.o stochasticTools.o soptols.o
	$(CXX) -std=c++11 -o sopt_olsTestQuadratic soptolsTestQuadratic.o seqols.o stochasticTools.o soptols.o -framework accelerate

