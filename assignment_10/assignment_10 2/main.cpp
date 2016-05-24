/*
 Assignment: Assignment 10 (Bonus) - Stars Near Earth
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Display the 100 closest stars to earth and their location
 to eachother.
 */


#include <iostream>
using namespace std;
#include "SNE_Analyzer.h"


// --------------- main ---------------
int main()
{
   string outString, longBlankString
   = "                                         "
   "                                         ";
   int k, arraySize, row, col;
   double maxX, minX, maxY, minY, maxZ, minZ,
   xRange, yRange, zRange,
   xConversion, yConversion, zConversion;
   StarNearEarthReader starInput("nearest_stars.txt");
   const int NUM_COLS = 70;
   const int NUM_ROWS = 35;

   if (starInput.readError())
   {
      cout << "couldn't open " << starInput.getFileName() << " for input.\n";
      exit(1);
   }

   cout << starInput.getFileName() << endl;
   cout << starInput.getNumStars() << endl;

   // create an array of objects for our own use:
   arraySize = starInput.getNumStars();
   SNE_Analyzer *starArray = new SNE_Analyzer[arraySize];
   for (k = 0; k < arraySize; k++)
      starArray[k] =  starInput[k];

   // display cartesian coords
   for (int k = 0; k < arraySize; k++){
      cout << starArray[k].getNameCommon() << " "
           << starArray[k].coordToString() << endl;
   }

   // get max and min coords for scaling
   maxX = minX = maxY = minY = maxZ = minZ = 0;
   for (int k = 0; k < arraySize; k++)
   {
      double tempX, tempY, tempZ;
      tempX = starArray[k].getX();
      tempY = starArray[k].getY();
      tempZ = starArray[k].getZ();

      if( tempX > maxX )
         maxX = tempX;

      if( tempX < minX )
         minX = tempX;

      if( tempY > maxY )
         maxY = tempY;

      if( tempY < minY )
         minY = tempY;

      if( tempZ > maxZ )
         maxZ = tempZ;

      if( tempZ < minZ )
         minZ = tempZ;
   }

   xRange = maxX - minX;
   yRange = maxY - minY;
   zRange = maxZ - minZ;

   // RUN 1: using y for row and x for column
   xConversion = ( NUM_COLS - 1 ) / xRange;
   yConversion = ( NUM_ROWS - 1 ) / yRange;

   // RUN 2: using x for row and y for column
//   xConversion = ( NUM_ROWS - 1 ) / xRange;
//   yConversion = ( NUM_COLS - 1 ) / yRange;

   // RUN 3: using y for row and z for column
//   yConversion = ( NUM_ROWS - 1 ) / yRange;
//   zConversion = ( NUM_COLS - 1 ) / zRange;

   // RUN 4: using x for row and z for column
//   xConversion = ( NUM_ROWS - 1 ) / xRange;
//   zConversion = ( NUM_COLS - 1 ) / zRange;

   // RUN 5: using z for row and x for column
//   xConversion = ( NUM_COLS - 1 ) / xRange;
//   zConversion = ( NUM_ROWS - 1 ) / zRange;

   // RUN 6: using z for row and y for column
//   yConversion = ( NUM_COLS - 1 ) / yRange;
//   zConversion = ( NUM_ROWS - 1 ) / zRange;

   SparseMat<char> starMap(NUM_ROWS, NUM_COLS, ' ');

   for (k = 0; k < arraySize; k++)
   {
      int rank = starArray[k].getRank();

      // RUN 1: using y for row and x for column
      row = (starArray[k].getY() - minY) * yConversion;
      col = (starArray[k].getX() - minX) * xConversion;

      // RUN 2: using X for row and Y for column
//      row = (starArray[k].getX() - minX) * xConversion;
//      col = (starArray[k].getY() - minY) * yConversion;

      // RUN 3: using y for row and z for column
//      row = (starArray[k].getY() - minY) * yConversion;
//      col = (starArray[k].getZ() - minZ) * zConversion;

      // RUN 4: using x for row and z for column
//      row = (starArray[k].getX() - minX) * xConversion;
//      col = (starArray[k].getZ() - minZ) * zConversion;

      // RUN 5: using z for row and x for column
//      row = (starArray[k].getZ() - minZ) * zConversion;
//      col = (starArray[k].getX() - minX) * xConversion;

      // RUN 6: using z for row and y for column
//      row = (starArray[k].getZ() - minZ) * zConversion;
//      col = (starArray[k].getY() - minY) * yConversion;

      if ( rank > 0 &&  rank < 10 )
         starMap.set(row, col) = static_cast<char>(rank + 48);
      else if( starMap.get( row, col ) == ' ' )
         starMap.set(row, col) = '*';

   }


   // RUN 1: using y for row and x for column
   row = (0 - minY) * yConversion;
   col = (0 - minX) * xConversion;
   cout << "\n\nRUN 1: using y for row and x for column\n\n";

   // RUN 2: using X for row and Y for column
//   row = (0 - minX) * xConversion;
//   col = (0 - minY) * yConversion;
//   cout << "\n\nRUN 2: using X for row and Y for column\n\n";

   // RUN 3: using y for row and z for column
//   row = (0 - minY) * yConversion;
//   col = (0 - minZ) * zConversion;
//   cout << "\n\nRUN 3: using y for row and z for column\n\n";

   // RUN 4: using x for row and z for column
//   row = (0 - minX) * xConversion;
//   col = (0 - minZ) * zConversion;
//   cout << "\n\nRUN 4: using x for row and z for column\n\n";

   // RUN 5: using z for row and x for column
//   row = (0 - minZ) * zConversion;
//   col = (0 - minX) * xConversion;
//   cout << "\n\nRUN 5: using z for row and x for column\n\n";

   // RUN 6: using z for row and y for column
//   row = (0 - minZ) * zConversion;
//   col = (0 - minY) * yConversion;
//   cout << "\n\nRUN 6: using z for row and y for column\n\n";

   starMap.set( row, col) = 'S';

   for (row = 0; row < NUM_ROWS; row++)
   {
      outString = longBlankString.substr(0, NUM_COLS);
      for (col = 0; col < NUM_COLS; col++)
      {
         try{
            outString[col] = starMap.get( row, col );
         }catch (...)
         {
            //cout << "Out of bounds of Sparce Matrix" << endl;
         }
      }
      cout << "| " << outString << endl;
   }

   cout << endl;

   delete[] starArray;

   return 0;
}


// output runs
// note: "|" was used as a border for the stars output to keep the formatting
// nice when pasting back into the following comments.

/*
 nearest_stars.txt
 100
 Proxima Centauri x: -1.546293; y: -1.183478; z: -3.769340
 Barnard's Star x: -0.056838; y: -5.943387; z: 0.487961
 Wolf 359 x: -7.430334; y: 2.113549; z: 0.950536
 Lalande 21185 x: -6.506375; y: 1.642238; z: 4.870046
 Sirius x: -1.609060; y: 8.062019; z: -2.468945
 BL Ceti x: 7.540929; y: 3.477280; z: -2.690181
 Ross 154 x: 1.910240; y: -8.648079; z: -3.912869
 Ross 248 x: 7.380606; y: -0.583729; z: 7.193456
 epsilon Eridani x: 6.213068; y: 8.315009; z: -1.729235
 Lacaille 9352 x: 8.465653; y: -2.037633; z: -6.292257
 Ross 128 x: -10.903230; y: 0.583818; z: -0.153313
 EZ Aquarii A x: 10.189198; y: -3.781402; z: -2.973612
 Procyon x: -4.767961; y: 10.306803; z: 1.038493
 61 Cygni A x: 6.475334; y: -6.096803; z: 7.137945
 (no common name) x: 1.081439; y: -5.726322; z: 9.944846
 GX Andromedae x: 8.332564; y: 0.669751; z: 8.079118
 epsilon Indi A x: 5.656768; y: -3.156226; z: -9.893750
 DX Cancri x: -6.421589; y: 8.382023; z: 5.328466
 tau Ceti x: 10.272825; y: 5.014184; z: -3.264361
 Henry et al. 1997, Henry et al. 2006 x: 5.026663; y: 6.918290; z: -8.407314
 YZ Ceti x: 11.027577; y: 3.610227; z: -3.547300
 Luyten's Star x: -4.584121; y: 11.430974; z: 1.126434
 Henry et al. 2006 x: 8.722794; y: 8.206661; z: 3.634488
 Henry et al. 2006 x: 1.078743; y: -5.412305; z: -11.296783
 Kapteyn's Star x: 1.890522; y: 8.832912; z: -9.038744
 AX Microscopii x: 7.599337; y: -6.533289; z: -8.077083
 Kruger 60 A x: 6.468808; y: -2.746124; z: 11.114720
 Jao et al. 2005, Costa et al. 2005 x: -9.606479; y: 3.109984; z: -8.453179
 Ross 614 A x: -1.705263; y: 13.224663; z: -0.655389
 Wolf 1061 x: -5.144192; y: -12.465562; z: -3.029767
 van Maanen's Star x: 13.684420; y: 2.981497; z: 1.321096
 (no common name) x: 11.309459; y: 0.266851; z: -8.635852
 Wolf 424 A x: -13.987421; y: -2.045946; z: 2.244233
 TZ Arietis x: 12.235161; y: 7.079642; z: 3.277077
 (no common name) x: -0.560574; y: -5.431906; z: 13.749622
 (no common name) x: -13.811689; y: 4.473702; z: -2.910823
 (no common name) x: -1.379413; y: -10.026031; z: -10.813192
 G 208-044 A x: 5.045035; y: -9.301152; z: 10.367499
 WD 1142-645 x: -6.390851; y: 0.398859; z: -13.633229
 (no common name) x: 15.175611; y: 0.445762; z: -2.009403
 Ross 780 x: 14.245303; y: -4.268489; z: -3.780531
 Henry et al. 2006 x: -7.112606; y: 2.436807; z: -13.681678
 (no common name) x: -11.156735; y: 2.705454; z: 10.904347
 (no common name) x: -9.167211; y: 4.702798; z: 12.043870
 (no common name) x: -13.578457; y: 6.360132; z: 5.418779
 (no common name) x: 8.470209; y: -6.292444; z: -12.142197
 (no common name) x: 7.589388; y: 10.797271; z: -9.388863
 Costa et al. 2005 x: 7.976259; y: 7.639721; z: -11.850010
 (no common name) x: -1.168028; y: -11.631093; z: -11.415034
 omicron 2 Eridani x: 7.168128; y: 14.579067; z: -2.182907
 EV Lacertae x: 11.186274; y: -3.697972; z: 11.510862
 70 Ophiuchi A x: 0.395798; y: -16.625700; z: 0.726099
 Altair x: 7.683131; y: -14.636794; z: 2.579289
 EI Cancri x: -11.266125; y: 11.439670; z: 5.768433
 Henry et al. 2006 x: -0.004344; y: 17.065735; z: 0.806790
 Henry et al. 2006 x: 4.317461; y: 16.681370; z: -2.099341
 (no common name) x: -3.437097; y: 0.184793; z: 17.211934
 Wolf 498 x: -15.324284; y: -7.617878; z: 4.550749
 (no common name) x: 11.711376; y: -12.498643; z: -5.228329
 Stein 2051 x: 3.516778; y: 8.617243; z: 15.475899
 (no common name) x: -3.598093; y: 14.755305; z: 9.964317
 (no common name) x: 2.400166; y: -15.313299; z: 10.065343
 Wolf 1453 x: 2.308490; y: 18.439631; z: -1.194327
 (no common name) x: 8.136879; y: 16.557594; z: -3.118102
 sigma Draconis x: 2.561450; y: -6.008141; z: 17.619822
 (no common name) x: -0.806496; y: 17.463344; z: -7.015201
 (no common name) x: -0.600820; y: -10.241262; z: -15.991598
 Wolf 1055 x: 6.257114; y: -17.937319; z: 1.718493
 Ross 47 x: 1.454069; y: 18.636838; z: 4.140631
 (no common name) x: -12.781470; y: -12.501982; z: -7.012379
 Jao et al. 2005 x: 4.665867; y: -12.681454; z: -13.778124
 (no common name) x: 19.319468; y: -0.910379; z: 0.811000
 eta Cassiopei A x: 10.083004; y: 2.194072; z: 16.395923
 (no common name) x: -8.752301; y: -11.637394; z: -12.781419
 (no common name) x: 18.602830; y: 1.257477; z: -5.393633
 Ross 882 x: -8.569699; y: 17.440895; z: 1.206420
 36 Ophiuchi A x: -3.370801; y: -17.082462; z: -8.720265
 (no common name) x: 8.635601; y: -13.400044; z: -11.625293
 82 Eridani x: 9.286259; y: 11.059744; z: -13.499667
 (no common name) x: -0.336453; y: -6.480310; z: 18.712521
 delta Pavonis x: 4.283820; y: -6.807420; z: -18.220683
 QY Aurigae A x: -4.711636; y: 14.936582; z: 12.471334
 HN Librae x: -15.287629; y: -12.190854; z: -4.341807
 (no common name) x: -14.171320; y: 10.148787; z: 9.871887
 (no common name) x: -9.147653; y: 8.066160; z: 16.001816
 (no common name) x: 7.870211; y: -11.903001; z: -14.351474
 Wolf 562 x: -13.081362; y: -15.513540; z: -2.751690
 EQ Pegasi x: 19.296400; y: -2.380411; z: 7.052438
 Henry et al. 2006 x: -13.672346; y: 13.625497; z: 7.734029
 Henry et al. 2006 x: -16.076443; y: -2.749320; z: -12.918523
 (no common name) x: -3.023791; y: -14.266115; z: 14.925990
 (no common name) x: -13.199350; y: -12.818077; z: -9.850687
 (no common name) x: -5.968151; y: -14.643988; z: 13.681141
 WD 0552-041 x: 0.443079; y: 20.984734; z: -1.530829
 Wolf 630 A x: -5.786061; y: -20.006955; z: -3.051816
 (no common name) x: 11.289693; y: -2.333702; z: 17.866835
 Jao et al. 2005 x: -6.342217; y: 4.327448; z: -19.882306
 GL Virginis x: -20.861352; y: -1.733903; z: 4.116539
 (no common name) x: -5.029564; y: -11.486251; z: 17.452763
 Ross 104 x: -19.340642; y: 5.175828; z: 8.429745


 RUN 1: using y for row and x for column

 |                          *
 |                                               *
 |                               *     *
 |              *                         *
 |                          *    *                  *
 |              *                                    *
 |          *   *      *     *      *         *     *     *
 |                            *
 |                                  **         *
 |                                        7
 |          *                                 *
 |                                    2 *  *     * * *
 |                                   *  *
 |                                              *       * *    *
 |         *  *                                  *   *    *            *
 | *                                1                                   *
 |                         *    *     S            8      *     *
 |                  *      4                         *                *
 |                 *      3                             *
 |                    *                            6     *    *
 |   *         *       *   *                            *
 |             *
 |                                             *    *      *
 |                     *   *        5     * *    9   *
 |
 |            *               *                    *  *
 |                 *          *
 |             *                   *
 |                            * *                  *
 |
 |                                    *       *     *
 |                      *            *    *
 |                                       *
 |
 |                                     *
 
 
 
 RUN 2: using X for row and Y for column

 |                               *
 |                                           *
 |
 |
 |              *      *        *
 |                               *          *        *
 |        *    *                               *           *
 |
 |                                   *   *             *
 |                                       *  *     *
 |               *                                                *
 |                                      3
 | *        *                        * 4   *      *
 |             * *                                    **     *
 |     *                            *                        *
 |          *
 |               * *              1               5       *       *
 |      *          *     *2*        S                            *
 |                         *                                        *   *
 |        *           7   *                        *               *
 |                                                 *
 |             *     *   *                      *               *
 |    *                        *                  9
 |                        *     *  8                         *
 |          * * *        **      *   *    6      *    *         *
 |                                                *    *
 |                            *         * *  *
 |             *              * *    *
 |                                              *
 |                           *           *
 |                                   *
 |
 |
 |                              *     *
 |                                 *
 
 
 
 RUN 3: using y for row and z for column

 |                               *
 |                                       *
 |                    *                *
 |                               *                      *
 |                                         *                   * *
 |               *  *
 |          ** *  *       *  **  *
 |                                                                   *
 |       *         *                                     *
 |                             7
 |   *                                        *
 |              *       *              2           *    *             * *
 |                *                                            *
 |                  *          * *                         *
 |             *           *              *        *      *           *
 |                             1       *     *
 |            *        *          *   S            8                 *
 |                          *         *        4    *
 |            *                         3                 *        *
 |                     *        *6      *
 | *                            **                   *      *
 |                                              *
 |               *     *                    *
 |                    *           59         *  *                 **
 |
 |            *      *                  *               *
 |                                      *       *
 |                                   *              *
 |                                *                     *   *
 |
 |                              * *    *
 |                        *         *   *
 |                                           *
 |
 |                                 *

 
 
 RUN 4: using x for row and z for column

 |                                           *
 |                                                   *
 |
 |
 |             *              *               *
 |                               *        *             *
 |                  *     *      *              *   *
 |
 |                                    *         *         *
 |                     *                                    *      *
 |             *                        *
 |            *                         3
 | *          *                  *             4*              *
 |                               *      *                   *        *
 |                    *                                 *            *
 |                                                               *
 |                **      *    1  5  *
 |       *                            S2                       *        *
 |                *                *         *          *
 |                    *        7    *                   *             *
 |                                                                *
 |   *       *         *          *                      *
 |                  *              9     *
 |                                *                8      *
 |          *   **   *  *  *    *6         *        *
 |            *                              *
 |                              **                                 *
 |                     *     *                             *          *
 |                                          *
 |                             *        *
 |                                *
 |
 |
 |                          *                      *
 |                                     *
 
 

 
 RUN 5: using z for row and x for column

 |                         *
 |                                            *
 |
 |                                   *
 |                                                  *
 |                        **                  *       *
 |         *           *                             *
 |                                  *   *           **
 |              *                               *
 |                               *        *        *      *
 |                    *                        *   *
 |              *                    *               *
 |                                                        *           *
 |          *
 |             *            **      1     7         *   **     *
 |              *                   5         *  9 6            *
 |                                 *   *  *
 |                  *                 S
 |                      * 3   *       **                      *         *
 |            *                                  *  *
 |                                                   *     *
 | *        *              4             *
 |             *   *       *
 |                                               * 8                   *
 |   *         *                                     *
 |
 |            *                 *       * *    *
 |                 *                             *        *
 |                     *      *
 |                          *        *
 |                               *
 |                     *                    *           *
 |                            * *
 |                                         *              *
 |                                    *
 
 
 
 
 RUN 6: using z for row and y for column

 |                                         *
 |                       *
 |
 |                 *
 |              *
 |             *                     *  *              *
 |               *        *     *
 |            *  * *       *                     *
 |             *               *
 |     *                             *             *  *
 |                       *               *      *
 |             *                 *                                *
 |             *                      *
 |              *
 | *           *      7      **   1       * **                  *
 |        *                          *    6       9          *  *
 |                                                        *        *    *
 |                        2         S*
 |      *                          *    3*            **         **
 |    *     *                    *
 |                                              * *
 |                     *         *     4                            *
 |                                             *  *    *
 |                        *     *  8
 |                                   *       *             *
 |
 |        *          *     *                         *       *
 |                            * *        *
 |                                          *                *
 |          *              *
 |          *
 |                                      *         **
 |               *                  *
 |                        *     *
 |                       *
 

 Program ended with exit code: 0
 */
