#include "schema.h"
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

    //std::cout << "schema:;reset\n";
    init = true;
}

void schema::clear()
{
    length = 0; PC = 0;
    memset(program, 0, max);    
}

void schema::create(int depth, int varnumber, int randnumber)
{
    clear();
    length = grow(0, depth, varnumber, randnumber);
    while(length <= 0)
    {
        length = grow(0, depth, varnumber, randnumber);
    }

    //std::cout << "create len " << length << "\n";
   // while(!grow(varnumber, randnumber));
}
/*
double schema::run(double *x)
{
    char primitive = program[PC++];
    
    std::cout << "PC " << PC << " prim " << ((int)primitive) << std::endl;

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
*/
  double schema::run(double *x) { /* Interpreter */
      //output();
    char primitive = program[PC++];
    if ( primitive < FSET_START )
    {
        //std::cout << "prim " << ((int)primitive) << " " << x[primitive] << "\n";        
        return(x[primitive]);
    }

    switch ( primitive ) {
      case ADD : return( run(x) + run(x) );
      case SUB : return( run(x) - run(x) );
      case MUL : return( run(x) * run(x) );
      case DIV : { 
        double num = run(x), den = run(x);
        if ( abs( den ) <= 0.001 ) 
          return( num );
        else 
          return( num / den );
        }
      }
    return( 0.0 ); // should never get here
  }
          
double schema::fitness(int fitnesscases, int varnumber, double *x, double *targets)//char *prog)
{
    int i=0, len;
    double result, fit = 0.0;

//std::cout << "here fitness a\n";
    //len = traverse(prog, 0);
    len = traverse(0);
    //std::cout << "len " << len << "\n";
    //std::cout << "here fitness b\n";
    for(i=0;i<fitnesscases;i++)
    {
        //std::cout << "here fitness c\n";
        for(int j=0;j<varnumber;j++)
        {
            x[j] = targets[i,j];           
           // std::cout << "x[j] " << j << " " << x[j] << "\n";     
        }
//std::cout << "here fitness d\n";
        //program = source.program;
        PC = 0;
        //std::cout << "here fitness e\n";
        result = run(x);
        //std::cout << "here fitness " << result << "\n";
        fit += abs(result - targets[i,varnumber]);
    }
//std::cout << "here fitness g\n";
    return (-fit);
}

schema schema::crossover(schema &parent1, schema &parent2)
{
    
    int xo1start, xo1end, xo2start, xo2end;
    schema offspring;

if((parent1.total()==0)||(parent2.total()==0)) return offspring;
    
  //  std::cout << "corssover a\n";
    int len1 = parent1.traverse(0);//total();//traverse(0);
    int len2 = parent2.traverse(0);//total();//traverse(0);
    int lenoff;
    
//std::cout << "corssover b\n";
    std::uniform_int_distribution<int> rand1{ 0, len1 };
    std::uniform_int_distribution<int> rand2{ 0, len2 };

    xo1start = rand1(generator);
    xo1end = parent1.traverse(xo1start);
    if(xo1end > len1) xo1end = len1;

    xo2start = rand2(generator);
    xo2end = parent2.traverse(xo2start);
    if(xo2end > len2) xo2end = len2;

//std::cout << "corssover c\n";
    lenoff = xo1start + (xo2end - xo2start) + (len1 - xo1end);

    offspring.length = lenoff;

/*
std::cout << "corssover d " << lenoff << " len1 " << len1 << " len2 " << len2 << "\n";

std::cout << "xo1start " << xo1start << "\n"; 
std::cout << "xo1end " << xo1end << "\n"; 

std::cout << "xo2start " << xo2start << "\n"; 
std::cout << "xo12nd " << xo2end << "\n"; 

std::cout << "xo2end - xo2start " << (xo2end - xo2start) << "\n";
std::cout << "xo1start + (xo2end - xo2start)" << (xo1start + (xo2end - xo2start)) << "\n";
std::cout << "len1 - xo1end " << (len1 - xo1end) << "\n";
*/
    memcpy(offspring.program, parent1.program, xo1start);
    memcpy(&offspring.program[xo1start], &parent2.program[xo2start], xo2end - xo2start);
    memcpy(&offspring.program[xo1start + (xo2end - xo2start)], &parent1.program[xo1end], len1 - xo1end);

/*
    std::cout << "parent1\n";
    parent1.print();

    std::cout << "parent2\n";
    parent2.print();

    std::cout << "offsrping\n";
    offspring.print();
*/
//std::cout << "corssover e \n";

//    int lenny = offspring.total();//offspring.traverse(0);
//    std::cout << "lenny " << lenny << "\n";
    
    return offspring;
}

void schema::print()
{
    for(int k=0;k<length;++k)
    {
        char p = program[k];

        if(p == ADD) std::cout << "ADD ";
        else if(p == SUB) std::cout << "SUB ";
        else if(p == DIV) std::cout << "DIV ";
        else if(p == MUL) std::cout << "MUL ";
        else std::cout << ((int)p) << " ";
        
    }

    std::cout << "\n";
}

schema schema::mutation(schema &parent, int varnumber, double pmut)
{
      std::uniform_real_distribution<double> rand1{ 0, 1.0 };

    int len = parent.total();//parent.traverse(0);
    int i;
    int mutsite;
    schema parentcopy(parent);

    for(i=0;i<len;++i)
    {
        if(rand1(generator) < pmut)
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
                    
                        std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START + 1 };
                        parentcopy.program[mutsite] = (char)rand3(generator) + FSET_START;
                    
                }
            }
        }
    }

    return parentcopy;
}


  int schema::traverse(int buffercount ) {
    if ( program[buffercount] < FSET_START )
      return( ++buffercount );
    
    if(buffercount >= length - 1) return buffercount;

    switch(program[buffercount]) {
      case ADD: 
      case SUB: 
      case MUL: 
      case DIV: 
      return( traverse(traverse(++buffercount ) ) );
      }
    return( 0 ); // should never get here
  }


/*
int schema::traverse(int buffercount)
{
    int len = total();

    do
    {
        if(program[buffercount] < FSET_START) return ++buffercount;

        //else ++buffercount;
        ++buffercount;
    }while((buffercount <  len)&&(buffercount < max));

    return buffercount;
}
*/

/*
int schema::traverse(int buffercount)
{
    if(buffercount >=max - 1) 
    {
        std::cout << "traversed maxxed\n";
        return 0;
    }

    //if(buffercount==0) std::cout << "suggarss\n";
    if((program[buffercount] < FSET_START) || (program[buffercount] == 0))    
    {
        //std::cout << "bing " << buffercount << "\n";
        return ++buffercount;
    }

    switch(program[buffercount]) {
        case ADD: 
        case SUB:
        case MUL:
        case DIV:
        return traverse(++buffercount);//(traverse(traverse(++buffercount)));
    }

    return 0;
}
*/
int schema::grow(int pos, int depth, int varnumber, int randnumber)
{
    //int pos = 0;
    //length = 0;
   // int depth = 5;

    std::uniform_int_distribution<int> rand{ 0, 2 };
    //bool running = true;

    //`do
    //{
        char prim = (char)rand(generator);
        if(pos >= max) return -1;
        if(pos == 0) prim = 1;

        if(prim == 0 || depth == 0)
        {
            std::uniform_int_distribution<int> randy{ 0, varnumber + randnumber };
            prim = (char) randy(generator);
            program[pos] = prim;
            return pos + 1;
           // ++length;
            //running = false;
        }
        else
        {
            std::uniform_int_distribution<int> randi{ 0, FSET_END - FSET_START + 1 };
            prim = (char)(randi(generator) + FSET_START);
            if((prim == ADD)||(prim == SUB)||(prim == DIV)||(prim == MUL))
            {
                program[pos] = prim;            
                int one_child = grow(pos+1,depth-1,varnumber,randnumber);
                if(one_child < 0) return -1;
                return grow(one_child,depth-1,varnumber,randnumber);
                //++length;
                //--depth;
            }
        }
    //}while((running)&&(length < max));

return 0;
//return true;
    //std::cout << "len " << length << "\n";
}

/*
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
*/

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
    memcpy(program, source.program, source.max);
    length = source.length;
    max = source.max;
}

void schema::makeNull()
{
    //std::cout << "schame:: makeNull\n";
    program = NULL;
}

void schema::cleanup()
{
    //std::cout << "schema::cleana\n";
    if(program != NULL) delete[] program;
    //std::cout << "schema::cleanb\n";
}
