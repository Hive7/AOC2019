#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  long num = 0;
  long total = 0;
  while (cin >> num)
  {
    total += num;
  }
  cout << total << endl;
  return 0;
}