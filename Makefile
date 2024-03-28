# Set g++ as the C++ compiler
CXX=g++

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES= src/ParseData.cpp src/Utilities.cpp src/Consult.cpp src/Script.cpp

# Your target program
PROGRAMS=run

# Target directory for Doxygen documentation
DOXYGEN_INPUT_DIR = docs
DOXYGEN_OUTPUT_DIR = docs/documentation

# Doxygen configuration file
DOXYGEN_CONFIG = $(DOXYGEN_INPUT_DIR)/Doxyfile

# Target for Doxygen documentation
DOXYGEN_TARGET = $(DOXYGEN_OUTPUT_DIR)/html/index.html

all: $(PROGRAMS)

run: $(COMMON_CPP_FILES) main.cpp
	$(CXX) -o run main.cpp $(COMMON_CPP_FILES)

doc: $(DOXYGEN_CONFIG)
	doxygen $(DOXYGEN_CONFIG)

clean:
	rm -fr *.dSYM $(PROGRAMS)