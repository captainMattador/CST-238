
/*
 Assignment:  Assignment 3 - Timing Matrix Multiplication
 File - main-part-a.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Timing the multiplication of matrices.
 */

#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;


int const MAT_SIZE = 770;
typedef float* DynMat[MAT_SIZE];

/*
 function that multiplies two matrices together. It takes three params
 matA and matB which are references to matrices and a size in int
 */
void matMultDyn( const DynMat & matA,  const DynMat & matB,
                DynMat & matC, int size);
/*
 Prints a portion of a matrix to the consile. Takes three params. matA which is
 a matrix reference, start and size which are ints representing the the length
 to print and the start position in the matrix
 */
void matShowDyn( const DynMat & matA, int start, int size);
/*
 helper function for creating a random double between 2 double values
 */
double randomgen(double max, double min);


int main()
{
   int row, col;
   clock_t startTime, stopTime;
   double randFrac;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;


   // allocate rows and initialize to 0
   for (row = 0; row < MAT_SIZE; row++)
   {
      matDyn[row] = new float[MAT_SIZE]();

      for (col = 0; col < MAT_SIZE; col++)
      {
         matDyn[row][col] = 0;
      }

   }

   // generate small% non-default values bet .1 and 1
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (row = 0; row < smallPercent; row++)
   {
      randFrac = randomgen(1.0, 0.1);
      randRow = rand() % MAT_SIZE;
      randCol = rand() % MAT_SIZE;
      matDyn[randRow][randCol] = randFrac;
   }


   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " <<  MAT_SIZE << " Dyn Array Mult Elapsed Time: "
        << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

   // clean up
   for (row = 0; row < MAT_SIZE; row++)
      delete [] matDyn[row];

   cout << endl;

   return 0;
}





double randomgen(double max, double min) //Pass in range
{
   return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}




void matMultDyn( const DynMat & matA,  const DynMat & matB,
                DynMat & matC, int size){

   int row, col;

   for( row = 0; row < size; ++row ){

      matC[row] = new float[size]();

      for( col = 0; col < size; ++col ){

         for(int compLoop = 0; compLoop < size; ++compLoop){
            matC[row][col] += matA[row][compLoop] * matB[compLoop][col];
         }

      }

   }

}





void matShowDyn( const DynMat & matA, int start, int size){
   cout << endl;
   for(int i = start; i < start + size; ++i){
      for(int k = start; k < start + size; ++k){
         cout << "  " << setw(2) << fixed << setprecision(2) << matA[i][k];
      }
      cout << endl;
   }
   cout << endl;
}




// answers too questions

/*
 Time complexity of matMultDyn().

 Based on my understanding my solution to matMultDyn should be
   T(N) = O(N^3)

 My results should (and hopefully will) confirm a cubic relation ship of time
 to N as N grows in size.
 
 My reasoning is based on N which is in this case size. The algorithm realies
 on three nested loops. Counting from the inner loop out, each loop represents
 1 N. All the code in the loops I beleive are linear and insignificant to the
 value of the upper bound and are thus ignored.
 
 
 Tests:

 1) What was the smallest M that gave you a non-zero time?
 Around 110 was my smallest non-zero time result.

 Size = 110 Dyn Array Mult Elapsed Time: 0.01 seconds.
 // displayed below

 2) What happened when you doubled M , tripled it, quadrupled it, etc?  Give 
 several M values and their times in a table.
 
 ***************************************************************************
 Size | 110    | 220   | 330   | 440   | 550   | 660   | 770
 ***************************************************************************
 Time | 0.01s  | 0.04s | 0.19s | 0.55s | 0.99s | 1.92s | 3.16s

 3) How large an M can you use before the program refuses to run 
 (exception or run-time error due to memory overload) or it takes so long you 
 can't wait for the run?
 I didn't get any errors but I got tired of waiting around 8000

 4) How did the data agree or disagree with your original time complexity 
 estimate?
 The Data seems to agree with my estimation
 
 */



//runs

/*
 
 run 1:
 shorest none 0 time run:

 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.39  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.90  0.00
 0.00  0.00  0.45  0.00  0.00  0.00  0.00  0.73  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.42  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.23  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 0.00  0.00  0.08  0.39  0.35  0.20  0.23  0.22  0.00  0.00
 0.00  0.00  0.10  0.00  0.00  0.21  0.00  0.76  0.00  0.00
 0.00  0.00  0.00  0.65  0.00  0.00  0.16  0.16  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.17  0.18  0.00  0.00  0.00  0.00
 0.58  0.82  0.49  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.35  0.00  0.00  0.41  0.00  0.48  0.55  0.00  0.00
 0.00  0.00  0.10  0.00  0.00  0.00  0.00  0.17  0.00  0.00
 0.00  0.00  0.00  0.30  0.69  0.00  0.00  0.00  0.43  0.00
 0.00  0.00  0.27  0.00  0.00  0.55  0.00  0.75  0.00  0.00


 Size = 110 Dyn Array Mult Elapsed Time: 0.01 seconds.


 Program ended with exit code: 0
 
 
 

 run 2:
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.93  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.73  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.11  0.72  0.00  0.00  0.00
 0.00  0.56  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.21  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 0.63  0.00  0.32  0.00  0.00  1.04  0.51  0.00  0.49  0.34
 0.00  0.35  0.00  0.46  0.00  0.43  0.00  0.00  0.00  0.22
 0.00  0.00  1.46  0.00  0.59  0.00  0.29  0.00  0.78  0.50
 0.00  0.13  0.00  0.00  0.00  0.00  0.04  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.25  0.00  0.00  0.15  0.00
 0.00  0.41  0.15  0.00  0.00  0.01  0.82  0.00  0.41  0.46
 0.00  0.00  0.00  0.00  0.55  0.00  1.33  0.00  0.00  0.00
 0.00  0.00  0.00  0.58  0.00  0.55  0.65  0.19  0.00  0.13
 0.00  0.00  0.16  0.00  0.00  0.00  0.30  0.00  0.00  0.00
 0.51  0.00  0.71  0.00  0.05  1.09  0.13  0.22  0.19  0.00


 Size = 220 Dyn Array Mult Elapsed Time: 0.04 seconds.


 Program ended with exit code: 0
 
 
 

 run 3:
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.39  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.92  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.64  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.54  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.54  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.63  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 0.85  0.28  1.68  0.26  0.00  0.00  0.15  0.40  0.70  0.19
 0.00  0.00  0.00  0.39  0.00  0.00  0.69  0.00  0.64  0.00
 0.00  0.00  0.00  0.43  0.00  0.25  0.06  0.00  0.00  0.00
 0.68  0.00  0.00  0.03  0.57  0.72  0.00  0.46  0.00  0.88
 0.00  0.00  0.00  0.00  0.85  0.00  0.50  0.32  0.00  0.00
 0.51  0.70  0.00  0.09  0.70  0.41  1.03  0.00  0.60  0.00
 0.00  0.00  0.59  0.00  0.68  1.13  0.48  0.55  2.21  0.00
 0.00  0.00  1.03  0.74  0.00  0.37  0.00  0.29  0.28  0.95
 0.00  0.00  0.19  0.00  0.22  0.21  0.00  0.03  0.00  0.00
 0.00  0.18  0.00  0.70  0.23  0.49  0.33  0.00  0.00  0.00


 Size = 330 Dyn Array Mult Elapsed Time: 0.19 seconds.


 Program ended with exit code: 0
 
 
 

 run 4:
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.72  0.00  0.00  0.00
 0.00  0.56  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.80  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 0.00  0.00  0.68  0.19  0.75  0.00  0.00  0.00  0.34  0.00
 0.00  0.45  0.46  1.22  0.32  0.61  0.17  0.00  0.00  0.00
 1.32  0.00  0.54  0.43  0.28  0.37  0.23  0.08  0.00  0.00
 0.24  0.00  0.29  0.00  0.00  0.09  0.00  0.00  0.00  0.00
 0.98  0.00  0.22  0.13  0.04  0.00  0.00  0.10  0.00  0.00
 0.05  0.41  0.00  0.44  0.96  0.87  0.00  0.00  0.29  0.00
 0.83  0.45  0.00  1.22  0.47  0.45  0.00  0.00  0.11  0.53
 0.26  1.33  0.70  0.00  0.63  0.00  0.13  0.38  0.00  0.00
 0.00  0.24  0.34  0.74  1.19  0.00  0.00  0.32  0.28  0.00
 0.11  0.00  0.33  0.00  0.09  0.40  1.04  0.00  0.00  0.22


 Size = 440 Dyn Array Mult Elapsed Time: 0.55 seconds.


 Program ended with exit code: 0
 
 
 

 run 5:
 0.00  0.00  0.59  0.00  0.00  0.00  0.00  0.00  1.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.29  0.00  0.51  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.11  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.23  0.00  0.00  0.00  0.00  0.98
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 0.00  0.00  0.17  0.08  0.25  0.00  0.30  0.00  0.10  0.00
 1.03  0.09  0.17  0.00  0.00  0.14  0.46  0.48  0.40  0.23
 0.47  1.22  0.12  0.00  0.82  0.07  0.97  0.00  0.50  0.00
 0.58  0.00  0.79  0.77  0.56  0.00  0.65  0.00  0.70  0.00
 0.00  0.02  0.15  1.48  0.32  0.08  0.32  0.00  0.00  0.39
 0.00  0.69  0.00  1.34  0.00  0.29  0.07  0.56  0.00  1.43
 0.00  0.00  0.64  0.64  0.00  0.27  0.00  1.36  0.00  0.05
 0.00  1.36  0.56  0.00  0.78  0.27  1.04  1.17  0.23  0.31
 0.60  0.79  0.29  1.28  0.53  0.67  0.00  0.57  0.28  0.12
 0.00  0.00  0.28  0.25  0.67  0.26  0.34  0.06  0.00  0.08


 Size = 550 Dyn Array Mult Elapsed Time: 0.99 seconds.


 Program ended with exit code: 0
 
 
 

 run 6:
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.95  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.73  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.54  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.18  0.00


 0.93  0.84  1.67  0.93  0.00  0.51  0.98  0.51  0.37  0.77
 0.00  0.23  0.00  1.44  0.70  0.39  0.15  0.00  1.07  0.55
 0.65  0.77  0.00  0.00  2.17  0.00  0.36  0.48  0.00  0.40
 0.68  0.00  0.37  1.69  0.02  0.32  0.42  0.11  0.12  0.00
 0.36  0.00  0.57  0.00  0.54  0.00  0.05  0.00  0.00  0.25
 0.51  0.88  0.09  0.90  0.99  0.00  1.36  0.27  1.15  0.17
 0.61  0.00  0.76  0.73  0.71  0.80  0.68  0.65  0.82  0.00
 1.51  0.87  1.09  0.63  0.00  0.89  0.90  0.64  0.62  0.14
 0.00  0.00  0.23  0.21  1.11  0.83  0.14  0.97  0.32  0.00
 0.81  0.00  0.00  0.34  0.36  0.52  0.00  0.46  0.00  0.73


 Size = 660 Dyn Array Mult Elapsed Time: 1.92 seconds.


 Program ended with exit code: 0
 
 
 

 run 7:
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.85  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
 0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 1.23  0.19  0.61  0.00  1.69  0.43  0.53  0.67  0.76  0.52
 0.47  0.00  1.07  0.83  1.08  0.69  0.11  0.00  0.13  1.67
 0.44  0.00  0.44  1.26  0.78  0.44  0.71  0.71  0.47  0.00
 0.00  0.24  0.48  0.38  1.55  0.00  0.00  0.53  0.09  0.56
 0.83  0.44  0.84  1.09  0.00  0.00  0.46  0.91  0.15  0.31
 0.52  0.34  0.71  0.13  0.00  0.00  0.19  0.57  0.14  0.78
 0.15  0.60  0.76  0.12  0.91  0.52  0.32  0.80  0.67  0.00
 0.58  0.00  0.69  1.15  1.25  0.00  0.27  0.94  0.15  1.28
 1.53  1.05  0.61  0.00  0.69  0.19  0.18  0.78  1.52  1.39
 0.16  0.40  1.31  1.02  0.67  1.51  0.00  2.45  0.04  1.01


 Size = 770 Dyn Array Mult Elapsed Time: 3.16 seconds.


 Program ended with exit code: 0
 */






