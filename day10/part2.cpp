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

  int totalcount = 0;

  while (totalcount == 0)
  {
    int count = 0;
    vector<int> xcoords;
    vector<int> ycoords;
    int x = 11;
    int y = 11;

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
        else
        {
          if (y1 < y && x1 < x && (y1 - y) / (double)(x1 - x) >= 2)
          {
            continue;
          }
          double gradient = (y1 - y) / (double)(x1 - x);
          double c = y - gradient * x;

          int i = min(x1, x) + 1;
          int j = max(x1, x);

          for (; i < j; i++)
          {
            double doubley = gradient * i + c;
            int y2 = round(doubley);

            if (fabs(y2 - doubley) == 0 && grid[y2][i])
            {
              blocked = true;
              break;
            }
          }
        }

        if (!blocked)
        {
          xcoords.push_back(x1);
          ycoords.push_back(y1);
          count++;
        }
      }
    }
    totalcount += count;

    cout << totalcount << endl;

    for (int i = 0; i < xcoords.size(); i++)
    {

      if (totalcount >= 200)
      {
        if (ycoords[i] < y && xcoords[i] < x && (ycoords[i] - y) / (double)(xcoords[i] - x) >= 1.5)
        {
          cout << (ycoords[i] - y) / (double)(xcoords[i] - x) << endl;
          cout << xcoords[i] << " " << ycoords[i] << endl;
        }
      }
      grid[ycoords[i]][xcoords[i]] = 0;
    }
  }

  return 0;
}
