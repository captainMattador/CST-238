/*
 Assignment: Assignment 4 - Lazy Deletion in Binary Search Trees
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: implementing lazy deletion to a binary search tree.
 */


// --------------- main ---------------

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   int k;
   FHlazySearchTree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);

   cout << "\ninitial size: " << searchTree.size() << endl;
   searchTree.insert(50);
   searchTree.insert(20);
   searchTree.insert(30);
   searchTree.insert(70);
   searchTree.insert(10);
   searchTree.insert(60);

   cout << "After populating -- traversal and sizes: \n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Collecting garbage on new tree - should be no garbage." << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   // test assignment operator
   FHlazySearchTree<int> searchTree2 = searchTree;

   cout << "\n\nAttempting 1 removal: \n";
   if (searchTree.remove(20))
      cout << "removed " << 20 << endl;
   cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   // testing find max and find min
   cout << endl << "Max/Min after soft delete of 20: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }

   // delete 10 as well to test findMin recuriosn. Min should now be 30.
   cout << "\n\nAttempting 1 more removal: \n";
   if (searchTree.remove(10))
      cout << "removed " << 10 << endl;
   cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   // testing find max and find min
   cout << endl << "Max/Min after soft delete of 10 and 20: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }

   // Soft insert 10 back to continue with the original outpt example
   cout << "\n10 is added back in\n";
   searchTree.insert(10);

   cout << "\nCollecting Garbage - should clean 1 item. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   // testing find max and find min
   cout << endl << "Max/Min after hard delete of 20: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }

   cout << "\nCollecting Garbage again - no change expected. " << endl;
   searchTree.collectGarbage();
   cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   // test soft insertion and deletion:

   cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "\nAfter soft removal. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Repeating soft removal. Should see no change. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Soft insertion. Hard size should not change. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;


   // testing find max and find min
   cout << endl << "Max/Min after addings and deletings of 22: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }


   // for loop to soft delet the whole tree.
   cout << "\n\nAttempting 100 removals: \n";
   for (k = 100; k > 0; k--)
   {
      if (searchTree.remove(k))
         cout << "removed " << k << endl;
   }

   cout << endl << "Max/Min test Empty of Soft deleted tree: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }

   cout << "performing garbage collecting of soft deleted tree.\n";
   searchTree.collectGarbage();

   cout << endl << "Max/Min test Empty of Hard deleted tree: \n";
   try{
      cout << "Current Min: " << searchTree.findMin() << endl;
   }catch(...){
      cout << "Min is null" << endl;
   }
   try{
      cout << "Current Max: " << searchTree.findMax() << endl;
   }catch(...){
      cout << "Max is null\n" << endl;
   }


   cout << "\nsearchTree now:\n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

   searchTree2.insert(500);
   searchTree2.insert(200);
   searchTree2.insert(300);
   searchTree2.insert(700);
   searchTree2.insert(100);
   searchTree2.insert(600);
   cout << "\nsearchTree2:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
        << "  Hard size: " << searchTree2.sizeHard() << endl;
   
   return 0;
}


// sample run from etudes for comparison
/* ---------------------- Run --------------------------
 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6


 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6
 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5
 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6


 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10

 searchTree now:

 tree 1 size: 0  Hard size: 0

 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12
 Press any key to continue . . .
 ---------------------------------------------------------------------- */
// end of sample run from etudes



// my run - with added testings for findMax and findMin
/*----------------------------------------------------------------------
 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6


 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6

 Max/Min after soft delete of 20:
 Current Min: 10
 Current Max: 70


 Attempting 1 more removal:
 removed 10
 tree 1 size: 4  Hard size: 6

 Max/Min after soft delete of 10 and 20:
 Current Min: 30
 Current Max: 70

 10 is added back in

 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5

 Max/Min after hard delete of 20:
 Current Min: 10
 Current Max: 70

 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 Max/Min after addings and deletings of 22:
 Current Min: 10
 Current Max: 70


 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10

 Max/Min test Empty of Soft deleted tree:
 Current Min: Min is null
 Current Max: Max is null

 performing garbage collecting of soft deleted tree.

 Max/Min test Empty of Hard deleted tree:
 Current Min: Min is null
 Current Max: Max is null


 searchTree now:

 tree 1 size: 0  Hard size: 0

 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12
 Program ended with exit code: 0
 ---------------------------------------------------------------------- */



