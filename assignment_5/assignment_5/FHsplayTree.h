/*
 Assignment: Assignment 5 - Top-Down Splay Trees Using Inheritance
 File - FHsplayTree.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Implement tree splay functionality. When the tree is played
 by a specific value, and that value exists in the tree it is moved to the
 trees root.
 */

#ifndef FHASPLAYTREE_H
#define FHASPLAYTREE_H
#include "FHsearch_tree.h"


// ---------------------- FHsplayTree Prototype --------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:

   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x){ return find(x) != NULL; };
   const Comparable & find( const Comparable &x );
   const Comparable &showRoot(){
      return (this->mRoot)? this->mRoot->data : Comparable();}

protected:
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 );
   void rotateWithRightChild( FHs_treeNode<Comparable> * & k2 );

};



/************************ public methods ***************************/

/* insert */
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x)
{
   FHs_treeNode<Comparable> *newNode;

   if(!this->mRoot)
   {
      this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
      this->mSize++;
      return true;
   }
   
   splay(this->mRoot, x);


   if(x < this->mRoot->data){
      newNode = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild,
                                             this->mRoot);
      this->mRoot = newNode;
      this->mSize++;
      return true;
   }

   if(this->mRoot->data < x){
      newNode = new FHs_treeNode<Comparable>(x, this->mRoot,
                                             this->mRoot->rtChild);
      this->mRoot = newNode;
      this->mSize++;
      return true;
   }

   return false;
}



/* remove */
template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
   FHs_treeNode<Comparable> *newRoot;

   // tree is empty so return
   if (!this->mRoot)
      return false;

   splay(this->mRoot, x);

   // x to remove was not found se return false silently
   if(this->mRoot->data < x || x < this->mRoot->data)
      return false;

   // x found so remove and handle accordingly
   if(!this->mRoot->lftChild){
      newRoot = this->mRoot->rtChild;
   }else{
      newRoot = this->mRoot->lftChild;
      splay(newRoot, x);
      newRoot->rtChild = this->mRoot->rtChild;
   }

   delete this->mRoot;
   this->mRoot = newRoot;

   return true;
}


/* find */
template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(
      const Comparable &x)
{
   // tree is empty, throw exception
   if (!this->mRoot)
      throw typename FHsearch_tree<Comparable>::NotFoundException();

   splay(this->mRoot, x);

   // x was not found during splay, so throw exception
   if (this->mRoot->data < x || x < this->mRoot->data)
      throw typename FHsearch_tree<Comparable>::NotFoundException();

   // x was found so return
   return this->mRoot->data;

}



/************************ protected methods ***********************/

/* splay */
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root,
      const Comparable & x)
{

   // set helper trees nodes to NULL
   FHs_treeNode<Comparable> *rightTree = NULL,
   *leftTree = NULL, *rightTreeMin = NULL, *leftTreeMax = NULL;

   while(root != NULL){

      // x < root
      if(x < root->data){
         if(!root->lftChild)
            break;
         // zig zag
         if(x < root->lftChild->data){
            rotateWithLeftChild( root );
            if(!root->lftChild)
               break;
         }
         if(!rightTree){
            rightTreeMin = rightTree = root;
         }else{
            rightTreeMin->lftChild = root;
            rightTreeMin = rightTreeMin->lftChild;
         }
         root = root->lftChild;
      }

      // x > root
      else if(root->data < x){
         if(!root->rtChild)
            break;
         // zig zag
         if(root->rtChild->data < x){
            rotateWithRightChild( root );
            if(!root->rtChild)
               break;
         }
         if(!leftTree){
            leftTreeMax = leftTree = root;
         }else{
            leftTreeMax->rtChild = root;
            leftTreeMax = leftTreeMax->rtChild;
         }
         root = root->rtChild;
      }

      // else x is at root
      else
         break;

   }

   // if a left tree was built reassemble it with main tree
   if(leftTree){
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }

   // if a right tree was built reassemble it with main tree
   if(rightTree){
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }

}

/* rotate left */
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

/* rotate right */
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}

#endif



