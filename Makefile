all:
	g++ -g -std=c++11 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -g -std=c++11 -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -g -std=c++11 -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt

run:
	./tct
	./nasa
	./pdt

try: all run