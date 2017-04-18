
#include <iostream>
#include<array>
#include <iomanip>
using std::setprecision;
using namespace std;

#include "Tree.h" // Tree class definition

int main()
{
	
  int dim=16;  
 
   Tree< int > intTree(16); // create Tree of int values
 
  
 //  int  value[dim]={ 21, 122, 3, 1, 43, 311, 31, 14, 236, 12, 4321, 5, 888, 444, 777, 222, 999, 111, 333, 555, 666,
  //  11122, 22211, 6677, 8899, 9988, 100000, 10101, 10293, 54023, 3213450, 4309004};
  
  
  
  int  value[dim]={ 21, 122, 3, 1, 43, 311, 31, 14, 236, 12, 4321, 5, 888, 444, 777, 222};
  
  
   for ( int i = 0; i < dim; i++ ) 
   {
     
      intTree.insertNode( value[i] );
   } // end for

  intTree.dsw();

   return 0;
} // end main


