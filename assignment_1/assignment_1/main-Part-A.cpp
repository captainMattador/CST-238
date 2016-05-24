
/*
 Assignment:  Assignment 1 - The Subset-Sum Problem
 File - Main-Part-A.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Solving the algorithm of the Subset-Sum Problem based
 on different data types and timing the outcome.
*/

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

/*
 Sublist Class Template

 showSubList();
 Pre-Condition: Accepts no paramters
 Post-Condition: Prints out the Sublist to the console

 addItem();
 Pre-Condition: Accepts one paramter named indexOfItemToAdd
 Post-Condition: Creates a new Sublist based off of the current Sublist
 and adds indexOfItemToAdd to the newly created Sublist.

 vector<int> *masterSet;
 holds a pointer to the original dataset that Sublist is based off of

 vector<int> subListItems;
 holds the indexes to each element of subList relative to masterSet
*/
class Sublist{
public:
   Sublist(vector<int> *master = NULL)
      : listSum(0), masterSet(master){};
   ~Sublist();
   void showSublist() const;
   Sublist addItem( int indexOfItemToAdd );
   int getSum() const;
private:
   vector<int> *masterSet;
   vector<int> subListItems;
   int listSum;
};


int main() {

   const int TARGET = 14;
   vector<int> dataSet;
   vector<Sublist> choices;
   vector<Sublist>::iterator iter, iterBest;
   int k, j, numSets, max, masterSum;
   bool foundPerfect = false;

   dataSet.push_back(15);
   dataSet.push_back(5);
   dataSet.push_back(3);
   dataSet.push_back(1);
   dataSet.push_back(5);
   max = 0;
   max = 20 + 12 + 22 + 15 + 25 + 19 + 29 + 18 + 11 + 13 + 17;

   cout << "Target time: " << TARGET << endl;

   if( TARGET > max ){
      cout << "\nThe Target is greater than the sum of all data elements.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create the initial empty set
   Sublist emptySet(&dataSet);
   choices.push_back(emptySet);
   numSets = 1;
   masterSum = 0;

   for(k = 0; k < dataSet.size(); ++k){

      if(foundPerfect)
         break;

      for(j = 0; j < numSets; ++j){

         if( (choices[j].getSum() + dataSet[k]) <= TARGET ){
            Sublist newSubList = choices[j].addItem(k);
            choices.push_back(newSubList);

            if(newSubList.getSum() > masterSum){
               masterSum = newSubList.getSum();
               iterBest = choices.end() - 1;
            }
         }

         if( (choices[j].getSum() + dataSet[k]) == TARGET ){
            foundPerfect = true;
            break;
         }

      }

      numSets = choices.size();
   }

   // how we determine the time elapsed -------------------
   stopTime = clock();

   iterBest->showSublist();

   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   return 0;
}



// SubList member functions

Sublist::~Sublist(){}

void Sublist::showSublist() const{

   cout << "\nSublist -----------------------------\n"
        << "Sum: " << getSum() << endl;

   for( int i = 0; i < subListItems.size(); i++ ){
      cout << "array[" << i << "] = " << (*masterSet)[subListItems[i]] << ";\n";
   }

   cout << endl << endl;

}

Sublist Sublist::addItem( int indexOfItemToAdd ){

   Sublist newSubList;
   newSubList.masterSet = this->masterSet;
   newSubList.listSum = this->listSum;
   newSubList.listSum += (*masterSet)[indexOfItemToAdd];
   newSubList.subListItems = this->subListItems;
   newSubList.subListItems.push_back( indexOfItemToAdd );

   return newSubList;

}

int Sublist::getSum() const {

   return listSum;

}


// Sample runs -----------------------

/*
 Sample Run 1 ------------------------

 Target time: 201

 Sublist -----------------------------
 Sum: 201
 array[0] = 20;
 array[1] = 12;
 array[2] = 22;
 array[3] = 15;
 array[4] = 25;
 array[5] = 19;
 array[6] = 29;
 array[7] = 18;
 array[8] = 11;
 array[9] = 13;
 array[10] = 17;



 Algorithm Elapsed Time: 0.002159 seconds.

 Program ended with exit code: 0
 
 

 Sample Run 2 ------------------------
 
 Sublist -----------------------------
 Sum: 179
 array[0] = 20;
 array[1] = 12;
 array[2] = 15;
 array[3] = 25;
 array[4] = 19;
 array[5] = 29;
 array[6] = 18;
 array[7] = 11;
 array[8] = 13;
 array[9] = 17;



 Algorithm Elapsed Time: 0.002193 seconds.

 Program ended with exit code: 0
 

 
 Sample Run 3 ------------------------
 
 Target time: 127

 Sublist -----------------------------
 Sum: 127
 array[0] = 20;
 array[1] = 12;
 array[2] = 22;
 array[3] = 25;
 array[4] = 19;
 array[5] = 29;



 Algorithm Elapsed Time: 0.000201 seconds.

 Program ended with exit code: 0
 


 Sample Run 4 ------------------------
 
 Target time: 73

 Sublist -----------------------------
 Sum: 73
 array[0] = 20;
 array[1] = 12;
 array[2] = 22;
 array[3] = 19;



 Algorithm Elapsed Time: 9.6e-05 seconds.

 Program ended with exit code: 0
 
 

 Sample Run 5 ------------------------

 Target time: 99999

 The Target is greater than the sum of all data elements.
 Program ended with exit code: 1

*/






