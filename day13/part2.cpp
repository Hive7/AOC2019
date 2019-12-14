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

  int index = 0;
  int fail = 0;
  int relative_address = 0;

  int output_type = 0;
  int x = 0;
  int y = 0;
  int score = 0;

  int minx = 0;
  int maxx = 0;

  int miny = 0;
  int maxy = 0;

  int paddlex = 0;
  int paddley = 0;

  int nextinput = 0;

  testitems[0] = 2;

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
      testitems[relative_address * addressing[0] / 2 + testitems[index + 1]] = nextinput;
      index += 2;
    }
    else if (opcode == 4)
    {
      if (output_type == 2)
      {
        if (x == -1 && y == 0)
        {
          score = operand1;
        }
        else
        {
          if (x < minx)
          {
            minx = x;
          }
          if (x > maxx)
          {
            maxx = x;
          }
          if (y < miny)
          {
            miny = y;
          }
          if (y > maxy)
          {
            maxy = y;
          }
          coords.insert_or_assign(pair<long, long>(x, y), operand1);

          if (operand1 == 3)
          {
            paddlex = x;
            paddley = y;
          }
          if (operand1 == 4)
          {
            if (paddlex < x)
            {
              nextinput = 1;
            }
            else if (paddlex > x)
            {
              nextinput = -1;
            }
            else
            {
              nextinput = 0;
            }
          }
        }
      }
      else if (output_type == 1)
      {
        y = operand1;
      }
      else
      {
        x = operand1;
      }
      output_type = (output_type + 1) % 3;
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

  for (int i = miny; i <= maxy; i++)
  {
    for (int j = minx; j <= maxx; j++)
    {
      if (coords.find(pair<long, long>(j, i)) == coords.end())
      {
        cout << " ";
      }
      else
      {
        int val = coords.at(pair<long, long>(j, i));

        if (val == 0)
        {
          cout << " ";
        }
        else if (val == 1)
        {
          cout << "|";
        }
        else if (val == 2)
        {
          cout << "X";
        }
        else if (val == 3)
        {
          cout << "_";
        }
        else if (val == 4)
        {
          cout << "o";
        }
      }
    }

    cout << endl;
  }

  cout << score << endl;

  return 0;
}
