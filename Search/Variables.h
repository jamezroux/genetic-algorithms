#ifndef VARIABLES_H
#define VARIABLES_H

// Includes
#include <cstdlib>
#include <string>
#include <iostream>

// General tweaks
const static int popSize = 100;
const static int geneSize = 12;
const static char target[] = "Hello World!";

// Population related
extern int population[popSize][geneSize];
extern int children[popSize][geneSize];
extern int scores[popSize];
extern int probability[popSize];

extern int mother;
extern int father;
extern int midpoint;



#endif
