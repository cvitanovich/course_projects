#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// TABLE: matrix of split locations ('N' means could not split, 'Y' means could split, 'U' untried)
vector<vector<char> > SplitTable;

struct Dict {
  map<string,int> keys;
  int longest;
  int count;
};

// the dictionary
Dict D;

// initialize matrix
void initSplitMatrix( int SIZE )
{
    SplitTable.resize( SIZE );
    for( int i = 0; i < SIZE; ++i ) {
        SplitTable[i].resize( SIZE );
    }
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
          SplitTable[i][j] = 'U';
        }
    }
}

// bool searchDict(string ss) {
//   if(D.longest < ss.length())
//     return false; // impossible since no dictionary element of this length
//   int cmp = 0;
//   for(vector<string>::iterator it = D.keys.begin(); it != D.keys.end(); ++it) {
//     cmp = ss.compare(*it);
//     if(cmp == 0)
//       return true;
//     if(cmp < 0)
//       return false;
//   }
//   return false;
// }


// bool iterativeSplit(Dict D, string ss) {
//   int n = ss.length();
//
//   // matrix of found words
//   vector<vector<bool> > results(n);
//   for ( int k = 0 ; k < n ; k++ )
//       results[k].resize(n);
//   for (int r = 0; r < n; ++r) {
//     for (int c = 0; c < n; ++c) {
//       results[r][c] = false;
//     }
//   }
//
//   // find all words at the beginning of the string
//   // note: zeroth word is a word that begins at first character
//   string str;
//   for(int word = 0; word < n; ++word) {
//     for(int i = 0; i < n; ++i) {
//       // did a previously discovered word end just before this index?
//       if(word == 0 || ((i > 0) && results[word-1][i-1])) {
//         // if so find the possible next words
//         for(int j = 0; j < n; ++j) {
//           str = ss.substr(i,j-i);
//           // is there a next word that ends at j?
//           if(searchDict(str)) {
//             results[word][j] = true;
//             if(j == (n - 1))
//               return true;
//           }
//         }
//       }
//     }
//   }
//
//   return false;
// }

// recursive memoized version
// to call initially use i = 0 and ss = the entire string
bool recursiveSplit(int i, string ss) {

  int n = ss.length();
  string str;
  bool searchResult;
  bool recurseResult;
  bool flag = false;

  if(i == n)
    flag = true;

  // loop indices until a good split is found
  for(int j=i; j<n; ++j) {

    // check if this split has been tested yet (avoids duplicate processing)
    if(SplitTable[i][j] == 'U') {

      str = ss.substr(i,j-i+1);

      // if splittable at index j save this:
      searchResult = (D.keys.find(str) != D.keys.end());
      recurseResult = recursiveSplit(j+1, ss);
      if(searchResult && recurseResult) {
        SplitTable[i][j] = 'Y';
      } else {
        SplitTable[i][j] = 'N'; // could not split here
      }

    }

    if(SplitTable[i][j] == 'Y')
      flag = true;

  }

  return flag; // no split found for any j=i...n-1

}

// print a splitting that was found
void printSplit(string ss) {
  int i = 0;
  int j = 0;
  int n = ss.size();
  while(j < n) {
    if(SplitTable[i][j] == 'Y') {
     cout << ss.substr(i,j-i+1) << " ";
     i=j+1;
     j=i;
    } else {
      j++;
    }
  }
  cout << endl;
}

// main
int main() {

  // setup dictionary data
  ifstream dfile;
  dfile.open("diction10k.txt");
  D.longest = 0;
  string temp;
  if (!dfile.is_open()) {
    cout << "Could not open dictionary file!" << endl;
  } else {
    map<string,int> m; // storing in c++ ordered map (hashing)
    while(dfile >> temp) {
      if(temp.length() > D.longest)
        D.longest = temp.length();
      m[temp] = 1;
    }
    D.keys = m;
  }
  dfile.close();

  // loop through input data and process

  int count;
  string input;
  cin >> count;
  string NO("NO, cannot be split");
  string YES("YES, can be split");
  string result;
  bool flag;

  for(int i = 0; i < count; ++i) {

    cout << "phrase number: " << i+1 << endl;

    // get the input phrase
    cin >> input;

    // resize/initialize Split matrix
    initSplitMatrix(input.length());

    // print the input
    cout << input << endl;

    // iterative attempt:
    cout << endl << "iterative attempt:" << endl;
    //iterativeSplit(D,input) ? (result = YES) : (result = NO);
    //cout << result << endl;

    // memoized attempt:
    cout << endl << "memoized attempt:" << endl;
    flag = recursiveSplit(0,input);
    flag ? (result = YES) : (result = NO);
    cout << result << endl;
    if(flag)
      printSplit(input);

    // extra empty line;
    cout << endl;

  }

  return 0;
}
