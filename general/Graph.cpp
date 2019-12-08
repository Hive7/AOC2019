#include "Graph.h"
#include "LinkedList.h"

#include <unordered_map>

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