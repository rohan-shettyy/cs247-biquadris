CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = exe
CCFILES = $(wildcard commands/*.cc) $(wildcard debuffs/*.cc) $(wildcard *.cc)
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(CCFILES:.cc=.d)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

clean:
	rm -rf *.o $(EXEC) *.d

-include $(DEPENDS)
