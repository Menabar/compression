CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lgmp -lgmpxx

all: encode decode

encode: encode.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

decode: decode.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f encode decode
