#include <string>
#include <vector>

using namespace std;

#define UNIQ_ID1(lineno) var_## lineno
#define UNIQ_ID2(lineno) UNIQ_ID1(lineno)

#define UNIQ_ID UNIQ_ID2(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4}; 
}