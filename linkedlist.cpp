#include <iostream>
using namespace std;

/********************************************
 * Author: Fernando Zamora
 * Class: Node
 * Purpose: Node within the list
 * ******************************************/
 
template <class T>
class Node
{
  
  public:
    
    T Data;
    Node<T>* Next;
    
    Node()
    {
      Next = NULL;
    }
    
    Node(T data)
    {
      Data = data;
      Next = NULL;
    }

};

/************************************************
 * Class: LinkedList 
 * Author: Fernando Zamora
 * Purpose: Implements a linked list but does not
 * expose internal operations of list
 *
 * **********************************************/
 template <class T>
class LinkedList
{
  
  private:
  
  Node<T>* m_head = NULL;
  Node<T>* m_current = NULL;
 
  //Recursive algorithm to delete from DeleteTail
  //it is a brute force approach
  //It can be done better by tracking the tail insted 
  //of walking from beginning to end each time
  //
  //A doubly linked list would be more efficient in keeping
  //track of the tail and then pointing to previous
  //that way it can walk backwards.
  void DeleteTail()
  {
    
    Node<T>* current = m_head;
    Node<T>* previous = current;
    
    if(current == NULL)
    {
      return;
    }
    
    if(current->Next == NULL)
    {
      
      cout << "Deleting: " << current->Data << endl;
      delete current;
      current = NULL;
      m_head = NULL;
      return;
    }
    
    while(current->Next != NULL)
    {
      previous = current;
      current = current->Next;
    }
    
    if(previous != NULL)
    {
      cout << "Deleting: " << current->Data << endl;
      delete current;
      previous->Next = NULL;
    }
    
    DeleteTail();
    
  }
  
  public:
  
    ~LinkedList()
    {
      cout << "Deleting list..." << endl;
      DeleteTail();
    }
    
    //Add data to the list  
    void Add(T data)
    {
      if(m_head == NULL)
      {
        m_head = new Node<T>(data);
      }
      else
      {
        Node<T>* current = m_head;
        while(current->Next != NULL)
        {
          current = current->Next;
        }
        current->Next = new Node<T>(data);
      }
    }
    
    //Gets the head of the list
    //Returns -1 if no head is present
    T Head()
    {
      int data = -1;
      if(m_head != NULL)
        data = m_head->Data;
        
      return data;  
    }

    //Gets an item by its index    
    T Get(int index)
    {
      int currentIndex = 0;
      Node<T> *current = m_head;
      T data;
      
      while(currentIndex != index && current != NULL)
      {
        current = current->Next;
        currentIndex++;
      }
      
      if(current != NULL && currentIndex == index)
      {
        data = current->Data;
      }
      
      if(current == NULL )
      {
        throw -777;
      }
      
      return data;
    }
    
    //Finds data item within list
    //Returns: index of item or -1 if not found
    int Find(T searchFor)
    {
      
      Node<T>* current = m_head;
      int index = 0;
      
      while(current != NULL){
        
        if(current->Data == searchFor)
        {
          return index;
        }
        current = current->Next;
        index++;
      }
      
      return -1; //Did not find it
    }

    //Gets first item in list
    T First()
    {
      m_current = m_head;
      return m_head->Data;
    }

    //For iterating over list    
    T Next()
    {
      T data;
      if(m_current != NULL){
        m_current = m_current->Next;
        return m_current->Data;
      }
      
      if(m_current != NULL){
        return m_current->Data;
      }
      
      return data;
    }
    
    //To determine if there is another item to iterate to
    bool HasNext()
    {
      return (m_current != NULL && m_current->Next != NULL);
    }
}; //End of LinkedList class declaration

void TestWithIntegers(){
    
    LinkedList<int> list;
    
    cout << "Testing with integers... " << endl;
    cout << endl;
    
    list.Add(1);
    list.Add(2);
    list.Add(3);
    
    cout << list.Get(0) << endl;
    cout << list.Get(1) << endl;
    cout << list.Get(2) << endl;
    
    cout << endl;
    cout << "Iterator: " << endl;
    cout <<   "First:  " << list.First() << endl;
    
    while(list.HasNext())
    {
      cout << "Next:   " << list.Next() << endl;
    }
    
    cout << "Should find 0 at -1: result: " << list.Find(0) << endl;
    cout << "Should find 1 at 0:  result: " << list.Find(1) << endl;
    cout << "Should find 2 at 1:  result: " << list.Find(2) << endl;
    cout << "Should find 3 at 2:  result: " << list.Find(3) << endl;
    cout << endl;
    cout << endl;
}


void TestWithStrings(){
    
    LinkedList<string> list;
    
    cout << endl;
    cout << "Testing with strings... " << endl;
    cout << endl;
    
    list.Add("aa");
    list.Add("bb");
    list.Add("cc");
    
    cout << list.Get(0) << endl;
    cout << list.Get(1) << endl;
    cout << list.Get(2) << endl;
    
    cout << endl;
    cout << "Iterator: " << endl;
    cout <<   "First:  " << list.First() << endl;
    
    while(list.HasNext())
    {
      cout << "Next:   " << list.Next() << endl;
    }

    cout << "Should find zz at -1: result: " << list.Find("zz") << endl;
    cout << "Should find aa at 0: result: " << list.Find("aa") << endl;
    cout << "Should find bb at 1: result: " << list.Find("bb") << endl;
    cout << "Should find cc at 2: result: " << list.Find("cc") << endl;
    cout << endl;
    cout << endl;
}

int main() 
{
  TestWithIntegers();
  TestWithStrings();
}