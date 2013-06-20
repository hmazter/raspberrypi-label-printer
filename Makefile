all:
	g++ `cups-config --cflags` PrintLabel.cpp `cups-config --libs` -o PrintLabel
