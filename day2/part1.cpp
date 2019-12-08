#include <iostream>
#include <vector>

using namespace std;

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
  long noun = -1, verb = -1;
  for (int i = 0; i < 100; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      vector<long> testitems = items;
      int index = 0;
      testitems[1] = i;
      testitems[2] = j;
      int fail = 0;
      while (testitems[index] != 99 && index < testitems.size())
      {
        item = testitems[index];

        if (item == 1)
        {
          testitems[testitems[index + 3]] = testitems[testitems[index + 1]] + testitems[testitems[index + 2]];
        }
        else if (item == 2)
        {
          testitems[testitems[index + 3]] = testitems[testitems[index + 1]] * testitems[testitems[index + 2]];
        }
        else
        {
          fail = 1;
          break;
        }
        index += 4;
      }
      if (!fail)
      {
        if (testitems[0] == 19690720)
        {
          noun = i;
          verb = j;
        }
      }
    }
    if (noun != -1)
    {
      break;
    }
  }

  cout << noun * 100 + verb << endl;

  return 0;
}
