#ifndef MINHEAP_H
#define MINHEAP_H
#include "redblacktree.h"			//include redblacktree since we need to provide node reference of RBT in minheap node
const int MAX = 2000;				//since max number of buildings can be 2000
class bNode 						//class for minHeap node
{
	public:
		long int cBuildingnum;
		long int cExecutedtime;
		long int cTotaltime;
		redblacknode* cRBTnode;
		bNode(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn);			//constructor for initialization
};

class minheap 						//class for minHeap functions
{
	private:	
		void bubbleDown(int index);		//function to conserve minHeap property when node is deleted
		void bubbleUp(int index);		//function to conserve minHeap property when node is inserted					
	public:
		bNode* cHeap[MAX];				//array to maintain the nodes of minheap
		int last = 0;					//last maintained so that the last element can be accessed during deletion
		void insertNode(bNode* value);	//function for insert
		bNode* getMinFromHeap();		//function to get min from minheap
		void deleteMin();				//function to delete min from minheap
};
#endif
