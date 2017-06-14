/////////////////////////////////////////////////
// Alejandro Pena Caicedo                 ///////
// ufid:3712-3113                        ///////
// gatorid:alejandropenacai             ////////
// ////////////////////////////////////////////




#include "MST.h"




Heap::Heap(int size) { //size should be n-1
            
            numElem = 0;

            heapSize = size;
}  

Heap::~Heap() {

}

 
void Heap::bubbleSort(){

Edge * temp;

for(int i = 0; i < myvec.size()-1; i++){

  int j = i+1;

    if(myvec[j]->edgWeight < myvec[i]->edgWeight)

               {
                   temp = myvec[i];
                   myvec[i] = myvec[j];
                   myvec[j] = temp;
                }
       }
} 



 
void Heap::push(int value, int NodeA, int NodeB) { //limit inserting more elements than heapsize***
            

            Edge *obj = new Edge;
            obj->edgWeight = value;
            obj->A = NodeA;
            obj->B= NodeB;
            myvec.push_back(obj);

            if(myvec.size()>2)
              bubbleSort();
              //sort(myvec.begin(), myvec.end(), cmd);


}
void Heap::quickprint(){

for(int i = 0; i<myvec.size(); i++){


  cout << "Edge Weight"<<myvec[i]->edgWeight<< ", NodeA "<< myvec[i]->A << ", NodeB "<< myvec[i]->B<<endl;

}

  
}



void Heap::pop() {//edit

myvec.pop_back();

}



//End of Heap class

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////




//Start of MST class


MST::MST(int numNod, int numEdg) : rows(numNod), cols(numNod){

  //rows = numNod;
  //cols = numNod;

  int numofNodes = numNod;
  int numofEdges = numEdg;


  // allocation
  a = new int*[rows];
	for(int i = 0; i < rows; i++)
		a[i] = new int[cols];

	  // initialization
	  for(int j = 0; j < rows; j++)
		  for(int i = 0; i < rows; i++)
			  a[i][j] = 0;


}

MST::~MST(){

  delete a;

}

void MST::input(){
	
  string inputString = "";
	getline(cin, inputString);

	//vector<int> inputStringAsVector;  made global
	stringstream ss(inputString);
	string token;

	while (getline(ss, token, ' '))
	{
		int intToken = stoi(token);
		inputStringAsVector.push_back(intToken);
	}

	//for (int i = 0; i < inputStringAsVector.size(); ++i)
	//{
	//	cout << inputStringAsVector[i] << endl;
	//}


}

void MST::inputAdjMatr(){

  //input();
  a[inputStringAsVector[0] ][inputStringAsVector[1] ] = inputStringAsVector[2];
  a[inputStringAsVector[1] ][inputStringAsVector[0] ] = inputStringAsVector[2];



}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


//Helper Functions

int MST::smallestkey(int element[], bool spanningtree[])
{
  int min = INT_MAX, key_min;
 
   for (int v = 0; v < numofNodes; v++)
     if (spanningtree[v] == false && element[v] < min)
         min = element[v], key_min = v;
 
   return key_min;
}
 
void MST::printSpanTree(int parenttree[], int n, int **graph)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < numofNodes; i++)
      printf("%d - %d    %d \n", parenttree[i], i, graph[i][parenttree[i]]);
}
 

void MST::edgeSearchPrint(int weight)
{
	bool search = false;
	for (int row = 0; row < numofNodes; row++)
	{
		for (int col = 0; col < numofNodes; col++)
		{
			if (a[col][row] == weight && search == false)
			{
				cout << "(" << col << ", " << row << ")" << endl;
				search = true;
			}
		}
	}
}

int MST::KrusWeight()
{
	for (int x = 0; x < numEdgesUsed; x++)
	{
		totalKrusWeight = totalKrusWeight + edgesUsed[x];
	}
	return totalKrusWeight;
}


int MST::borWeight()
{
	for (int x = 0; x < numEdgesUsed; x++)
	{
		totalBorWeight = totalBorWeight + edgesUsed[x];
	}
	return totalBorWeight;
}

bool MST::usedEdgeFound(int usedEdge)
{
	for (int m = 0; m < numEdgesUsed; m++)
	{ 
		if (edgesUsed[m] == usedEdge)
		{
			return true;
		}
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//Primary Algorithms/Functions


// boruvka
void MST::boruvka()
{
	int star = start;

	while (numEdgesUsed < numofNodes - 1)
	{
		int index = 0;
		Heap* BorHeap = new Heap(numofNodes); 

		for (int row = 0; row < numofNodes; row++)
		{
			if (a[star][row] != 0 && usedEdgeFound(a[star][row]) == false)
			{
				BorHeap->push(a[star][row], star, row);
			}

		}

		edgesUsed[index] = BorHeap->myvec[0]->edgWeight;
		index++;
		BorHeap->pop();
		numEdgesUsed++;

		if (star < numofNodes)
		{
			star++;
		}
		else
		{
			star = 0;
		}
		
	}

	for (int x = 0; x < numofEdges; x++)
	{
		edgeSearchPrint(edgesUsed[x]);
	}
}


void MST::primTree(int **graph)
{
     int parenttree[numofNodes]; 
     int element[numofNodes];   
     bool spanningtree[numofNodes];   

     for (int i = 0; i < numofNodes; i++)
        element[i] = INT_MAX, spanningtree[i] = false;
 
     element[0] = 0;     
     parenttree[0] = -1;  

     for (int count = 0; count < numofNodes-1; count++)
     {
        int x = smallestkey(element, spanningtree);
 
        spanningtree[x] = true;
 
        for (int v = 0; v < numofNodes; v++)
 
          if (graph[x][v] && spanningtree[v] == false && graph[x][v] <  element[v])
             parenttree[v]  = x, element[v] = graph[x][v];
     }
 
     printSpanTree(parenttree, numofNodes, graph);
}


// kruskal
void MST::kruskal()
{
	numEdgesUsed = 0;
	int totalKrusWeight = 0;
	int cheapestEdge = 0;
	maxEdges = numofNodes - 1;
	
	Heap* kruskalHeap = new Heap(numofNodes);
	
	for (int i = 0; i < numEdgesUnused; i++)
	{
		kruskalHeap->push(edgesUnused[i],rows, cols );
	}

	int y = 0;
	while (kruskalHeap->myvec.size() != 0 && numEdgesUsed != maxEdges)
	{
		cheapestEdge = kruskalHeap->myvec[0]->edgWeight;
		kruskalHeap->pop();
		if (true)
		{
			edgesUsed[y] = cheapestEdge;
			y++;
			numEdgesUsed++;
		}
	}

	for (int x = 0; x < numofEdges; x++)
	{
		edgeSearchPrint(edgesUsed[x]);
	}

}











int main()
{

  
  string str;
  cout<<"Enter number of edges:" <<endl;  //combine this with num of nodes linesvvvvvvvvv
  cin>> str;

  int x = stoi(str); //number of edges

  cout<< "Enter number of Nodes:" <<endl;
  cin>>str;
  int y = stoi(str); //number of nodes

  MST* tree = new MST(y,x);

  
  cout<< "Enter Node A and Node B and Undirected Edge Weight(s):"<<endl;
  
  for(int j = 0; j<x; j++){//changed j to start 1

    if(j == 0){  
      tree->input(); 
    }


    tree->input();
    tree->inputAdjMatr(); 
    tree->inputStringAsVector.clear();
  } 

	  for(int j = 0; j < y; j++){
      cout << '\n';
		  for(int i = 0; i < y; i++)
			  cout<< tree->a[i][j] << " ";}
    cout<< '\n'<<endl;




/*
Heap* myheap= new Heap(5);//initalize for size =  number of nodes-1
myheap->push(6, 1, 2);
myheap->push(1, 2, 3);
myheap->push(2, 3, 4);
myheap->push(3, 4, 5);
myheap->push(4, 5, 6);
myheap->push(20, 2, 3);

myheap->quickprint(); */





  
    tree->boruvka();
    cout<<tree->borWeight() <<endl;

    tree->primTree(tree->a);

    tree->kruskal();
    cout<< tree->KrusWeight()<<endl;
      




	return 0;
}
