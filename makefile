make:
	g++ src/main.cpp src/clock.cpp `wx-config --cxxflags --libs`