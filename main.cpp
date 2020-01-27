#include <iostream>
#include <string>
#include "genetic.h"

class factory : public schema::factory
{
public:
    schema::base *create()
    {
        return new schema::schema();
    }
};

int main(int argc, char *argv[])
{
    std::string filename = "sin-data.txt";
    factory f;

    genetic *gp = new genetic(&f, filename);
    if(gp != NULL)
    {
        if(gp->initalised()) gp->evolve();
        delete gp;
    }

    return 0;
}