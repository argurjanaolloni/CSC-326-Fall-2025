#include <iostream>
#include <fstream>
using namespace std;

struct Caller
{
  string name;
  string state;
  int serviceTime;
};

template <typename T>
struct Node
{
  T data;
  Node *next;
  Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class Queue
{
private:
  Node<T> *front;
  Node<T> *rear;

public:
  Queue() : front(nullptr), rear(nullptr) {}

  ~Queue()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }

  bool isEmpty() const
  {
    return front == nullptr;
  }

  void enqueue(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (rear == nullptr)
    {
      front = rear = newNode;
      return;
    }
    rear->next = newNode;
    rear = newNode;
  }

  T dequeue()
  {
    if (isEmpty())
      throw runtime_error("Cannot dequeue from an empty queue.");

    Node<T> *temp = front;
    T removedVal = front->data;

    front = front->next;

    if (front == nullptr)
      rear = nullptr;

    delete temp;
    return removedVal;
  }

  T peek() const
  {
    if (isEmpty())
      throw runtime_error("Queue is empty.");

    return front->data;
  }

  void display() const
  {
    if (isEmpty())
    {
      throw runtime_error("Queue is empty.");
      return;
    }

    Node<T> *current = front;
    cout << "Queue elements: " << endl;
    while (current != nullptr)
    {
      cout << current->data << " ---> ";
      current = current->next;
    }
    cout << endl;
  }
};

template <typename T>
class Stack
{
private:
  Node<T> *top;

public:
  Stack() : top(nullptr) {}

  ~Stack()
  {
    while (!isEmpty())
    {
      pop();
    }
  }

  bool isEmpty() const
  {
    return top == nullptr;
  }

  void push(T value)
  {
    Node<T> *newNode = new Node<T>(value);
    if (top == nullptr)
    {
      top = newNode;
      return;
    }
    newNode->next = top;
    top = newNode;
  }

  T pop()
  {
    if (isEmpty())
      throw runtime_error("Cannot pop from an empty stack.");

    Node<T> *temp = top;
    T removedVal = top->data;
    top = top->next;
    delete temp;
    return removedVal;
  }

  T peek() const
  {
    if (isEmpty())
      throw runtime_error("Stack is empty.");

    return top->data;
  }

  void display() const
  {
    if (isEmpty())
    {
      throw runtime_error("Stack is empty.");
      return;
    }

    Node<T> *current = top;
    cout << "Stack elements: " << endl;
    while (current != nullptr)
    {
      cout << current->data << " ---> ";
      current = current->next;
    }
    cout << endl;
  }
};

int main()
{
  Queue<Caller> ourQueue;
  Stack<Caller> ourStack;
  Caller temp;
  int totalServiceTime = 0;

  fstream inData("calls.txt");
  if (!inData)
  {
    cout << "Error opening file." << endl;
    return 1;
  }

  while (inData >> temp.name >> temp.state >> temp.serviceTime)
  {
    if (temp.state == "waiting")
      ourQueue.enqueue(temp);
    else if (temp.state == "missed")
      ourStack.push(temp);
  }

  inData.close();

  while (!ourQueue.isEmpty() || !ourStack.isEmpty())
  {

    for (int i = 0; i < 3 && !ourQueue.isEmpty(); i++)
    {
      Caller currentWaitingCaller = ourQueue.dequeue();
      totalServiceTime += currentWaitingCaller.serviceTime;
      cout << "Answered call from: " << currentWaitingCaller.name << endl
           << "Service time: " << currentWaitingCaller.serviceTime << endl;
    }

    if (!ourStack.isEmpty())
    {
      Caller currentMissedCaller = ourStack.pop();
      totalServiceTime += currentMissedCaller.serviceTime;
      cout << "Returned call to: " << currentMissedCaller.name << endl
           << "Service time: " << currentMissedCaller.serviceTime << endl;
    }
  }

  cout << "All calls are answered." << endl
       << "Total service time: " << totalServiceTime << endl;

  return 0;
}

/*
SAMPLE OUTPUT
Answered call from: Alice
Service time: 3
Answered call from: Bob
Service time: 5
Answered call from: David
Service time: 2
Returned call to: Jack
Service time: 3
Answered call from: Frank
Service time: 6
Answered call from: Henry
Service time: 4
Answered call from: Ivy
Service time: 5
Returned call to: Grace
Service time: 2
Answered call from: Kelly
Service time: 2
Answered call from: Leo
Service time: 4
Returned call to: Emma
Service time: 3
Returned call to: Charlie
Service time: 4
All calls are answered.
Total service time: 43
*/