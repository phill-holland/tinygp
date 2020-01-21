#include "genetic.h"
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

const double tiny_gp::PMUT_PER_NODE = 0.05;
const double tiny_gp::CROSSOVER_PROB = 0.9;

std::mt19937_64 tiny_gp::generator(std::random_device{}());

void tiny_gp::reset(std::string filename)
{
    //buffer = new char[MAX_LEN];

    // ****

    std::uniform_real_distribution<double> rand1{ 0.0, MAXFLOAT };

    // ***
    minrandom = 0.0;
    maxrandom = MAXFLOAT;

    fbestpop = 0.0;
    favgpop = 0.0;

    // ***

    fitness = new double[POPSIZE];
    if(fitness == NULL) return;

    population = new schema[POPSIZE];
    if(population == NULL) return;
    
    //charreturn;

    setup_fitness(filename);
    randomize(POPSIZE, DEPTH, fitness);
    //population = create_random_pop(POPSIZE, DEPTH, fitness);

    for(int i=0;i<FSET_START;++i)
    {
        x[i] = (maxrandom - minrandom) * rand1(generator) + minrandom;
    }

    std::cout << "monkey\n";
}


void tiny_gp::randomize(int n, int depth, double *fitness)
{
    for(int i=0;i<n;++i)
    {
        population[i].create(depth,varnumber,randomnumber);
        fitness[i] = population[i].fitness(fitnesscases, varnumber, x, targets);
    }
}
/*
double tiny_gp::run()
{
    char primitive = program[PC++];
    
    if(primitive < FSET_START)
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
*/
/*
int tiny_gp::traverse(char *buffer, int buffercount)
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
*/
void tiny_gp::setup_fitness(string filename)
{
    int i,j;
    string line;

    ifstream in;

    in.open(filename);
    std::getline(in, line);
    
    std::istringstream iss(line);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    std::cout << "filename " << filename << "\n";
    std::vector<std::string>::iterator it = tokens.begin();

    varnumber = std::stoi(it[0]);
    randomnumber = std::stoi(it[1]); 
    minrandom = std::stod(it[2]);
    maxrandom = std::stod(it[3]);
    fitnesscases = std::stoi(it[4]);

    targets = new double[fitnesscases,varnumber+1];
    if(varnumber + randomnumber >= FSET_START) std::cout << "Too many\n";

    for(i=0;i<fitnesscases;++i) 
    {
         std::getline(in, line);
         iss = std::istringstream(line);
         tokens = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
         j = 0;
         for(it = tokens.begin();it != tokens.end(); ++it) 
         {
             targets[i,j++] = std::stod(*it);

             std::cout << *it << ",";
         }

         std::cout << "\n";
    }
    
    in.close();

    std::cout << "moo\n";
}

/*
double tiny_gp::fitness_function(schema &source)//char *prog)
{
    int i=0, len;
    double result, fit = 0.0;

    //len = traverse(prog, 0);
    len = source.traverse(0);
    for(i=0;i<fitnesscases;i++)
    {
        for(int j=0;j<varnumber;j++)
        {
            x[j] = targets[i,j];                
        }

        program = source.program;
        PC = 0;
        result = run();
        fit += abs(result = targets[i,varnumber]);
    }

    return (-fit);
}
*/
/*
int tiny_gp::grow(char *buffer, int pos, int max, int depth)
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
*/
/*
int tiny_gp::print_indiv(char *buffer, int buffercounter) 
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
*/
// this is stupid
/*
char *tiny_gp::create_random_indiv(int depth)
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
*/
void tiny_gp::stats(double *fitness, schema *pop, int gen)
{
    std::uniform_int_distribution<int> randi{ 0, POPSIZE };

    int i, best = randi(generator);
    int node_count = 0;
    fbestpop = fitness[best];
    favgpop = 0.0;

    for(i =0; i < POPSIZE; ++i)
    {
        //node_count += traverse(population[i],0);
        node_count += population[i].traverse(0);
        favgpop += fitness[i];
        if(fitness[i] > fbestpop)
        {
            best = i;
            fbestpop = fitness[i];
        }
    }

    avg_length = (double) node_count / POPSIZE;
    favgpop /= POPSIZE;

    cout << "Generation=" << gen << " Avg Fitness=" << (-favgpop) << " Best Fitness=" << (-fbestpop);
    cout << " Avg Size=" << avg_length << " Best Individual: " ;
    //print_indiv(population[best], 0);
    population[best].print_indiv(0,varnumber, x);
    cout << "here\n";
}

int tiny_gp::tournament(double *fitness, int tsize)
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

int tiny_gp::negative_tournament(double *fitness, int tsize)
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
/*
char *tiny_gp::crossover(char *parent1, char *parent2)
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
    xo2end = traverse(parent2, xo2start);

    lenoff = xo1start + (xo2end - xo2start) + (len1 - xo1end);

    offspring = new char[lenoff];

    memcpy(offspring, parent1, xo1start);
    memcpy(&offspring[xo1start], &parent2[xo2start], xo2end - xo2start);
    memcpy(&offspring[xo1start + (xo2end - xo2start)], &parent1[xo1end], len1 - xo1end);

    return offspring;
}

// also stupid
char *tiny_gp::mutation(char *parent, double pmut)
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
*/
void tiny_gp::print_params()
{
}

void tiny_gp::evolve()
{
    std::uniform_real_distribution<double> rand1{ 0.0, 1.0 };

    int gen = 0, indivs, offspring, parent1, parent2, parent;
    double newfit;

    //char *newind;
    schema newind;

    print_params();

    stats(fitness, population, 0);
    for(gen = 1; gen < GENERATIONS; ++gen) 
    {
        std::cout << "gen " << gen << "\n";
        if(fbestpop > -1e-5)
        {
            cout << "PROBLEM SOLVED BITCHES\n";
            return;
        }

//std::cout << "here a\n";
        for(indivs = 0; indivs < POPSIZE; ++indivs)
        {
            //std::cout << "here b " << indivs << "\n";
            // erm
            if(rand1(generator) > CROSSOVER_PROB)
            {
                std::cout << "here c\n";
                parent1 = tournament(fitness,TSIZE);
                //std::cout << "here d\n";
                parent2 = tournament(fitness, TSIZE);
                //std::cout << "here e\n";
                newind = schema::crossover(population[parent1], population[parent2]);
                //std::cout << "here f\n";
            }
            else
            {
                std::cout << "here g\n";
                parent = tournament(fitness, TSIZE);
                std::cout << "here h\n";
                newind = schema::mutation(population[parent], varnumber, PMUT_PER_NODE);
                std::cout << "here i\n";
            }
           // std::cout << "here j " << fitnesscases << " " << varnumber << " " << "\n";
            //fitness[i] = population[i].fitness(fitnesscases, varnumber, x, targets);
            newfit = newind.fitness(fitnesscases, varnumber, x, targets);
            std::cout << "here k\n";
            offspring = negative_tournament(fitness, TSIZE);
            std::cout << "here l\n";
            population[offspring] = newind;
           // std::cout << "here n\n";
            fitness[offspring] = newfit;
           // std::cout << "here m\n";
        }

        stats(fitness,population,gen);
        cout << "what\n";
    }
    cout << "NOT SOLVED, CALL THE BITCHES\n";
}

