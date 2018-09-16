# Algorithms
Algorithm projects mainly used for practice


# Explanation

 ## Binary Search Tree
  Binary search tree is a tree structure with at most two children. Each left child is 
  smaller than it's parent and each right child is greater than it's parent.
  ### Complexity
  At average the time complexity for insert, remove and search according to big O notation is 
  O(log<i>n</i>). However, the worst case is O(<i>n</i>). Еven though BSTs are widely used because
  of their simple implementation.	

  ### Operations
  <b>Insertion</b>- insertion operation is done fairly simple- recursively going to the position where 
  we have to add the new value allocate space for new node with the given value and attach it 
  to the tree as left or right child of already existing leaf node.
  <b>Searching</b>- recursively going through the nodes starting from the left children to the right ones,
  the base case of the recursion is when we found leaf node, consequently node without children.</br>
  <b>Deletion</b>- deletion is a bit trickier than the insertion but compared to the other tree structures
  in this repo it is also fairy simple. The idea is when we find the node, which we want to delete
  we have to determine if it is a leaf or not. If it is a leaf, simply deleting the reference to it
  and release the resource acquired by it. If it is not a leaf we have to find it's successor, which could be
  the greatest value in it's left sub tree or the least value of it's right sub tree, then we replace the
  values and delete the leaf node, where the new value was just placed.
  
  
  ## Red-Black Tree
   Red- Black tree is also kind of a Binary Search tree the values are also arranged as smaller values
   are in the left sub tree and greater values are in the right sub tree what RBT adds as extra are
   these two colors red and black which provides a way of self- balancing while the tree perform insertion
   or deletion. There are some rules which must to be followed in order to have a proper Red- Black tree. </br>
   <b>1. The all "black" paths should be equal</b>- this means the number of black nodes from the root to each
   leaf has to be the same.</br>
   <b>2. There are no red- red relationships between parent and child</b>- we cannot have red parent with red child</br>
   <b>3. The root is always black</b> </br>
   <b>4. Every node has a color</b>- every node has to be either red or black.</br>
   
   ### Complexity
   Again the average complexity according to big O notation is O(log<i>n</i>), but despite BST RBT with it's 
   self-balancing property has the time complexity in it's worst case as in it's average O(log<i>n</i>).</br>
   
   ### Operations
   <b>Searching</b>- searching is implemented the same way as BST</br>
   <b>Insertion</b>- Insertion is way more complex than BST. It follows the logic: first we found the
   appropriate position- same way as in BST then we check the parent of the newly added node if it is
   black- we are done, remember we always add red nodes. If the parent is red though we have to perform
   some rotations. Rotations are chosen according to the position of the newly added node and it's parent.
   They can be LeftLeft- the newly added node is left child and it's parent is again left child of it's 
   parent, LeftRight- the newly added node is left child but the parent is right child of it's parent and
   vice versa. Depending of which of this situations we have we perform two types of rotations- left and right
   and sometimes combinations between them- left followed by right and vice versa.
   
   ![treerotation](https://user-images.githubusercontent.com/12647334/45601637-fe1b8d00-ba18-11e8-8540-f02fe2f27f6b.JPG)   
   credit: Balazs Holczer- splay trees</br>
   <b>Deletion</b>- COMING SOON!
   
 ## 2-3-4 Trees(2-4 Trees, B-Trees)
   2-3-4 Trees are data structure, which is also a self- balancing search tree but it is no longer a binary one.
   It contains from 1 to 3 values and from 2 to 4 children. Each children contains values between the values in
   the parent node. What I mean? Consider the following picture.
   ![2tree](https://user-images.githubusercontent.com/12647334/45601718-0a541a00-ba1a-11e8-8349-3144a7ce4da4.png)
   credit: Wikipedia
   
   Each node has 0 or 2, 3 or 4 children. All leaves are at the same depth (the bottom level).
   
   ### Complexity
   The time complexity for each operation is O(log<i>n</i>). It is the same as RBT but it is preferred for managing
   main memory or databases because it keeps more than one value for a node.
   
   ### Operations
   <b> Searching </b>- Searching is like BST but with more validation because we are not just greater or less than
   one value. Also recursive implementation is very intuitive.
   <b> Insertion </b>- Insertion is more complex than the other trees so far. We will introduce the term splitting,
   which is moving the middle value of a node with 3 values to it's parent and splitting the node to two nodes with
   one element each. This splitting is the way how we deal with adding an element to already full (with 4 children)
   node. The implementation here in this split each 3 node, found in it's path below to the node, where the
   value has to be inserted in this way we are sure that when we found the node we will be able to split it if
   necessary without going back in the recursion to rearrange the tree.</br>
   <b> Deletion </b>- Deletion is again a tough operation. Deleting a value from a node presupposes new arrangement
   of the nodes above in order to keep the perfect balance in the tree. The implementation removes the value and then
   check what is it's status. If it is a leaf and there are more than one value in this node we can simply remove the
   value if there are less values or it is not a leaf it becomes much more complex. We perform 4 different operations, 
   which later on are propageted to the root. They are merging with left or right sibling or borrowing a value from
   left or right sibling.
   
   
   
   
Used sources and useful links:</br>
 DTU course "Algorithm and Data Structures 2" lectures</br>
 http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Trees/2,4-delete.html </br>
 https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree </br>
 https://www.youtube.com/watch?v=9tioidySJmM </br>
 https://www.cs.usfca.edu/~galles/visualization/BTree.html </br>
 https://www.youtube.com/watch?v=aZjYr87r1b8 </br>
 Tushar Roy - Coding Made Simple series on Red Black Trees </br>
 http://www.programirane.org/ </br>
 https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844 </br>
 
 Remark: I don't claim any ownership of this implementation of well-known algorithms I've been using sample codes
 pseudo code and explanations gathered from many places in order to implemented it. Feel free to use them!
 
  
