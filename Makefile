%: %.cpp
	g++ $< -lm -lcrypt -g -pipe -DONLINE_JUDGE -std=c++11 -o $@