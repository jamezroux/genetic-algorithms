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

	// Generate population
	cout << "Starting setup." << endl;
	setup();
	cout << "Successfull setup.\n" << endl;

	while(true) {

		generation++;
		//cout << "Successful generation | ";

		// Score population
		score();
		//cout << "Successful scoring" << endl;

		// Check to see if we found it
		if(check()) {
			break;
		}

		// Breed population
		breed();
	}

	return 0;
}
