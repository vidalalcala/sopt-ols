defaul: seq_olsTest

MonteCarloTools.o: MonteCarloTools.cpp MonteCarloTools.h makefile
	g++ -std=c++11 -c MonteCarloTools.cpp -framework accelerate

seqols.o: seqols.cpp seqols.h MonteCarloTools.h makefile
	g++ -std=c++11 -c seqols.cpp -framework accelerate

seqolsTest.o: seqolsTest.cpp seqolsTest.h seqols.h MonteCarloTools.h makefile
	g++ -std=c++11 -c seqolsTest.cpp -framework accelerate

seq_olsTest: seqolsTest.o seqols.o MonteCarloTools.o
	g++ -std=c++11 -o seq_olsTest seqolsTest.o seqols.o MonteCarloTools.o -framework accelerate

