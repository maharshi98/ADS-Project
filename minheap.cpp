#include "minheap.h"			//header file contains the declarations

bNode::bNode(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn) 	//constructor defined
{
	cBuildingnum = buildingNum;			//values assigned
	cExecutedtime = executedTime;
	cTotaltime = totalTime;
	cRBTnode = rbn;
}

void minheap::insertNode(bNode* value)		//function to insert a new node
{
	cHeap[last] = value;
	bubbleUp(last);							//bubbleUp called to rebalance from the last node
	last++;									//last incremented due to addition of one node
}

void minheap::deleteMin()					//delete function to delete a node
{
	if(last == 0)
	{
		return;
	}	
	cHeap[0] = cHeap[last-1];				//last node added to the top
	last--;									
	bubbleDown(0);							//bubbleDown called to rebalance from the top
}

bNode* minheap::getMinFromHeap()			//function to get min from MinHeap
{
	return cHeap[0];
}

void minheap::bubbleDown(int index)			//definition of bubbleDown
{
	int lcIndex = 2*index + 1;				//initializing left and right indexes
	int rcIndex = 2*index + 2;
	if(lcIndex >= last) 
	{
		return;
	}
	int index_min = index;
	bNode current = *cHeap[index];
	bNode lchild = *cHeap[lcIndex];
	bNode rchild = *cHeap[rcIndex];
	if(current.cExecutedtime > lchild.cExecutedtime)	//check if parent's execution time is greater than child's
	{
		index_min = lcIndex;						//if true then change index
		current = lchild;
	}
	else if(current.cExecutedtime == lchild.cExecutedtime) 	//check if execution time is same for parent and child
	{
		if (current.cBuildingnum > lchild.cBuildingnum) 	//if true, check if parent's building number is more than childs
		{
			index_min = lcIndex;						//if yes, then re-index
			current = lchild;
		}
	}
	if ((rcIndex < last) && (current.cExecutedtime > rchild.cExecutedtime)) 		//check the above conditions for right child
	{
		index_min = rcIndex;
	} 
	else if (current.cExecutedtime == rchild.cExecutedtime) 
	{
		if (current.cBuildingnum > rchild.cBuildingnum) 
		{
			index_min = rcIndex;
		}
	}
	if(index_min != index)					//if index_min is different than index, it means we need to swap
	{
		bNode* temp = cHeap[index];			//swapping
		cHeap[index] = cHeap[index_min];
		cHeap[index_min] = temp;
		bubbleDown(index_min);				//recursive call to bubbleDown
	}
}

void minheap::bubbleUp(int index) 			//definition of bubbleUp
{
	if (index == 0) 						//check if root, if true then return
	{
		return;
	}
	int index_parent = (index-1)/2;			//getting index of parent
	bNode parent = *cHeap[index_parent];	
	bNode current = *cHeap[index];
    if(parent.cExecutedtime > current.cExecutedtime) //check if execution time of parent is more than that of child
    {
        bNode* temp = cHeap[index_parent];		//if true then, swap the parent and child
        cHeap[index_parent] = cHeap[index];
        cHeap[index] = temp;
        bubbleUp(index_parent);
    } 
    else if (parent.cExecutedtime == current.cExecutedtime) 	//in case execution time is same for parent and child
    {
		if (parent.cBuildingnum > current.cBuildingnum) 	//check if building number of parent is more than that of child
		{
			bNode* temp = cHeap[index_parent];				//if true then swap parent and child
			cHeap[index_parent] = cHeap[index];
			cHeap[index] = temp;
			bubbleUp(index_parent);				//recursive call to bubbleUp
		}
    }
}