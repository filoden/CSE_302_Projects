// Implementation file for AUList
#include <iostream>
#include "ASList.h"

ASList::ASList() {
  length = 0; //a newly constructed list has 0 elements; we don't care about the contents of the array.
  MAXSIZE = 1000; //default array size
  ListItems=new int[MAXSIZE];
}

ASList::ASList(int arraysize) {
  length = 0; //a newly constructed list has 0 elements; we don't care about the contents of the array.
  MAXSIZE = arraysize; //default array size
  ListItems=new int[MAXSIZE];
}

ASList::~ASList() {
  delete(ListItems);
}

bool ASList::IsFull() const {
  return (length == MAXSIZE); //Remember that preprocessor commands like #define carry over into files to which they are included (like this one!)
}
int ASList::GetLength() const {
  return length;
}

int ASList::GetItem(int gitem) {
    int midpoint=0;
    int first=0; 
    int last=length-1;
    bool moreToSearch = first <= last;
    while (moreToSearch) {
        midpoint = ( first + last) / 2;
        if (gitem==ListItems[midpoint])
            return midpoint;
        else if (gitem<ListItems[midpoint])
            last = midpoint-1;
        else
            first = midpoint+1;
        moreToSearch = first <= last;
    }
    return -1; 
}

void ASList::PutItem(int pitem) {
    int aloc=0;
    bool moreToSearch = aloc < length;
    while (moreToSearch) {
        if (pitem<ListItems[aloc])
            moreToSearch = false;
        else {		
            aloc++;
            moreToSearch = aloc < length;
        }
    }
    for (int i = length; i > aloc; i--)
        ListItems[i] = ListItems[i-1];
    ListItems[aloc] = pitem;
    length++;
}

void ASList::DeleteItem(int ditem) {
    int aloc=0;
    bool moreToSearch = true;
    while (moreToSearch) {
        if (ditem==ListItems[aloc])
            moreToSearch = false;
        else 
            aloc++;
    }
    for (int i = aloc; i < length; i++)
        ListItems[i] = ListItems[i+1];
    length--;
}

void ASList::MakeEmpty() {
  length = 0; //as with the constructor, we need do nothing to the actual array, as it now "junk" data
}




void ASList::ResetList() {
  currentPos = -1;
}

int ASList::GetNextItem() {
  currentPos++; //Remember that currentPos is a class variable
  return ListItems[currentPos];
}

void ASList::PrintList() {
  std::cout<<"(";
  for (int loc=0; loc<length; loc++) {
  	std::cout<<ListItems[loc];
	if (loc<length-1)
  	  std::cout<<", ";
  }
  std::cout<<")"<<std::endl;
}

