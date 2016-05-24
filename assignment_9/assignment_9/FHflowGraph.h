// File FHflowGraph.h EXPERIMENT
// Template definitions for FHflowGraph.  
#ifndef FHFLOWGRAPH_H
#define FHFLOWGRAPH_H
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iostream>
#include <functional>
using namespace std;


/******************************************************************************
 FHflowVertex
 *****************************************************************************/

// CostType is some numeric type that expresses cost of edges
// Object is the non-graph data for a vertex
template <class Object, typename CostType>
class FHflowVertex
{
   // internal typedefs to simplify syntax
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;

public:
   static int nSortKey;
   static stack<int> keyStack;
   static enum { SORT_BY_DATA, SORT_BY_DIST } eSortType;
   static bool setNSortType( int whichType );
   static void pushSortKey() { keyStack.push(nSortKey); }
   static void popSortKey() { nSortKey = keyStack.top(); keyStack.pop(); }

   static int const INFINITY_FH = INT_MAX;  // defined in limits.h
   EdgePairList flowAdjList, resAdjList;
   Object data;
   CostType dist;
   VertPtr nextInPath;  // used for client-specific info

   FHflowVertex( const Object & x = Object() );

   void addToFlowAdjList(VertPtr neighbor, CostType cost);
   void addToResAdjList(VertPtr neighbor, CostType cost);
   bool operator<( const FHflowVertex<Object, CostType> & rhs) const;
   const FHflowVertex<Object, CostType> & operator=
      ( const FHflowVertex<Object, CostType> & rhs);
   void showFlowAdjList();
   void showResAdjList();
};

// static const initializations for Vertex --------------
template <class Object, typename CostType>
int FHflowVertex<Object, CostType>::nSortKey 
   = FHflowVertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHflowVertex<Object, CostType>::keyStack;
// ------------------------------------------------------

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::setNSortType( int whichType )
{
   switch (whichType)
   {
   case SORT_BY_DATA:
   case SORT_BY_DIST:
      nSortKey = whichType;
      return true;
   default:
      return false;
   }
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>::FHflowVertex( const Object & x) 
   : data(x), dist((CostType)INFINITY_FH),
   nextInPath(NULL)
{
   // nothing to do
}


/*********** addToFlowAdjList *************/
template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToFlowAdjList
   (FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   flowAdjList[neighbor] = cost;
}

/*********** addToResAdjList *************/
template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToResAdjList
(FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   resAdjList[neighbor] = cost;
}


template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::operator<(
   const FHflowVertex<Object, CostType> & rhs) const
{
   switch (nSortKey)
   {
   case SORT_BY_DIST:
      return (dist < rhs.dist);
   case SORT_BY_DATA:
      return (data < rhs.data);
   default:
      return false;
   }
}

template <class Object, typename CostType>
const FHflowVertex<Object, CostType> & FHflowVertex<Object, CostType>::
   operator=(const FHflowVertex<Object, CostType> & rhs)
{
//   flowAdjList = rhs.flowAdjList;
   resAdjList = rhs.resAdjList;
   flowAdjList = rhs.flowAdjList;
   data = rhs.data;
   dist = rhs.dist;
   nextInPath = rhs.nextInPath;;
   return *this;
}


/*********** showFlowAdjList *************/
template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showFlowAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Adj Flow List for " << data << ": ";
   for (iter = flowAdjList.begin(); iter != flowAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}



/*********** showResAdjList *************/
template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showResAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Adj Res List for " << data << ": ";
   for (iter = resAdjList.begin(); iter != resAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}


/******************************************************************************
 FHflowGraph
*******************************************************************************/
template <class Object, typename CostType>
class FHflowGraph
{
   // internal typedefs to simplify syntax
   typedef FHflowVertex<Object, CostType> Vertex;
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;
   typedef set<VertPtr> VertPtrSet;
   typedef set<Vertex> VertexSet;

private:
   VertPtrSet vertPtrSet;
   VertexSet vertexSet;
   VertPtr startVertPtr, endVertPtr;

public:
   FHflowGraph () {}
   void addEdge(const Object &source, const Object &dest, CostType cost);
   VertPtr addToVertexSet(const Object & object);
   void showFlowAdjTable();
   void showResAdjTable();
   void clear();

   // algorithms
   bool dijkstra(const Object & x);
   CostType findMaxFlow();
   bool setStartVert(const Object &x);
   bool setEndVert(const Object &x);

private:
   VertPtr getVertexWithThisData(const Object & x);
   bool establishNextFlowPath();
   CostType getLimitingFlowOnResPath();
   bool adjustPathByCost(CostType cost);
   CostType getCostOfResEdge(VertPtr src, VertPtr dst);
   bool addCostToResEdge(VertPtr src, VertPtr dst, CostType cost);
   bool addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost);
};

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::addToVertexSet(
   const Object & object)
{
   pair<typename VertexSet::iterator, bool> retVal;
   VertPtr vPtr;

   // save sort key for client
   Vertex::pushSortKey();
   Vertex::setNSortType(Vertex::SORT_BY_DATA);

   // build and insert vertex into master list
   retVal = vertexSet.insert( Vertex(object) );

   // get pointer to this vertex and put into vert pointer list
   vPtr = (VertPtr)&*retVal.first;
   vertPtrSet.insert(vPtr);

   Vertex::popSortKey();  // restore client sort key
   return vPtr;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::clear()
{
   vertexSet.clear();
   vertPtrSet.clear();
}


template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::addEdge(
   const Object &source, const Object &dest, CostType cost )
{
   VertPtr src, dst;

   // put both source and dest into vertex list(s) if not already there
   src = addToVertexSet(source);
   dst = addToVertexSet(dest);

   // add dest to source's adjacency lists
   src->addToResAdjList(dst, cost);
   dst->addToResAdjList(src, 0);
   src->addToFlowAdjList(dst, 0);

}


/*********** showFlowAdjTable *************/
template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showFlowAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showFlowAdjList();
   cout << endl;
}


/*********** showResAdjTable *************/
template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showResAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showResAdjList();
   cout << endl;
}



template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::
   getVertexWithThisData(const Object & x)
{
   typename VertexSet::iterator findResult;
   Vertex vert(x);

   Vertex::pushSortKey();  // save client sort key
   Vertex::setNSortType(Vertex::SORT_BY_DATA);
   findResult = vertexSet.find(vert);
   Vertex::popSortKey();  // restore client value

   if ( findResult == vertexSet.end() )
      return NULL;
   return  (VertPtr)&*findResult;
}

/*********** main algorithm methods *************/

// public: setStartVert
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setStartVert(const Object &x)
{

   startVertPtr = getVertexWithThisData(x);
   if ( !startVertPtr )
      return  false;
   return  true;

}


// public: setEndVert
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setEndVert(const Object &x)
{

   endVertPtr = getVertexWithThisData(x);
   if ( !endVertPtr )
      return  false;
   return  true;

}


// public: findMaxFlow
template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::findMaxFlow()
{

   typename EdgePairList::iterator edgePrIter;
   CostType minCost = 0, maxFlow = 0;

   // return early if no start and end
   if( !startVertPtr || !endVertPtr )
      return minCost;

   // main calls
   // loop until establishNextFlowPath == false, or minCost == 0
   while(establishNextFlowPath())
   {
      minCost = getLimitingFlowOnResPath();

      if(minCost == 0)
         return minCost;
      else
         adjustPathByCost(minCost);
   }

   // final loop to count the total flow potential
   for (edgePrIter = startVertPtr->flowAdjList.begin();
        edgePrIter != startVertPtr->flowAdjList.end();
        ++edgePrIter)
   {
      maxFlow += edgePrIter->second;
   }

   return maxFlow;

}



// private: establishNextFlowPath (updated dijkstra algorithm)
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::establishNextFlowPath()
{

      typename VertPtrSet::iterator vIter;
      typename EdgePairList::iterator edgePrIter;
      VertPtr wPtr, vPtr;
      CostType costVW;
      queue<VertPtr> partiallyProcessedVerts;

      if ( !startVertPtr )
         return false;
   
      // initialize the vertex list and place the starting vert in p_p_v queue
      for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
      {
         (*vIter)->dist = Vertex::INFINITY_FH;
         (*vIter)->nextInPath = NULL;
      }
   
      startVertPtr->dist = 0;
      partiallyProcessedVerts.push( startVertPtr );
   
      // outer dijkstra loop
      while( !partiallyProcessedVerts.empty() )
      {
         vPtr = partiallyProcessedVerts.front();
         partiallyProcessedVerts.pop();

         // inner dijkstra loop: for each vert adj to v,
         // lower its dist to s if you can
         for (edgePrIter = vPtr->resAdjList.begin();
            edgePrIter != vPtr->resAdjList.end();
            edgePrIter++)
         {
            wPtr = edgePrIter->first;
            costVW = edgePrIter->second;

            if ( costVW != 0 && vPtr->dist + costVW < wPtr->dist )
            {
               wPtr->dist = vPtr->dist + costVW;
               wPtr->nextInPath = vPtr;

               if(wPtr == endVertPtr)
                  return true;

               // *wPtr now has improved distance, so add wPtr to p_p_v queue
               partiallyProcessedVerts.push(wPtr); 
            }
         }
      }
      return false;

}


// private: getLimitingFlowOnResPath
template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getLimitingFlowOnResPath()
{

   VertPtr vp;
   CostType cost = 0, tempCost;

   // retrun cost of 0 early if null
   if( !startVertPtr || !endVertPtr )
      return cost;

   cost = endVertPtr->dist;
   for( vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath ){

      // if nextInPath is null return current cost
      if( !vp->nextInPath )
         return cost;

      tempCost = getCostOfResEdge(vp->nextInPath, vp);

      if( tempCost < cost )
         cost = tempCost;
   }

   return cost;

}


// private: getCostOfResEdge
template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getCostOfResEdge(VertPtr src,
                                                         VertPtr dst)
{

   typename EdgePairList::iterator edgePrIter;
   CostType cost = 0;

   // return cost of 0 if null
   if( !src || !dst )
      return cost;

   // if dst is found update cost
   for (edgePrIter = src->resAdjList.begin();
        edgePrIter != src->resAdjList.end();
        edgePrIter++)
   {
      if(edgePrIter->first == dst){
         cost = edgePrIter->second;
      }
   }

   return cost;

}


// private: adjustPathByCost
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::adjustPathByCost(CostType cost)
{

   VertPtr vp;

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath){

      // return early if nextInPath is null
      if ( !vp->nextInPath )
         return false;

      // add to the correct edge and check for return true
      // indicating if it was found or not
      if (
          // add to reverse edge
          !addCostToResEdge(vp, vp->nextInPath, cost) ||
          // remove from ResEdge
          !addCostToResEdge(vp->nextInPath, vp, -cost) ||
          // add to flow edge
          !addCostToFlowEdge(vp->nextInPath, vp, cost)
          )
         return false;

   }
   return true;

}


// private: addCostToResEdge
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToResEdge(VertPtr src, VertPtr dst,
                                                     CostType cost)
{

   typename EdgePairList::iterator edgePrIter;

   // check for null and return early if null
   if ( !src || !dst )
      return false;

   // if find dst is found the add the cost
   for (edgePrIter = src->resAdjList.begin();
        edgePrIter != src->resAdjList.end();
        edgePrIter++)
   {
      if (edgePrIter->first == dst)
      {
         edgePrIter->second += cost;
         return true;

      }
   }

   return false;

}


// private: addCostToFlowEdge
template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToFlowEdge(VertPtr src, VertPtr dst,
                                                      CostType cost)
{

   typename EdgePairList::iterator edgePrIter;

   // check for null and return early if null
   if ( !src || !dst )
      return false;

   // check if dst is found then updated the cost
   for (edgePrIter = src->flowAdjList.begin();
        edgePrIter != src->flowAdjList.end();
        edgePrIter++)
   {
      if(edgePrIter->first == dst){
         edgePrIter->second += cost;
         return true;
      }
   }

   // dst was NOT found so implies it was a reverse edge
   // so see if it exists and subtract from the cost
   for (edgePrIter = dst->flowAdjList.begin();
        edgePrIter != dst->flowAdjList.end();
        edgePrIter++)
   {
      if(edgePrIter->first == src){
         edgePrIter->second -= cost;
         return true;
      }
   }

   return false;

}


#endif