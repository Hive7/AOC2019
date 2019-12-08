#include <iostream>

using namespace std;

bool valid(long num)
{
  string strnum = to_string(num);
  bool pair = false;

  for (int i = 0; i < strnum.length() - 1; i++)
  {
    if (strnum[i] > strnum[i + 1])
    {
      return false;
    }
  }

  for (int i = 0; i < strnum.length() - 1; i++)
  {
    if (strnum[i] == strnum[i + 1])
    {
      if (i <= strnum.length() - 2 && strnum[i + 1] == strnum[i + 2])
      {
        while (i < strnum.length() - 1 && strnum[i] == strnum[i + 1])
        {
          i++;
        }
      }
      else
      {
        pair = true;
      }
    }
  }
  return pair;
}

int main(int argc, char const *argv[])
{
  long num;
  cin >> num;
  cout << valid(num) << endl;
  long min = 240298;
  long max = 784956;
  long count = 0;

  for (; min <= max; min++)
  {
    if (valid(min))
    {
      count++;
    }
  }

  cout << count << endl;
  return 0;
}