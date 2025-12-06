
#include <iostream> 
#ifndef QUEUETYPE_H
#define QUEUETYPE_H
#include "QueType.h"
#endif
struct TreeNode;

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

void PreOrder(TreeNode*, QueType<int>&);
// Enqueues tree items in preorder.

void InOrder(TreeNode*, QueType<int>&);
// Enqueues tree items in inorder.

void PostOrder(TreeNode*, QueType<int>&);
// Enqueues tree items in postorder.
void GetPredecessor(TreeNode* tree, int& data);

class TreeType
{
public:
  TreeType();                     // Constructor.
  ~TreeType();                    // Destructor.
  TreeType(const TreeType& originalTree);  // Copy constructor.
  void operator=(const TreeType& originalTree);
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;
  int GetItem(int item, bool& found) const; 
  void PutItem(int item); 
  void DeleteItem(int item); 
  void ResetTree(OrderType order);
  int GetNextItem (OrderType order, bool& finished);
  void Print(std::ofstream& outFile) const;
private:
  TreeNode* root;
  QueType<int> postQue;
  QueType<int> inQue;
  QueType<int> preQue;
};