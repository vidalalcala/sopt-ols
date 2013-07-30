defaul: seq_olsTest

mtrand.o: mtrand.cpp mtrand.h makefile
	g++ -c mtrand.cpp

MonteCarloTools.o: MonteCarloTools.cpp MonteCarloTools.h mtrand.h makefile
	g++ -c MonteCarloTools.cpp -framework accelerate

seqols.o: seqols.cpp seqols.h MonteCarloTools.h mtrand.h makefile
	g++ -c seqols.cpp -framework accelerate

seqolsTest.o: seqolsTest.cpp seqolsTest.h seqols.h MonteCarloTools.h mtrand.h makefile
	g++ -c seqolsTest.cpp -framework accelerate

seq_olsTest: seqolsTest.o seqols.o MonteCarloTools.o mtrand.o
	g++ -o seq_olsTest seqolsTest.o seqols.o MonteCarloTools.o mtrand.o -framework accelerate

