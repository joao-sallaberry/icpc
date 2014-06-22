#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

#define MAX_DIM 40

vector<string> words;
bool table[40][40];
string rows[MAX_DIM];
string columns[MAX_DIM];

int main() {
  int r, c, k; // n=r(ows), m=c(olumns)
  
  while (1) {
    cin >> r >> c >> k;
    
    if (!r)
      break;
    
    for (int i = 0; i < k; i++) {
      string word;
      cin >> word;
      words.push_back(word);
      //tekst = string ( tekst.rbegin(), tekst.rend() );
    }

    //memset(rows, 0, sizeof rows);
    //memset(columns, 0, sizeof columns);
    memset(table, false, sizeof table);

    for (int i = 0; i < r; i++)
      cin >> rows[i];

    for (int i = 0; i < c; i++)
      for (int j = 0; j < r; j++) {
	columns[i].append(string(1, rows[j].at(i)));
      }

    //cout << columns[5] << endl;

    for (int i = 0; i < r; i++)
      for (auto a : words) {
	size_t pos = 0;
	while (1) {
	  pos = rows[i].find(a, pos);
	  if (pos == string::npos)
	    break;
	  for (int j = 0; j < a.length(); j++) {
	    table[i][pos+j] = true;
	    //cout << "score1" << endl;
	  }
	  if (pos < c-1) pos++;
	  else break;
	}
      }


    // print
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
	//cout << table[i][j];
    if (!table[i][j])
	cout << rows[i].at(j);
    cout << endl;

    r = 0;
  }

  return 0;
}
