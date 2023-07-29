CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = exe
CCFILES = $(wildcard commands/*.cc) $(wildcard *.cc)
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(CCFILES:.cc=.d)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

clean:
	rm -f *.o $(EXEC) *.d

-include $(DEPENDS)
