#include <cstdlib>
#include <string>
#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

const int popSize = 1000;
const int geneSize = 42;
const char target[] = "Just a random phrase for the discord peeps";
const float mutationRate = 1;
const int epochCount = 1000;

random_device rd;
mt19937 e2(rd());
uniform_real_distribution<> dist(0,1);

random_device sp;
knuth_b s3(sp());
uniform_real_distribution<> lett(32,126);

random_device ps;
knuth_b p2(ps());
uniform_real_distribution<> selprnt(0,popSize-1);

random_device mc;
knuth_b mt(mc());
uniform_real_distribution<> mutate(0,100);

int population[popSize][geneSize];
int children[popSize][geneSize];
float scores[popSize];
float probability[popSize];

int mother;
int father;
int midpoint;
int generation = 0;

int count;
int sum = 0;
int epoch = 0;

void setup() {

	int number = 0;

	// Iterate through full population
	for(int i = 0; i < popSize; i++) {
		//cout << number << " | ";
		// Iterate through each entity in population
		for(int j = 0; j < geneSize; j++) {
			population[i][j] = lett(s3);
			//cout << population[i][j];
		}
		number++;
		//cout << endl;
	}
	return;
}

// The fitness function
void score() {

	sum = 0;

	for(int i = 0; i < popSize; i++) {
		scores[i] = 0;
	}

	// Main scoring, based off characters correct
	for(int i = 0; i < popSize; i++) {
		count = 0;
		for(int j = 0; j < geneSize; j++) {
			// Check to see if right character in right position
			if((int)population[i][j] == (int)target[j]) { 
				count++;
			}
		}
		scores[i] = count;
	}

	// Normalize the scores
	for(int i = 0; i < popSize; i++) {
		sum = sum + scores[i];
	}
	for(int i = 0; i < popSize; i++) {
		probability[i] = scores[i] / sum;
	}
	return;
}

// The breeding function
void breed() {

	float pick;
	float pickMax;
	float chance;

	for(int i = 0; i < popSize; i++) {
		pickMax = probability[i] + pickMax;
	}

	uniform_real_distribution<> selprnt(0,pickMax);

	// Create array of spawns
	for(int spawn = 0; spawn < popSize; spawn++) {

		// Select a mother
		mother = floor(selprnt(p2));
		pick = dist(e2);
		if(pick == 0) {
			throw runtime_error("Mother pick was 0.");
		}
		int loop = 0;
		while(pick > 0 & mother < popSize) {
			pick = pick - probability[mother];
			mother++;
			loop++;
		}
		mother--;

		// Select a father
		father = floor(selprnt(p2));
		pick = dist(e2);
		if(pick == 0) {
			throw runtime_error("Father pick was 0.");
		}
		while(pick > 0 & father < popSize) {
			pick = pick - probability[father];
			father++;
		}
		father--;

		// Select a midpoint
		midpoint = rand()%(geneSize - 1 + 2) + 2;
		if(midpoint == 0) {
			throw runtime_error("Midpoint was 0.");
		}
		// Breed from midpoint
		// Also applies mutation
		for (int i = 0; i < geneSize; i++) {
			chance = mutate(mt);
			if(chance > mutationRate) {
				if(i < midpoint) {
					children[spawn][i] = population[mother][i];
				} else {
					children[spawn][i] = population[father][i];
				}
			} else {
				children[spawn][i] = lett(s3);
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
	float highscore = 0;
	int highword[geneSize];
	
	epoch++;

	for(int i = 0; i < popSize; i++) {
		if(scores[i] == geneSize) {
			cout << "Found ";
			for(int j = 0; j < geneSize; j++) {
				cout << (char)population[i][j] << " | ";
			} cout << " in " << generation << " generations.";
			return true;
		} else {
			if(probability[i] > highscore) {
				highscore = probability[i];
				for(int j = 0; j < geneSize; j++) {
					highword[j] = population[i][j];
				}
			}
		}
	}
	if(epoch%epochCount == 0 || epoch == 1) {
		cout << "Highest score: " << highscore << " Highest word: ";
		for(int i = 0; i < geneSize; i++) {
			cout << (char)highword[i] << " | ";
		} cout << " | Generation: " << generation << endl;
	}
	return false;
}
