#include "LinkedList.h"

template <class T>
class LinkedListItem
{
public:
  LinkedListItem<T> *next;
  T data;

  LinkedListItem(T d)
  {
    next = nullptr;
    data = d;
  }
};

template <class T>
class LinkedList
{
public:
  LinkedListItem<T> *head;
  LinkedListItem<T> *tail;

  LinkedList()
  {
    head = nullptr;
    tail = nullptr;
  }

  void push(T item)
  {
    LinkedListItem<T> *newItem = new LinkedListItem<T>(item);

    newItem->next = head;
    head = newItem;

    if (tail == nullptr)
    {
      tail = head;
    }
  }

  void append(T item)
  {
    LinkedListItem<T> *newItem = new LinkedListItem<T>(item);

    if (tail == nullptr)
    {
      tail = head = newItem;
    }
    else
    {
      tail->next = newItem;
      tail = newItem;
    }
  }

  T pop()
  {
    if (head == nullptr)
    {
      return nullptr;
    }
    LinkedListItem<T> *item = head;

    head = item->next;

    if (head == nullptr)
    {
      tail = nullptr;
    }

    return item->data;
  }
};