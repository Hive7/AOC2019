#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <stdlib.h>
#include <map>

using namespace std;

typedef pair<long, long> pairs;

int main(int argc, char const *argv[])
{
  long sdist = 9999999999;

  pairs currentPos = make_pair(0, 0);
  map<pairs, long> positions;
  long steps = 0;

  char direction;
  long magnitude;

  int s = -1;

  while (cin >> direction)
  {
    if (direction != ',')
    {
      currentPos = make_pair(0, 0);
      steps = 0;
      s++;
    }
    else
    {
      cin >> direction;
    }
    cin >> magnitude;
    for (int i = 0; i < magnitude; i++)
    {
      if (direction == 'L')
      {
        currentPos.first -= 1;
      }
      else if (direction == 'R')
      {
        currentPos.first += 1;
      }
      else if (direction == 'U')
      {
        currentPos.second += 1;
      }
      else if (direction == 'D')
      {
        currentPos.second -= 1;
      }
      steps++;
      if (s == 0)
      {
        if (positions.find(currentPos) == positions.end())
        {
          positions[currentPos] = steps;
        }
      }
      else if (positions.find(currentPos) != positions.end())
      {
        if (positions[currentPos] + steps < sdist)
        {
          sdist = positions[currentPos] + steps;
        }
      }
    }
  }

  cout << sdist << endl;

  return 0;
}
