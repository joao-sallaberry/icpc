#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <utility> 

using namespace std;

#define MAX_DIM 40

class line {
public:
  line() {}

  void append(char c, int x, int y) {
    str.append(string(1, c));
    pos.push_back(pair<int,int>(x,y));
  }

  string str;
  vector<pair<int, int>> pos;
};


vector<string> words;
char table[MAX_DIM][MAX_DIM];
vector<line> lines;


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
      word = string (word.rbegin(), word.rend());
      words.push_back(word);
    }

    // table
    for (int i = 0; i < r; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < c; j++) {
	//l.append(s.at(j), i, j);
	//lines.push_back(s);
	table[i][j] = s.at(j);
      }
    }

    // rows
    for (int i = 0; i < r; i++) {
      line l;
      for (int j = 0; j < c; j++)
	l.append(table[i][j], i, j);
      lines.push_back(l);
    }

    // columns
    for (int i = 0; i < c; i++) {
      line l;
      for (int j = 0; j < r; j++)
        l.append(table[j][i], j, i);
      lines.push_back(l);
    }

    // diags
    for (int i = 0; i < r; i++) {
      line l;
      for (int x = i, y = 0; x < r && y < c; x++, y++)
	l.append(table[x][y], x, y);
      lines.push_back(l);
    }
    for (int i = 1; i < c; i++) {
      line l;
      for (int x = 0, y = i; x < r && y < c; x++, y++)
 	l.append(table[x][y], x, y);
      lines.push_back(l);
    }

    // opp diags
    for (int i = 0; i < r; i++) {
      line l;
      for (int x = i, y = c-1; x < r && y >= 0; x++, y--)
	l.append(table[x][y], x, y);
      lines.push_back(l);
    }
    for (int i = c-1-1; i >= 0; i--) {
      line l;
      for (int x = 0, y = i; x < r && y >= 0; x++, y--)
 	l.append(table[x][y], x, y);
      lines.push_back(l);
    }

    // search lines
    for (auto l : lines)
      for (auto w : words) {
	size_t pos = 0;
	while (1) {
	  pos = l.str.find(w, pos);
	  if (pos == string::npos)
	    break;
	  for (int j = 0; j < w.length(); j++) {
	    table[get<0>(l.pos[pos+j])] [get<1>(l.pos[pos+j])] = 0;
	  }
	  if (pos < l.str.length()-1) pos++;
	  else break;
	}
      }
    
    //for (auto a : lines)
    //cout << a.str << endl;

    // print
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
	if (table[i][j])
	  cout << table[i][j];
    cout << endl;
    
    r = 0;
  }

  return 0;
}
