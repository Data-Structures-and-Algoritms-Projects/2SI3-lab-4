#include "objPosBST.h"

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root = nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL
    deleteTree(root);
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.
    if (thisNode != nullptr)
    {
        deleteTree(thisNode->left);
        deleteTree(thisNode->right);
        delete thisNode;
    }
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    return (root == NULL);
}


bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes
    if(thisNode == NULL) // Leaf Node
        return false;
    else if(thisPos.getPF() < thisNode->data.getPF()) // the left half
        return isLeaf(thisPos, thisNode->left);
    else if(thisPos.getPF() > thisNode->data.getPF()) // the right half
        return isLeaf(thisPos, thisNode->right);
    else
        return (thisNode->left == NULL && thisNode->right == NULL); // found it! Check if it is a leaf node.

}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**

    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.

    // DO NOT use printObjPos() as it will mess up the game display.
    // Instead, use the following code to print the Prefix and Number
    if (thisNode != nullptr) {
        printTree(thisNode->left);
        cout << thisNode->data.getPF() << thisNode->data.getNum() << " ";
        printTree(thisNode->right);
    }
}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}


int objPosBST::getHeight(const TNode* thisNode) const
{
    // Tree Height Calculation Algorithm 

    // 1. If thisNode is null, height is zero.

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.

    // 3. Compare the two returned heights, and return the larger one.
    if (thisNode == nullptr)
        return 0;
    else
    {
        int leftHeight = getHeight(thisNode->left);
        int rightHeight = getHeight(thisNode->right);
        return max(leftHeight, rightHeight) + 1;
    }
}

void objPosBST::printCurrentLevel(const TNode* thisNode, const int level) const
{
    // Recursive Level-Order Tree-Printing Algorithm 
    
    // 1. First check if at leaf node.  If yes, do not print anything

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
    int height = getHeight(root);
    int width = pow(2,height);
    static int savedLevel = -1; // Static variable, only updated in the first call
    if (savedLevel == -1) {
        savedLevel = level; // Set only in the first call
    }

    if (thisNode == nullptr){
        cout << " ";
        for(int k = pow(2,level-1); k > 1; k--)
            for(int j = 0; j < (width/(pow(2,savedLevel)))*2; j++) 
                cout << " ";
        return;
    }
    if (level == 1){
        cout << thisNode->data.getPF();
    }
    else if (level > 1)
    {
        printCurrentLevel(thisNode->left, level - 1);
        for(int j = 1; j < (width/(pow(2,savedLevel)))*2; j++) 
            cout << " ";
        printCurrentLevel(thisNode->right, level - 1);        
    }
    if(level == savedLevel)
        savedLevel = -1;
}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm 

    // 1. Get the height of the tree
    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
    int height = getHeight(root);
    int width = pow(2,height);
    for (int i = 1; i <= height; i++) { 
        for(int j = 1; j < (width/(pow(2,i))); j++) 
            cout << " ";
        printCurrentLevel(root, i);
        cout << endl;
    }
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true

    if(thisNode == NULL) // Leaf Node
        return false;
    else if(thisPos.getPF() < thisNode->data.getPF()) // the left half
        return isInTree(thisPos, thisNode->left);
    else if(thisPos.getPF() > thisNode->data.getPF()) // the right half
        return isInTree(thisPos, thisNode->right);
    else
        return true; // found item
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)
    if(thisNode == NULL) // Empty Tree
        thisNode = new TNode(thisPos);
    else if(thisPos.getPF() < thisNode->data.getPF()) // Binary Search
        insert(thisPos, thisNode->left);
    else if(thisPos.getPF() > thisNode->data.getPF())
        insert(thisPos, thisNode->right);
    else 
        thisNode->data.setNum(thisNode->data.getNum() + thisPos.getNum()); // If FOUND
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode

    // Used as part of remove() algorithm

    // Check Lecture Notes for implementation
    if(thisNode == NULL) // Leaf Node
        return NULL;
    else if(thisNode->left == NULL) // Smallest Prefix
        return thisNode;
    else
        return findMin(thisNode->left);
}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
    if(thisNode == NULL) // Item not found. Do nothing.
    return;
    if(thisPos.getPF() < thisNode->data.getPF()) // Find the node in the tree
    remove(thisPos, thisNode->left);
    else if(thisPos.getPF() > thisNode->data.getPF())
    remove(thisPos, thisNode->right);
    else if(thisNode->left != NULL && thisNode->right != NULL){
    // Case 3 - Delete Node with 2 children (Method 1)
    thisNode->data = findMin(thisNode->right)->data;
    remove(thisNode->data, thisNode->right);
    }
    else{ // Takes care of Case 1 and 2 – HOW?
        TNode* oldNode = thisNode;
        thisNode = (thisNode->left != NULL)? thisNode->left : thisNode->right;
        delete oldNode;
    }
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
    if (thisNode == nullptr) {
        return false;
    }
    else {
        return findGreater(numThreshold, thisNode->left) || findGreater(numThreshold, thisNode->right) || thisNode->data.getNum() > numThreshold;
    }
}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
