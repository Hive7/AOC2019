#include <iostream>
#include <vector>

using namespace std;

long getinput()
{
  return 5;
}

int main(int argc, char const *argv[])
{
  vector<long> items;
  long item;
  while (cin >> item)
  {
    items.push_back(item);
    char c;

    cin >> c;
  }
  vector<long> testitems = items;
  int index = 0;
  int fail = 0;
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
    long operand1 = addressing[0] ? testitems[index + 1] : testitems[testitems[index + 1]];
    long operand2 = addressing[1] ? testitems[index + 2] : testitems[testitems[index + 2]];
    if (opcode == 1 || opcode == 2)
    {
      if (opcode == 1)
      {
        testitems[testitems[index + 3]] = operand1 + operand2;
      }
      else
      {
        testitems[testitems[index + 3]] = operand1 * operand2;
      }
      index += 4;
    }
    else if (opcode == 3)
    {
      testitems[testitems[index + 1]] = getinput();
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
        testitems[testitems[index + 3]] = 1;
      }
      else
      {
        testitems[testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else if (opcode == 8)
    {
      if (operand1 == operand2)
      {
        testitems[testitems[index + 3]] = 1;
      }
      else
      {
        testitems[testitems[index + 3]] = 0;
      }
      index += 4;
    }
    else
    {
      break;
    }
  }

  return 0;
}
