#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[])
{
  vector<vector<int>> grid;
  string line;
  int width = 0;

  while (cin >> line)
  {
    if (width == 0)
    {
      width = line.size();
    }
    char c;
    stringstream sstream(line);
    vector<int> items;

    while (sstream >> c)
    {
      if (c == '.')
      {
        items.push_back(0);
      }
      else
      {
        items.push_back(1);
      }
    }

    grid.push_back(items);
  }

  int maxcount = 0;
  int max_x = 0;
  int max_y = 0;

  for (int y = 0; y < grid.size(); y++)
  {
    for (int x = 0; x < width; x++)
    {
      if (grid[y][x] == 0)
      {
        continue;
      }
      int count = 0;

      for (int y1 = 0; y1 < grid.size(); y1++)
      {
        for (int x1 = 0; x1 < width; x1++)
        {
          if (grid[y1][x1] == 0 || (y == y1 && x == x1))
          {
            continue;
          }

          bool blocked = false;

          if (x1 == x)
          {
            int miny = min(y1, y) + 1;
            int maxy = max(y1, y);
            for (; miny < maxy; miny++)
            {
              if (grid[miny][x])
              {
                blocked = true;
                break;
              }
            }
          }
          else if (y1 == y)
          {
            int minx = min(x1, x) + 1;
            int maxx = max(x1, x);
            for (; minx < maxx; minx++)
            {
              if (grid[y][minx])
              {
                blocked = true;
                break;
              }
            }
          }
          else
          {
            double gradient = (y1 - y) / (double)(x1 - x);
            double c = y - gradient * x;

            int i = min(x1, x) + 1;
            int j = max(x1, x);

            for (; i < j; i++)
            {
              double doubley = gradient * i + c;
              int y2 = round(doubley);

              if (fabs(y2 - doubley) < 0.02 && grid[y2][i])
              {
                blocked = true;
                break;
              }
            }
          }

          if (!blocked)
          {
            count++;
          }
        }
      }

      if (x == 5 && y == 8)
      {
        cout << count << endl;
      }

      if (count > maxcount)
      {
        max_x = x;
        max_y = y;
        maxcount = count;
      }
    }
  }

  cout << maxcount << endl;
  cout << max_x << " " << max_y << endl;

  return 0;
}
