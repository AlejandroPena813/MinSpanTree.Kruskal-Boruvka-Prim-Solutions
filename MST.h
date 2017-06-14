/////////////////////////////////////////////////
// Alejandro Pena Caicedo                 ///////
// ufid:3712-3113                        ///////
// gatorid:alejandropenacai             ////////
// ////////////////////////////////////////////



#ifndef _MST_H_
#define _MST_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <limits.h>
#include <queue>



using namespace std;

class MST{

  private:

  int NodeA = 0;
  int NodeB = 0;
  int weightOfEdg = 0;
  int numofNodes;
  int numofEdges;
  int maxEdges = 0;
  int start = 0;
  int totalKrusWeight = 0;
  int totalBorWeight = 0;
  int numEdgesUnused = 0;
  int numEdgesUsed = 0;
  int locCol = 0;
  int locRow = 0;


  public:
    MST(int numNod, int numEdg);
    
    ~MST();
    
    //global variables
  	vector<int> inputStringAsVector; //global vector that stores edge weights and nodes

    //start of the 2D adjacency matrix
    const int rows;
	  const int cols;
	  int ** a; //adjaceny matrix

    int * edgesUnused = new int[numofEdges];
    int * edgesUsed = new int[maxEdges];

    bool rowLocEqVisited = false;
    bool colLocEqVisited = false;

    
    //helper functions
    void input();
    void inputAdjMatr();
    int smallestkey(int element[], bool spanningtree[]);
    void printSpanTree(int parenttree[], int n, int **graph);
    void edgeSearchPrint(int weight);
    int KrusWeight();
    bool usedEdgeFound(int usedEdge);
    int borWeight();



    
    //main functions
    void boruvka();//Boruvka function
    void primTree(int **graph);//Prim Function
    void kruskal();//Kruskal function




};




class Heap {
private:

      struct Edge{

      int A;//Node A
      int B;//Node B
      int edgWeight;//weight of edge
      
      }; 

      

      int heapSize;
      int numElem;//stores amount of heap elements


public:

      Heap(int size);

      ~Heap();

       vector<Edge*> myvec;


      void bubbleSort();
      
      void push(int value, int NodeA, int NodeB);  

      void pop(); //EDIT !!!!

      void quickprint(); //delete this     RENAME AND ADD FINAL FUNCTIO


};


#endif
