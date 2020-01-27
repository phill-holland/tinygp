#include "schema.h"
#include <string.h>
#include <iostream>

std::mt19937_64 schema::schema::generator(std::random_device{}());

void schema::schema::reset(int total)
{
    init = false; cleanup();

    max = total;
    program = new char[max];
    if(program == NULL) return;

    clear();

    init = true;
}

void schema::schema::clear()
{
    length = 0; PC = 0;
    memset(program, 0, max);    
}

int schema::schema::traverse(int buffercount)
{
    if (program[buffercount] < FSET_START)
      return ++buffercount;
    
    switch(program[buffercount]) 
    {
      case ADD: 
      case SUB: 
      case MUL: 
      case DIV: 
    
      return traverse(traverse(++buffercount));
    }

    return 0;
}

void schema::schema::crossover(schema::base *parent1, schema::base *parent2)
{
    clear();

   int xo1start, xo1end, xo2start, xo2end;

    int len1 = parent1->traverse(0);
    int len2 = parent2->traverse(0);
    
    std::uniform_int_distribution<int> rand{ 0, len1 - 1 };

    xo1start =  rand(generator);
    xo1end = parent1->traverse(xo1start);
    
    std::uniform_int_distribution<int> rand2{ 0, len2 - 1 };

    xo2start =  rand2(generator);
    xo2end = parent2->traverse(xo2start);
    
    length = xo1start + (xo2end - xo2start) + (len1-xo1end);

    schema t1 = *reinterpret_cast<schema*>(parent1);
    schema t2 = *reinterpret_cast<schema*>(parent2);

    memcpy(program,t1.program,xo1start);
    memcpy(&program[xo1start],&t2.program[xo2start],(xo2end - xo2start));
    memcpy(&program[xo1start + (xo2end - xo2start)], &t1.program[xo1end], (len1-xo1end));
}

void schema::schema::mutate(double pmut, int varnumber, int randomnumber)
{
    int len = traverse(0), i;
    int mutsite;

    std::uniform_real_distribution<double> rand{ 0, 1.0 };
    std::uniform_int_distribution<int> rand2{ 0, varnumber+randomnumber - 1 };
    std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START };

    for (i = 0; i < len; i ++) 
    {  
        if (rand(generator) < pmut) 
        {
            mutsite = i;
            if (program[mutsite] < FSET_START)
                program[mutsite] = (char) rand2(generator);
            else
                switch(program[mutsite]) 
                {
                    case ADD: 
                    case SUB: 
                    case MUL: 
                    case DIV:
                    program[mutsite] = (char) rand3(generator);
                }
        }
    }
}

int schema::schema::grow(int pos, int max, int depth,int varnumber, int randomnumber) 
{
    std::uniform_int_distribution<int> rand{ 0, 1 };

    char prim = (char)rand(generator);
    int one_child;

    if (pos >= max) 
        return -1;

    if (pos == 0)
        prim = 1;

    if (prim == 0 || depth == 0) 
    {
        std::uniform_int_distribution<int> rand2{ 0, varnumber + randomnumber - 1 };

        prim = (char)rand2(generator);
        program[pos] = prim;
        return(pos+1);
    }
    else  
    {
        std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START };
        prim = (char)rand3(generator) + FSET_START;
        switch(prim) 
        {
            case ADD: 
            case SUB: 
            case MUL: 
            case DIV:
            program[pos] = prim;
            one_child = grow(pos+1, max,depth-1, varnumber, randomnumber);
            if (one_child < 0) return -1;
            return(grow(one_child, max,depth-1, varnumber, randomnumber));
        }
    }

    return 0;
}
  
int schema::schema::print(int buffercounter, double *x, int varnumber) 
{
    int a1=0, a2;
    if (program[buffercounter] < FSET_START) 
    {
        if (program[buffercounter] < varnumber)
        {
            std::cout <<  "X" << (program[buffercounter] + 1 ) <<  " ";
        }
        else std::cout << x[program[buffercounter]];
        return ++buffercounter;
    }
    switch(program[buffercounter]) 
    {
        case ADD: std::cout << "(";
        a1=print( ++buffercounter,x,varnumber); 
        std::cout << " + "; 
        break;
        case SUB: std::cout << "(";
        a1=print( ++buffercounter,x,varnumber); 
        std::cout << " - "; 
        break;
        case MUL: std::cout << "(";
        a1=print( ++buffercounter,x,varnumber); 
        std::cout <<  " * "; 
        break;
        case DIV: std::cout <<  "(";
        a1=print( ++buffercounter,x,varnumber); 
        std::cout << " / "; 
        break;
    }

    a2=print(a1,x,varnumber); 
    std::cout << ")"; 
    return a2;
}

void schema::schema::create(int depth, int varnumber, int randomnumber) 
{
    int len = grow(0, MAX, depth, varnumber, randomnumber);
    while (len < 0) len = grow(0, MAX, depth, varnumber, randomnumber);
}

double schema::schema::run(double *x) 
{
    char primitive = program[PC++];
    if ( primitive < FSET_START )
      return(x[primitive]);
    switch (primitive) 
    {
      case ADD : return( run(x) + run(x) );
      case SUB : return( run(x) - run(x) );
      case MUL : return( run(x) * run(x) );
      case DIV : 
      { 
        double num = run(x), den = run(x);
        if ( abs( den ) <= 0.001 ) 
          return( num );
        else 
          return( num / den );
      }
    }

   return 0.0;
}
       
double schema::schema::fitness(int fitnesscases, int varnumber, double *x, double *targets)
{
    int i = 0, len;
    double result, fit = 0.0;

    len = traverse(0);
    for (i = 0; i < fitnesscases; i ++) 
    {    
        for (int j = 0; j < varnumber; j ++)
        {
            x[j] = targets[i,j];
        }

        PC = 0;
        result = run(x);
        fit += abs( result - targets[i,varnumber]);
    }

    return -fit;
}

void schema::schema::copy(const schema &source)
{
    memcpy(program, source.program, source.max);
    length = source.length;
    max = source.max;
}

void schema::schema::copy(schema::base *source)
{
    schema t1 = *reinterpret_cast<schema*>(source);
    copy(t1);
}

void schema::schema::makeNull()
{
    program = NULL;
}

void schema::schema::cleanup()
{
    if(program != NULL) delete[] program;
}
