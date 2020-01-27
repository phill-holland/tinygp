#include <random>

#ifndef SCHEMA
#define SCHEMA

namespace schema
{
    class base
    {
    public:
        virtual int traverse(int buffercount) = 0;
        virtual void crossover(base *parent1, base *parent2) = 0;
        virtual void mutate(double pmut, int varnumber, int randomnumber) = 0;

        virtual double run(double *x) = 0;
        virtual double fitness(int fitnesscases, int varnumber, double *x, double *targets) = 0;

        virtual int print(int buffercounter, double *x, int varnumber) = 0;
        virtual void create(int depth, int varnumber, int randomnumber) = 0;

        virtual void copy(base *source) = 0;
    };

    class factory
    {
    public:
        virtual base *create() = 0;
    };

    class schema : public base
    {
        static const int ADD = 110;
        static const int SUB = 111;
        static const int MUL = 112;
        static const int DIV = 113;

        static const int FSET_START = ADD;
        static const int FSET_END = DIV;

        static std::mt19937_64 generator;
        const static int MAX = 10000;

        int PC;

        int max, length;    
        bool init;

    public:
        char *program;

    public:
        schema(int total = MAX) { makeNull(); reset(total); }
        schema(const schema &source) { makeNull(); reset(source.max); copy(source); }
        ~schema() { cleanup(); }

        bool initalised() { return init; }
        void reset(int total);

        void clear();
        int total() { return length; }
        
        int traverse(int buffercount);
        void crossover(schema::base *parent1, schema::base *parent2);
        void mutate(double pmut, int varnumber, int randomnumber);

        double run(double *x);
        double fitness(int fitnesscases, int varnumber, double *x, double *targets);

        int grow(int pos, int max, int depth, int varnumber, int randomnumber);  
        int print(int buffercounter, double *x, int varnumber);

        void create(int depth, int varnumber, int randomnumber);

        void copy(const schema &source);
        void copy(schema::base *source);

    public:
        schema operator=(const schema &src) { clear(); copy(src); return *this; }

    protected:
        void makeNull();
        void cleanup();
    };
};

#endif