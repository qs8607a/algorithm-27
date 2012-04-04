CFLAGS=-g
CXXFLAGS=-g

%: %.cpp
	$(CXX) $(CXXFLAGS) $<
