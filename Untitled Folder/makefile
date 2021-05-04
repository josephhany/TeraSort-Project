include makefile.vars

$(BIN)/FINAL: $(OBJECTS)/CommandLineArguments.o $(OBJECTS)/TeraSortItem.o $(OBJECTS)/QuickSort.o $(OBJECTS)/Partition.o $(OBJECTS)/Partitioner.o  $(OBJECTS)/Mapper.o $(OBJECTS)/Reducer.o $(OBJECTS)/TeraSort.o $(OBJECTS)/parallel_terasort.o 
	g++ -std=c++11 -pthread $(INCLUDES) $(OBJECTS)/CommandLineArguments.o $(OBJECTS)/TeraSortItem.o $(OBJECTS)/QuickSort.o $(OBJECTS)/Partition.o $(OBJECTS)/Partitioner.o  $(OBJECTS)/Mapper.o $(OBJECTS)/Reducer.o $(OBJECTS)/TeraSort.o $(OBJECTS)/parallel_terasort.o  -o $(BIN)/FINAL

$(OBJECTS)/CommandLineArguments.o: $(SOURCES)/CommandLineArguments.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/CommandLineArguments.cpp -o $(OBJECTS)/CommandLineArguments.o

$(OBJECTS)/Mapper.o: $(SOURCES)/Mapper.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/Mapper.cpp -o $(OBJECTS)/Mapper.o

$(OBJECTS)/parallel_terasort.o: $(SOURCES)/parallel_terasort.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/parallel_terasort.cpp -o $(OBJECTS)/parallel_terasort.o

$(OBJECTS)/Partition.o: $(SOURCES)/Partition.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/Partition.cpp -o $(OBJECTS)/Partition.o

$(OBJECTS)/Partitioner.o: $(SOURCES)/Partitioner.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/Partitioner.cpp -o $(OBJECTS)/Partitioner.o

$(OBJECTS)/QuickSort.o: $(SOURCES)/QuickSort.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/QuickSort.cpp -o $(OBJECTS)/QuickSort.o

$(OBJECTS)/Reducer.o: $(SOURCES)/Reducer.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/Reducer.cpp -o $(OBJECTS)/Reducer.o

$(OBJECTS)/TeraSort.o: $(SOURCES)/TeraSort.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/TeraSort.cpp -o $(OBJECTS)/TeraSort.o

$(OBJECTS)/TeraSortItem.o: $(SOURCES)/TeraSortItem.cpp
	g++ -c -std=c++11 -pthread $(INCLUDES) $(SOURCES)/TeraSortItem.cpp -o $(OBJECTS)/TeraSortItem.o