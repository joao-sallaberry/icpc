%: %.cpp
	g++ $< -lm -lcrypt -O2 -pipe -DONLINE_JUDGE -o $@