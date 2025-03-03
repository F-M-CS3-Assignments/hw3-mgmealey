all:
	g++ -g -std=c++11 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -g -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa

run:
	./tct
	./nasa

try: all run