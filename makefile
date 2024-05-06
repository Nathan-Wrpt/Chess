CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++11

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
EXEC=echecs

DOXYGEN=doxygen
DOXYGEN_CONFIG=Doxyfile

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

doc: $(DOXYGEN_CONFIG)
	$(DOXYGEN) $(DOXYGEN_CONFIG)

clean:
	rm -f $(OBJS) $(EXEC)
	rm -rf doc
