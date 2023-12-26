# Set g++ as the C++ compiler
CXX=g++

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES= ParseData.cpp Utilities.cpp OutputData.cpp Consult.cpp ListAirports.cpp Script.cpp

# Your target program
PROGRAMS=run

# Doxygen configuration file
DOXYGEN_CONFIG = docs/Doxyfile

# Target directory for Doxygen documentation
DOXYGEN_OUTPUT_DIR = docs/output

# Target for Doxygen documentation
DOXYGEN_TARGET = $(DOXYGEN_OUTPUT_DIR)/html/index.html

all: $(PROGRAMS)

run: $(COMMON_CPP_FILES) main.cpp
	$(CXX) -o run main.cpp $(COMMON_CPP_FILES)

clean:
	rm -fr *.dSYM $(PROGRAMS)
