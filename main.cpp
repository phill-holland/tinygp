#include <iostream>
#include <string>
#include "genetic.h"

int main(int argc, char *argv[])
{
    std::string filename = "sin-data.txt";
    
    tiny_gp *gp = new tiny_gp(filename);
    if(gp != NULL)
    {
        gp->evolve();

        delete gp;
    }
    return 0;
}