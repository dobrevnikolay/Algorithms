#include <iostream>
#include "SplayTree.h"

int main()
{
	SplayTree::Node * T= nullptr;
	SplayTree::InsertNode(&T, 10);
	SplayTree::InsertNode(&T, 20);
	SplayTree::InsertNode(&T, 15);
	SplayTree::InsertNode(&T, 25);
	SplayTree::InsertNode(&T, 5);
	SplayTree::find(&T, 10);
	SplayTree::InsertNode(&T, 40);
	SplayTree::InsertNode(&T, 17);
	SplayTree::deleteNode(&T, 5);

}