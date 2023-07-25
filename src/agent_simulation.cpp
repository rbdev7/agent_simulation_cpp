// agent_simulation.cpp : Defines the entry point for the application.
//

#include "agent_simulation.h"
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[])
{
	Simulation sim(640, 480);
	
	sim.Run();

	return 0;
}
