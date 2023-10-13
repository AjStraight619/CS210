#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class PrintItem
{
public:
    string fileName;
    float fileSize;

    PrintItem(string fileName, float fileSize)
    {
        this->fileName = fileName;
        this->fileSize = fileSize;
    }

    void print()
    {
        cout << "File Name: " << fileName << ", File Size: " << fileSize << endl;
    }

    ~PrintItem()
    {
        cout << "Destructor called" << endl;
    }
};

// Node Class : Node for the LinkedList
template <typename T>
class Node
{
public:
    T *data;
    Node *nextNode;

    Node(T *value)
    {
        this->data = value;
        nextNode = nullptr;
    }
    void print() { data->print(); }

    // ~Node()
    // {
    //     delete data;
    // }
};

template <typename T>
class LLStack
{
private:
    Node<T> *top;
    int stackSize;
    const int SMAXITEMS;

public:
    // Constructor
    LLStack(int maxItems) : SMAXITEMS(maxItems)
    {
        this->top = nullptr;
        this->stackSize = 0;
    }

    ~LLStack()
    {
        while (this->top != nullptr)
        {
            Node<T> *temp = this->top;
            this->top = this->top->nextNode;
            delete temp;
        }
    }

    int getSize()
    {
        return this->stackSize;
    }

    bool isFull()
    {
        return this->stackSize == SMAXITEMS;
    }

    bool isEmpty()
    {
        return this->top == nullptr;
    }

    void push(T *item)
    {
        if (!isFull())
        {
            Node<T> *newNode = new Node<T>(item);
            newNode->nextNode = this->top;
            this->top = newNode;
            this->stackSize++;
        }
        else
        {
            cout << "Stack is full, cannot push item." << endl;
        }
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node<T> *temp = this->top;

            this->top = this->top->nextNode;
            delete temp;
            this->stackSize--;
        }
        else
        {
            cout << "Stack is empty, cannot pop item." << endl;
        }
    }

    T *peek()
    {
        if (!isEmpty())
        {
            return this->top->data;
        }
        else
        {
            cout << "Stack is empty, cannot peek." << endl;
            return nullptr;
        }
    }

    void print()
    {
        Node<T> *currentNode = this->top;
        while (currentNode != nullptr)
        {
            currentNode->data->print();
            currentNode = currentNode->nextNode;
        }
    }
};

template <typename T>
class StackQ
{
private:
    LLStack<T> *enQStack;
    LLStack<T> *deQStack;
    int queueSize;
    const int QMAXITEMS;

public:
    StackQ(int maxItems) : QMAXITEMS(maxItems)
    {
        this->enQStack = new LLStack<T>(maxItems);
        this->deQStack = new LLStack<T>(maxItems);
        this->queueSize = 0;
    }

    // check if queue is full by adding both stacks and comparing them to QMAXITEMS
    bool isFull()
    {
        return (enQStack->getSize() + deQStack->getSize() == QMAXITEMS);
    }

    // check if the queue is empty by checking if BOTH of the stacks are empty.

    bool isEmpty()
    {
        return (enQStack->isEmpty() && deQStack->isEmpty());
    }

    void print()
    {
        cout << "Contents of enQStack:" << endl;
        enQStack->print();
        cout << "Contents of deQStack:" << endl;
        deQStack->print();
    }

    void enqueue(T *item)
    {
        if (!isFull())
        {

            this->enQStack->push(item);
            this->queueSize++;
        }
        else
        {
            cout << "Queue is full" << endl;
        }
    }

    void dequeue()
    {
        // if the stakcs are not empty continue
        if (!isEmpty())
        {
            // if the dequestack is empty continue
            if (this->deQStack->isEmpty())
            {
                // while the enqstack is not empty peek at the top item and push it to the deqstack and pop it from the enqstack
                while (!this->enQStack->isEmpty())
                {
                    T *item = this->enQStack->peek();
                    this->deQStack->push(item);
                    this->enQStack->pop();
                }
            }
            // pop the top item from the deqstack and decrement the queue size
            this->deQStack->pop();
            this->queueSize--;
        }
        else
        {
            cout << "Queue is empty, cannot dequeue." << endl;
        }
    }
};

// Main Program

int main()
{
    StackQ<PrintItem> queue(10);
    PrintItem item("document.txt", 12.5);
    queue.enqueue(&item);
    queue.print();
    return 0;
}

// LinkedList Class : Container for Nodes
// template <typename T>
// class LinkedList
// {
// private:
//     Node<T> *head;
//     Node<T> *tail;
//     int length;

// public:
//     // Constructor
//     LinkedList(T *value)
//     {
//         Node<T> *newNode = new Node<T>(value);
//         head = newNode;
//         tail = newNode;
//         length = 1;
//     }

//     // Destructor
//     ~LinkedList()
//     {
//         Node<T> *temp = head;
//         while (head)
//         {
//             head = head->next;
//             delete temp;
//             temp = head;
//         }
//     }

//     void printList()
//     {
//         Node<T> *temp = head;
//         while (temp != nullptr)
//         {
//             temp->print();
//             temp = temp->next;
//         }
//     }

//     // get and set
//     Node<T> *getHead()
//     {
//         if (head == nullptr)
//         {
//             cout << "Head: nullptr" << endl;
//         }
//         else
//         {
//             cout << "Head: " << head->value << endl;
//         }
//         return head;
//     }

//     Node<T> *getTail()
//     {
//         if (tail == nullptr)
//         {
//             cout << "Tail: nullptr" << endl;
//         }
//         else
//         {
//             cout << "Tail: " << tail->value << endl;
//         }
//         return tail;
//     }

//     int getLength()
//     {
//         cout << "Length: " << length << endl;
//         return length;
//     }

//     Node<T> *get(int index)
//     {
//         if (index < 0 || index >= length)
//             return nullptr;
//         Node<T> *temp = head;
//         for (int i = 0; i < index; ++i)
//         {
//             temp = temp->next;
//         }
//         return temp;
//     }

//     bool set(int index, T *value)
//     {
//         Node<T> *temp = get(index);
//         if (temp)
//         {
//             temp->value = value;
//             return true;
//         }
//         return false;
//     }

//     // All insert methods
//     // Insert at end
//     void append(T *value)
//     {
//         Node<T> *newNode = new Node<T>(value);
//         if (length == 0)
//         {
//             head = newNode;
//             tail = newNode;
//         }
//         else
//         {
//             tail->next = newNode;
//             tail = newNode;
//         }
//         length++;
//     }

//     // Insert at beginning

//     void prepend(T *value)
//     {
//         Node<T> *newNode = new Node<T>(value);
//         if (length == 0)
//         {
//             head = newNode;
//             tail = newNode;
//         }
//         else
//         {
//             newNode->next = head;
//             head = newNode;
//         }
//         length++;
//     }

//     // Insert at Index

//     bool insert(int index, T *value)
//     {
//         if (index < 0 || index > length)
//             return false;
//         if (index == 0)
//         {
//             prepend(value);
//             return true;
//         }
//         if (index == length)
//         {
//             append(value);
//             return true;
//         }
//         Node<T> *newNode = new Node<T>(value);
//         Node<T> *temp = get(index - 1);
//         newNode->next = temp->next;
//         temp->next = newNode;
//         length++;
//         return true;
//     }

//     // All delete Methods
//     // Delete Tail

//     void deleteLast()
//     {
//         if (length == 0)
//             return;
//         Node<T> *temp = head;
//         if (length == 1)
//         {
//             head = nullptr;
//             tail = nullptr;
//         }
//         else
//         {
//             Node<T> *pre = head;
//             while (temp->next)
//             {
//                 pre = temp;
//                 temp = temp->next;
//             }
//             tail = pre;
//             tail->next = nullptr;
//         }
//         delete temp;
//         length--;
//     }

//     // Delete Head

//     void deleteFirst()
//     {
//         if (length == 0)
//             return;
//         Node<T> *temp = head;
//         if (length == 1)
//         {
//             head = nullptr;
//             tail = nullptr;
//         }
//         else
//         {
//             head = head->next;
//         }
//         delete temp;
//         length--;
//     }

//     // Delete at Index

//     void deleteNode(int index)
//     {
//         if (index < 0 || index >= length)
//             return;
//         if (index == 0)
//             return deleteFirst();
//         if (index == length - 1)
//             return deleteLast();

//         Node<T> *prev = get(index - 1);
//         Node<T> *temp = prev->next;

//         prev->next = temp->next;
//         delete temp;
//         length--;
//     }
// };