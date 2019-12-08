#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{

  long width = 25;
  long height = 6;
  long layers[150][width * height];

  char c;
  long index = 0;
  long layercount = -1;

  while (cin >> c)
  {
    long num = c - '0';

    if (index == 0)
    {
      layercount++;
    }

    layers[layercount][index] = num;

    index = (index + 1) % (width * height);
  }

  for (int i = 0; i < width * height; i++)
  {
    long val;
    long j = 0;

    while (layers[j][i] == 2)
    {
      j++;
    }

    if (j > layercount)
    {
      val = 2;
    }
    else
    {
      val = layers[j][i];
    }

    if (val == 1)
    {
      cout << 'X';
    }
    else
    {
      cout << '.';
    }

    if (i % width == width - 1)
    {
      cout << endl;
    }
  }

  cout << endl;

  return 0;
}
