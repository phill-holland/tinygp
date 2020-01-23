#include <random>
#include <string>

#ifndef BUGGER
#define BUGGER

using namespace std;

namespace bugger
{
    class schema
    {
    static const int ADD = 110;
    static const int SUB = 111;
    static const int MUL = 112;
    static const int DIV = 113;

    static const int FSET_START = ADD;
    static const int FSET_END = DIV;

    static std::mt19937_64 generator;
    const static int MAX = 10000;

    int PC;

    int max, length;    
    bool init;

public:
    char *program;

public:
    schema(int total = MAX) { makeNull(); reset(total); }
    schema(const schema &source) { makeNull(); reset(source.max); copy(source); }
    ~schema() { cleanup(); }

    bool initalised() { return init; }
    void reset(int total);

    void clear();
    int total() { return length; }
    
    int traverse(int buffercount);
    void crossover(schema &parent1, schema &parent2);
    void mutate(double pmut, int varnumber, int randomnumber);

    void copy(const schema &source);

public:
    schema operator=(const schema &src) { clear(); copy(src); return *this; }

protected:
    void makeNull();
    void cleanup();
    };


class tiny_gp 
{
        static std::mt19937_64 generator;

public:

  double *fitness;
  schema *pop;
  //char **pop;
  //static Random rd = new Random();
  const static int ADD = 110;
    const static int SUB = 111;
    const static int MUL = 112; 
    const static int DIV = 113;
    const static int FSET_START = ADD;
    const static int FSET_END = DIV;

  double x[FSET_START];

  double minrandom, maxrandom;
  char *program;
  int PC;
  int varnumber, fitnesscases, randomnumber;
  static double fbestpop, favgpop;
  long seed;
  double avg_len; 
  const static int MAX_LEN = 10000;
    const static int POPSIZE = 100000;
    const static int DEPTH   = 5;
    const static int GENERATIONS = 100;
    const static int TSIZE = 2;

   static double  PMUT_PER_NODE, CROSSOVER_PROB;

  double *targets;

  char buffer[MAX_LEN];

    bool init;

public:
    tiny_gp(string fname) { makeNull(); reset(fname); } 
    ~tiny_gp() { cleanup(); }

    bool initalised() { return init; }
    void reset(string fname);

  double run();
          
  int traverse( char *buffer, int buffercount );

    void output(char *buffer);
    
  void setup_fitness(string filename);

  //double fitness_function( char *Prog );
  double fitness_function(schema &source);

  int grow( char *buffer, int pos, int max, int depth );
  
  int print_indiv( char *buffer, int buffercounter );

  //char *create_random_indiv( int depth );
  void create_random_indiv( schema &destination, int depth );

  //char **create_random_pop(int n, int depth, double *fitness );

  //void stats( double *fitness, char **pop, int gen );
  void stats( double *fitness, schema *pop, int gen );

  int tournament( double *fitness, int tsize );

  int negative_tournament( double *fitness, int tsize );
  
  //char *crossover( char *parent1, char *parent2 );
  //schema crossover( schema &parent1, schema &parent2 );
  
  //char *mutation( char *parent, double pmut );
 // schema mutation( schema &parent, double pmut );
  
  void print_parms();

  void evolve();

  protected:
    void makeNull()
    {
        fitness = NULL;
        pop = NULL;
    }

    void cleanup()
    {
        if(pop != NULL) delete[] pop;
        if(fitness != NULL) delete[] fitness;
    }
};
};
#endif