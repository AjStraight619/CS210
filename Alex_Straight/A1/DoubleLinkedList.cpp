/*
Alex Straight
CS 210
Programming assignment 1
10/01/2023
*/

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

  DoubleLinkedList()
  {
    head = nullptr;
    tail = nullptr;
    length = 0;
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

  // Delete at head of DLL

  void deleteAtHead()
  {
    cout << head << endl;

    if (head == nullptr)
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
      Node<T> *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
    length--;
  }

  // Delete at tail of DLL

  void deleteAtTail()
  {

    cout << tail << endl;

    Node<T> *temp;

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
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }

    length--;
  }

  // Delete at specific index.

  void deleteAtIndex(int index)
  {
    if (isEmpty())
      return;

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
      current = head;
      for (int i = 0; i < index; i++)
      {
        current = current->next;
      }
    }
    else
    {
      current = tail;
      for (int i = length - 1; i > index; i--)
      {
        current = current->prev;
      }
    }

    cout << current << endl;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    length--;
  }

  // Remove multiples. We utilize the count mutliples function here.

  void removeMultiples()
  {
    if (isEmpty())
      return;

    Node<T> *current = head;
    while (current != nullptr)
    {
      int count = countMultiples(*(current->value));
      if (count > 1)
      {
        Node<T> *toDelete = current;
        if (current->prev != nullptr)
          current->prev->next = current->next;
        if (current->next != nullptr)
          current->next->prev = current->prev;
        if (current == head)
          head = current->next;
        if (current == tail)
          tail = current->prev;
        current = current->next;
        delete toDelete;
      }
      else
      {
        current = current->next;
      }
    }
  }

  // Count multiples

  int countMultiples(T value)
  {
    if (isEmpty())
      return 0;

    Node<T> *current = head;
    int count = 0;

    while (current != nullptr)
    {
      if (current->value->value == value.value)
      {
        count++;
      }
      current = current->next;
    }
    return count;
  }
  void headTailSplit()
  {
    if (isEmpty())
      return;

    Node<T> *slow = head, *fast = head;
    while (fast != nullptr && fast->next != nullptr)
    {
      slow = slow->next;
      fast = fast->next->next;
    }

    DoubleLinkedList<T> listA, listB;

    Node<T> *current = head;
    while (current != slow)
    {
      listA.append(current->value);
      Node<T> *temp = current;
      current = current->next;
      delete temp;
    }

    current = tail;
    while (current != slow)
    {
      listB.append(current->value);
      Node<T> *temp = current;
      current = current->prev;
      delete temp;
    }

    delete this;

    listA.printList();
    listB.printList();
  }

  // Sort the list. I tried using a hash map but I kept getting weird bugs so I used essentially bubble sort instead. O(n^2)

  void sortList()
  {
    if (isEmpty())
      return;

    bool swapped;
    Node<T> *ptr1;
    Node<T> *lptr = nullptr;

    do
    {
      swapped = false;
      ptr1 = head;

      while (ptr1->next != lptr)
      {
        if (ptr1->value->value > ptr1->next->value->value)
        {
          std::swap(ptr1->value, ptr1->next->value);
          swapped = true;
        }
        ptr1 = ptr1->next;
      }
      lptr = ptr1;

    } while (swapped);

    printList();
  }

  // Reverse the list

  void reverseList()
  {
    Node<T> *current = head, *temp = nullptr;

    while (current != nullptr)
    {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }

    if (temp != nullptr)
      head = temp->prev;

    printList();
  }

  // Helper function
  bool isEmpty()
  {
    return (head == nullptr);
  }
};

// Main Program

int main()
{
  int choice, value;
  string name;
  DoubleLinkedList<Data> *list = nullptr;
  // do while loop to inform user of possible interactions
  do
  {
    cout << "Menu:\n";
    cout << "1. Create new list\n";
    cout << "2. Append data\n";
    cout << "3. Prepend data\n";
    cout << "4. Insert data at index\n";
    cout << "5. Print list\n";
    cout << "6. Delete from head\n";
    cout << "7. Delete from tail\n";
    cout << "8. Delete at index\n";
    cout << "9. Sort list\n";
    cout << "10. Reverse list\n";
    cout << "11. Count multiples of a value\n";
    cout << "12. Remove multiples\n";
    cout << "13. Split list\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Switching on choice case 1-13 are operations. 0 to exit.

    switch (choice)
    {
    case 1:
      if (list)
      {
        delete list;
      }
      cout << "Enter initial value and name (separated by space): ";
      cin >> value >> name;
      list = new DoubleLinkedList<Data>(new Data(value, name));
      break;
    case 2:
      cout << "Enter value and name (separated by space): ";
      cin >> value >> name;
      list->append(new Data(value, name));
      break;
    case 3:
      cout << "Enter value and name (separated by space): ";
      cin >> value >> name;
      list->prepend(new Data(value, name));
      break;
    case 4:
      int index;
      cout << "Enter index, value and name (separated by space): ";
      cin >> index >> value >> name;
      list->insert(index, new Data(value, name));
      break;
    case 5:
      list->printList();
      break;
    case 6:
      list->deleteAtHead();
      break;
    case 7:
      list->deleteAtTail();
      break;
    case 8:
      cout << "Enter index to delete: ";
      cin >> index;
      list->deleteAtIndex(index);
      break;
    case 9:
      list->sortList();
      break;
    case 10:
      list->reverseList();
      break;
    case 11:
      cout << "Enter value to count multiples of: ";
      cin >> value;
      cout << "Multiples Count: " << list->countMultiples(Data(value, "")) << "\n";
      break;
    case 12:
      list->removeMultiples();
      break;
    case 13:
      list->headTailSplit();
      break;
    case 0:
      if (list)
      {
        delete list;
      }
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  } while (choice != 0);

  return 0;
}
