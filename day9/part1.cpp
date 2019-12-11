#include <iostream>
#include <vector>

using namespace std;

long long getinput()
{
  return 2;
}

int main(int argc, char const *argv[])
{
  vector<long long> items;
  long long item;
  while (cin >> item)
  {
    items.push_back(item);
    char c;

    cin >> c;
  }
  for (int i = 0; i < 1000000; i++)
  {
    items.push_back(0);
  }
  vector<long long> testitems = items;
  long long index = 0;
  long relative_index = 0;
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
    if (addressing[0] == 1)
    {
      operand1 = testitems[index + 1];
    }
    else
    {
      operand1 = testitems[(addressing[0] / 2) * relative_index + testitems[index + 1]];
    }
    long long operand2;
    if (addressing[1] == 1)
    {
      operand2 = testitems[index + 2];
    }
    else
    {
      operand2 = testitems[(addressing[1] / 2) * relative_index + testitems[index + 2]];
    }
    if (opcode == 1 || opcode == 2)
    {
      if (opcode == 1)
      {
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = operand1 + operand2;
      }
      else
      {
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = operand1 * operand2;
      }
      index += 4;
    }
    else if (opcode == 3)
    {
      testitems[(addressing[0] / 2) * relative_index + testitems[index + 1]] = getinput();
      index += 2;
    }
    else if (opcode == 4)
    {
      cout << operand1 << endl;
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
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = 1;
      }
      else
      {
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else if (opcode == 8)
    {
      if (operand1 == operand2)
      {
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = 1;
      }
      else
      {
        testitems[(addressing[2] / 2) * relative_index + testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else if (opcode == 9)
    {
      relative_index += operand1;
      index += 2;
    }
    else
    {
      cout << "error" << endl;
      break;
    }
  }

  return 0;
}
