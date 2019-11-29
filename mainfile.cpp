/*
Name: Maharshi Doshi
UFID: 05339287
Program: ADS Project
*/

//libraries and header files added
#include <iostream>				
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "minheap.h"				//contains classes for minheap node and minheap functions
#include "redblacktree.h"			////contains classes for redblacktree node and redblacktree functions

using namespace std;
 
void runInputLine(string cmd, string parseArgs, minheap* mhTree, redblacktree* rbTree, ofstream& opF) 	//function for running the input command
{
	if (cmd == "Insert") 					//check if command is insert
	{ 
		long int buildingNum,totalTime;
		regex re("(.*),(.*)");
		if (regex_match(parseArgs, re)) 		//regex extracts out the arguments from the input line
		{
			for (smatch itr; regex_search(parseArgs, itr, re); parseArgs = itr.suffix()) 	//for loop extracts values one by one
			{
				buildingNum = stol(itr.str(1));
				totalTime = stol(itr.str(2));
			}
			redblacknode* rbNode = new redblacknode(buildingNum, 0, totalTime, 1, nullptr, rbTree->ext, rbTree->ext);	//create new redblack node
			rbTree->insertNode(rbNode);									//insert the node in the tree
			bNode* B = new bNode(buildingNum,0,totalTime,rbNode);		//create new minheap node
			mhTree->insertNode(B);										//insert node into minheap tree
		}
	} 
	else if (cmd == "PrintBuilding")					//check if command is Print 
	{	
		long int building1 = -1;
		long int building2 = -1;
		regex re("(.*),(.*)");							//defining a regex pattern
		if (regex_match(parseArgs, re)) 				//regex extracts out the building numbers
		{
			for (smatch itr; regex_search(parseArgs, itr, re); parseArgs = itr.suffix()) 	//for loop extracts values one by one
			{
				building1 = stol(itr.str(1));							//building1
				building2 = stol(itr.str(2));							//building2
			}
			vector<redblacknode*>* vect = new vector<redblacknode*>;		//create a vector for storing the nodes
			rbTree->searchTreeInRange(building1, building2, vect);			//call search in range			
			int vect_size = vect->size();
			for (int i = 0; i < vect_size; i++)
			{
				opF << "("<<vect->at(i)->cBuildingnum << "," << vect->at(i)->cExecutedtime << "," << vect->at(i)->cTotaltime << ")"; //write output to file
			}
			if (vect_size == 0) {
				opF << "(" << 0 << "," << 0 << "," << 0 << ")";			//write output in specific format
			}
			opF << endl;
		} 
		else 
		{
			building1 = stol(parseArgs);
			redblacknode* searchnode = rbTree->searchTree(building1);		//call search for single building number
			if (searchnode->cBuildingnum == -1) 							//if node not found
			{
				opF<<"("<<0<< "," <<0<< "," <<0<<")";						//write (0,0,0)
			}
			else 
			{
				opF << "("<<searchnode->cBuildingnum << "," << searchnode->cExecutedtime << "," << searchnode->cTotaltime << ")"<<endl;	//result written to output file
			}
		}
	}
}

int main(int argc, char *argv[]) 					//main function
{
	minheap* mhTree = new minheap;					//initializing minheap
	redblacktree* rbTree = new redblacktree();		//initializing redblacktree
	vector<string> input;
	string line = "";
	ifstream inpF(argv[1]);							//ifstream used to open a file and get input data
	if(!inpF || argc!=2) 							//check if file exists or command entered properly
	{
		cout <<"\n--- Invalid File Name or Invalid Input ---\n";
		return 1;
	}	
	while (getline(inpF, line)) 					//store the commands from input file into a string vector
	{
		input.push_back(line);						//store all lines one by one to a string vector
	}
	inpF.close();									//close the file
	ofstream opF;
	opF.open("output_file.txt");
	int s = input.size();							//size of input vector
	long int lNum=0;	
	bNode* current=nullptr;							//current refers to the current node we will be working on
	int flag = 1;									
	long int globalTime = 0;						//global timer	
	int work = 0;									//variable keeps track of work done 
	bool busy = false;								//boolean to check if wayne enterprises is busy or not
	regex re("(.*): (.*)\\((.*)\\)"); // regex to split the input line in cmdtime, cmd and parseArgs.
	long int cmdtime = -1;
	string cmd;
	string parseArgs;	

	while(flag) 									//run till flag is 1
	{
		string line = "-1: Break()";
		if (lNum != s) 
		{
			line = input[lNum];
		}
		if (regex_match(line, re)) 					//regex matches the pattern
		{
			for (smatch itr; regex_search(line, itr, re); line = itr.suffix()) {		//for loop extracts arguments one by one
				cmdtime = stol(itr.str(1));
				cmd = itr.str(2);
				parseArgs = itr.str(3);
			}
			while (globalTime != cmdtime) 			//run loop till global time reaches the last command time
			{
				if((current!=nullptr) && (current->cExecutedtime == current->cTotaltime)) 		//check if building's construction is complete
				{
					busy = false;
					opF<<"("<<current->cBuildingnum<<","<<globalTime<<")"<<endl;
					rbTree->deleteNode(current->cRBTnode);							//delete the completed node 
					current = nullptr;
					if ((mhTree->last == 0) && (cmdtime == -1)) 			//check if last element of array is 0 or command time not valid
					{
						flag = 0;									//if yes then break from loop
						break;
					}
				} 
				else if (current!=nullptr && work == 5) 				//check if work done for a building equals 5, if true then insert the building in minheap
				{
					busy = false;
					mhTree->insertNode(current);						//insert current again
				} 
				else if (current != nullptr) 
				{
					work++;												//increment work done and execution time
					current->cExecutedtime++;
					current->cRBTnode->cExecutedtime++;
				}	
				if(!busy && mhTree->last!=0) 
				{
					work = 0;											//re-initialize work
					busy = true;
					current = mhTree->getMinFromHeap();					//pick the building with min execution time from minHeap
					mhTree->deleteMin();								//delete the picked node
					current->cExecutedtime++;
					current->cRBTnode->cExecutedtime++;
					work ++;
				}
				globalTime++;											//increment global counter on each iteration
			}
		    runInputLine(cmd, parseArgs, mhTree, rbTree, opF);			//call function to run command
			lNum++;
		}
	}
	opF.close();													//close file
	return 0;
}