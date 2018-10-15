

namespace SplayTree
{
	enum class ReturnInfo
	{
		eNodeIsAlreadyInserted,
		eMemoryAllocationProblem,
		eNodeDoesNotExist,
		eSuccess
	};

	struct Node
	{
		Node(const int val) :value(val),parent(nullptr),
			left(nullptr),right(nullptr) {}
		int value;
		Node* parent;
		Node* left;
		Node* right;
	};

	ReturnInfo find(Node ** root, const int valueToFind);

	ReturnInfo InsertNode(Node **T, const int value);

	ReturnInfo deleteNode(Node** T, const int value);
}
