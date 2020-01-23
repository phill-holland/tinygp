#include <iostream>
#include <string>
#include "genetic.h"
#include "bugger.h"

int main(int argc, char *argv[])
{
    std::string filename = "sin-data.txt";
    
    bugger::tiny_gp *gp = new bugger::tiny_gp(filename);
    if(gp != NULL)
    {
        gp->evolve();

        delete gp;
    }
    return 0;
}