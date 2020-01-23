#include <random>
#include <string>

#ifndef BUGGER
#define BUGGER

using namespace std;

namespace bugger
{
class tiny_gp 
{
        static std::mt19937_64 generator;

public:

  double *fitness;
  char **pop;
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

  double run();
          
  int traverse( char *buffer, int buffercount );

    void output(char *buffer);
    
  void setup_fitness(string filename);

  double fitness_function( char *Prog );

  int grow( char *buffer, int pos, int max, int depth );
  
  int print_indiv( char *buffer, int buffercounter );

  char buffer[MAX_LEN];

  char *create_random_indiv( int depth );

  char **create_random_pop(int n, int depth, double *fitness );

  void stats( double *fitness, char **pop, int gen );

  int tournament( double *fitness, int tsize );

  int negative_tournament( double *fitness, int tsize );
  
  char *crossover( char *parent1, char *parent2 );
  
  char *mutation( char *parent, double pmut );
  
  void print_parms();

  tiny_gp(string fname);

  void evolve();
};
};
#endif