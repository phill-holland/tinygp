#include "schema.h"
#include <random>
#include <string.h>
#include <iostream>

std::mt19937_64 schema::generator(std::random_device{}());

void schema::reset(int total)
{
    init = false; cleanup();

    max = total;
    program = new char[max];
    if(program == NULL) return;

    clear();

    init = true;
}

void schema::clear()
{
    length = 0; PC = 0;
    memset(program, 0, max);    
}

void schema::create(int depth, int varnumber, int randnumber)
{
    int len = grow(0,MAX,depth,varnumber, randnumber);

    while(len < 0)
    {
        len = grow(0,MAX,depth, varnumber, randnumber);
    }
}
double schema::run(double *x)
{
    char primitive = program[PC++];
    
    if(primitive < FSET_START)
        return (x[primitive]);
    
    switch(primitive) 
    {
        case ADD : return run(x) + run(x);
        case SUB : return run(x) - run(x);
        case MUL : return run(x) * run(x);
        case DIV : {
            double num = run(x), den = run(x);
            if(abs(den) <= 0.001)
                return num;
            else return num / den;
        }
    }

    return 0.0;
}

double schema::fitness(int fitnesscases, int varnumber, double *x, double *targets)//char *prog)
{
    int i=0, len;
    double result, fit = 0.0;

    //len = traverse(prog, 0);
    len = traverse(0);
    for(i=0;i<fitnesscases;i++)
    {
        for(int j=0;j<varnumber;j++)
        {
            x[j] = targets[i,j];                
        }

        //program = source.program;
        PC = 0;
        result = run(x);
        fit += abs(result = targets[i,varnumber]);
    }

    return (-fit);
}

schema schema::crossover(schema &parent1, schema &parent2)
{
    int xo1start, xo1end, xo2start, xo2end;
    schema offspring;

    int len1 = parent1.traverse(0);
    int len2 = parent2.traverse(0);
    int lenoff;

    std::uniform_int_distribution<int> rand1{ 0, len1 };
    std::uniform_int_distribution<int> rand2{ 0, len2 };

    xo1start = rand1(generator);
    xo1end = parent1.traverse(xo1start);

    xo2start = rand2(generator);
    xo2end = parent2.traverse(xo2start);

    lenoff = xo1start + (xo2end - xo2start) + (len1 - xo1end);

    offspring.length = lenoff;

    memcpy(offspring.program, parent1.program, xo1start);
    memcpy(&offspring.program[xo1start], &parent2.program[xo2start], xo2end - xo2start);
    memcpy(&offspring.program[xo1start + (xo2end - xo2start)], &parent1.program[xo1end], len1 - xo1end);

    return offspring;
}

schema schema::mutation(schema &parent, int varnumber, double pmut)
{
      std::uniform_real_distribution<double> rand1{ 0, 1.0 };

    int len = parent.traverse(0);
    int i;
    int mutsite;
    schema parentcopy(parent);

    for(i=0;i<len;++i)
    {
        if(rand1(generator) , pmut)
        {
            mutsite = i;
            if(parentcopy.program[mutsite] < FSET_START)
            {
                std::uniform_int_distribution<int> rand2{ 0, varnumber };
                parentcopy.program[mutsite] = (char) rand2(generator);
            }
            else
            {
                switch(parentcopy.program[mutsite])
                {
                    case ADD:
                    case SUB:
                    case MUL:
                    case DIV:
                    {
                        std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START + 1 };
                        parentcopy.program[mutsite] = (char)rand3(generator) + FSET_START;
                    }
                }
            }
        }
    }

    return parentcopy;
}

int schema::traverse(int buffercount)
{
    if(program[buffercount] < FSET_START)
        return ++buffercount;

    switch(program[buffercount]) {
        case ADD: 
        case SUB:
        case MUL:
        case DIV:
        return (traverse(traverse(++buffercount)));
    }

    return 0;
}

int schema::grow(int pos, int max, int depth, int varnumber, int randnumber)
{
    std::uniform_int_distribution<int> rand{ 0, 2 };

    char prim = (char)rand(generator);

    if(pos >= max) return -1;

    if(pos == 0) prim = 1;

    if(prim == 0 || depth == 0)
    {
        std::uniform_int_distribution<int> randy{ 0, varnumber + randnumber };
        prim = (char) randy(generator);
        program[pos] = prim;
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
                program[pos] = prim;
                return grow(grow(pos + 1,max, depth-1, varnumber, randnumber), max, depth-1, varnumber, randnumber);
        }
    }

    return 0;
}

int schema::print_indiv(int buffercounter, int varnumber, double *x) 
{
    int a1=0, a2;

    if(program[buffercounter] < FSET_START) 
    {
        if(program[buffercounter] < varnumber)            
            std::cout << "X" << program[buffercounter] + 1 << "_";
        else
            std::cout << x[program[buffercounter]];
        
        return ++buffercounter;
    }

    switch(program[buffercounter]) 
    {
        case ADD:
            std::cout << "(";
            a1 = print_indiv(++buffercounter, varnumber, x);
            std::cout << " + ";
            break;
        case SUB:
            std::cout << "(";
            a1 = print_indiv(++buffercounter, varnumber, x);
            std::cout << " - ";
            break;
        case MUL:
            std::cout << "(";
            a1 = print_indiv(++buffercounter, varnumber, x);
            std::cout << " * ";
            break;
        case DIV:
            std::cout << "(";
            a1 = print_indiv(++buffercounter, varnumber, x);
            std::cout << " / ";
            break;
    }

    a2 = print_indiv(a1, varnumber, x);
    std::cout << ")";

    return a2;
}

void schema::copy(const schema &source)
{
    memcpy(program, source.program, max);
    length = source.length;
}

void schema::makeNull()
{
    program = NULL;
}

void schema::cleanup()
{
    if(program != NULL) delete program;
}
