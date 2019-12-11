#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct pair_hash
{
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const
  {
    auto h1 = hash<T1>{}(p.first);
    auto h2 = hash<T2>{}(p.second);

    // Mainly for demonstration purposes, i.e. works but is overly simple
    // In the real world, use sth. like boost.hash_combine
    return h1 ^ h2;
  }
};

int main(int argc, char const *argv[])
{
  unordered_map<pair<long, long>, int, pair_hash> coords;
  vector<long long> items;
  long long item;
  while (cin >> item)
  {
    items.push_back(item);
    char c;

    cin >> c;
  }
  vector<long long> testitems = items;

  for (int i = 0; i < 100000; i++)
  {
    testitems.push_back(0);
  }

  long count = 0;

  long x = 0;
  long y = 0;
  int heading = 0;

  long minx = 0;
  long maxx = 0;
  long miny = 0;
  long maxy = 0;

  coords[pair<long, long>(x, y)] = 1;

  bool draw = true;

  int index = 0;
  int fail = 0;
  int relative_address = 0;

  while (testitems[index] != 99 && index < testitems.size())
  {
    item = testitems[index];

    int opcode = item % 100;

    item = item / 100;

    int addressing[3] = {0, 0, 0};
    int k = 0;
    while (item > 0)
    {
      addressing[k++] = item % 10;
      item = item / 10;
    }
    long long operand1;
    long long operand2;

    if (addressing[0] == 1)
    {
      operand1 = testitems[index + 1];
    }
    else
    {
      operand1 = testitems[relative_address * addressing[0] / 2 + testitems[index + 1]];
    }

    if (addressing[1] == 1)
    {
      operand2 = testitems[index + 2];
    }
    else
    {
      operand2 = testitems[relative_address * addressing[1] / 2 + testitems[index + 2]];
    }

    if (opcode == 1 || opcode == 2)
    {
      if (opcode == 1)
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = operand1 + operand2;
      }
      else
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = operand1 * operand2;
      }
      index += 4;
    }
    else if (opcode == 3)
    {
      int input = 0;

      if (coords.find(pair<long, long>(x, y)) != coords.end() && coords[pair<long, long>(x, y)])
      {
        input = 1;
      }
      testitems[relative_address * addressing[0] / 2 + testitems[index + 1]] = input;
      index += 2;
    }
    else if (opcode == 4)
    {
      if (draw)
      {
        if (coords.find(pair<long, long>(x, y)) == coords.end())
        {
          count++;
        }
        coords.insert_or_assign(pair<long, long>(x, y), operand1);
      }
      else
      {
        if (operand1)
        {
          heading++;
        }
        else
        {
          heading--;
        }
        heading = (heading + 4) % 4;
        if (heading == 0)
        {
          y--;
          if (y < miny)
          {
            miny = y;
          }
        }
        else if (heading == 1)
        {
          x++;
          if (x > maxx)
          {
            maxx = x;
          }
        }
        else if (heading == 2)
        {
          y++;
          if (y > maxy)
          {
            maxy = y;
          }
        }
        else
        {
          x--;
          if (x < minx)
          {
            minx = x;
          }
        }
      }
      draw = !draw;
      index += 2;
    }
    else if (opcode == 5)
    {
      if (operand1 != 0)
      {
        index = operand2;
        continue;
      }
      index += 3;
    }
    else if (opcode == 6)
    {
      if (operand1 == 0)
      {
        index = operand2;
        continue;
      }
      index += 3;
    }
    else if (opcode == 7)
    {
      if (operand1 < operand2)
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = 1;
      }
      else
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else if (opcode == 8)
    {
      if (operand1 == operand2)
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = 1;
      }
      else
      {
        testitems[relative_address * addressing[2] / 2 + testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else if (opcode == 9)
    {
      relative_address += operand1;
      index += 2;
    }
    else
    {
      break;
    }
  }

  cout << count << endl;

  for (y = miny; y <= maxy; y++)
  {
    for (x = minx; x <= maxx; x++)
    {
      int input = 0;

      if (coords.find(pair<long, long>(x, y)) != coords.end() && coords[pair<long, long>(x, y)])
      {
        input = 1;
      }

      if (input)
      {
        cout << "#";
      }
      else
      {
        cout << ".";
      }
    }
    cout << endl;
  }

  return 0;
}
