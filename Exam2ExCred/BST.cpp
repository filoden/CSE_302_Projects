#include <iostream>
#include <fstream>
#include "BST.h"

#ifndef QUEUETYPE_H
#define QUEUETYPE_H
#include "QueType.h"
#endif

struct TreeNode
{
  int info; 
  TreeNode* left; 
  TreeNode* right;
};


bool TreeType::IsFull() const
// Returns true if the free store has no room for another node
//  and false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty and false otherwise.
{
  return root == NULL;
}

int CountNodes(TreeNode* tree);

int TreeType::GetLength() const {
    return CountNodes(root);
}
int CountNodes(TreeNode* tree) {
    if (tree == NULL)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode* tree, 
     int& item, bool& found);

int TreeType::GetItem(int item, bool &found) const
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}
void Retrieve(TreeNode* tree, 
     int& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise, found is false and item is unchanged.

{
 if (tree == NULL)
   found = false;                        // item is not found.
 else if (item < tree->info)
   Retrieve(tree->left, item, found);    // Search left subtree.
 else if (item > tree->info)
   Retrieve(tree->right, item, found);   // Search right subtree.
 else
 {
   item = tree->info;                    // item is found.
   found = true;
 }
}

void Insert(TreeNode*& tree, int item);

void TreeType::PutItem(int item)
// Calls the recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

void Insert(TreeNode*& tree, int item)
// Inserts item into tree.
// Post: item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);            // Insert in left subtree.
  else
    Insert(tree->right, item);           // Insert in right subtree.
}

void DeleteNode(TreeNode*& tree);

void Delete(TreeNode*& tree, int item);

void TreeType::DeleteItem(int item)
// Calls the recursive function Delete to delete item from tree.
{
  Delete(root, item);
}
void Delete(TreeNode*& tree, int item)
// Deletes item from tree.
// Post: item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);            // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);           // Look in right subtree.
  else
    DeleteNode(tree);                    // Node found; call DeleteNode.
}

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree. If tree is a leaf node or has only one
//       non-NULL child pointer, the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
  int data;
  TreeNode* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}

void GetPredecessor(TreeNode* tree, int& data)
// Sets data to the info member of the rightmost node in tree.
{
 while (tree->right != NULL)
   tree = tree->right;
 data = tree->info;
}

void PrintTree(TreeNode* tree, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
  if (tree != NULL)
  {
    PrintTree(tree->left, outFile);  // Print left subtree.
    outFile << tree->info;
    PrintTree(tree->right, outFile); // Print right subtree.
  }
}

void TreeType::Print(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root, outFile);
}

TreeType::TreeType()
{
  root = NULL;
}

void Destroy(TreeNode*& tree); TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}

void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left); Destroy(tree->right); delete tree;
  }
}

void CopyTree(TreeNode*& copy,
       const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;

  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;

    CopyTree(copy->left, originalTree->left); 
    CopyTree(copy->right, originalTree->right);
  }
}

TreeType::TreeType(const TreeType& originalTree)
// Calls the recursive function CopyTree to copy originalTree
//  into root.
{
  CopyTree(root, originalTree.root);
}

void TreeType::operator=(const TreeType& originalTree)
// Calls the recursive function CopyTree to copy originalTree
//  into root.
{
  {
    if (&originalTree == this)
      return; // Ignore assigning self to self.
    Destroy(root); // Deallocate existing tree nodes.
    CopyTree(root, originalTree.root);
  }
}

void TreeType::ResetTree(OrderType order)
// Calls a function to create a queue of the tree elements in
// the desired order.
{
  switch (order)
  {
    case PRE_ORDER : PreOrder(root, preQue);
                     break;
    case IN_ORDER  : InOrder(root, inQue);
                     break;
    case POST_ORDER: PostOrder(root, postQue);
                     break;
  }
}

void PreOrder(TreeNode* tree, QueType<int>& preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue); PreOrder(tree->right, preQue);
  }
}
void InOrder(TreeNode* tree, QueType<int>& inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}

void PostOrder(TreeNode* tree, QueType<int>& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}

int TreeType::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true;
//       otherwise, finished is false.
{
  int item; finished = false; switch (order)
  {
    case PRE_ORDER : preQue.Dequeue(item);
                     if (preQue.IsEmpty())
                       finished = true;
                     break;
    case IN_ORDER : inQue.Dequeue(item);
                    if (inQue.IsEmpty())
                      finished = true;
                    break;
   case POST_ORDER : postQue.Dequeue(item);
                     if (postQue.IsEmpty())
                       finished = true;
                     break;
  }
  return item;
}



