#include "bugger.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

std::mt19937_64 bugger::tiny_gp::generator(std::random_device{}());

double bugger::tiny_gp::fbestpop = 0.0;
double bugger::tiny_gp::favgpop = 0.0;
double bugger::tiny_gp::PMUT_PER_NODE  = 0.05;
double bugger::tiny_gp::CROSSOVER_PROB = 0.9;

double bugger::tiny_gp::run() 
{ /* Interpreter */
      //output();
    char primitive = program[PC++];
    if ( primitive < FSET_START )
      return(x[primitive]);
    switch ( primitive ) {
      case ADD : return( run() + run() );
      case SUB : return( run() - run() );
      case MUL : return( run() * run() );
      case DIV : { 
        double num = run(), den = run();
        if ( abs( den ) <= 0.001 ) 
          return( num );
        else 
          return( num / den );
        }
      }
    return( 0.0 ); // should never get here
  }
          
  int bugger::tiny_gp::traverse( char *buffer, int buffercount ) {
    if ( buffer[buffercount] < FSET_START )
      return( ++buffercount );
    
    switch(buffer[buffercount]) {
      case ADD: 
      case SUB: 
      case MUL: 
      case DIV: 
      return( traverse( buffer, traverse( buffer, ++buffercount ) ) );
      }
    return( 0 ); // should never get here
  }

    void bugger::tiny_gp::output(char *buffer)
    {
	int len = traverse(buffer,0);

	for(int i=0;i<len;++i)
        {
	    char p = buffer[i];

	    if(p == ADD) std::cout << "ADD ";
	    else if(p == SUB) std::cout << "SUB ";
	    else if(p == DIV) std::cout << "DIV ";
	    else if(p == MUL) std::cout << "MUL ";
	    else
	    {
		std::cout << (int)p << " ";
	    }
	}

	std::cout << " ";
    }
    
  void bugger::tiny_gp::setup_fitness(string filename) 
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
      /*
    try {
      int i,j;
      string line;
      
      BufferedReader in = 
      new BufferedReader(
      		    new
      		    FileReader(fname));
      line = in.readLine();
      StringTokenizer tokens = new StringTokenizer(line);
      varnumber = Integer.parseInt(tokens.nextToken().trim());
      randomnumber = Integer.parseInt(tokens.nextToken().trim());
      minrandom =	Double.parseDouble(tokens.nextToken().trim());
      maxrandom =  Double.parseDouble(tokens.nextToken().trim());
      fitnesscases = Integer.parseInt(tokens.nextToken().trim());
      targets = new double[fitnesscases][varnumber+1];
      if (varnumber + randomnumber >= FSET_START ) 
        System.out.println("too many variables and constants");
      
      for (i = 0; i < fitnesscases; i ++ ) {
        line = in.readLine();
        tokens = new StringTokenizer(line);
        for (j = 0; j <= varnumber; j++) {
          targets[i][j] = Double.parseDouble(tokens.nextToken().trim());
          System.out.print(targets[i][j]);
          System.out.print(" ");
      	}
        System.out.println(" ");
      }
      in.close();
    }
   catch(FileNotFoundException e) {
      System.out.println("ERROR: Please provide a data file");
      System.exit(0);
    }
    catch(Exception e ) {
      System.out.println("ERROR: Incorrect data format");
      System.exit(0);
    }
    */
  }

  double bugger::tiny_gp::fitness_function( char *Prog ) {
    int i = 0, len;
    double result, fit = 0.0;
    
    len = traverse( Prog, 0 );
    for (i = 0; i < fitnesscases; i ++ ) {
      for (int j = 0; j < varnumber; j ++ )
          x[j] = targets[i,j];
      program = Prog;
      PC = 0;
      result = run();
      fit += abs( result - targets[i,varnumber]);
      }
    return(-fit );
  }

  int bugger::tiny_gp::grow( char *buffer, int pos, int max, int depth ) 
  {
    std::uniform_int_distribution<int> rand{ 0, 1 };//2 };

    char prim = (char)rand(generator);
    //char prim = (char) rd.nextInt(2);
    int one_child;

    if ( pos >= max ) 
      return( -1 );
    
    if ( pos == 0 )
      prim = 1;
    
    if ( prim == 0 || depth == 0 ) 
    {
     std::uniform_int_distribution<int> rand2{ 0, varnumber + randomnumber - 1 };//2 };

      //prim = (char) rd.nextInt(varnumber + randomnumber);
      prim = (char)rand2(generator);
      buffer[pos] = prim;
      return(pos+1);
      }
    else  
    {
        std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START };//2 };
        prim = (char)rand3(generator) + FSET_START;
      //prim = (char) (rd.nextInt(FSET_END - FSET_START + 1) + FSET_START);
      switch(prim) {
      case ADD: 
      case SUB: 
      case MUL: 
      case DIV:
        buffer[pos] = prim;
	one_child = grow( buffer, pos+1, max,depth-1);
	if ( one_child < 0 ) 
		return( -1 );
        return( grow( buffer, one_child, max,depth-1 ) );
      }
    }
    return( 0 ); // should never get here
  }
  
  int bugger::tiny_gp::print_indiv( char *buffer, int buffercounter ) {
    int a1=0, a2;
    if ( buffer[buffercounter] < FSET_START ) {
      if ( buffer[buffercounter] < varnumber )
        std::cout <<  "X" << (buffer[buffercounter] + 1 ) <<  " ";
      else
        std::cout << x[buffer[buffercounter]];
      return( ++buffercounter );
      }
    switch(buffer[buffercounter]) {
      case ADD: std::cout << "(";
        a1=print_indiv( buffer, ++buffercounter ); 
        std::cout << " + "; 
        break;
      case SUB: std::cout << "(";
        a1=print_indiv( buffer, ++buffercounter ); 
        std::cout << " - "; 
        break;
      case MUL: std::cout << "(";
        a1=print_indiv( buffer, ++buffercounter ); 
        std::cout <<  " * "; 
        break;
      case DIV: std::cout <<  "(";
        a1=print_indiv( buffer, ++buffercounter ); 
        std::cout << " / "; 
        break;
      }
    a2=print_indiv( buffer, a1 ); 
    std::cout << ")"; 
    return( a2);
  }
  

  char * bugger::tiny_gp::create_random_indiv( int depth ) {
    char *ind;
    int len;

    len = grow( buffer, 0, MAX_LEN, depth );

    while (len < 0 )
      len = grow( buffer, 0, MAX_LEN, depth );

    ind = new char[len];

    memcpy(ind,buffer,len);
    //System.arraycopy(buffer, 0, ind, 0, len ); 

   // output(buffer);
    return( ind );
  }

  char **bugger::tiny_gp::create_random_pop(int n, int depth, double *fitness ) 
  {
    char **pop = new char*[n];
    int i;
    
    for ( i = 0; i < n; i ++ ) {
      pop[i] = create_random_indiv( depth );
      fitness[i] = fitness_function( pop[i] );
      }
    return( pop );
  }


  void bugger::tiny_gp::stats( double *fitness, char **pop, int gen ) 
  {
      std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };

    int i;//, best = rd.nextInt(POPSIZE);
    int best = rand(generator);
    int node_count = 0;
    fbestpop = fitness[best];
    favgpop = 0.0;

    for ( i = 0; i < POPSIZE; i ++ ) {
      node_count +=  traverse( pop[i], 0 );
      favgpop += fitness[i];
      if ( fitness[i] > fbestpop ) {
      best = i;
      fbestpop = fitness[i];
      }
    }
    avg_len = (double) node_count / POPSIZE;
    favgpop /= POPSIZE;
    std::cout << "Generation=" << gen << " Avg Fitness=" << (-favgpop) <<
    		 " Best Fitness=" << (-fbestpop) << " Avg Size=" << avg_len << 
    		 "\nBest Individual: ";
    print_indiv( pop[best], 0 );
    std::cout << "\n";
    //System.out.flush();
  }

  int bugger::tiny_gp::tournament( double *fitness, int tsize ) 
  {
      std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };
    //int best = rd.nextInt(POPSIZE), 
    int best = rand(generator);
    int i, competitor;
    double  fbest = -1.0e34;
    
    for ( i = 0; i < tsize; i ++ ) {
      competitor = rand(generator);//rd.nextInt(POPSIZE);
      if ( fitness[competitor] > fbest ) {
        fbest = fitness[competitor];
        best = competitor;
      }
    }
    return( best );
  }
  
  int bugger::tiny_gp::negative_tournament( double *fitness, int tsize ) 
  {
      std::uniform_int_distribution<int> rand{ 0, POPSIZE - 1 };

    int worst = rand(generator);//rd.nextInt(POPSIZE)
    int i, competitor;
    double fworst = 1e34;
    
    for ( i = 0; i < tsize; i ++ ) {
      competitor = rand(generator);//rd.nextInt(POPSIZE);
      if ( fitness[competitor] < fworst ) {
    	fworst = fitness[competitor];
    	worst = competitor;
        }
    }
    return( worst );
  }
  
  char *bugger::tiny_gp::crossover( char *parent1, char *parent2 ) {
    int xo1start, xo1end, xo2start, xo2end;
    char *offspring;
    int len1 = traverse( parent1, 0 );
    int len2 = traverse( parent2, 0 );
    int lenoff;
    
    std::uniform_int_distribution<int> rand{ 0, len1 - 1 };

    xo1start =  rand(generator);//rd.nextInt(len1);
    xo1end = traverse( parent1, xo1start );
    
    std::uniform_int_distribution<int> rand2{ 0, len2 - 1 };

    xo2start =  rand2(generator);//rd.nextInt(len2);
    xo2end = traverse( parent2, xo2start );
    
    lenoff = xo1start + (xo2end - xo2start) + (len1-xo1end);

    offspring = new char[lenoff];

    memcpy(offspring,parent1,xo1start);
    memcpy(&offspring[xo1start],&parent2[xo2start],(xo2end - xo2start));
    memcpy(&offspring[xo1start + (xo2end - xo2start)], &parent1[xo1end], (len1-xo1end));
    
    /*
    System.arraycopy( parent1, 0, offspring, 0, xo1start );
    System.arraycopy( parent2, xo2start, offspring, xo1start,  
    		  (xo2end - xo2start) );
    System.arraycopy( parent1, xo1end, offspring, 
    		  xo1start + (xo2end - xo2start), 
    		  (len1-xo1end) );
    */
    return( offspring );
  }
  
  char * bugger::tiny_gp::mutation( char *parent, double pmut ) 
  {
    int len = traverse( parent, 0 ), i;
    int mutsite;
    char *parentcopy = new char [len];
    
    memcpy( parentcopy, parent, len );

std::uniform_real_distribution<double> rand{ 0, 1.0 };
std::uniform_int_distribution<int> rand2{ 0, varnumber+randomnumber - 1 };
std::uniform_int_distribution<int> rand3{ 0, FSET_END - FSET_START };

    //System.arraycopy( parent, 0, parentcopy, 0, len );

    for (i = 0; i < len; i ++ ) {  
      //if ( rd.nextDouble() < pmut ) {
    if ( rand(generator) < pmut ) {
      mutsite =  i;
      if ( parentcopy[mutsite] < FSET_START )
        parentcopy[mutsite] = (char) rand2(generator);//rd.nextInt(varnumber+randomnumber);
      else
        switch(parentcopy[mutsite]) {
      	case ADD: 
      	case SUB: 
      	case MUL: 
      	case DIV:
           //parentcopy[mutsite] = (char) (rd.nextInt(FSET_END - FSET_START + 1) + FSET_START);
           parentcopy[mutsite] = (char) rand3(generator);//(rd.nextInt(FSET_END - FSET_START + 1) + FSET_START);
        }
      }
    }
    return( parentcopy );
  }
  
  void bugger::tiny_gp::print_parms() {
   std::cout << "-- TINY GP (Java version) --\n";
   std::cout << "SEED=" << seed << "\nMAX_LEN=" << MAX_LEN <<
   	    "\nPOPSIZE=" << POPSIZE << "\nDEPTH=" << DEPTH << 
     	    "\nCROSSOVER_PROB=" << CROSSOVER_PROB <<
     	    "\nPMUT_PER_NODE=" << PMUT_PER_NODE <<
     	    "\nMIN_RANDOM=" << minrandom << 
     	    "\nMAX_RANDOM=" << maxrandom <<
     	    "\nGENERATIONS=" << GENERATIONS << 
     	    "\nTSIZE=" << TSIZE << 
     	    "\n----------------------------------\n";
  }

  bugger::tiny_gp::tiny_gp( string fname ) {
    fitness =  new double[POPSIZE];
    //seed = s;
    //if ( seed >= 0 )
        //rd.setSeed(seed);
    setup_fitness(fname);

std::uniform_real_distribution<double> rand{ 0, 1.0 };

    for ( int i = 0; i < FSET_START; i ++ )
      //x[i]= (maxrandom-minrandom)*rd.nextDouble()+minrandom;
      x[i]= (maxrandom-minrandom)*rand(generator)+minrandom;
    pop = create_random_pop(POPSIZE, DEPTH, fitness );
  }

  void bugger::tiny_gp::evolve() {
      std::uniform_real_distribution<double> rand{ 0, 1.0 };
    int gen = 0, indivs, offspring, parent1, parent2, parent;
    double newfit;
    char *newind;
    print_parms();
    stats( fitness, pop, 0 );
    for ( gen = 1; gen < GENERATIONS; gen ++ ) {
      if (  fbestpop > -1e-5 ) {
      std::cout << "PROBLEM SOLVED\n";
      return;
      //System.exit( 0 );
      }
      for ( indivs = 0; indivs < POPSIZE; indivs ++ ) {
      //if ( rd.nextDouble() < CROSSOVER_PROB  ) {
          if ( rand(generator) < CROSSOVER_PROB  ) {
        parent1 = tournament( fitness, TSIZE );
        parent2 = tournament( fitness, TSIZE );
        newind = crossover( pop[parent1],pop[parent2] );
      }
      else {
        parent = tournament( fitness, TSIZE );
        newind = mutation( pop[parent], PMUT_PER_NODE );
      }
      newfit = fitness_function( newind );
      offspring = negative_tournament( fitness, TSIZE );
      pop[offspring] = newind;
      fitness[offspring] = newfit;
      }
      stats( fitness, pop, gen );
    }
    std::cout << "PROBLEM *NOT* SOLVED\n";
    //System.exit( 1 );
  }


