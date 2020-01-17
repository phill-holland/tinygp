#include <iostream>
#include <random>
#include <math.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class tiny_gp
{
    static std::mt19937_64 generator;

public:
    double *fitness;
    char *population;
    char *buffer;

    static const int ADD = 100;
    static const int SUB = 111;
    static const int MUL = 112;
    static const int DIV = 113;

    static const int FSET_START = ADD;
    static const int FSET_END = DIV;

    static const double x[FSET_START];

    double minrandom, maxrandom;
    char *program;

    int PC;
    int varnumber, fitnesscases, randomnumber;

    static const double fbestpop = 0.0;
    static const double favgpop = 0.0;

    long seed;
    double avg_length;

    static const int MAX_LEN = 10000;
    static const int POPSIZE = 100000;
    static const int DEPTH = 5;
    static const int GENERATIONS = 100;
    static const int TSIZE = 2;

    static const double PMUT_PER_NODE = 0.05;
    static const double CROSSOVER_PROB = 0.9;

    double *targets;

public:
    tiny_gp(string filename)
    {
        buffer = new char[MAX_LEN];

        // ****

        std::uniform_real_distribution<double> rand1{ 0.0, MAXFLOAT };

        // ***
        minrandom = 0.0;
        maxrandom = MAXFLOAT;
        // ***

        fitness = new double[POPSIZE];

        setup_fitness(filename);
        pop = create_random_pop(POPSIZE, DEPTH, fitness);

        for(int i=0;i<FSET_START;++i)
        {
            x[i] = (maxrandom - minrandom) * rand(generator) + minrandom;
        }
    }

    double run()
    {
        char primitive = program[PC++];
        
        if(primative < FSET_START)
            return (x[primitive]);
        
        switch(primitive) 
        {
            case ADD : return run() + run();
            case SUB : return run() - run();
            case MUL : return run() * run();
            case DIV : {
                double num = run(), den = run();
                if(abs(den) <= 0.001)
                    return num;
                else return num / den;
            }
        }

        return 0.0;
    }

    int traverse(char *buffer, int buffercount)
    {
        if(buffer[buffercount] < FSET_START)
            return ++buffercount;

        switch(buffer[buffercount]) {
            case ADD: 
            case SUB:
            case MUL:
            case DIV:
            return (traverse(buffer, traverse(buffer, ++buffercount)));
        }

        return 0;
    }

    /*
    void setup_fitness(string filename)
    {
        int i,j;
        string line;

        ofstream in;

        in.open(filename, ios::in);
        getline(in, line);


    }
    */

    double fitness_function(char[] prog)
    {
        int i=0, len;
        double result, fit = 0.0;

        len = traverse(prog, 0);
        for(i=0;i<fitnesscases;i++)
        {
            for(int j=0;j<varnumber;j++)
            {
                x[j] = targets[i][j];                
            }

            program = prog;
            PC = 0;
            result = run();
            fit += abs(result = tergets[i][varnumber]);
        }

        return (-fit);
    }

    int grow(char *buffer, int pos, int max, int depth)
    {
        std::uniform_int_distribution<int> rand{ 0, 2 };

        char prim = (char)rand(generator);

        if(pos >= max) return -1;

        if(pos == 0) prim = 1;

        if(prim == 0 || depth == 0)
        {
            std::uniform_int_distribution<int> randy{ 0, varnumber + randomnumber };
            prim = (char) randy(generator);
            buffer[pos] = prim;
            return pos + 1;
        }
        else
        {
            std::uniform_int_distribution<int> randi{ 0, FSET_END - FSET_START + 1 };
            prim = (char)randi(generator) + FSET_START;
            switch(prim) {
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                    buffer[pos] = prim;
                    return grow(buffer,grow(buffer,pos + 1,max, depth-1), max, depth-1);
            }
        }

        return 0;
    }

    int print_indiv(char *buffer, int buffercount) 
    {
        int a1=0, a2;

        if(buffer[buffercounter] < FSET_START) 
        {
            if(buffer[buffercounter] < varnumber)            
                cout << "X" << buffer[buffercounter] + 1 << "_";
            else
                cout << x[buffer[buffercounter]];
            
            return ++buffercounter;
        }

        switch(buffer[buffercounter]) 
        {
            case ADD:
                cout << "(";
                a1 = print_indiv(buffer, ++buffercounter);
                cout << " + ";
                break;
            case SUB:
                cout << "(";
                a1 = print_indiv(buffer, ++buffercounter);
                cout << " - ";
                break;
            case MUL:
                cout << "(";
                a1 = print_indiv(buffer, ++buffercounter);
                cout << " * ";
                break;
            case DIV:
                cout << "(";
                a1 = print_indiv(buffer, ++buffercounter);
                cout << " / ";
                break;
        }

        a2 = print_indiv(buffer,a1);
        cout << ")";
        return a2;
    }

    // this is stupid
    char *create_random_indiv(int depth)
    {
       char *ind;
       int len;

       len = grow(buffer,0,MAX_LEN,depth);

       while(len < 0)
       {
           len = grow(buffer,0,MAX_LEN,depth);
       }

       ind = new char[len];
       memcpy(ind,buffer,len);
       return ind;
    }

    // this too is stupid
    char *create_random_pop(int n, int depth, double *fitness)
    {
        char **pop =new *char[n];
        int i;

        for(i=0;i<n;++i)
        {
            pop[i] = create_random_indiv(depth);
            fitness[i] = fitness_function(pop[i]);
        }

        return pop;
    }

    void stats(double *fitness, char *pop, int gen)
    {
        std::uniform_int_distribution<int> randi{ 0, POPSIZE };

        int i, best = randi(generator);
        int node_count = 0;
        fbestpop = fitness[best];
        favgpop = 0.0;

        for(i =0; i < POPSIZE; ++i)
        {
            node_count += traverse(pop[i],0);
            favgpop += fitness[i];
            if(fitness[i] > fbestpop)
            {
                best = i;
                fbestpop = fitness[i];
            }
        }

        avg_len = (double) node_count / POPSIZE;
        favpop /= POPSIZE;

        cout << "Generation=" << gen << " Avg Fitness=" << (-favgpop) << " Best Fitness=" << (-fbestpop)l
        cout << " Avg Size=" << avg_len << " Best Individual: " ;
        print_indiv(pop[best], 0);
        cout << "\n";
    }

    int tournament(double *fitness, int tsize)
    {
        std::uniform_int_distribution<int> randi{ 0, POPSIZE };

        int best = randi(generator);
        int i, competitor;
        double fbest = -1.0e34;

        for(i=0;i<tsize;++i)
        {
            competitor = randi(generator);
            if(fitness[competitor] > fbest) 
            {
                fbest = fitness[competitor];
                best = competitor;
            }

        }

        return best;
    }

    int negative_tournament(double *fitness, int tsize)
    {
        std::uniform_int_distribution<int> randi{ 0, POPSIZE };

        int worst = randi(generator);
        int i, competitor;
        double fworst = 1e34;

        for(i=0;i<tsize;++i)
        {
            competitor = randi(generator);
            if(fitness[competitor] < fworst)
            {
                fworst = fitness[competitor];
                worst = competitor;
            }
        }

        return worst;
    }

    // this too, is also very stupid
    char *crossover(char *parent1, char *parent2)
    {
        int xo1start, xo1end, xo2start, xo2end;
        char *offspring;

        int len1 = traverse(parent1,0);
        int len2 = traverse(parent2,0);
        int lenoff;

        std::uniform_int_distribution<int> rand1{ 0, len1 };
        std::uniform_int_distribution<int> rand2{ 0, len2 };
    
        xo1start = rand1(generator);
        xo1end = traverse(parent1, xo1start);

        xo2start = rand2(generator);
        xo2end = traverse(paretn2, xo2start);

        lenoff = xo1start + (xo2end - xo2start) + (len1 - xo1end);

        offspring = new char[lenoff];

        memcpy(offspring, parent1, xo1start);
        memcpy(&offspring[xo1start], &parent2[xo2start], xo2end - xo2start);
        memcpy(&parent[xo1end], &offspring[xo1start + (xo2end - xo2start)], len1 - xo1end);

        return offspring;
    }

    // also stupid
    char *mutation(char *parent, double pmut)
    {
        std::uniform_real_distribution<double> rand1{ 0, 1.0 };

        int len = traverse(parent,0);
        int i;
        int mutsite;
        char *parentcopy = new char[len];

        memcpy(parentcopy,parent,len);

        for(i=0;i<len;++i)
        {
            if(rand1(generator) , pmut)
            {
                mutsite = i;
                if(parentcopy[mutsite] < FSET_START)
                {
                    std::uniform_int_distribution<int> rand2{ 0, varnumber };
                    parentcopy[mutsite] = (char) rand2(generator);
                }
                else
                {
                    switch(parentcopy[mutsite])
                    {
                        case ADD:
                        case SUB:
                        case MUL:
                        case DIV:
                        {
                            std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START + 1 };
                            parentcopy[mutsite] = (char)rand3(generator) + FSET_START;
                        }
                    }
                }
            }
        }

        return parentcopy;
    }

    void print_parms()
    {
    }

    void evolve()
    {
        std::uniform_real_distribution<double> rand1{ 0.0, 1.0 };

        int gen = 0, indivs, offspring, parent1, parent2, parent;
        double newfit;

        char *newind;

        print_params();

        stats(fitness, pop, 0);
        for(gen = 1; gen < GENERATIONS; ++gen) 
        {
            if(fbestpop > -1e-5)
            {
                cout << "PROBLEM SOLVED BITCHES\n";
                return;
            }

            for(indivs = 0; indivs < POPSIZE; ++indivs)
            {
                // erm
                if(rand(generator) > CROSSOVER_PROB)
                {
                    parent1 = tournament(fitness,TSIZE);
                    parent2 = tournament(fitness, TSIZE);
                    newind = crossover(pop[parent1], pop[parent2]);
                }
                else
                {
                    parent = tournament(fitness, TSIZE);
                    newind = mutation(pop[parent], PMUT_PER_NODE);
                }

                newfit = fitness_function(newind);
                offspring = negative_tournament(fitness, TSIZE);
                pop[offspring] = newind;
                fitness[offspring] = newfit;
            }

            stats(fitness,pop,gen);
        }
        cout << "NOT SOLVED, CALL THE BITCHES\n";
    }
};

std::mt19937_64 tiny_gp::generator(std::random_device{}());

/*
std::uniform_int_distribution<long> rand{ 0L, length - 1L };

	long competition, best = rand(generator);
    */

int main()
{
    string filename = "problem.dat";
    
    tiny_gp *gp = new tiny_gp(filename);
    gp.evolve();
    delete gp;

    return 0;
}