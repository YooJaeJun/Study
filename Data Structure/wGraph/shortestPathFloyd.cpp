#include "wGraphFloyd.h"
void main() {
	wGraphFloyd g;
	g.load("graph.txt");
	printf("Shortest Path By Floyd Algorithm\n");
	g.shortestPathFloyd();
}