#include <random>

#ifndef SCHEMA
#define SCHEMA

class schema
{
    static const int ADD = 100;
    static const int SUB = 111;
    static const int MUL = 112;
    static const int DIV = 113;

    static const int FSET_START = ADD;
    static const int FSET_END = DIV;

    static std::mt19937_64 generator;
    const static int MAX = 4095;

    char *program;

    int PC;

    int max, length;    
    bool init;

public:
    schema(int total = MAX) { makeNull(); reset(total); }
    schema(const schema &source) { copy(source); }
    ~schema() { cleanup(); }

    bool initalised() { return init; }
    void reset(int total);

    void clear();
    void create(int depth, int varnumber, int randnumber);
    
    double run(double *x);
    double fitness(int fitnesscases, int varnumber, double *x, double *targets);

    static schema crossover(schema &parent1, schema &parent2);
    static schema mutation(schema &parent, int varnumber, double pmut);

    
//protected:
    int traverse(int buffercount);
    int grow(int pos, int max, int depth, int varnumber, int randnumber);
    
    int print_indiv(int buffercounter, int varnumber, double *x);

    void copy(const schema &source);

protected:
    void makeNull();
    void cleanup();
};

#endif