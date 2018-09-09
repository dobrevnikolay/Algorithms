/*
 * BinarySearchTree.hpp
 *
 *  Created on: 05.06.2016 ã.
 *      Author: NikolayD
 */

#ifndef BINARYSEARCHTREE_HPP_
#define BINARYSEARCHTREE_HPP_

enum class ReturnInfo
{
	eNodeIsAlreadyInserted,
	eMemoryAllocationProblem,
	eNodeDoesNotExist,
	eSuccess
};

struct Node
{
	int ID;
	int Data;
	Node * left;
	Node * right;

	Node(int id, int data)
	{
		this->ID = id;
		this->Data = data;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node& operator = (const Node& other)
	{
		this->ID = other.ID;
		this->Data = other.Data;
		this->left = other.left;
		this->right = other.right;
		return *this;
	}
};

//Function that find node by given ID, it return eNodeDoesNotExist when there is no
//such node and eSuccess when there is
ReturnInfo FindNodeByID(Node **T, const int ID, Node *getNode);

//Insert node in given tree by given ID and Data
//return eMemoryAllocation if there is problem with allocating
//return eSuccess when everything is fine
//return eNodeIsAlreadyInserted if there is node with the same ID in
//the given tree
ReturnInfo InsertNode(Node ** T,const int ID,const int Data);

//Delete Node by given ID, possible cases are described below
//return eNodeDoesNotExist if the tree pointer is invalid
//return eSuccess if everything is fine
ReturnInfo DeleteNodeByID(Node ** T, const int ID);

//Recursive function
ReturnInfo PrintInOrder(Node **T);

#endif /* BINARYSEARCHTREE_HPP_ */
