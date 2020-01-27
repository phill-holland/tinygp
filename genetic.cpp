#include "genetic.h"
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

std::mt19937_64 genetic::generator(std::random_device{}());

double genetic::fbestpop = 0.0;
double genetic::favgpop = 0.0;
double genetic::PMUT_PER_NODE  = 0.05;
double genetic::CROSSOVER_PROB = 0.9;

void genetic::reset(schema::factory *factory, string filename) 
{
    init = false; cleanup();

    fitness =  new double[POPSIZE];
    if(fitness == NULL) return;

    load(filename);

    std::uniform_real_distribution<double> rand{ 0, 1.0 };

    for ( int i = 0; i < FSET_START; i ++ )
    {    
        x[i]= (maxrandom-minrandom)*rand(generator)+minrandom;
    } 
    
    pop = new schema::base*[POPSIZE];
    if(pop == NULL) return;
    for (int i = 0; i < POPSIZE; i ++) { pop[i] = NULL; }

    for (int i = 0; i < POPSIZE; i ++) 
    {
       pop[i] = factory->create();
       if(pop[i] == NULL) return;

       pop[i]->create(DEPTH, varnumber, randomnumber);
       fitness[i] = pop[i]->fitness(fitnesscases, varnumber, x, targets);
    }
    
    init = true;
}

  void genetic::load(string filename) 
  {
    int i,j;
    string line;

    ifstream in;

    in.open(filename);
    std::getline(in, line);
    
    std::istringstream iss(line);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    std::vector<std::string>::iterator it = tokens.begin();

    varnumber = std::stoi(it[0]);
    randomnumber = std::stoi(it[1]); 
    minrandom = std::stod(it[2]);
    maxrandom = std::stod(it[3]);
    fitnesscases = std::stoi(it[4]);

    targets = new double[fitnesscases,varnumber+1];
    if(varnumber + randomnumber >= FSET_START) 
    {
        std::cout << "Too many\n";
        return;
    }

    for(i=0;i<fitnesscases;++i) 
    {
         std::getline(in, line);
         iss = std::istringstream(line);
         tokens = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
         j = 0;
         for(it = tokens.begin();it != tokens.end(); ++it) 
         {
             targets[i,j++] = std::stod(*it);
         }
    }
    
    in.close();
  }

  void genetic::stats(double *fitness, int gen) 
  {
    std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };

    int i;
    int best = rand(generator);
    int node_count = 0;
    fbestpop = fitness[best];
    favgpop = 0.0;

    for ( i = 0; i < POPSIZE; i ++ ) 
    {
      node_count +=  pop[i]->traverse(0);
      favgpop += fitness[i];
      if ( fitness[i] > fbestpop ) 
      {
        best = i;
        fbestpop = fitness[i];
      }
    }
    avg_len = (double) node_count / POPSIZE;
    favgpop /= POPSIZE;
    std::cout << "Generation=" << gen << " Avg Fitness=" << (-favgpop) <<
    		 " Best Fitness=" << (-fbestpop) << " Avg Size=" << avg_len << 
    		 "\nBest Individual: ";

    pop[best]->print(0, x, varnumber);
    std::cout << "\n";
  }

int genetic::tournament(double *fitness, int tsize) 
{
    std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };
    int best = rand(generator);
    int i, competitor;
    double  fbest = -1.0e34;

    for ( i = 0; i < tsize; i ++ ) 
    {
        competitor = rand(generator);
        if (fitness[competitor] > fbest) 
        {
            fbest = fitness[competitor];
            best = competitor;
        }
    }

    return best;
}
  
int genetic::negative_tournament(double *fitness, int tsize) 
{
    std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };

    int worst = rand(generator);
    int i, competitor;
    double fworst = 1e34;

    for ( i = 0; i < tsize; i ++ ) 
    {
        competitor = rand(generator);
        if (fitness[competitor] < fworst) 
        {
            fworst = fitness[competitor];
            worst = competitor;
        }
    }

    return worst;
}
  
void genetic::print_parms() 
{
    std::cout << "-- TINY GP Inspired --\n";
    std::cout << "SEED=" << seed << "\nMAX_LEN=" << MAX_LEN <<
    "\nPOPSIZE=" << POPSIZE << "\nDEPTH=" << DEPTH << 
        "\nCROSSOVER_PROB=" << CROSSOVER_PROB <<
        "\nPMUT_PER_NODE=" << PMUT_PER_NODE <<
        "\nMIN_RANDOM=" << minrandom << 
        "\nMAX_RANDOM=" << maxrandom <<
        "\nGENERATIONS=" << GENERATIONS << 
        "\nTSIZE=" << TSIZE << 
        "\n----------------------------------\n";
}


void genetic::evolve() 
{
    std::uniform_real_distribution<double> rand{ 0, 1.0 };
    int gen = 0, indivs, offspring, parent1, parent2, parent;
    double newfit;

    print_parms();
    stats(fitness, 0);

    for (gen = 1; gen < GENERATIONS; gen ++) 
    {    
        if (fbestpop > -1e-5) 
        {
            std::cout << "PROBLEM SOLVED\n";
            return;
        }
        
        for (indivs = 0; indivs < POPSIZE; indivs ++) 
        {
            offspring = negative_tournament(fitness, TSIZE);

            if (rand(generator) < CROSSOVER_PROB) 
            {
                parent1 = tournament(fitness, TSIZE);
                parent2 = tournament(fitness, TSIZE);
                pop[offspring]->crossover(pop[parent1],pop[parent2]);
            }
            else 
            {
                parent = tournament(fitness, TSIZE);
                pop[offspring]->copy(pop[parent]);
                pop[offspring]->mutate(PMUT_PER_NODE, varnumber, randomnumber);

            }

            newfit = pop[offspring]->fitness(fitnesscases, varnumber,x,targets);
            
            fitness[offspring] = newfit;        
        }

    stats(fitness, gen);
}

std::cout << "PROBLEM *NOT* SOLVED\n";
}

void genetic::makeNull()
{
    fitness = NULL;
    pop = NULL;
}

void genetic::cleanup()
{
    if(pop != NULL) 
    {
        for(int i=0; i < POPSIZE; ++i)
        {
            if(pop[i] != NULL) delete pop[i];
        }

        delete[] pop;
    }

    if(fitness != NULL) delete[] fitness;
}