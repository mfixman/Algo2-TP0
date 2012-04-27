all:
	g++ tests.cpp -o anillo -Wno-unused-result

optimizado:
	g++ tests.cpp -o anillo -O2 -Wno-unused-result

debug:
	g++ tests.cpp -o anillo -g

