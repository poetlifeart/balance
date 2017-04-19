#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <new>
#include<cmath>
#include "Treenode.h"
#include "plotter.h"
#include <string>
using namespace std;

// Tree class-template definition
template< typename NODETYPE > class Tree
{
public:
	  
   Tree(double d); // constructor
   ~Tree();
   void insertNode( const NODETYPE & );

 TreeNode< NODETYPE > * compression(TreeNode< NODETYPE >  *, int );
    double xcor = 1500;
    double ycor=2500;  
    double dimension;
 
   void vine_to_tree ( TreeNode< NODETYPE > * , int );
   void tree_to_vine (  TreeNode< NODETYPE >*  );
   void dsw();
private:
   TreeNode< NODETYPE > *rootPtr;
    plotter* plotbst;
    plotter* plotdsw;
   
 
   
   // utility functions
   void insertNodeHelper( TreeNode< NODETYPE > **, const NODETYPE & );
   void preOrderHelper( TreeNode< NODETYPE > * , double d, double xcor, double ycor, double depth, string stg, plotter *plot ) ;

}; // end class Tree

// constructor
template< typename NODETYPE >
Tree< NODETYPE >::Tree(double d) 
{ 

   plotbst = new plotter(3000, 3000);
   plotdsw = new plotter(3000, 3000);
           
   dimension=d;
        // plot it
      
   rootPtr = 0; // indicate tree is initially empty 
 
} // end Tree constructor



template <typename NODETYPE>
Tree<NODETYPE>::~Tree(){
	
	delete plotbst;
	delete plotdsw;
}

// insert node in Tree
template< typename NODETYPE >
void Tree< NODETYPE >::insertNode( const NODETYPE &value )
{ 
   insertNodeHelper( &rootPtr, value ); 
   
    
             
} // end function insertNode



// utility function called by insertNode; receives a pointer
// to a pointer so that the function can modify pointer's value
template< typename NODETYPE >
void Tree< NODETYPE >::insertNodeHelper( 
   TreeNode< NODETYPE > **ptr, const NODETYPE &value )
{
   // subtree is empty; create new TreeNode containing value
   if ( *ptr == 0 )  
      *ptr = new TreeNode< NODETYPE >( value );
   else // subtree is not empty
   {
      // data to insert is less than data in current node
      if ( value < ( *ptr )->data )
         insertNodeHelper( &( ( *ptr )->leftPtr ), value );
      else
      {
         // data to insert is greater than data in current node
         if ( value > ( *ptr )->data )
            insertNodeHelper( &( ( *ptr )->rightPtr ), value );
         else // duplicate data value ignored
            cout << value << " dup" << endl;
      } // end else
   } // end else
} // end function insertNodeHelper



    template< typename NODETYPE >
    void Tree< NODETYPE >:: dsw()
    { 


    TreeNode <NODETYPE>  *troot;

    TreeNode< NODETYPE > base( 0);
  
    preOrderHelper( rootPtr, 0, 1500, 2500, 0, "bst" , plotbst); 

    troot=&base;

    troot->rightPtr=rootPtr;

    tree_to_vine (  troot );

    troot->rightPtr=this->rootPtr;
 
    vine_to_tree (  troot,  dimension );
 
    } 




template< typename NODETYPE >
void Tree< NODETYPE >:: tree_to_vine (  TreeNode< NODETYPE > *root )
{  TreeNode< NODETYPE > *vineTail, *remainder, *tempPtr;


  

   int flag=0;
   vineTail = root;
   remainder = vineTail->rightPtr;
    

   while ( remainder != NULL )
   {//If no leftward subtree, move rightward
   if ( remainder->leftPtr== NULL )
       
      {    flag=1;
	  
	 vineTail = remainder;
         remainder = remainder->rightPtr;
       

      
      }
    //else eliminate the leftward subtree by rotations
      else  // Rightward rotation
      {  tempPtr = remainder->leftPtr;
         remainder->leftPtr = tempPtr->rightPtr;
         tempPtr->rightPtr = remainder;
         remainder = tempPtr;
         vineTail->rightPtr = tempPtr;
         
         
      }
      
      if (flag==0) {
	  rootPtr=tempPtr;  
//	  flag=1; 
	  }       
   }
  
}


template< typename NODETYPE >
TreeNode< NODETYPE >* Tree< NODETYPE >::compression(TreeNode< NODETYPE >  *root, int count)
{TreeNode< NODETYPE >  *child ;
 TreeNode< NODETYPE > *scanner;
 TreeNode< NODETYPE > *next;
int flag=0;
      next=root;
      scanner=root;



   for ( int j = 0; j < count; j++ )
   {//Leftward rotation
       child = scanner->rightPtr;
      scanner->rightPtr = child->rightPtr;
      
      if(flag==0){	
      	next=scanner;
      	flag=flag+1;
	  }
      
      scanner = scanner->rightPtr;
      child->rightPtr = scanner->leftPtr;
      scanner->leftPtr = child;
   
      
   }  // end for
   
  return next;
}  // end compression



// Loop structure taken directly from Day's code
template< typename NODETYPE >
void Tree< NODETYPE >::vine_to_tree ( TreeNode< NODETYPE > * root, int size  )
{ 


 int NBack = size - 1;
TreeNode< NODETYPE >* next=root;

int m=0;
int l=0;

l= log2(size+1);
m=pow(2, l)-1;


cout<<"size-m  "<<size-m<<endl;
if (size-m !=0){
	next=  compression (  next, size-m );
//preOrderHelper(  next->rightPtr );
}



while (m>1)
    { 
  
next=  compression (  next, m /=2 );
//preOrderHelper(  next->rightPtr );
         
 }
   
 preOrderHelper( next->rightPtr, 0, 1500, 2500, 0, "dsw", plotdsw ); 
    
}


template< typename NODETYPE >
void Tree< NODETYPE >::preOrderHelper( TreeNode< NODETYPE > *ptr, double d, double xcorr, double ycorr, double depth, string stg, plotter *plot ) 
{ //  double s=0.9*log2(dimension);
   double s=log2(4*dimension);
   if ( ptr != 0 ) 
   {
   	        
	cout << ptr->data << ' '; // process node   
	
	
	 if(d !=0){
		
       plot->plot( xcorr, ycorr, 6, s, d, depth, stg);
	     
	     
	  if (d==-1)
	{
	    xcorr=xcorr-(abs(d))*3000/(s*depth);
	    ycorr=ycorr-(abs(d))*3000/(s*depth);
	   }
	   else{
	     
	   xcorr= xcorr+(abs(d))*3000/(s*depth);
	   ycorr= ycorr-(abs(d))*3000/(s*depth);		  
             
 }
 }
		      
    preOrderHelper( ptr->leftPtr, -1, xcorr, ycorr, depth+1, stg, plot ); // traverse left subtree    
     
    preOrderHelper( ptr->rightPtr, 1,  xcorr, ycorr, depth+1, stg , plot); // traverse right subtree
    
   } // end if
} // end function preOrderHelper





#endif


