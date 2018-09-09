/*
 * RBT.cpp
 *
 *  Created on: 05.06.2016 ã.
 *      Author: NikolayD
 */

#include <iostream>

struct Node
{
	int key;
	bool isRed;
	Node *parent;
	Node *left;
	Node *right;
	Node(int key)
	{
		this->key = key;
		this->isRed = true;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};

static Node* Insert(Node** T, Node* node);
static void solveConflicts(Node** Root, Node* node);
static void RightRotate(Node* root, bool changeColor);
static void LeftRotate(Node* root, bool changeColor);

void InsertNode(Node** root, int key)
{
	//create new node
	Node* newNode = new Node(key);
	//Insert it into the Red- Black tree
	Node* temp = Insert(root, newNode);

	if( nullptr == temp )
	{
		//Duplicate key
		delete newNode;
	}
	else
	{
		(*root) = temp;
		solveConflicts(root,newNode);
	}
}

static Node* Insert(Node** T, Node* node)
{
	if( nullptr == (*T) )
	{
		return node;
	}
	if(node->key > (*T)->key )
	{
		(*T)->right = Insert(&(*T)->right, node);
		(*T)->right->parent = (*T);
	}
	else if( node->key < (*T)-> key)
	{
		(*T)->left = Insert(&(*T)->left, node);
		(*T)->left->parent = (*T);
	}
	else
	{
		return nullptr;

	}
	return (*T);
}

Node *FindSibling(Node* node)
{
	if( node->parent->left == node )
	{
		if( node->parent->right != nullptr )
		{
			return node->parent->right;
		}
	}
	else
	{
		if( nullptr != node->parent->left )
		{
			return node->parent->left;
		}
	}
	return nullptr;
}

static void LeftRotate(Node* root, bool changeColor)
{
	Node* temp = root;
	root = root->right;
	Node* left = root->left;
	root->parent = temp->parent;
	if( nullptr != temp->parent )
	{
		if( temp == temp->parent->left )
		{
			root->parent->left = root;
		}
		else
		{
			root->parent->right = root;
		}
	}
	root->left = temp;
	temp->parent = root;
	temp->right = left;
	if( changeColor )
	{
		root->isRed = false;
		temp->isRed = true;
	}
}

static void RightRotate(Node* root, bool changeColor)
{
	Node *parent = root->parent;
	root->parent = parent->parent;
	if( nullptr != parent->parent )
	{
		if( parent-> parent-> left == parent )
		{
			parent-> parent-> left = root;
		}
		else
		{
			parent->parent->right = root;
		}
	}
	Node* Right = root->right;
	root->right = parent;
	parent->parent = root;
	parent->left = Right;
	if( nullptr != Right )
	{
		Right->parent = parent;
	}
	if(changeColor)
	{
		root->isRed = false;
		parent->isRed = true;
	}
}

static void solveConflicts(Node** Root, Node* node)
{
	if(nullptr == node)
	{
		return;
	}
	if((*Root) == node)
	{
		(*Root)->isRed = false;
	}
	else
	{
		if( !node->parent->isRed )
		{
			//everything is okay, no additional operations needed
		}
		else
		{
			Node* temp = FindSibling(node->parent);
			if( temp && temp->isRed )
			{
				node->parent->isRed = false;
				temp->isRed = false;
				if( (*Root) != node->parent->parent )
				{
					node->parent->parent->isRed = true;
				}
				solveConflicts(Root, node->parent->parent);
			}
			else
			{
				//Left- Left situation, consequently one Right rotation + recoloring
				if( ( node == node->parent->left )
						&& ( node->parent == node->parent->parent->left ) )
				{
					RightRotate(node->parent, true);
				}
				//Right- Left situation, consequently Left followed by Right rotation and
				//recoloring at the end
				else if( ( node == node->parent->right )
						&& ( node->parent == node->parent->parent->left) )
				{
					LeftRotate(node->parent,false);
					RightRotate(node, true);
				}
				//Right- Right situation, consequently one Left rotation + recoloring
				else if( ( node == node->parent->right )
						&& ( node->parent == node->parent->parent->right ) )
				{
					LeftRotate(node->parent->parent,true);
				}
				//Left- Right situation, consequently Right followed by Left rotation and
				//recoloring at the end
				else if( ( node == node->parent->left )
						&& ( node->parent == node->parent->parent->right ) )
				{
					RightRotate(node, false);
					LeftRotate(node->parent, true);
				}
				solveConflicts(Root, node->parent->parent);
			}
		}
	}
}

void printDataNColor(Node* root)
{
	if( nullptr == root)
	{
		return;
	}
	std::string colour = root->isRed?"red":"black";
	std::cout<<root->key<<" is "<<colour<<"\n";
	printDataNColor(root->left);
	printDataNColor(root->right);

}

int main()
{
	Node* root = nullptr;
	InsertNode(&root, 10);

	InsertNode(&root, 20);

	InsertNode(&root, 1);

	InsertNode(&root, 15);

	InsertNode(&root, 17);

	InsertNode(&root, 40);

	InsertNode(&root, 38);

	std::string colour = root->isRed?"red":"black";
	std::cout<<"this should be 10(black): "<<root->key<<" "<<colour<<std::endl;
	colour = root->left->isRed?"red":"black";
	std::cout<<"this should be 1(black): "<<root->left->key<<" "<<colour<<std::endl;
	if(root->left->left == nullptr && root->left->right == nullptr && root->left->parent == root)
	{
		std::cout<<"so far so good"<<std::endl;
	}
	colour = root->right->isRed?"red":"black";
	std::cout<<"this should be 17(red): "<<root->right->key<<" "<<colour<<std::endl;
	colour = root->right->left->isRed?"red":"black";
	std::cout<<"this should be 15(black): "<<root->right->left->key<<" "<<colour<<std::endl;
	if(root->right->left->left == nullptr && nullptr == root->right->left->right &&
			root->right->left->parent == root->right)
	{
		std::cout<<"so far so good 2"<<std::endl;
	}
	colour = root->right->right->isRed?"red":"black";
	std::cout<<"this should be 38(black): "<<root->right->right->key<<" "<<colour<<std::endl;
	colour = root->right->right->left->isRed?"red":"black";
	std::cout<<"this should be 20(red): "<<root->right->right->left->key<<" "<<colour<<std::endl;
	if(nullptr == root->right->right->left->left && nullptr == root->right->right->left->right &&
			root->right->right == root->right->right->left->parent)
	{
		std::cout<<"So far so good 3"<<std::endl;
	}
	colour = root->right->right->right->isRed?"red":"black";
	std::cout<<"this should be 40(red): "<<root->right->right->right->key<<" "<<colour<<std::endl;
	if(nullptr == root->right->right->right->left && nullptr == root->right->right->right->left &&
			root->right->right == root->right->right->right->parent)
	{
		std::cout<<"So far so good 4"<<std::endl;
	}

//	printDataNColor(root);
}

