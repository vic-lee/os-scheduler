
CXX = g++
CXXFLAGS = -Wall -std=c++11
MODULES = process utils/ utils/randnum scheduler process

exec: main.o compproc.o printer.o process.o randnum.o scheduler.o statcalc.o util.o 
	$(CXX) $(CXXFLAGS) ../bin/*.o -o ../bin/exec 

process.o: process/process.cc process/process.h
	$(CXX) $(CXXFLAGS) -c process/process.cc -o ../bin/process.o

scheduler.o: scheduler/scheduler.cc scheduler/scheduler.h
	$(CXX) $(CXXFLAGS) -c scheduler/scheduler.cc -o ../bin/scheduler.o

compproc.o: utils/compproc.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/compproc.cc -o ../bin/compproc.o

printer.o: utils/printer.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/printer.cc -o ../bin/printer.o

statcalc.o: utils/statcalc.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/statcalc.cc -o ../bin/statcalc.o

util.o: utils/util.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/util.cc -o ../bin/util.o

randnum.o: utils/randnum/randnum.cc utils/randnum/randnum.h 
	$(CXX) $(CXXFLAGS) -c utils/randnum/randnum.cc -o ../bin/randnum.o

main.o: main.cc header.h 
	$(CXX) $(CXXFLAGS) -c main.cc -o ../bin/main.o

clean:
	rm ../bin/*o ../bin/exec
