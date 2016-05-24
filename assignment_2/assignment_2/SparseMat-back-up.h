

/*
 Assignment:  Assignment 2 - Sparse Matrices
 File - SparseMat.h
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Class the handles the storing of the Matrice points
 
 // member data

 // vecor which represnts rows of matrices (each row holds a list)
 MasterCol rows;
 // default value if no value is given
 Object defaultVal;
 // the column and row size of matrice
 int rowSize, colSize;
 
 // member methods
 SparseMat( int r = 1, int c = 1, const Object& defaultVal = Object() );
 Pre-Condition: default constructor with optional params of r 
 representing numbers of rows and c represnting numbers of columns, and
 defaultVal which represents what the default value is (does not get stored)
 Post-Condition: Sets up the rows and columns for the matrice

 const Object& get(int r, int c) const;
 Pre-Condition: takes params r and c which represent the column and row
 to recieve the data from.
 Post-Condition: returns the value stored at column c and row r

 bool set(int r, int c, const Object &x);
 Pre-Condition: et(int r, int c) const;
 Pre-Condition: takes params r and c which represent the column and row
 and an Object that represents the data to be stored.
 Post-Condition: Stores the value at column c and row r.

 void clear();
 Pre-Condition: Accepts no paramters
 Post-Condition: Clears all values but in matrice but does not change it's
 list sizes.

 void showSubSquare(int start, int size);
 Pre-Condition: takes a parameter start and size which represents a sub square
 representation of where to print from
 Post-Condition: Prints out the Sub square to the console.

 */


#ifndef SparseMat_h
#define SparseMat_h

#include "MatNode.h"
#include "FHlist.h"
#include "FHvector.h"
#include <iomanip>
using namespace std;


template <class Object>
class SparseMat{

protected:

   typedef MatNode<Object> mNdoe;
   typedef FHlist< mNdoe > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;

public:

   SparseMat( int r = 1, int c = 1, const Object& defaultVal = Object() ) :
      rowSize(r), colSize(c), defaultVal(defaultVal){
         rows.resize(rowSize);
      };
   const Object& get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);
};



template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const{

   typename MatRow::const_iterator lIter, lIterBegin, lIterEnd;
   lIterBegin = rows[r].begin();
   lIterEnd = rows[r].end();

   if( r >= rowSize || c >= colSize )
      throw;

   for(lIter = lIterBegin; lIter != lIterEnd; ++lIter){
      if( c == (*lIter).getCol() )
         return (*lIter).data;
   }

   return defaultVal;
   
}




template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x){

   // if c is larger than colSize return false
   if( r >= rowSize || c >= colSize )
      return false;

   // define iterators and new node
   typename MatRow::iterator lIter, lIterBegin, lIterEnd;
   lIterBegin = rows[r].begin();
   lIterEnd = rows[r].end();
   mNdoe node( c, x );

   if( rows[r].size() == 0 && x != defaultVal ){
      rows[r].push_back( node );
   }else{
      for(lIter = lIterBegin; lIter != lIterEnd; ++lIter){

         // if c matches an existing col and x == default clear from list
         if( c == (*lIter).getCol() && x == defaultVal ){
            rows[r].erase( lIter );
            break;
         }

         // if c matches an existing col update the data
         else if (c == (*lIter).getCol()){
            (*lIter).data = x;
            break;
         }

         // else it must be new
         else{

            if( c < (*lIter).getCol() ){
               rows[r].insert( lIter , node );
            }else{
               rows[r].push_back( node );
            }
            break;
         }

      }
   }

   return true;

}






template <class Object>
void SparseMat<Object>::clear(){

   for(int i = 0; i < rowSize; ++i){

      typename MatRow::iterator lIter, lIterBegin, lIterEnd;
      lIterBegin = rows[i].begin();
      lIterEnd = rows[i].end();
      
      for(lIter = lIterBegin; lIter != lIterEnd; ++lIter){
         rows[i].erase(lIterBegin);
         lIter = rows[i].begin();
      }
 
   }

}



template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size){

   cout << endl;

   for(int i = start; i < start + size; ++i){

      for(int k = start; k < start + size; ++k){

         cout << setw(3) << get(i,k);

      }

      cout << endl;
   }

   cout << endl;
}




#endif
