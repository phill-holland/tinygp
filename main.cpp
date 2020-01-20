#include <iostream>
#include <string>
#include "genetic.h"

int main(int argc, char *argv[])
{
    std::string filename = "sin-data.dat";
    
    tiny_gp *gp = new tiny_gp(filename);
    
    //gp->evolve();

    delete gp;

    return 0;
}