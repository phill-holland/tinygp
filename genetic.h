#include <iostream>
#include <random>
#include <math.h>
#include <string>
#include "schema.h"

#ifndef GENETIC
#define GENETIC

using namespace std;

class genetic
{
    static std::mt19937_64 generator;

public:
    double *fitness;
    schema::base **pop;

    const static int ADD = 110;
    const static int SUB = 111;
    const static int MUL = 112; 
    const static int DIV = 113;
    const static int FSET_START = ADD;
    const static int FSET_END = DIV;

    const static int MAX_LEN = 10000;
    const static int POPSIZE = 100000;
    const static int DEPTH   = 5;
    const static int GENERATIONS = 100;
    const static int TSIZE = 2;

    static double  PMUT_PER_NODE, CROSSOVER_PROB;

    double x[FSET_START];

    double minrandom, maxrandom;
    
    int varnumber, fitnesscases, randomnumber;
    static double fbestpop, favgpop;
    long seed;
    double avg_len; 

    double *targets;

    bool init;

public:
    genetic(schema::factory *factory, string filename) { makeNull(); reset(factory, filename); } 
    ~genetic() { cleanup(); }

    bool initalised() { return init; }
    void reset(schema::factory *factory, string filename);
    
    void load(string filename);
  
    void stats(int gen);

    int tournament();
    int negative_tournament();
  
    void print_parms();

    void evolve();

protected:
    void makeNull();
    void cleanup();
};

#endif