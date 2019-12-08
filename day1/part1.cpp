#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  long total = 0;
  long val;

  while (cin >> val)
  {
    while ((val = val / 3 - 2) > 0)
    {
      total += val;
    }
  }

  cout << total << endl;

  return 0;
}
