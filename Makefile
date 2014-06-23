%: %.cpp
	g++ $< -lm -lcrypt -g -pipe  -std=c++11 -o $@
