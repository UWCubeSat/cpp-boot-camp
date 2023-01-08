
SRCS := $(wildcard *.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

BIN := prog

all: $(BIN)

# Adds very useful optional debugging options, just uncomment to use.
# CXXFLAGS := $(CXXFLAGS) -Ivendor -Isrc -Idocumentation -Wall -Wextra -Wno-missing-field-initializers -pedantic --std=c++11

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(wildcard *.so) $(BIN)