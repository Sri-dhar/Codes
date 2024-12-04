#include <iostream>
#include <string>
using namespace std;

bool endsAtStart(const string &path) {
  int x = 0, y = 0; // Starting coordinates

  for (char dir : path) {
    if (dir == 'N')
      y++; // Move North, increase y
    else if (dir == 'S')
      y--; // Move South, decrease y
    else if (dir == 'E')
      x++; // Move East, increase x
    else if (dir == 'W')
      x--; // Move West, decrease x
  }

  // Check if back at starting point
  return x == 0 && y == 0;
}

int main() {
  int P;
  cin >> P;
  cin.ignore(); // Ignore newline after P

  for (int i = 0; i < P; i++) {
    string path;
    getline(cin, path); // Read each path

    if (endsAtStart(path))
      cout << "true" << endl;
    else
      cout << "false" << endl;
  }

  return 0;
}
