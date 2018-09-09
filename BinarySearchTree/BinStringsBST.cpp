#include <iostream>
#include <vector>

struct Node
{
    bool isEnd;
    Node * left;
    Node * right;
};

void insert(Node* head, std::string binStr)
{
    auto currentNode = head;
    for (int i = 0; i<binStr.size(); ++i)
    {
        if ('0' == binStr[i])
        {
            if (!currentNode->left)
            {
                currentNode->left = new Node();
            }
            currentNode = currentNode->left;
        }
        else
        {
            if (!currentNode->right)
            {
                currentNode->right = new Node();
            }
            currentNode = currentNode->right;
        }
        if (i == binStr.size() - 1)
        {
            currentNode->isEnd = true;
        }
    }    
}

void loopThroughInOrder(Node* node, std::vector<std::string>& strings, std::string& binString)
{
    if (node->isEnd)
    {
        strings.push_back(binString);
    }
    if (node->left)
    {
        binString += '0';
        loopThroughInOrder(node->left, strings, binString);
        binString.pop_back();
    }
    if(node->right)
    {
        binString += '1';
        loopThroughInOrder(node->right, strings, binString);
        binString.pop_back();
    }
}

std::vector<std::string> collect(Node* head)
{
    std::vector<std::string> strings{};
    std::string binStr{};
    loopThroughInOrder(head, strings, binStr);
    return strings;
}

int main()
{
    auto head = new Node();
    insert(head, "011");
    insert(head, "0");
    insert(head, "001");
    insert(head, "1011");
    insert(head, "10");
    insert(head, "100");

    auto result = collect(head);
    for (auto str : result)
    {
        std::cout << str.c_str() << std::endl;
    }
}