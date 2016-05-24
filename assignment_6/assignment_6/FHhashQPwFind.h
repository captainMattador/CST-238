/*
 Assignment: Assignment 6 - Quadratic Probing with a find()
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Purpose: Extends FHhashQP.h to include a find method
 
 pre-condition: is a pbublic function and 
 takes one paramater with the name of key
 post-condition: key represents the location of the desired object which is
 found by a client supplied hash function
 const Object find(const KeyType & key);
 
 */

#ifndef FHHASHQPWFIND_H
#define FHHASHQPWFIND_H
#include "FHhashQP.h"

template <class Object, typename KeyType>
class FHhashQPwFind: public FHhashQP<Object>
{

public:
   const Object find(const KeyType & key);
   class NotFoundException {};

protected:
   int myHashKey(const KeyType & key) const;
   int findPosKey( const KeyType & key ) const;

};



/********************** public ************************/

template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key)
{

   typename FHhashQP<Object>::HashEntry searchResult =
         this->mArray[findPosKey(key)];

   if(searchResult.state != FHhashQP<Object>::ACTIVE )
      throw NotFoundException();
   
   return searchResult.data;

}



/********************** Protected ********************/

// redfined to use key
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const
{
   int hashVal;

   hashVal = Hash(key) % this->mTableSize;
   if(hashVal < 0)
      hashVal += this->mTableSize;

   return hashVal;
}


// redfined to use key
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey( const KeyType & key ) const
{
   int kthOddNum = 1;
   int index = this->myHashKey(key);

   while ( this->mArray[index].state != FHhashQP<Object>::EMPTY
          && getKey( this->mArray[index].data ) != key )
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;      // compute next odd #
      if ( index >= this->mTableSize )
         index -= this->mTableSize;
   }

   return index;
}


#endif



