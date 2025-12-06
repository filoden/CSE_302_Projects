struct LNode;

//Remember that header files should contain DECLARATIONS, but not DEFINITIONS for the associated class functions.
class LLUList
{
public:
  
  LLUList(); // Constructor
  
  ~LLUList(); // Destructor
  
  void MakeEmpty();  // Returns the list to the empty state.
    
  bool IsFull() const; //Determines whether list is full. (Precondition -- list has been initialized).  Return value of "True" indicates class is full.
  
  int GetLength() const; //Determines the number of elements in list.

  int GetItem(int); //Retrieves position of list element matching input item (if present).  If not present, -1 is returned.

  void PutItem(int); //Adds the item to the list.
  
  void DeleteItem(int); //Deletes the element whose key matches item's key.
  
  void ResetList();  //Initializes iterator's current position for an iteration through the list.
  
  void PrintList();  //Print all elements of the list in a readable format.
  
  int GetNextItem(); //Gets the next element in the list.  

private:
  LNode* ListStart;  
  LNode* curPos;
};

