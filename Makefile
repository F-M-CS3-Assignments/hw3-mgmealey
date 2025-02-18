all:
	g++ -std=c++11 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct

run:
	./tct

try: all run