
CXX = g++
CXXFLAGS = -Wall -std=c++11

output: main.o compproc.o printer.o process.o randnum.o scheduler.o statcalc.o util.o 
	$(CXX) $(CXXFLAGS) *.o -o output 

process.o: process/process.cc process/process.h
	$(CXX) $(CXXFLAGS) -c process/process.cc

scheduler.o: scheduler/scheduler.cc scheduler/scheduler.h
	$(CXX) $(CXXFLAGS) -c scheduler/scheduler.cc

compproc.o: utils/compproc.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/compproc.cc

printer.o: utils/printer.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/printer.cc

statcalc.o: utils/statcalc.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/statcalc.cc

util.o: utils/util.cc utils/schedutil.h
	$(CXX) $(CXXFLAGS) -c utils/util.cc

randnum.o: utils/randnum/randnum.cc utils/randnum/randnum.h 
	$(CXX) $(CXXFLAGS) -c utils/randnum/randnum.cc

main.o: main.cc header.h 
	$(CXX) $(CXXFLAGS) -c main.cc 
