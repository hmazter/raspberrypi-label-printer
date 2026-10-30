all:
	g++ `cups-config --cflags` PrintLabel.cpp `cups-config --libs` -o PrintLabel

# This is for local debugging on macOS
CXX_INCLUDES := $(shell xcrun --show-sdk-path)/usr/include/c++/v1
macos:
	g++ -I$(CXX_INCLUDES) `cups-config --cflags` PrintLabel.cpp `cups-config --libs` -o PrintLabel