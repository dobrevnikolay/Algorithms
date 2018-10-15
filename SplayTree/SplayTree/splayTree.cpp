#include <iostream>
#include "SplayTree.h"

namespace SplayTree
{



	void rightRotate(Node* node);
	void leftRotate(Node* node);
	ReturnInfo InsertNode(Node** T, Node* node, const int value);
	ReturnInfo find(Node **root, Node* node, const int valueToFind);

    void splay(Node** Root, Node* node)
    {
		if (*Root == node)
		{
			return;
		}
        while (node->parent)
        {
            auto parent = node->parent;
            auto grandParent = node->parent->parent;
            if (node == parent->left)
            {
                if (grandParent)
                {
                    if (parent == grandParent->left)
                    {
                        //zig-zig right-right
                        rightRotate(parent);
                        rightRotate(node);
                    }
                    else
                    {
                        //zig-zag right-left
                        rightRotate(node);
                        leftRotate(node);

                    }
                }
                else
                {
                    //right rotation
					rightRotate(node);
                }
            }
            else
            {
                if (grandParent)
                {
                    if (parent == grandParent->left)
                    {
                         //zig-zag left-right
                        leftRotate(node);
                        rightRotate(node);
                    }
                    else
                    {
                         //zig-zig left-left
                        leftRotate(parent);
                        leftRotate(node);
                    }
                }
                else
                {
                    //left ratation
					leftRotate(node);
                }
            }			
        }
		*Root = node;
    }
	
	ReturnInfo find(Node ** root, const int valueToFind)
	{
		return find(root, *root, valueToFind);
	}
	
    ReturnInfo find(Node **root, Node* node, const int valueToFind)
    {
        if (nullptr == node)
        {
            return ReturnInfo::eNodeDoesNotExist;
        }
        else
        {
            if (valueToFind == node->value)
            {
				splay(root, node);
                
                return ReturnInfo::eSuccess;
            }
            else if (valueToFind > node->value)
            {
                find(root, node->right, valueToFind);
            }
            else if (valueToFind < node->value)
            {
                find(root, node->left, valueToFind);
            }
            else
            {
                //not reachable
            }
        }
    }

	ReturnInfo InsertNode(Node **T, const int value)
	{
		return InsertNode(T, *T, value);
	}

    ReturnInfo InsertNode(Node** T, Node* node, const int value)
    {
        if (nullptr == node)
        {
            Node * newOne = new Node(value);
            if (nullptr == newOne)
            {
                return ReturnInfo::eMemoryAllocationProblem;
            }
            newOne->parent = nullptr;
            *T = newOne;
            return ReturnInfo::eSuccess;
        }
        if (value > node->value)
        {
            if (node->right)
            {
                InsertNode(T,node->right, value);
            }
            else
            {
                Node * newOne = new Node(value);
                node->right = newOne;
                newOne->parent = node;
				splay(T, newOne);
                //Splay this node upwards
                return ReturnInfo::eSuccess;
            }
        }
        else if (value < node->value)
        {
            if (node->left)
            {
                InsertNode(T,node->left, value);
            }
            else
            {
                Node * newOne = new Node(value);
                node->left = newOne;
                newOne->parent = node;
                //Splay this node upwards
				splay(T, newOne);
                return ReturnInfo::eSuccess;
            }
        }
        else
        {
            return ReturnInfo::eNodeIsAlreadyInserted;
        }
    }

	void rightRotate(Node* node)
	{
		Node *parent;
		if (node->parent)
		{
			parent = node->parent;
			node->parent = parent->parent;
			if (nullptr != parent->parent)
			{
				if (parent->parent->left == parent)
				{
					parent->parent->left = node;
				}
				else
				{
					parent->parent->right = node;
				}
			}

			parent->left = node->right;
			if (parent->left)
			{
				parent->left->parent = parent;
			}
			node->right = parent;
			parent->parent = node;
		}
	}

	void leftRotate(Node* node)
	{
		Node * parent;
		if (node->parent)
		{
			parent = node->parent;
			node->parent = parent->parent;
			if (parent->parent)
			{
				if (parent->parent->left == parent)
				{
					parent->parent->left = node;
				}
				else
				{
					parent->parent->right = node;
				}
			}
			
			parent->right = node->left;
			if (parent->right)
			{
				parent->right->parent = parent;
			}
			node->left = parent;
			parent->parent = node;

		}

	}

	//To be checked for correctness
    ReturnInfo deleteNode(Node** T, const int value)
    {
		auto retVal = find(T, value);
		if (!(ReturnInfo::eSuccess == retVal))
		{
			return retVal;
		}
		auto left = (*T)->left;
		auto right = (*T)->right;

		auto toBeDeleted = *T;

		delete toBeDeleted;
		if (left)
		{
			if (left->right)
			{
				auto successor = left->right;
				while (nullptr != successor->right)
				{
					successor = successor->right;
				}
				left->parent = nullptr;
				splay(&left, successor);
			}

			left->right = right;
			right->parent = left;
			*T = left;
		}
		else
		{
			*T = right;
			right->parent = nullptr;
		}
		return retVal;
			   
    }

}


