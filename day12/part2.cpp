#include <iostream>
#include <sstream>
#include <set>
#include <vector>

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
  long iterations = 500000;
  vector<vector<vector<short>>> ipositions(iterations + 1);
  vector<vector<vector<short>>> ivelocities(iterations + 1);
  // short itervelocities[iterations + 1][4][3];
  // short iterpositions[iterations + 1][4][3];
  short iterengtot[iterations - 1];
  long positions[4][3];
  long velocities[4][3];

  set<string> velocity_set;

  ivelocities[0].resize(4);
  ipositions[0].resize(4);

  for (int i = 0; i < 4; i++)
  {
    ivelocities[0][i].resize(3);
    ipositions[0][i].resize(3);
    long x, y, z;
    char c;
    x = next_long();
    y = next_long();
    z = next_long();

    positions[i][0] = x;
    positions[i][1] = y;
    positions[i][2] = z;

    // iterpositions[0][i][0] = x;
    // iterpositions[0][i][1] = y;
    // iterpositions[0][i][2] = z;

    ipositions[0][i][0] = x;
    ipositions[0][i][1] = y;
    ipositions[0][i][2] = z;

    velocities[i][0] = 0;
    velocities[i][1] = 0;
    velocities[i][2] = 0;

    // itervelocities[0][i][0] = 0;
    // itervelocities[0][i][1] = 0;
    // itervelocities[0][i][2] = 0;

    ivelocities[0][i][0] = 0;
    ivelocities[0][i][1] = 0;
    ivelocities[0][i][2] = 0;

    cin >> c;
  }

  long time = 0;

  while (time++ < iterations)
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
    ipositions[time].resize(4);
    ivelocities[time].resize(4);

    for (int i = 0; i < 4; i++)
    {
      ipositions[time][i].resize(3);
      ivelocities[time][i].resize(3);
      for (int j = 0; j < 3; j++)
      {
        positions[i][j] += velocities[i][j];
        // iterpositions[time][i][j] = positions[i][j];
        // itervelocities[time][i][j] = velocities[i][j];

        ipositions[time][i][j] = positions[i][j];
        ivelocities[time][i][j] = velocities[i][j];
      }
    }
  }

  iterations = iterations - 2;

  long velpattern[4][3];

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      velpattern[i][j] = -1;
    }
  }

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      int k = 1;
      int prev = 0;

      while (k < iterations)
      {
        if (ivelocities[k][i][j] == ivelocities[0][i][j] && ipositions[k][i][j] == ipositions[0][i][j])
        {
          cout << k - prev << " ";
          prev = k;
        }
        k++;
      }

      cout << endl;
    }
  }

  // for (int size = 1; size < iterations / 3; size++)
  // {
  //   bool match = true;

  //   for (int i = 0; i < size && match; i++)
  //   {
  //     for (int j = 0; j < 4 && match; j++)
  //     {
  //       if (iterengtot[j * size + i] != iterengtot[(j + 2) * size - 1 - i])
  //       {
  //         match = false;
  //       }
  //     }
  //   }

  //   if (match)
  //   {
  //     cout << size << endl;
  //     break;
  //   }
  // }

  // for (int i = 0; i < 4; i++)
  // {
  //   for (int j = 0; j < 3; j++)
  //   {
  //     for (int size = 1; size < iterations / 4; size++)
  //     {
  //       bool match = false;
  //       for (int offset = 0; offset < size && !match; offset++)
  //       {
  //         match = true;
  //         int sections = 4;
  //         if (size > 100)
  //         {
  //           sections = 2;
  //         }
  //         for (int k = 0; k < sections && match; k++)
  //         {
  //           for (int l = 0; l < size && match; l++)
  //           {
  //             if (iterpositions[iterations - (k * size) - l - offset][i][j] != iterpositions[iterations - ((k + 2) * size) + l + 1 - offset][i][j])
  //             {
  //               match = false;
  //             }
  //           }
  //         }
  //         if (match)
  //         {
  //           velpattern[i][j] = size;
  //           break;
  //         }
  //       }

  //       if (match)
  //       {
  //         break;
  //       }
  //     }
  //   }
  // }

  // for (int i = 0; i < 4; i++)
  // {
  //   for (int j = 0; j < 3; j++)
  //   {
  //     cout << velpattern[i][j] << endl;
  //   }
  // }

  return 0;
}
