// Implementation file for AUList
#include <iostream>
#include "AUList.h"


AUList::AUList() {
  length = 0; //a newly constructed list has 0 elements; we don't care about the contents of the array.
}
bool AUList::IsFull() const {
  return (length == MAXSIZE); //Remember that preprocessor commands like #define carry over into files to which they are included (like this one!)
}
int AUList::GetLength() const {
  return length;
}

int AUList::GetItem(int gitem) {
  int searchiter;
  for (searchiter = length-1; searchiter>=0; searchiter--) { //main loop decrements from the final index in the list down to -1 
	if (ListItems[searchiter] == gitem) //if this condition is met, we have a match
  	  break;  //break terminates the innermost-loop in progress (so in this case, the for-loop.  Has no impact on other conditionals or scope.
  } 
  return searchiter;
}

void AUList::MakeEmpty() {
  length = 0; //as with the constructor, we need do nothing to the actual array, as it now "junk" data
}
void AUList::PutItem(int item) { //This function assumes the "IsFull" condition hasn't been met.
  ListItems[length] = item; //Remember that C++ uses 0-indexing.
  length++;
}
void AUList::DeleteItem(int item) { //This is the less efficient version of what we discussed ("Move-Up") that maintains list order
//Note: assumes item is actually in list

  bool indexfound=false;
  for (int loc=0; loc<length; loc++) {
  	if (ListItems[loc]==item) 
  	  indexfound=true;
  	if (indexfound)
  	  ListItems[loc]=ListItems[loc+1];	
  }
  length--;
}

void AUList::ResetList() {
  currentPos = -1; //We want the position BEFORE the first element, since incrementation in GetNextItems happens first
}

int AUList::GetNextItem() {
  currentPos++; //Remember that currentPos is a class member variable
  return ListItems[currentPos];
}

void AUList::PrintList() { //simple function to print a list's items in stored order
  std::cout<<"(";
  for (int loc=0; loc<length; loc++) {
  	std::cout<<ListItems[loc];
	if (loc<length-1)
  	  std::cout<<", ";
  }
  std::cout<<")"<<std::endl;
}

