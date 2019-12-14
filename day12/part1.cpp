#include <iostream>
#include <sstream>
#include <set>

using namespace std;

long next_long()
{
  string str;
  set<char> nums;
  nums.insert('0');
  nums.insert('1');
  nums.insert('2');
  nums.insert('3');
  nums.insert('4');
  nums.insert('5');
  nums.insert('6');
  nums.insert('7');
  nums.insert('8');
  nums.insert('9');
  nums.insert('-');
  char c;
  long val;

  cin >> str;

  stringstream sstream(str);

  while (!sstream.eof())
  {
    char n = sstream.peek();

    if (nums.find(n) == nums.end())
    {
      sstream >> c;
    }
    else
    {
      sstream >> val;
      return val;
    }
  }

  return 0;
}

int main(int argc, char const *argv[])
{
  long positions[4][3];
  long velocities[4][3];

  for (int i = 0; i < 4; i++)
  {
    long x, y, z;
    char c;
    x = next_long();
    y = next_long();
    z = next_long();

    positions[i][0] = x;
    positions[i][1] = y;
    positions[i][2] = z;

    velocities[i][0] = 0;
    velocities[i][1] = 0;
    velocities[i][2] = 0;

    cin >> c;
  }

  long time = 0;

  while (time++ < 100000)
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = i + 1; j < 4; j++)
      {
        for (int k = 0; k < 3; k++)
        {
          if (positions[i][k] == positions[j][k])
          {
            continue;
          }
          if (positions[i][k] < positions[j][k])
          {
            velocities[i][k]++;
            velocities[j][k]--;
          }
          else
          {
            velocities[i][k]--;
            velocities[j][k]++;
          }
        }
      }
    }

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        positions[i][j] += velocities[i][j];
      }
    }
  }

  long engtot = 0;

  for (int i = 0; i < 4; i++)
  {
    long pottot = 0;
    long kintot = 0;

    for (int j = 0; j < 3; j++)
    {
      pottot += abs(positions[i][j]);
      kintot += abs(velocities[i][j]);
    }

    engtot += pottot * kintot;
  }

  cout << engtot << endl;

  return 0;
}
