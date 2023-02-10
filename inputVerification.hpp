#include <iostream>
#include <limits>
#include <string>
using namespace std;

int verifyInputs(string message)
{
  int i;
  cout << message;
  while (true){
    cin >> i;
    if (!cin)
    {
      cout << "Wrong Choice. Enter again " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    else break;
  }
  return i;
}