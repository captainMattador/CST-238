
/*
 Assignment: Assignment 9 - The Maximum Flow Problem
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: implement a maximum flow graph algorithm
 by modifying dijkstra algorithm
 */

#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"

int main() {

   int finalFlow;

   // build graph
   FHflowGraph<string, int> myG;
   // used just for testing purposes
   bool gStart, gEnd;

   // teacher included graph for testing.
//   myG.addEdge("s","a", 3);    myG.addEdge("s","b", 2);
//   myG.addEdge("a","b", 1);    myG.addEdge("a","c", 3); myG.addEdge("a","d", 4);
//   myG.addEdge("b","d", 2);
//   myG.addEdge("c","t", 2);
//   myG.addEdge("d","t", 3);

   myG.addEdge("s","a", 1);
   myG.addEdge("s","b", 1);
   myG.addEdge("s","t", 4);
   myG.addEdge("b","d", 2);
   myG.addEdge("a","c", 1);
   myG.addEdge("c","t", 1);
   myG.addEdge("d","t", 2);

   cout << "\n------------------------";
   cout << "\nteacher included graph\n";

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   gStart = myG.setStartVert("s");
   gEnd = myG.setEndVert("t");

   // tests to see if start and end were found
//   if(gStart)
//      cout << "found start" << endl;
//   else
//      cout << "start not found" << endl;
//
//   if(gEnd)
//       cout << "found end" << endl;
//   else
//       cout << "end not found" << endl;

   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();



   
   // second test case
   // from the text exercise 9.11
   myG.clear();
   myG.addEdge("s","A", 1); myG.addEdge("s","D", 4); myG.addEdge("s","G", 6);
   myG.addEdge("A","B", 2); myG.addEdge("A","E", 2);
   myG.addEdge("B","C", 2);
   myG.addEdge("C","t", 4);
   myG.addEdge("D","E", 3); myG.addEdge("D","A", 3);
   myG.addEdge("E","C", 2); myG.addEdge("E","F", 3); myG.addEdge("E","I", 3);
   myG.addEdge("F","C", 1); myG.addEdge("F","t", 3);
   myG.addEdge("G","D", 2); myG.addEdge("G","E", 1); myG.addEdge("G","H", 6);
   myG.addEdge("H","E", 2); myG.addEdge("H","I", 6);
   myG.addEdge("I","F", 1); myG.addEdge("I","t", 4);

   cout << "\n------------------------";
   cout << "\nsecond test case\n";

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");

   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();




   // third test case
   // graph test case (from Eric Reed)
   myG.clear();
   myG.addEdge("s","h", 5);
   myG.addEdge("h","i", 5);
   myG.addEdge("i","b", 5);
   myG.addEdge("a","b", 5);
   myG.addEdge("s","a", 5);
   myG.addEdge("s","c", 5);
   myG.addEdge("s","d", 5);
   myG.addEdge("a","e", 5);
   myG.addEdge("e","j", 5);
   myG.addEdge("j","t", 5);
   myG.addEdge("d","g", 5);
   myG.addEdge("g","t", 5);
   myG.addEdge("b","t", 5);
   myG.addEdge("c","t", 5);
   myG.addEdge("d","c", 5);

   cout << "\n------------------------";
   cout << "\nthird test case\n";

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");

   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   return 0;

}

// out put of all three test graphs

/*

 ------------------------
 teacher included graph
 ------------------------
 Adj Res List for s: a(3) b(2)
 Adj Res List for a: s(0) b(1) c(3) d(4)
 Adj Res List for b: s(0) a(0) d(2)
 Adj Res List for c: a(0) t(2)
 Adj Res List for d: a(0) b(0) t(3)
 Adj Res List for t: c(0) d(0)

 ------------------------
 Adj Flow List for s: a(0) b(0)
 Adj Flow List for a: b(0) c(0) d(0)
 Adj Flow List for b: d(0)
 Adj Flow List for c: t(0)
 Adj Flow List for d: t(0)
 Adj Flow List for t:

 Final flow: 5
 ------------------------
 Adj Res List for s: a(0) b(0)
 Adj Res List for a: s(3) b(1) c(1) d(3)
 Adj Res List for b: s(2) a(0) d(0)
 Adj Res List for c: a(2) t(0)
 Adj Res List for d: a(1) b(2) t(0)
 Adj Res List for t: c(2) d(3)

 ------------------------
 Adj Flow List for s: a(3) b(2)
 Adj Flow List for a: b(0) c(2) d(1)
 Adj Flow List for b: d(2)
 Adj Flow List for c: t(2)
 Adj Flow List for d: t(3)
 Adj Flow List for t:


 ------------------------
 second test case
 ------------------------
 Adj Res List for s: A(1) D(4) G(6)
 Adj Res List for A: s(0) D(0) B(2) E(2)
 Adj Res List for D: s(0) A(3) G(0) E(3)
 Adj Res List for G: s(0) D(2) E(1) H(6)
 Adj Res List for B: A(0) C(2)
 Adj Res List for E: A(0) D(0) G(0) C(2) F(3) I(3) H(0)
 Adj Res List for C: B(0) E(0) t(4) F(0)
 Adj Res List for t: C(0) F(0) I(0)
 Adj Res List for F: E(0) C(1) t(3) I(0)
 Adj Res List for I: E(0) t(4) F(1) H(0)
 Adj Res List for H: G(0) E(2) I(6)

 ------------------------
 Adj Flow List for s: A(0) D(0) G(0)
 Adj Flow List for A: B(0) E(0)
 Adj Flow List for D: A(0) E(0)
 Adj Flow List for G: D(0) E(0) H(0)
 Adj Flow List for B: C(0)
 Adj Flow List for E: C(0) F(0) I(0)
 Adj Flow List for C: t(0)
 Adj Flow List for t:
 Adj Flow List for F: C(0) t(0)
 Adj Flow List for I: t(0) F(0)
 Adj Flow List for H: E(0) I(0)

 Final flow: 11
 ------------------------
 Adj Res List for s: A(0) D(0) G(0)
 Adj Res List for A: s(1) D(3) B(0) E(0)
 Adj Res List for D: s(4) A(0) G(2) E(0)
 Adj Res List for G: s(6) D(0) E(0) H(3)
 Adj Res List for B: A(2) C(0)
 Adj Res List for E: A(2) D(3) G(1) C(0) F(0) I(0) H(2)
 Adj Res List for C: B(2) E(2) t(0) F(0)
 Adj Res List for t: C(4) F(3) I(4)
 Adj Res List for F: E(3) C(1) t(0) I(0)
 Adj Res List for I: E(3) t(0) F(1) H(1)
 Adj Res List for H: G(3) E(0) I(5)

 ------------------------
 Adj Flow List for s: A(1) D(4) G(6)
 Adj Flow List for A: B(2) E(2)
 Adj Flow List for D: A(3) E(3)
 Adj Flow List for G: D(2) E(1) H(3)
 Adj Flow List for B: C(2)
 Adj Flow List for E: C(2) F(3) I(3)
 Adj Flow List for C: t(4)
 Adj Flow List for t:
 Adj Flow List for F: C(0) t(3)
 Adj Flow List for I: t(4) F(0)
 Adj Flow List for H: E(2) I(1)


 ------------------------
 third test case
 ------------------------
 Adj Res List for s: h(5) a(5) c(5) d(5)
 Adj Res List for h: s(0) i(5)
 Adj Res List for i: h(0) b(5)
 Adj Res List for b: i(0) a(0) t(5)
 Adj Res List for a: s(0) b(5) e(5)
 Adj Res List for c: s(0) d(0) t(5)
 Adj Res List for d: s(0) c(5) g(5)
 Adj Res List for e: a(0) j(5)
 Adj Res List for j: e(0) t(5)
 Adj Res List for t: b(0) c(0) j(0) g(0)
 Adj Res List for g: d(0) t(5)

 ------------------------
 Adj Flow List for s: h(0) a(0) c(0) d(0)
 Adj Flow List for h: i(0)
 Adj Flow List for i: b(0)
 Adj Flow List for b: t(0)
 Adj Flow List for a: b(0) e(0)
 Adj Flow List for c: t(0)
 Adj Flow List for d: c(0) g(0)
 Adj Flow List for e: j(0)
 Adj Flow List for j: t(0)
 Adj Flow List for t:
 Adj Flow List for g: t(0)

 Final flow: 20
 ------------------------
 Adj Res List for s: h(0) a(0) c(0) d(0)
 Adj Res List for h: s(5) i(0)
 Adj Res List for i: h(5) b(0)
 Adj Res List for b: i(5) a(0) t(0)
 Adj Res List for a: s(5) b(5) e(0)
 Adj Res List for c: s(5) d(0) t(0)
 Adj Res List for d: s(5) c(5) g(0)
 Adj Res List for e: a(5) j(0)
 Adj Res List for j: e(5) t(0)
 Adj Res List for t: b(5) c(5) j(5) g(5)
 Adj Res List for g: d(5) t(0)

 ------------------------
 Adj Flow List for s: h(5) a(5) c(5) d(5)
 Adj Flow List for h: i(5)
 Adj Flow List for i: b(5)
 Adj Flow List for b: t(5)
 Adj Flow List for a: b(0) e(5)
 Adj Flow List for c: t(5)
 Adj Flow List for d: c(0) g(5)
 Adj Flow List for e: j(5) 
 Adj Flow List for j: t(5) 
 Adj Flow List for t: 
 Adj Flow List for g: t(5) 
 
 Program ended with exit code: 0
 
 */
