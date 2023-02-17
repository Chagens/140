#include <string>
#include <list>
#include <vector>
using namespace std;

class candyCrush {
public:
  candyCrush(const string &inputFile);
  int getRowLength() const;
  int getScore() const;
  void printCandy() const;
  int play(int choice);		
protected:
  list<string> candy;
  vector<string> flavors;
  vector<int> points;
  vector<int> probabilities;
  int score;
  int rowLength;
};
