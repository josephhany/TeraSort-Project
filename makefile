include makefile.vars

$(BIN)/FINAL: $(SOURCES)/CommandLineArguments.cpp $(SOURCES)/TeraSortItem.cpp $(SOURCES)/QuickSort.cpp $(SOURCES)/Partition.cpp $(SOURCES)/Partitioner.cpp  $(SOURCES)/Mapper.cpp $(SOURCES)/Reducer.cpp $(SOURCES)/TeraSort.cpp $(SOURCES)/parallel_terasort.cpp 
	g++ -std=c++11 -pthread $(INCLUDES) $(SOURCES)/CommandLineArguments.cpp $(SOURCES)/TeraSortItem.cpp $(SOURCES)/QuickSort.cpp $(SOURCES)/Partition.cpp $(SOURCES)/Partitioner.cpp  $(SOURCES)/Mapper.cpp $(SOURCES)/Reducer.cpp $(SOURCES)/TeraSort.cpp $(SOURCES)/parallel_terasort.cpp   -o $(BIN)/FINAL
