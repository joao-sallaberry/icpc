%: %.cpp
	g++ $< -lm -lcrypt -O2 -pipe -DONLINE_JUDGE -std=c++11 -o $@ && ./$@