# Set g++ as the C++ compiler
CXX=g++

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES= Data.cpp ParseData.cpp Utilities.cpp OutputData.cpp Consult.cpp ListAirports.cpp

# Your target program
PROGRAMS=run

all: $(PROGRAMS)

run: $(COMMON_CPP_FILES) main.cpp
	$(CXX) -o run main.cpp $(COMMON_CPP_FILES)

clean:
	rm -fr *.dSYM $(PROGRAMS)
