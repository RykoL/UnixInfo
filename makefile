PROJ_INCLUDE = include/
PROJ_SRC = src/
PROJ_DEBUG = bin/Debug/
PROJ_RELEASE = bin/Release/
HEADER_FILES = $(shell find include/ -type f -name "*.h" -print)
SOURCE_FILES = $(shell find src/ -type f -name "*.cpp" -print)
CXX_FLAGS = -std=c++1y -Wall

debug:
	g++ main.cpp $(HEADER_FILES) $(SOURCE_FILES) $(CXX_FLAGS) -g -o $(PROJ_DEBUG)t1

release:
	g++ main.cpp $(HEADER_FILES) $(SOURCE_FILES) $(CXX_FLAGS) -o $(PROJ_RELEASE)t1 && $(PROJ_RELEASE)/./t1

drun: debug
	$(PROJ_DEBUG)/./t1