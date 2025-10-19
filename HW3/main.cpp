#include "BST.h"
//#include "CLQueue.h"

using namespace std;
int main() {
  BST myBST;
  myBST.PutItem(6);
  myBST.PutItem(3);
  myBST.PutItem(7);
  myBST.PutItem(9);
  myBST.PutItem(5);
  myBST.PutItem(1);
  BST clonedBST(myBST);
  myBST.DeleteItem(3);
  
  cout<<"My Tree: ";
  myBST.PrintTree();
  cout<<"Cloned Tree: ";
  clonedBST.PrintTree();
  clonedBST.MakeEmpty();
  cout<<"Cloned Tree V2: ";
  clonedBST.PrintTree();
  int curItem;
  myBST.ResetTree(PRE_ORDER);
  cout<<"My Tree Pre-Order: ";
  while (!(myBST.TravEmpty())) {
    cout<< myBST.GetNextItem();
    if (!myBST.TravEmpty())
      cout<<", ";
  }
  cout<<endl;
  
  myBST.ResetTree(POST_ORDER);
  cout<<"My Tree Post-Order: ";
  while (!(myBST.TravEmpty())) {
    cout<< myBST.GetNextItem();
    if (!myBST.TravEmpty())
      cout<<", ";
  }
  cout<<endl;
}
