#include <bits/stdc++.h>
using namespace std;

#define MS_PER_UPDATE 16.0

double getCurrentTime() {}
void processInput() {}
void update() {}
void render(double t) {}

int main()
{
	double previous = getCurrentTime();
	double lag = 0.0;
	while (true)
	{
		double current = getCurrentTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;
		processInput();
		
		while (lag >= MS_PER_UPDATE)
		{
			update();
			lag -= MS_PER_UPDATE;
		}
		render(lag / MS_PER_UPDATE);
	}
}