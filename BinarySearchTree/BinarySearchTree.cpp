/*
 * BinarySearchTree.cpp
 *
 *  Created on: 05.06.2016 ã.
 *      Author: NikolayD
 */

#include "BinarySearchTree.hpp"

#include<iostream>



//Helper function, return the node with minimum ID value of given tree
static Node* findMinNode( Node ** T )
{
	Node * temp = (*T);
	while(nullptr != temp)
	{
		temp = temp->left;
	}
	return temp;
}
//Function that find node by given ID, it return eNodeDoesNotExist when there is no
//such node and eSuccess when there is
ReturnInfo FindNodeByID(Node **T, const int ID, Node *getNode)
{
	if(nullptr == (*T))
	{
		return ReturnInfo::eNodeDoesNotExist;
	}
	else
	{
		if( ID == (*T)->ID )
		{
			*getNode = *(*T);
			return ReturnInfo::eSuccess;
		}
		else if( ID > (*T)->ID )
		{
			FindNodeByID(&(*T)->right, ID, getNode);
		}
		else if( ID < (*T)->ID)
		{
			FindNodeByID(&(*T)->left, ID, getNode);
		}
		else
		{
			//not reachable
		}
	}
	return ReturnInfo::eSuccess; //not reachable
}
//Insert node in given tree by given ID and Data
//return eMemoryAllocation if there is problem with allocating
//return eSuccess when everything is fine
//return eNodeIsAlreadyInserted if there is node with the same ID in
//the given tree
ReturnInfo InsertNode(Node ** T,const int ID,const int Data)
{
	if(nullptr == (*T))
	{
		Node * newOne = new Node(ID, Data);
		if(nullptr == newOne)
		{
			return ReturnInfo::eMemoryAllocationProblem;
		}
		*T = newOne;
		return ReturnInfo::eSuccess;
	}
	if( ID > (*T)->ID )
	{
		if((*T)->right)
		{
			InsertNode(&(*T)->right,ID,Data);
		}
		else
		{
			Node * newOne = new Node(ID, Data);
			(*T)->right = newOne;
			return ReturnInfo::eSuccess;
		}
	}
	else if( ID < (*T)->ID )
	{
		if((*T)->left)
		{
			InsertNode(&(*T)->left,ID,Data);
		}
		else
		{
			Node * newOne = new Node(ID, Data);
			(*T)->left = newOne;
			return ReturnInfo::eSuccess;
		}
	}
	else
	{
		return ReturnInfo::eNodeIsAlreadyInserted;
	}
	return ReturnInfo::eSuccess; //not reachable
}

ReturnInfo PrintInOrder(Node **T)
{
	if( nullptr == (*T) )
	{
		return ReturnInfo::eSuccess;
	}
	(void)PrintInOrder(&(*T)->left);
	std::cout<<(*T)->ID<<" has value: "<<(*T)->Data<<std::endl;
	(void)PrintInOrder(&(*T)->right);
	return ReturnInfo::eSuccess;
}

//Delete Node by given ID, possible cases are described below
//return eNodeDoesNotExist if the tree pointer is invalid
//return eSuccess if everything is fine
ReturnInfo DeleteNodeByID(Node ** T, const int ID)
{
	if(nullptr == (*T))
	{
		return ReturnInfo::eNodeDoesNotExist;
	}
	else
	{
		if(ID > (*T)->ID)
		{
			DeleteNodeByID(&(*T)->right, ID);
		}
		else if( ID < (*T)->ID)
		{
			DeleteNodeByID(&(*T)->left, ID);
		}
		else if ( ID == (*T)->ID )
		{
			//4 sub cases
			//1. if it is a leaf, consequently it has no left neither right child
			//2. if it has left child
			//3. if it has right child
			//4. if it has both right and left child, then we find the left most child
			//in the right subtree and we substitute it with the pointed one

			if((*T)->left && (*T)->right)
			{
				Node *replace = findMinNode(&(*T)->right);
				(*T)->ID = replace->ID;
				(*T)->Data = replace->Data;
				replace->ID = ID;
				DeleteNodeByID(&(*T)->right, ID);
			}
			else
			{
				//if there is one child or no children at all, we replace the desired
				//node with its left or right child and then we release the memory
				//or just release the memory (where we unref its parent?!)
				Node *temp = (*T);
				if((*T)->left)
				{
					(*T) = (*T)->left;
				}
				else if((*T)->right)
				{
					(*T)= (*T)->right;
				}
				else
				{
					(*T) = nullptr;
				}
				delete temp;
				return ReturnInfo::eSuccess;
			}
		}

	}
	return ReturnInfo::eSuccess; //not reachable
}

int main()
{
	Node *T = nullptr;
	ReturnInfo retVal;
	retVal = InsertNode(&T,8,25);
	retVal = InsertNode(&T,3,22);
	retVal = InsertNode(&T,10,14);
	retVal = InsertNode(&T,14,2);
	retVal = InsertNode(&T,1,1);
	retVal = InsertNode(&T,6,100);
	retVal = InsertNode(&T,7,110);
	retVal = InsertNode(&T,13,1111);

	(void)PrintInOrder(&T);

	std::cout<<std::endl;
	(void)DeleteNodeByID(&T,14);
//	std::cout<<DeleteNodeByID(&T,6)<<std::endl;
	(void)PrintInOrder(&T);


	return 0;
}
