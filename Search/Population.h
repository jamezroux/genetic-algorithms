#include "Variables.h"

int population[popSize][geneSize];
int children[popSize][geneSize];
int scores[popSize];
int probability[popSize];

int mother;
int father;
int midpoint;

int count;
int sum;

void setup() {

	// Iterate through full population
	for(int i = 0; i < popSize; i++) {
		// Iterate through each entity in population
		for(int j = 0; j < geneSize; j++) {
			population[i][j] = rand()%(32 - 126 + 1) + 126;
		}
	}
	return;
}

// The fitness function
void score() {

	int popLength = *(&population + 1) - population;
	int geneLength;

	// Main scoring, based off characters correct
	for(int i = 0; i < popLength; i++) {
		count = 0;
		geneLength = *(&population[i] + 1) - population[i];
		for(int j = 0; j < geneLength; j++) {
			// Check to see if right character in right position
			if(population[i][j] == target[j]) { count++; }
		}
		scores[i] = count;
	}

	// Normalize the scores
	for(int i = 0; i < popLength; i++) {
		sum = sum + scores[i];
	}
	for(int i = 0; i < popLength; i++) {
		probability[i] = scores[i] / sum;
	}
	return;
}

// The breeding function
void breed() {

	int popSize = *(&population + 1) - population;
	int geneSize;
	double pick;

	// Create array of spawns
	for(int spawn = 0; spawn < popSize; spawn++) {

		geneSize = *(&population[spawn] + 1) - population[spawn];

		// Select a mother
		mother = 0;
		//pick = ((double) rand() / (RAND_MAX)) + 1;
		//pick = ((double) rand()%(0+1)+0);
		pick = rand()%2;

		while(pick > 0) {
			pick = pick - probability[mother];
			mother++;
		}
		mother--;

		// Select a father
		father = 0;
		//pick = ((double) rand()%(0 + 1) + 0);
		pick = rand()%2;

		while(pick > 0) {
			pick = pick - probability[father];
			father++;
		}
		father--;

		// Select a midpoint
		midpoint = rand()%(geneSize - 0 + 1) + 1;
		// Breed from midpoint
		for (int i = 0; i < geneSize; i++) {
			if(i < midpoint) {
				children[spawn][i] = population[mother][i];
			} else {
				children[spawn][i] = population[father][i];
			}
		}
	}

	// Replace old population with new population
	for(int replace = 0; replace < popSize; replace++) {
		for(int character = 0; character < geneSize; character++) {
			population[replace][character] = children[replace][character];
		}
	}
	return;
}

// Let's see how we did
bool check() {
	int score;
	int popSize = *(&population + 1) - population;
	int geneSize;
	for(int i = 0; i < popSize; i++) {
		geneSize = *(&population[i] + 1) - population[i];
		for(int j = 0; j < geneSize; j++) {
			// Check the dna
			if(population[i][j] == int(target[j])) { score++; }
		}
	}
	if(score == *(&target + 1) - target) {
		return true;
	} else {
		return false;
	}
}
