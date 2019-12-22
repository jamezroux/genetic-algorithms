#include "Population.h"

using namespace std;

// Author
//  - James Moore / jamezroux
// Date
//  - 12/22/2019
// Version
//  - Production
//
// TODO: Write method for mutation
//
// Goal
//  -Write genetic algorithm that evolves to any phrase

int main() {

	int generations = 0;

	// Generate population
	cout << "Starting setup.";
	setup();
	cout << "Successfull setup.";

	while(true) {

		generations++;
		cout << "Successful generation.";

		// Breed population
		breed();
		cout << "Successfully bred.";

		// Score population
		score();
		cout << "Successful scoring";

		// Check to see if complete
		if(check()) {
			break;
		}
		cout << "Target not found.";
	}

	cout << "Ended in " << generations << " generations.";
}
