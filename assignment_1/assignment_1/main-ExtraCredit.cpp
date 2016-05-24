/*
 Assignment:  Assignment 1 - The Subset-Sum Problem
 File - Main-ExtraCredit.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Solving the algorithm of the Subset-Sum Problem based
 on different data types and timing the outcome.
*/


#include <iostream>
#include <time.h>
#include <vector>
#include "iTunes.h"
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
 
   vector<T> *masterSet;
   holds a pointer to the original dataset that Sublist is based off of
   
   vector<int> subListItems;
   holds the indexes to each element of subList relative to masterSet
*/
template <class T>
class Sublist{
public:
   Sublist(vector<T> *master = NULL)
      : listSum(0), masterSet(master){};
   ~Sublist();
   void showSublist() const;
   Sublist addItem( int indexOfItemToAdd );
   int getSum() const;
private:
   vector<T> *masterSet;
   vector<int> subListItems;
   int listSum;
};


/*
   Overloaded opperator << for an iTunesEntry. Allows an iTunesEntry to
   be printed to the output
*/
ostream & operator<<( ostream& os, const iTunesEntry& entry )
{
   cout << entry.getTitle()
        << " by "
        << entry.getArtist()
        << " (" << entry.getTime() << "); ";
   return os;
}


/*
   Overloaded opperator + for an iTunesEntry. Allows an int and iTunesEntry to
   be added together. (based on the iTunesEntry song length)
*/
int operator +( int addative, const iTunesEntry& entry ){

   return addative + entry.getTime();

}


int main() {

   const int TARGET = 3600;
   vector<iTunesEntry> dataSet;
   vector<Sublist<iTunesEntry>> choices;
   vector<Sublist<iTunesEntry>>::iterator iter, iterBest;
   int k, j, numSets, max, masterSum, array_size;
   bool foundPerfect = false;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
      << " for input.\n";
      exit(1);
   }

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   max = 0;
   for (int k = 0; k < array_size; k++){
      dataSet.push_back(tunes_input[k]);
      max = max + tunes_input[k].getTime();
   }

   cout << "Target time: " << TARGET << endl;

   if( TARGET > max ){
      cout << "\nThe Target is greater than the sum of all data elements.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();
   
   // create the initial empty set
   Sublist<iTunesEntry> emptySet(&dataSet);
   choices.push_back(emptySet);
   numSets = 1;
   masterSum = 0;

   for(k = 0; k < dataSet.size(); ++k){

      if(foundPerfect)
         break;

      for(j = 0; j < numSets; ++j){

         if( (choices[j].getSum() + dataSet[k]) <= TARGET ){
            Sublist<iTunesEntry> newSubList = choices[j].addItem(k);
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
template <class T>
Sublist<T>::~Sublist(){}

template <class T>
void Sublist<T>::showSublist() const{

   cout << "\nSublist -----------------------------\n"
        << "Sum: " << getSum() << endl;

   for( int i = 0; i < subListItems.size(); i++ ){
      cout << "array[" << i << "] = " << (*masterSet)[subListItems[i]] << endl;
   }

}

template <class T>
Sublist<T> Sublist<T>::addItem( int indexOfItemToAdd ){

   Sublist<T> newSubList;
   newSubList.masterSet = this->masterSet;
   newSubList.listSum = this->listSum;
   newSubList.listSum = newSubList.listSum + (*masterSet)[indexOfItemToAdd];
   newSubList.subListItems = this->subListItems;
   newSubList.subListItems.push_back( indexOfItemToAdd );

   return newSubList;

}

template <class T>
int Sublist<T>::getSum() const {

   return listSum;

}


// Sample runs -----------------------

/*
 Sample Run 1 ------------------------

 Target time: 3600

 Sublist -----------------------------
 Sum: 3600
 array[0] = Cowboy Casanova by Carrie Underwood (236);
 array[1] = Quitter by Carrie Underwood (220);
 array[2] = Russian Roulette by Rihanna (228);
 array[3] = Monkey Wrench by Foo Fighters (230);
 array[4] = Pretending by Eric Clapton (283);
 array[5] = Bad Love by Eric Clapton (308);
 array[6] = Everybody's In The Mood by Howlin' Wolf (178);
 array[7] = Well That's All Right by Howlin' Wolf (175);
 array[8] = Samson and Delilah by Reverend Gary Davis (216);
 array[9] = Hot Cha by Roy Buchanan (208);
 array[10] = Green Onions by Roy Buchanan (443);
 array[11] = I'm Just a Prisoner by Janiva Magness (230);
 array[12] = You Were Never Mine by Janiva Magness (276);
 array[13] = Hobo Blues by John Lee Hooker (187);
 array[14] = I Can't Quit You Baby by John Lee Hooker (182);

 Algorithm Elapsed Time: 0.158769 seconds.

 Program ended with exit code: 0
 
 
 Sample Run 2:------------------------

 Target time: 1600

 Sublist -----------------------------
 Sum: 1600
 array[0] = Cowboy Casanova by Carrie Underwood (236);
 array[1] = All My Life by Foo Fighters (263);
 array[2] = Monkey Wrench by Foo Fighters (230);
 array[3] = Pretending by Eric Clapton (283);
 array[4] = Everybody's In The Mood by Howlin' Wolf (178);
 array[5] = Samson and Delilah by Reverend Gary Davis (216);
 array[6] = Twelve Sticks by Reverend Gary Davis (194);

 Algorithm Elapsed Time: 0.001848 seconds.

 Program ended with exit code: 0

 
 Sample Run 3 ------------------------

 Target time: 167

 Sublist -----------------------------
 Sum: 155
 array[0] = Ogeechee Hymnal by Blue Record (155);

 Algorithm Elapsed Time: 5e-05 seconds.

 Program ended with exit code: 0
 
 
 Sample Run 4 ------------------------

 Target time: 3456

 Sublist -----------------------------
 Sum: 3456
 array[0] = Cowboy Casanova by Carrie Underwood (236);
 array[1] = Russian Roulette by Rihanna (228);
 array[2] = All My Life by Foo Fighters (263);
 array[3] = Monkey Wrench by Foo Fighters (230);
 array[4] = Pretending by Eric Clapton (283);
 array[5] = Bad Love by Eric Clapton (308);
 array[6] = Everybody's In The Mood by Howlin' Wolf (178);
 array[7] = Well That's All Right by Howlin' Wolf (175);
 array[8] = Samson and Delilah by Reverend Gary Davis (216);
 array[9] = Hot Cha by Roy Buchanan (208);
 array[10] = Green Onions by Roy Buchanan (443);
 array[11] = I'm Just a Prisoner by Janiva Magness (230);
 array[12] = You Were Never Mine by Janiva Magness (276);
 array[13] = I Can't Quit You Baby by John Lee Hooker (182);

 Algorithm Elapsed Time: 0.133953 seconds.

 Program ended with exit code: 0
 
 
 Sample Run 5 ------------------------

 Target time: 9999999

 The Target is greater than the sum of all data elements.
 Program ended with exit code: 1

*/









