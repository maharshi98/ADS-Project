#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include <vector>
using namespace std;

class redblacknode 						//class for redblack node
{
	public:
		long int cBuildingnum;			//variables declared
		long int cExecutedtime;
		long int cTotaltime;
		redblacknode* cLeft;
		redblacknode* cRight;
		redblacknode* cParent;
		int cColor;
		redblacknode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right); //constructor declared
};

class redblacktree 
{
	private:
		void reInsert(redblacknode* node);							//function to preserve redblack property when node is inserted
		void reDelete(redblacknode* node);							//function to preserve redblack property when node is deleted
		void rbtRelink(redblacknode* n1, redblacknode* n2);			//link a subtree from one side to another
		void lRotate(redblacknode* node);							//left rotate
		void rRotate(redblacknode* node);							//right rotate
		redblacknode* findMin(redblacknode* node);					//find min from RBT
		redblacknode* searchTreeHelper(redblacknode* node, long int key);			//helper function for single node search
		void searchTreeInRangeHelper(redblacknode* node, long int building1, long int building2, vector<redblacknode*>* vect); //helper function for multiple node search
	public:
		redblacknode* root;	
		redblacknode* ext;
		redblacktree();
		redblacknode* searchTree(long int buidingNum);				//function for single node search
		void insertNode(redblacknode* node);						//function for node insertion
		void deleteNode(redblacknode* node);						//function for node deletion
		void searchTreeInRange(long int building1, long int building2, vector<redblacknode*>* vect); // function for multiple node search
};
#endif
