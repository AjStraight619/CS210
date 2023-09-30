#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data
{
public:
  int value;
  string name;
  Data(int value, string name)
  {
    this->value = value;
    this->name = name;
  }
  void print()
  {

    cout << value << " " << endl;
    cout << name << " " << endl;
  }
};

// Node Class : Node for the LinkedList
template <typename T>
class Node
{
public:
  T *value;
  Node<T> *next;
  Node<T> *prev;
  Node(T *value)
  {
    this->value = value;
    next = nullptr;
    prev = nullptr;
  }
  void print() { value->print(); }
};

// LinkedList Class : Container for Nodes
template <typename T>
class DoubleLinkedList
{
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

public:
  // Constructor
  DoubleLinkedList(T *value)
  {
    Node<T> *newNode = new Node<T>(value);
    head = newNode;
    tail = newNode;
    length = 1;
  }

  // Destructor
  ~DoubleLinkedList()
  {
    Node<T> *temp = head;
    while (head)
    {
      head = head->next;
      delete temp;
      temp = head;
    }
  }

  void printList()
  {
    Node<T> *temp = head;
    while (temp != nullptr)
    {
      temp->print();
      temp = temp->next;
    }
  }

  // get and set
  Node<T> *getHead()
  {
    if (head == nullptr)
    {
      cout << "Head: nullptr" << endl;
    }
    else
    {
      cout << "Head: " << head->value << endl;
    }
    return head;
  }

  Node<T> *getTail()
  {
    if (tail == nullptr)
    {
      cout << "Tail: nullptr" << endl;
    }
    else
    {
      cout << "Tail: " << tail->value << endl;
    }
    return tail;
  }

  int getLength()
  {
    cout << "Length: " << length << endl;
    return length;
  }

  Node<T> *get(int index)
  {
    if (index < 0 || index >= length)
      return nullptr;
    Node<T> *temp = head;
    for (int i = 0; i < index; ++i)
    {
      temp = temp->next;
    }
    return temp;
  }

  bool set(int index, T *value)
  {
    Node<T> *temp = get(index);
    if (temp)
    {
      temp->value = value;
      return true;
    }
    return false;
  }

  // All insert methods
  // Insert at end
  void append(T *value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (length == 0)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    length++;
  }

  // Insert at beginning

  void prepend(T *value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (length == 0)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    length++;
  }

  // Insert at Index

  bool insert(int index, T *value)
  {
    if (index < 0 || index > length)
      return false;
    if (index == 0)
    {
      prepend(value);
      return true;
    }
    if (index == length)
    {
      append(value);
      return true;
    }
    Node<T> *newNode = new Node<T>(value);
    Node<T> *prev1 = get(index - 1);
    Node<T> *next1 = prev1->next;
    newNode->prev = prev1;
    newNode->next = next1;
    prev1->next = newNode;
    next1->prev = newNode;
    length++;
    return true;
  }

  // All delete Methods
  // Write DeleteHead, DeleteTail & DeleteAtIndex here

  void deleteAtHead()
  {
    cout << head << endl;
    if (head == nullptr)
    {
      return; // list is empty, nothing to delete
    }
    if (head == tail)
    {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else
    {
      Node<T> *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
    length--;
  }

  void deleteAtTail()
  {

    if (tail == nullptr)
    {
      return;
    }

    if (head == tail)
    {
      delete head;
      head = nullptr;
      tail = nullptr;
    }

    else
    {
      temp = tail;
      tail = tail->prev
                 tail->next = nullptr;
      delete temp;
    }

    length--;
  }

  void deleteAtIndex(int index)
  {
    if (index < 0 || index >= length)
    {
      return;
    }
    if (index == 0)
    {
      deleteAtHead();
      return;
    }
    if (index == length - 1)
    {
      deleteAtTail();
      return;
    }

    Node<T> *current;
    if (index <= length / 2)
    {
      // If the index is in the first half, start traversal from head
      current = head;
      for (int i = 0; i < index; i++)
      {
        current = current->next;
      }
    }
    else
    {
      // If the index is in the second half, start traversal from tail
      current = tail;
      for (int i = length - 1; i > index; i--)
      {
        current = current->prev;
      }
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    length--;
  }
};

// Main Program

int main()
{
  // creating data object
  Data *d1 = new Data(10, "a");

  // Creating Linked List
  DoubleLinkedList<Data> *ll1 = new DoubleLinkedList<Data>(d1);

  // Calling operations on Linked List
  ll1->printList();

  return 0;
}