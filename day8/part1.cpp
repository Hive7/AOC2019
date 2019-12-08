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

    cout << layercount << " " << index << " " << layers[layercount][index] << endl;

    index = (index + 1) % (width * height);
  }

  long minzero = width * height + 1;
  long zeroindex = 0;

  for (int i = 0; i <= layercount; i++)
  {
    long zero = 0;

    for (int j = 0; j < width * height; j++)
    {
      if (layers[i][j] == 0)
      {
        zero++;
      }
    }

    if (zero < minzero)
    {
      minzero = zero;
      zeroindex = i;
    }
  }

  cout << minzero << " " << zeroindex << endl;

  long ones = 0;
  long twos = 0;

  for (int j = 0; j < width * height; j++)
  {
    if (layers[zeroindex][j] == 1)
    {
      ones++;
    }
    if (layers[zeroindex][j] == 2)
    {
      twos++;
    }
  }

  cout << ones * twos << endl;

  return 0;
}
