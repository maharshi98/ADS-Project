#include "redblacktree.h"

redblacknode::redblacknode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right) 
{										//constructor definition
	//node values initialized
	cBuildingnum = buildingNum;			
	cExecutedtime = executedTime;
	cTotaltime = totalTime;
	cColor = color;
	cParent = parent;
	cLeft = left;
	cRight = right;
}

redblacktree::redblacktree()		//call to constructor
{
	ext = new redblacknode(-1,-1,-1,0,nullptr,nullptr,nullptr);
	root = ext;
}

void redblacktree::insertNode(redblacknode* node) 				//function insertNode
{
	redblacknode* n1 = ext;
	redblacknode* n2 = root;
	while (n2 != ext) {											//run till n2 not extermal node
		n1 = n2;
		if (node->cBuildingnum < n2->cBuildingnum) 				//search like that in a Binary search tree
		{
			n2 = n2->cLeft;
		} 
		else 
		{
			n2 = n2->cRight;
		}
	}
	node->cParent = n1;								
	if (n1 == ext) 										//if n1 equal ext, root is node
	{
		root = node;
	} 
	else if (node->cBuildingnum < n1->cBuildingnum) 	//check for lesser building num
	{
		n1->cLeft = node;								//insert into left
	} 
	else 
	{
		n1->cRight = node;								//insert into right
	}
	node->cLeft = ext;
	node->cRight = ext;
	node->cColor = 1;									//new node is always inserted as red
	reInsert(node);										//function call to preserve the properties of RBT
}

void redblacktree::reInsert(redblacknode* node)					//function definition
{
	redblacknode* temp;
	while (node->cParent->cColor == 1) 							//run while parent is red
	{
		if (node->cParent == node->cParent->cParent->cLeft) 	//check for left
		{
			temp = node->cParent->cParent->cRight;				//set temp as uncle to node
			if (temp->cColor == 1) 								//check if nodes' parents' sibling is red
			{	
				temp->cColor = 0;								//change colour of parent and uncle
				node->cParent->cColor = 0;
				node->cParent->cParent->cColor = 1;				//colour of grandparent set as red
				node = node->cParent->cParent;				
			}
			else 												//if nodes parents' sibling is black
			{	
				if (node == node->cParent->cRight) 			
				{	
					node = node->cParent;						
					lRotate(node);								//left rotate
				}
				node->cParent->cColor = 0;
				node->cParent->cParent->cColor = 1;
				rRotate(node->cParent->cParent);				//do right rotate
			
			}
		}
		else
		{
			temp = node->cParent->cParent->cLeft;				//set temp as left uncle to node
			if (temp->cColor == 1)								//repeat above for right
			{	
				temp->cColor = 0;
				node->cParent->cColor = 0;
				node->cParent->cParent->cColor = 1;
				node = node->cParent->cParent;
			}
			else 
			{
				if (node == node->cParent->cLeft) 
				{	//case 2
					node = node->cParent;
					rRotate(node);									//right rotate
				}
				node->cParent->cColor = 0;	
				node->cParent->cParent->cColor = 1;
				lRotate(node->cParent->cParent);					//do left rotate
			}
		}
	}
	root->cColor = 0;
}


void redblacktree::reDelete(redblacknode* node) 						//reDelete function definition
{
	while (node != root && node->cColor == 0) 							//check if node is not root and colour is black
	{
		redblacknode* temp;
		if (node == node->cParent->cLeft) 								//checks if node is left child or not			
		{
			temp = node->cParent->cRight;
			if (temp->cColor == 1) 										//handles case1 for delete i.e. color of sibling is red
			{	
				temp->cColor = 0;
				node->cParent->cColor = 1;
				lRotate(node->cParent);
				temp = node->cParent->cRight;
			}
			if (temp->cLeft->cColor == 0 && temp->cRight->cColor == 0) 		//handles 2nd case i.e. color of both children of sibling is black 
			{	
				temp->cColor = 1;
				node = node->cParent;
			} 
			else 
			{
				if (temp->cRight->cColor == 0) 								//handles 3rd case i.e. checks if right child of sibling is black
				{
					temp->cLeft->cColor = 0;
					temp->cColor = 1;
					rRotate(temp);
					temp = node->cParent->cRight;
				} 
				temp->cColor = node->cParent->cColor;
				node->cParent->cColor = 0;
				temp->cRight->cColor = 0;
				lRotate(node->cParent);
				node = root;
			}
		} 
		else 															//if node is right child, the above cases are handled in the same way
		{
			temp = node->cParent->cLeft;
			if (temp->cColor == 1) 										//handles case1 for delete i.e. color of sibling is red
			{	//case 1
				temp->cColor = 0;
				node->cParent->cColor = 1;
				rRotate(node->cParent);
				temp = node->cParent->cLeft;
			}
			if (temp->cLeft->cColor == 0 && temp->cRight->cColor == 0) 			//handles 2nd case i.e. color of both children of sibling is black
			{	//case 2
				temp->cColor = 1;
				node = node->cParent;
			}
			else 															//handles 3rd case
			{
				if (temp->cLeft->cColor == 0) 
				{	//case 3
					temp->cRight->cColor = 0;						
					temp->cColor = 1;
					lRotate(temp);
					temp = node->cParent->cLeft;
				} 
				temp->cColor = node->cParent->cColor;	//case 4
				node->cParent->cColor = 0;
				temp->cLeft->cColor = 0;
				rRotate(node->cParent);
				node = root;
			}
		} 
	}
	node->cColor = 0;
}

void redblacktree::rbtRelink(redblacknode* n1, redblacknode* n2)			//function call for reconnection of subtree
{
	if (n1->cParent == ext) 												//checks if parent is external node
	{	
		root = n2;
	} 
	else if (n1 == n1->cParent->cLeft)										//check if n1 is left child
	{
		n1->cParent->cLeft = n2;											//make n2 parents left child
	} 
	else 																	//check if n1 is right child
	{
		n1->cParent->cRight = n2;											//make n2 parents right child
	}
	n2->cParent = n1->cParent;
}

void redblacktree::deleteNode(redblacknode* node) 							//function for node deletion
{
	redblacknode *n1,*n2;
	n2 = node;
	int tempColor = n2->cColor;	
	if (node->cLeft == ext) 												//check if left node is leaf node
	{
		n1 = node->cRight;
		rbtRelink(node, node->cRight);										//if yes, just delte and call relink
	} 
	else if (node->cRight == ext) 											//check if right node is leaf node
	{
		n1 = node->cLeft;
		rbtRelink(node, node->cLeft);										//if yes, just delte and call relink
	} 
	else 																	//if node is not leaft
	{
		n2 = findMin(node->cRight);											//find minimum from right subtree
		tempColor = n2->cColor;
		n1 = n2->cRight;
		if (n2->cParent == node) 											//check if n2's parent is node		
		{
			n1->cParent = n2;
		} 
		else																//if not, perform re-link for the subtree
		{
			rbtRelink(n2, n2->cRight);
			n2->cRight = node->cRight;
			n2->cRight->cParent = n2;
		}
		rbtRelink(node, n2);												//call re-link again
		n2->cLeft = node->cLeft;
		n2->cLeft->cParent = n2;
		n2->cColor = node->cColor;
	}
	if (tempColor == 0)
	{
		reDelete(n1);													//call to reDelete() for fixing the imbalances
	}
}




void redblacktree::lRotate(redblacknode* node) 						//function for left rotate
{
	redblacknode* temp = node->cRight;								//assign node's right to temp
	node->cRight = temp->cLeft;
	if (temp->cLeft != ext) 										//check if left child is not external node
	{
		temp->cLeft->cParent = node;								
	}
	temp->cParent = node->cParent;
	if (node->cParent == ext) 										//if parent of node is external, that node becomes root
	{
		root = temp;												//assign temp to root
	}
	else if (node == node->cParent->cLeft)							//check if node is left child
	{
		node->cParent->cLeft = temp;								//rotate and assign temp to left child to node's parent
	}
	else															//node is right child
	{
		node->cParent->cRight = temp;								//rotate and assign temp to right child to node's parent
	}
	temp->cLeft = node;
	node->cParent = temp;
}

void redblacktree::rRotate(redblacknode* node)						//function for right rotate
{
	redblacknode* temp = node->cLeft;								//assign node's left to temp
	node->cLeft = temp->cRight;
	if (temp->cRight != ext)										//check if left child is not external node
	{
		temp->cRight->cParent = node;
	}
	temp->cParent = node->cParent;
	if (node->cParent == ext)										//if parent of node is external, that node becomes root
	{
		root = temp;												//assign temp to root
	}
	else if (node == node->cParent->cRight)							//check if node is right child
	{
		node->cParent->cRight = temp;								//rotate and assign temp to right child to node's parent
	}
	else															//node is left child
	{
		node->cParent->cLeft = temp;								//rotate and assign temp to left child to node's parent
	}
	temp->cRight = node;
	node->cParent = temp;
}


redblacknode* redblacktree::findMin(redblacknode* node) 				//function to find minimum node in redblack tree
{
	while (node->cLeft != ext) 											//while there is aleft node, go left
	{
		node = node->cLeft;
	}
	return node;
}

redblacknode* redblacktree::searchTree(long int bnum) 					//function for searching a single building
{
	return searchTreeHelper(root, bnum);								//calls recursive helper function
}

redblacknode* redblacktree::searchTreeHelper(redblacknode* node, long int bnum)			//recursice helper function
{
	if (node == ext || bnum == node->cBuildingnum) 						//check if we reached external node or search was succesful, if yes then return
	{
		return node;
	}
	if (bnum < node->cBuildingnum) 										//else, we call search again
	{
		return searchTreeHelper(node->cLeft, bnum);
	} 
	return searchTreeHelper(node->cRight, bnum);
}

void redblacktree::searchTreeInRange(long int bnum1, long int bnum2, vector<redblacknode*>* vect) 		//function for searching between two building numbers
{
	searchTreeInRangeHelper(root, bnum1, bnum2, vect);								//recursive helper function called for searchinf
}

void redblacktree::searchTreeInRangeHelper(redblacknode* node, long int bnum1, long int bnum2, vector<redblacknode*>* vect) 
{
	if (!((node == ext) || (node == nullptr))) 
	{
		if (!(node->cBuildingnum < bnum1)) 									
		{
			searchTreeInRangeHelper(node->cLeft, bnum1, bnum2, vect);		//recursive call on left subtree	
		}
		if ((node->cBuildingnum >= bnum1) and (node->cBuildingnum <= bnum2)) 
		{
			vect->push_back(node);											//if search between range was successful, add that node to out resultant vector
		}
		if (!(node->cBuildingnum > bnum2)) 									
		{
			searchTreeInRangeHelper(node->cRight, bnum1, bnum2, vect);		//recursive call on right subtree
		}
	}
}