#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <set>

using namespace std;

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

template <class T>
class Node
{
public:
  LinkedList<Node<T> *> incoming;
  LinkedList<Node<T> *> outgoing;
  T data;
  bool explored;
  long depth;

  Node(T d)
  {
    incoming = LinkedList<Node<T> *>();
    outgoing = LinkedList<Node<T> *>();
    data = d;
    explored = false;
    depth = 0;
  }
};

template <class T>
class Graph
{
public:
  LinkedList<Node<T> *> nodes;
  unordered_map<T, Node<T> *> node_map;

  Graph()
  {
    nodes = LinkedList<Node<T> *>();
  }

  void add_node(T data)
  {
    if (node_map.find(data) == node_map.end())
    {
      Node<T> *node = new Node<T>(data);

      node_map.insert_or_assign(data, node);
      nodes.push(node);
    }
  }

  void add_edge(T u, T v)
  {
    if (node_map.find(u) != node_map.end() && node_map.find(v) != node_map.end())
    {
      Node<T> *u_node = node_map.at(u);
      Node<T> *v_node = node_map.at(v);

      u_node->outgoing.push(v_node);
      v_node->incoming.push(u_node);
    }
  }
};

int main(int argc, char const *argv[])
{
  string line;
  Graph<string> g = Graph<string>();
  set<string> nodes;

  while (cin >> line)
  {
    string u, v;
    replace(line.begin(), line.end(), ')', '\n');

    stringstream sstream(line);

    sstream >> u;
    sstream >> v;

    g.add_node(u);
    g.add_node(v);

    g.add_edge(u, v);

    nodes.insert(u);
    nodes.insert(v);
  }

  for (pair<string, Node<string> *> node : g.node_map)
  {
    node.second->explored = false;
    node.second->depth = 0;
  }

  LinkedList<Node<string> *> frontier;

  bool found = false;

  frontier.append(g.node_map.at("YOU"));

  while (frontier.head != nullptr)
  {
    Node<string> *node = frontier.pop();

    node->explored = true;

    if (node->data == "SAN")
    {
      cout << node->depth - 2 << endl;
      break;
    }

    LinkedListItem<Node<string> *> *head = node->incoming.head;

    while (head != nullptr)
    {
      if (!head->data->explored)
      {
        head->data->depth = node->depth + 1;
        frontier.append(head->data);
      }

      head = head->next;
    }

    head = node->outgoing.head;

    while (head != nullptr)
    {
      if (!head->data->explored)
      {
        head->data->depth = node->depth + 1;
        frontier.append(head->data);
      }

      head = head->next;
    }
  }
}
