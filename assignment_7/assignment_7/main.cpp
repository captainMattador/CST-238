
/*
 Assignment: Assignment 7 - Analyzing Shellsort's Gaps
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Testing of Shell Sort with different gap sequences.
 */

#include <iostream>
using namespace std;
#include "FHvector.h"
#include <time.h>
#include <math.h>

// helper function for generating a random number
int randomNum(const int & generateBetween);

// shellSort1
template <typename Comparable>
void shellSort1( FHvector<Comparable> & a )
{
   int k, pos, arraySize, ONE;
   Comparable tmp;

   arraySize = a.size();
   for (ONE = arraySize/2;  ONE > 0;  ONE /= 2)
   {
      for(pos = ONE ; pos < arraySize; pos++ )
      {
         tmp = a[pos];
         for(k = pos; k >= ONE && tmp < a[k - ONE]; k -= ONE )
            a[k] = a[k - ONE];
         a[k] = tmp;
      }
   }
}

// shellSortX
template <typename Comparable>
void shellSortX( FHvector<Comparable> & a, const int gapSequence[],
                const int gapSize )
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();

   for (gap = gapSize - 1;  gap >= 0; --gap)
   {
      for(pos = gapSequence[gap]; pos < arraySize; pos++ )
      {
         tmp = a[pos];
         for(k = pos; k >= gapSequence[gap] && tmp < a[k - gapSequence[gap]];
             k -= gapSequence[gap] )
            a[k] = a[k - gapSequence[gap]];
         a[k] = tmp;
      }
   }
}

int main() {

   #define ARRAY_SIZE 200000
   #define GAP_SIZE 30

   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;

   for(int i = 0; i < ARRAY_SIZE; ++i){
      int randInt = randomNum(ARRAY_SIZE);
      fhVectorOfInts1.push_back( randInt );
      fhVectorOfInts2.push_back( randInt );
      fhVectorOfInts3.push_back( randInt );
      fhVectorOfInts4.push_back( randInt );
   }

   // gap arrays
   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
   int sedgewickArray[GAP_SIZE] = { 0 }, myGapArray[GAP_SIZE] = { 0 };
   int gapArraySize = 0, sedgewickArraySize = 0, myGapArraySize = 0, i = 0;
   clock_t startTime, stopTime;

   // setting an explicit gapArraySize
   for(i = 0; i < 21; ++i)
   {
      if(gapArray[i] > ARRAY_SIZE)
         break;
      gapArraySize++;
   }

   // creation of Sedgewick gap sequence
   for(i = 0; i < GAP_SIZE; ++i)
   {
      int val = (i%2 == 0) ?
         9*pow(2, i) - 9*pow(2, i/2) + 1 : 8*pow(2, i) - 6*pow(2, (i+1)/2) + 1;

      if( val > ARRAY_SIZE )
         break;
      sedgewickArray[i] = val;
      sedgewickArraySize++;
   }

   // creation of my best gap sequence
   for(i = 0; i < GAP_SIZE; ++i)
   {
      int val = pow(2, i) - 1 + (i + 1); // so far my best equation
      if(val > ARRAY_SIZE)
         break;
      myGapArray[i] = val;
      myGapArraySize++;
   }

   cout << "\nPrint out of sedgewickArray gap array\n";
   for(i = 0; i < sedgewickArraySize; ++i)
      cout << sedgewickArray[i] << " ";
   cout << endl;

   cout << "\nPrint out of my best gap array\n";
   for(i = 0; i < myGapArraySize; ++i)
      cout << myGapArray[i] << " ";
   cout << endl;

   // timing of shellSort1
   startTime = clock();  // ------------------ start

   shellSort1( fhVectorOfInts1 );

   stopTime = clock();  // ---------------------- stop
   cout << "\nshellSort1 Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   // timing of shellSortx with gap array
   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts2, gapArray, gapArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "\nshellSortx with explicit gap sequence Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   // timing of shellSortx with sedgewick array
   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts3, sedgewickArray, sedgewickArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "\nFH Sedgewick Gap Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   // timing of shellSortx with my best gap design
   startTime = clock();  // ------------------ start

   shellSortX(fhVectorOfInts4, myGapArray, myGapArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "\nFH My best Gap Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   return 0;
}


int randomNum(const int & generateBetween)
{

   srand (time(NULL) + rand( ));
   return rand() % generateBetween;
   
}


// table of run info
/*
 ****************************************************************************************
 Size           | 10,000    | 43,500    | 76,750    | 109,000   | 165,745   | 200,000
 ****************************************************************************************
 shellSort1     | 0.00567s  | 0.033321s | 0.061326s | 0.094146s | 0.166878s | 0.188684s
 ****************************************************************************************
 shellSortX     |           |           |           |           |           |
 with explicit  | 0.013782s | 0.098282s | 0.199691s | 0.511344s | 0.681207s | 0.987515s
 gap            |           |           |           |           |           |
 ****************************************************************************************
 shellSortX     |           |           |           |           |           |
 with Sedgewick | 0.004398s | 0.023153s | 0.044903s | 0.071089s | 0.111154s | 0.130547s
 gap            |           |           |           |           |           |
 ****************************************************************************************
 shellSortX     |           |           |           |           |           |
 with my gap    | 0.004854s | 0.02409s  | 0.046023s | 0.071617s | 0.114195s | 0.135008s
 sequence       |           |           |           |           |           |
 */


// Questions
/*
 
 I believe the reason for the time differences in shellSort1() and shellSortX()
 with the explicit gap sequence is that the explicit sequence is full of ints 
 that are even setting up an always worse case scenario for the sort leaving
 things still mostly unsorted in the final pass.
 
 In my tests Shell's implied gap sequence is faster than Shell's explicit gap 
 sequence. In the explicit gap sequence, becasue all the elements are even,
 by the time it gets to the final pass all the largest numbers are still in 
 even positions and all the smallest numbers are still in the odd positions 
 creating a lot of work still on the final pass. 
 
 My gap sequence was figured out mostly through trial and error, and overall
 produces a time that is comparable to Sedgewick gap sequence. Usually it is
 slower but occasionally seems to beat it on my computer.

 */





// run of 10,000
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205

 shellSort1 Elapsed Time: 0.00567 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.013782 seconds.


 FH Sedgewick Gap Elapsed Time: 0.004398 seconds.


 FH My best Gap Elapsed Time: 0.004854 seconds.

 Program ended with exit code: 0
 */





// run of 43,500
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205 16398 32783

 shellSort1 Elapsed Time: 0.033321 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.098282 seconds.


 FH Sedgewick Gap Elapsed Time: 0.023153 seconds.


 FH My best Gap Elapsed Time: 0.02409 seconds.

 Program ended with exit code: 0
 */




// run of 76,750
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289 64769

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205 16398 32783 65552

 shellSort1 Elapsed Time: 0.061326 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.199691 seconds.


 FH Sedgewick Gap Elapsed Time: 0.044903 seconds.


 FH My best Gap Elapsed Time: 0.046023 seconds.

 Program ended with exit code: 0
 */





// run of 109,000
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289 64769

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205 16398 32783 65552

 shellSort1 Elapsed Time: 0.108644 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.503808 seconds.


 FH Sedgewick Gap Elapsed Time: 0.065274 seconds.


 FH My best Gap Elapsed Time: 0.067616 seconds.

 Program ended with exit code: 0
 */





// run of 165,745
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289 64769 146305

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205 16398 32783 65552 131089

 shellSort1 Elapsed Time: 0.166878 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.681207 seconds.


 FH Sedgewick Gap Elapsed Time: 0.111154 seconds.


 FH My best Gap Elapsed Time: 0.114195 seconds.

 Program ended with exit code: 0
 */





// run of 200,000
/*
 Print out of sedgewickArray gap array
 1 5 19 41 109 209 505 929 2161 3905 8929 16001 36289 64769 146305

 Print out of my best gap array
 1 3 6 11 20 37 70 135 264 521 1034 2059 4108 8205 16398 32783 65552 131089

 shellSort1 Elapsed Time: 0.188684 seconds.


 shellSortx with explicit gap sequence Elapsed Time: 0.987515 seconds.


 FH Sedgewick Gap Elapsed Time: 0.130547 seconds.


 FH My best Gap Elapsed Time: 0.135008 seconds.

 Program ended with exit code: 0
 */