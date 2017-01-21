all:
	g++ main.cpp -std=c++11 -O0 -o WaveNation -I/home/jscheil/.sfml/include -L/home/jscheil/.sfml/lib -lBox2D -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
