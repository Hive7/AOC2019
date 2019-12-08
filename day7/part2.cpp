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
  vector<long> settings = {5, 6, 7, 8, 9};
  vector<vector<long>> perms = permutations(settings);

  vector<long> items;
  long item;
  while (cin >> item)
  {
    items.push_back(item);
    char c;

    cin >> c;
  }
  long max = 0;

  for (int permutation = 0; permutation < perms.size(); permutation++)
  {
    int current = 0;
    int prev = 0;
    vector<long> testitems[settings.size()];
    vector<long> indices;
    vector<bool> perm_prev;

    for (int i = 0; i < settings.size(); i++)
    {
      testitems[i] = items;
      indices.push_back(0);
      perm_prev.push_back(true);
    }

    while (testitems[current][indices[current]] != 99 && indices[current] < testitems[current].size())
    {
      long index = indices[current];
      item = testitems[current][index];

      int opcode = item % 100;

      item = item / 100;

      int addressing[3] = {0, 0, 0};
      int k = 0;
      while (item > 0)
      {
        addressing[k++] = item % 10;
        item = item / 10;
      }
      long operand1 = addressing[0] ? testitems[current][index + 1] : testitems[current][testitems[current][index + 1]];
      long operand2 = addressing[1] ? testitems[current][index + 2] : testitems[current][testitems[current][index + 2]];
      if (opcode == 1 || opcode == 2)
      {
        if (opcode == 1)
        {
          testitems[current][testitems[current][index + 3]] = operand1 + operand2;
        }
        else
        {
          testitems[current][testitems[current][index + 3]] = operand1 * operand2;
        }
        index += 4;
      }
      else if (opcode == 3)
      {
        testitems[current][testitems[current][index + 1]] = perm_prev[current] ? perms[permutation][current] : prev;
        perm_prev[current] = false;
        index += 2;
      }
      else if (opcode == 4)
      {
        prev = operand1;
        index += 2;
        indices[current] = index;
        current++;
        current = current % settings.size();
        continue;
      }
      else if (opcode == 5)
      {
        if (operand1 != 0)
        {
          indices[current] = operand2;
          continue;
        }
        index += 3;
      }
      else if (opcode == 6)
      {
        if (operand1 == 0)
        {
          indices[current] = operand2;
          continue;
        }
        index += 3;
      }
      else if (opcode == 7)
      {
        if (operand1 < operand2)
        {
          testitems[current][testitems[current][index + 3]] = 1;
        }
        else
        {
          testitems[current][testitems[current][index + 3]] = 0;
        }
        index += 4;
      }
      else if (opcode == 8)
      {
        if (operand1 == operand2)
        {
          testitems[current][testitems[current][index + 3]] = 1;
        }
        else
        {
          testitems[current][testitems[current][index + 3]] = 0;
        }
        index += 4;
      }
      else
      {
        break;
      }
      indices[current] = index;
    }

    if (prev > max)
    {
      max = prev;
    }
  }

  cout << max << endl;

  return 0;
}
