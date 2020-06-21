COPTIONS= -I include/

all:
	g++ -c src/Timer.cpp $(COPTIONS)
	g++ -c src/TimeWheel.cpp $(COPTIONS)
	g++ -c src/TimeHelper.cpp $(COPTIONS)
	g++ -c src/TimeDriver.cpp $(COPTIONS)
	g++ -c src/TimeDriverBySelect.cpp $(COPTIONS)
	ar -crsv lib.a Timer.o TimeWheel.o TimeHelper.o TimeDriver.o TimeDriverBySelect.o
	g++ samples/TimeDriverBySelect_unit_test.cpp -o main $(COPTIONS) ./lib.a -g

clear:
	rm *.o
	rm main