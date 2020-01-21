#include <iostream>
#include <random>
#include <math.h>
#include <string>
#include "schema.h"

#ifndef GENETIC
#define GENETIC

class tiny_gp
{
    static std::mt19937_64 generator;

public:
    double *fitness;
    //char **population;
    schema *population;
    //char *buffer;

    static const int ADD = 110;
    static const int SUB = 111;
    static const int MUL = 112;
    static const int DIV = 113;

    static const int FSET_START = ADD;
    static const int FSET_END = DIV;

    double x[FSET_START];
    //double *x;

    double minrandom, maxrandom;
    
    //char *program;
    //int PC;

    int varnumber, fitnesscases, randomnumber;

    double fbestpop;
    double favgpop;

    long seed;
    double avg_length;

    static const int MAX_LEN = 10000;
    static const int POPSIZE = 100000;
    static const int DEPTH = 5;
    static const int GENERATIONS = 100;
    static const int TSIZE = 2;

    static const double PMUT_PER_NODE;
    static const double CROSSOVER_PROB;

    double *targets;

public:
    tiny_gp(std::string filename) { makeNull(); reset(filename); }
    ~tiny_gp() { cleanup(); }

    void reset(std::string filename);

    //double run();    
    //int traverse(char *buffer, int buffercount);    
    void setup_fitness(std::string filename);

    //double fitness_function(schema &source);//char  *prog);
    
   //int grow(char *buffer, int pos, int max, int depth);    
    //int print_indiv(char *buffer, int buffercounter);

    //char *create_random_indiv(int depth);
    //char **create_random_pop(int n, int depth, double *fitness);
    //schema *create_random_pop(int n, int depth, double *fitness);

    void stats(double *fitness, schema *pop, int gen);
    int tournament(double *fitness, int tsize);
    
    int negative_tournament(double *fitness, int tsize);

    //char *crossover(char *parent1, char *parent2);
    //char *mutation(char *parent, double pmut);
    
    void print_params();
    void evolve();

protected:
    //schema *create_random_pop(int n, int depth, double *fitness);
    void randomize(int n, int depth, double *fitness);

protected:
    void makeNull() 
    { 
        fitness = NULL; 
        population = NULL; 
        targets = NULL;
    }

    void cleanup()
    {
        std::cout << "clean a\n";
        if(targets != NULL) delete[] targets;
        std::cout << "clean b\n";
        if(population != NULL) delete[] population;
        std::cout << "clean c\n";
        if(fitness != NULL) delete[] fitness;
    }
};

#endif