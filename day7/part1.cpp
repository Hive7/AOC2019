#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

long getinput()
{
  return 5;
}

vector<vector<long>> permutations(vector<long> input)
{
  if (input.size() == 1)
  {
    return vector<vector<long>>({{input[0]}});
  }

  vector<vector<long>> output;

  for (int i = 0; i < input.size(); i++)
  {
    vector<long> input_cpy = input;

    input_cpy.erase(input_cpy.begin() + i);

    vector<vector<long>> output_i = permutations(input_cpy);

    for (int j = 0; j < output_i.size(); j++)
    {
      output_i[j].push_back(input[i]);
    }

    output.insert(output.end(), make_move_iterator(output_i.begin()), make_move_iterator(output_i.end()));
  }

  return output;
}

int main(int argc, char const *argv[])
{
  vector<long> test = {5, 6, 7, 8, 9};
  vector<vector<long>> perms = permutations(test);

  vector<long> items;
  long item;
  while (cin >> item)
  {
    items.push_back(item);
    char c;

    cin >> c;
  }
  long max = 0;

  perms = {{9, 8, 7, 5, 6}};

  for (int permutation = 0; permutation < perms.size(); permutation++)
  {
    int inputindex = 0;
    bool perm_prev = true;
    int prev = 0;
    for (int i = 0; i < perms[permutation].size(); i++)
    {
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
          testitems[testitems[index + 1]] = perm_prev ? perms[permutation][inputindex++] : prev;
          perm_prev = !perm_prev;
          index += 2;
        }
        else if (opcode == 4)
        {
          prev = operand1;
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
    }
    if (prev > max)
    {
      max = prev;
    }
  }

  cout << max << endl;

  return 0;
}
