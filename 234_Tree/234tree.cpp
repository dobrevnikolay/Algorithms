#include <iostream>
#include <vector>


//attempt
/*
        if (node->isLeaf)
        {
            //Esiest one
            if (node->numOfValues > 1)
            {
                node->values[i] = constants::InvalidValue;
                --node->numOfValues;
            }
            //if it is the only value
        }
        else
        {
            //if it is single value and one of its children has at least two values
            if (1 == node->numOfValues &&
                (node->children[0]->numOfValues > 1 || node->children[1]->numOfValues >1))
            {
                applyInternalRemoving(*node);
            }
            //or is the value between and one of its children has at least two values
            else if ((1 == i && constants::MaxNumberOfValues == node->numOfValues) &&
                (node->children[1]->numOfValues > 1 || node->children[2]->numOfValues >1))
            {
                applyInternalRemoving(*node, i);
            }
        }
 */


//We assume -1 as input node value is used as invalid, consequently
//there is no value assigned

const enum constants
{
    MaxNumberOfValues = 3,
    MaxNumberOfChildren = 4,
    InvalidValue = -1
};

struct Node
{
    Node(int val1, int val2 = constants::InvalidValue, int val3 = constants::InvalidValue) :
        values{ val1,val2,val3 },
        parent(nullptr), children()
    {
        if (constants::InvalidValue != values[2])
        {
            numOfValues = constants::MaxNumberOfValues;
        }
        else if (constants::InvalidValue != values[1])
        {
            numOfValues = 2;
        }
        else
        {
            numOfValues = 1;
        }
        isLeaf = true;
    }

    int values[constants::MaxNumberOfValues];
    int numOfValues;
    bool isLeaf;
    Node* parent;
    Node* children[constants::MaxNumberOfChildren];
};

Node* splitTo(Node * node, const int value);

/*private*/
int emplaceValue(Node* currentNode, const int value)
{
    if (!currentNode->numOfValues)
    {
        currentNode->values[0] = value;
        return 1;
    }
    if (value < currentNode->values[0])
    {
        currentNode->values[2] = currentNode->values[1];
        currentNode->values[1] = currentNode->values[0];
        currentNode->values[0] = value;
        return 1;
    }
    else if (constants::InvalidValue == currentNode->values[1])
    {
        currentNode->values[1] = value;
        return 2;
    }
    else if (value > currentNode->values[0] && value < currentNode->values[2])
    {
        currentNode->values[2] = value;
        return 2;
    }
    else if(value > currentNode->values[2] && value != currentNode->values[1])
    {
        currentNode->values[2] = value;
        return constants::MaxNumberOfValues;
    }
    else
    {
        //indicates duplicates
        return constants::InvalidValue;
    }
}

/*private*/
Node* insertNotFull(Node* node, const int value)
{
    if (!node->isLeaf)
    {
        if (value < node->values[0] && node->children[0])
        {
            return splitTo(node->children[0], value);
        }
        else if ((value > node->values[0] && (value < node->values[1] || constants::InvalidValue == node->values[1])) && node->children[1])
        {
            return splitTo(node->children[1], value);
        }
        else if ((value > node->values[1] && (value < node->values[2] || constants::InvalidValue == node->values[2])) && node->children[2])
        {
            return splitTo(node->children[2], value);
        }
        else if (value > node->values[2] && node->children[3])
        {
            return splitTo(node->children[3], value);
        }
        else
        {
            //Should never come here
            return nullptr;
        }
    }
    else
    {
        //its leaf, consequently its the right position to insert value in
        return node;
    }
}

/*private*/
bool checkIsLeaf(const Node& node)
{
    for (int i = 0; i < constants::MaxNumberOfChildren; ++i)
    {
        if (node.children[i])
        {
            return false;
        }
    }
    return true;
}

/*private*/
Node* splitTo(Node * node, const int value)
{
    auto nodeToInsertIn = node;
    if (node->numOfValues > 2)
    {
        //Split the node as moving the value in the middle
        //upwards and later on create one more node, where
        //we emplace the right side of the node
        //consider this
        int place{ emplaceValue(node->parent,node->values[1])};
        auto otherChild = new Node(node->values[2]);
        otherChild->children[0] = node->children[2];
        otherChild->children[1] = node->children[3];
        otherChild->numOfValues = 1;
        otherChild->parent = node->parent;
        otherChild->isLeaf = checkIsLeaf(*otherChild);
        node->children[2] = nullptr;
        node->children[3] = nullptr;
        node->numOfValues = 1;
        node->values[1] = constants::InvalidValue;
        node->values[2] = constants::InvalidValue;
        node->parent->children[place] = otherChild;
        ++node->parent->numOfValues;
        nodeToInsertIn = node->parent;
    }
    return insertNotFull(nodeToInsertIn, value);
    
}

void insert(Node** root, const int value)
{
    Node* nodeToInsertIn = nullptr;

    if ((*root)->numOfValues > 2)
    {
        auto newRoot = new Node(((*root)->values[1]));
        newRoot->numOfValues = 0;
        newRoot->isLeaf = false;
        newRoot->children[0] = (*root);
        (*root)->parent = newRoot;
        (*root) = newRoot;
        nodeToInsertIn = splitTo((*root)->children[0], value);
    }
    else
    {
        nodeToInsertIn = splitTo(*root, value);
    }
    if (nodeToInsertIn)
    {
        if (constants::InvalidValue != emplaceValue(nodeToInsertIn, value))
        {
            ++nodeToInsertIn->numOfValues;
        }        
    }
}

void print(Node* root)
{
    if (!root)
    {
        return;
    }
    std::cout << "Values ";
    for (int i{}; i < root->numOfValues; ++i)
    {
        std::cout << root->values[i];
        std::cout << " ";
    }
    std::cout << std::endl;
    print(root->children[0]);
    print(root->children[1]);
    print(root->children[2]);
    print(root->children[3]);
}

/*private*/
void addIfInInterval(Node* node,const int x, const int y, std::vector<int>& buffer)
{
    if (!node)
    {
        return;
    }
    int i{};

    for (int i{}; i < node->numOfValues; ++i)
    {
        if (node->values[i] > x && node->values[i] < y)
        {
            buffer.push_back(node->values[i]);
        }
    }
    addIfInInterval(node->children[0], x, y, buffer);
    addIfInInterval(node->children[1], x, y, buffer);
    addIfInInterval(node->children[2], x, y, buffer);
    addIfInInterval(node->children[3], x, y, buffer);
}

std::vector<int> contains(Node* root, const int x, const int y)
{
    std::vector<int> between;
    addIfInInterval(root, x, y, between);
    return between;
}

void add(Node* root, const int number)
{
    if (!root)
    {
        return;
    }
    for (auto& el : root->values)
    {
        el += number;
    }
    add(root->children[0], number);
    add(root->children[1], number);
    add(root->children[2], number);
    add(root->children[3], number);
}

//the absence of index meanst that we are taking the first value into account
void applyInternalRemoving(Node& node, const int index = -1)
{
    int indexes[2]{};
    int* theValueToChange = nullptr;
    if (index != -1)
    {
        indexes[0] = 1;
        indexes[1] = 2;
        theValueToChange = &node.values[index];
    }
    else
    {
        indexes[0] = 0;
        indexes[1] = 1;
        theValueToChange = node.values;
    }

    int indexToUse = 0;

    if (node.children[indexes[0]]->numOfValues > 1)
    {
        
    }
    else
    {
        indexToUse = 1;
    }
    //assign the value we want to delete with the greatest value in the left child
    *theValueToChange = node.children[indexes[indexToUse]]->values[node.children[indexes[indexToUse]]->numOfValues - 1];
    node.children[indexes[indexToUse]]->values[node.children[indexes[indexToUse]]->numOfValues - 1] = constants::InvalidValue;
    --node.children[indexes[indexToUse]]->numOfValues;
}

void fixUnderflow(Node**root, Node* node, Node* subtree)
{
    if (!node->parent)
    {
        *root = subtree;
        return;
    }

    //1. Find the position of the Node in its parent
    int indexOfNodeInParent{};
    for (; indexOfNodeInParent < node->parent->numOfValues + 1; ++indexOfNodeInParent)
    {
        if (node == node->parent->children[indexOfNodeInParent])
        {
            break;
        }
    }

    //2. Try to borrow a value from the right sibling
    auto rightSibling = 2 >= indexOfNodeInParent ? node->parent->children[indexOfNodeInParent + 1] : nullptr;
    auto leftSibling =  0 < indexOfNodeInParent ? node->parent->children[indexOfNodeInParent - 1] : nullptr;
        
    if ( rightSibling &&
        1 < rightSibling->numOfValues)
    {
        node->children[0] = subtree;
        if (subtree)
        {
            subtree->parent = node;
        }
        node->values[0] = node->parent->values[indexOfNodeInParent];
        node->numOfValues = 1;
        node->children[1] = rightSibling->children[0];
        node->parent->values[indexOfNodeInParent] = rightSibling->values[0];

        node->isLeaf = checkIsLeaf(*node);

        for (int i{}; i < constants::MaxNumberOfValues - 1; ++i)
        {
            rightSibling->values[i] = rightSibling->values[i + 1];
            rightSibling->children[i] = rightSibling->children[i + 1];
        }
        rightSibling->values[constants::MaxNumberOfValues - 1] = constants::InvalidValue;
        rightSibling->children[constants::MaxNumberOfChildren - 1] = nullptr;
        --rightSibling->numOfValues;

        return;
    }

    //3. Try to borrow from the left sibling

    else if (leftSibling && 1 < leftSibling->numOfValues)
    {
        int lastElement = leftSibling->values[leftSibling->numOfValues - 1];

        node->children[0] = leftSibling->children[leftSibling->numOfValues];
        if (leftSibling->children[leftSibling->numOfValues])
        {
            leftSibling->children[leftSibling->numOfValues]->parent = node;
        }
        node->values[0] = node->parent->values[indexOfNodeInParent - 1];
        ++node->numOfValues;
        node->children[1] = subtree;
        if (subtree)
        {
            subtree->parent = node;
        }
        node->parent->values[indexOfNodeInParent - 1] = lastElement;

        leftSibling->children[leftSibling->numOfValues] = nullptr;
        leftSibling->values[leftSibling->numOfValues - 1] = constants::InvalidValue;
        --leftSibling->numOfValues;

        return;
    }
    //4.Merging with right sibling
    else if (rightSibling)
    {
        //delete right sibling
        node->children[0] = subtree;
        if (subtree)
        {
            subtree->parent = node;
        }
        node->children[1] = rightSibling->children[0];
        
        if (rightSibling->children[0])
        {
            rightSibling->children[0]->parent = node;
        }
        node->children[2] = rightSibling->children[1];
        if (rightSibling->children[1])
        {
            rightSibling->children[1]->parent = node;
        }


        node->values[0] = node->parent->values[indexOfNodeInParent];
        node->values[1] = rightSibling->values[0];
        node->numOfValues = 2;

        //rearrange parent
        for (int i{ indexOfNodeInParent }; i < constants::MaxNumberOfValues - 1; ++i)
        {
            node->parent->values[i] = node->parent->values[i + 1];
            node->parent->children[i] = node->parent->children[i + 1];
        }
        node->parent->values[constants::MaxNumberOfValues - 1] = constants::InvalidValue;
        node->parent->children[constants::MaxNumberOfChildren - 1] = nullptr;
        --node->parent->numOfValues;

        delete rightSibling;

        if (0 == node->parent->numOfValues)
        {
            fixUnderflow(root, node->parent, node);
        }
        return;
    }
    //5. Merging with left sibling
    else
    {
        leftSibling->values[1] = node->parent->values[0];
        ++leftSibling->numOfValues;
        leftSibling->children[2] = subtree;
        if (subtree)
        {
            subtree->parent = leftSibling;
        }
        for (int i{}; i < node->parent->numOfValues; ++i)
        {
            node->parent->values[i] = node->parent->values[i + 1];
        }
        for (int i{ 1 }; i < node->parent->numOfValues + 1; ++i)
        {
            node->parent->children[i] = node->parent->children[i + 1];
        }
        --node->parent->numOfValues;
        node->parent->children[constants::MaxNumberOfChildren - 1] = nullptr;
        node->parent->values[constants::MaxNumberOfValues - 1] = constants::InvalidValue;
        
        delete node;

        if (0 == node->parent->numOfValues)
        {
            fixUnderflow(root, leftSibling->parent, leftSibling);
        }
        return;
    }


}

void removePrivate(Node**root, Node* node, const int num)
{
    if (!node)
    {
        return;
    }
    int i{};
    for (; i < node->numOfValues; ++i)
    {
        if (num == node->values[i])
        {
            break;
        }
    }
    //we found the value we want to delete
    if (i < node->numOfValues)
    {
        Node* noteToDelete = nullptr;
        Node* currNode = node;
        if (currNode->isLeaf)
        {
            for (;i < constants::MaxNumberOfValues - 1; ++i)
            {
                currNode->values[i] = currNode->values[i + 1];
            }
            currNode->values[i] = constants::InvalidValue;
            --currNode->numOfValues;

            //consider deleting the allocated memory
            if (0 == currNode->numOfValues)
            {
                noteToDelete = currNode;
            }
            
        }
        else
        {
            //find the successor
            Node * successor = currNode->children[i + 1];
            //find the smallest in the right side
            while (successor->children[0])
            {
                successor = successor->children[0];
            }

            currNode->values[i] = successor->values[0];
            for (int i{ 0 }; i < successor->numOfValues; ++i)
            {
                successor[i] = successor[i+1];
            }
            --successor->numOfValues;
            for (int i{ constants::MaxNumberOfValues - 1 }; i > successor->numOfValues; --i)
            {
                successor[i] = -1;
            }
            currNode = successor;            
        }

        if (0 == currNode->numOfValues)
        {
            fixUnderflow(root, currNode, nullptr);
        }
    }
    else
    {
        if (num < node->values[0])
        {
            removePrivate(root, node->children[0], num);
        }
        else if (num > node->values[0] && (constants::InvalidValue == node->values[1] || num < node->values[1]))
        {
            removePrivate(root,node->children[1], num);
        }
        else if (num > node->values[1] && (constants::InvalidValue == node->values[2] || num < node->values[2]))
        {
            removePrivate(root, node->children[2], num);
        }
        else if (constants::InvalidValue != node->values[2])
        {
            removePrivate(root, node->children[3], num);
        }
    }
}

void remove(Node** root, const int num)
{
    removePrivate(root, *root, num);
}

int main()
{
    auto root = new Node(10);
    insert(&root, 14);
    insert(&root, 3);
    insert(&root, 20);
    insert(&root, 24);
    insert(&root, 17);
    insert(&root, 17);

    //auto results{ contains(root,10, 20) };

    //std::cout << "Contains results: " << std::endl;
    //for (int i{}; i < results.size(); ++i)
    //{
    //    std::cout << " " << results[i];
    //}
    //std::cout << std::endl;

    print(root);

    remove(&root, 24);

    //add(root,5);r

    print(root);


    int a;
    std::cin >> a;

}
