#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstdio>

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


vector<int> KMP(string S, string K) {
  vector<int> T(K.size() + 1, -1);
  vector<int> matches;
  
  if (K.size() == 0) {
    matches.push_back(0);
    return matches;
  }
  for (int i = 1; i <= K.size(); i++) {
    int pos = T[i - 1];
    while (pos != -1 && K[pos] != K[i - 1])
      pos = T[pos];
    T[i] = pos + 1;
  }
  
  int sp = 0;
  int kp = 0;
  while (sp < S.size()) {
    while (kp != -1 && (kp == K.size() || K[kp] != S[sp]))
      kp = T[kp];
    kp++;
    sp++;
    if(kp == K.size())
      matches.push_back(sp - K.size());
  }
  
  return matches;
}


int main() {
  int r, c, k; // n=r(ows), m=c(olumns)
  
  while (1) {
    scanf("%d %d", &r, &c);
    scanf("%d", &k);

    if (!r)
      break;
    
    for (int i = 0; i < k; i++) {
      string word;
      cin >> word;
      //scanf("%s", word);
      words.push_back(word);
      word = string (word.rbegin(), word.rend());
      words.push_back(word);
    }

    // table
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
	char c;
	scanf(" %c", &c);
	table[i][j] = c;
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

    // search
    for (auto l : lines)
      for (auto w : words) {
	vector<int> founds = KMP(l.str, w);
	for (auto f : founds)
	  for (int j = 0; j < w.length(); j++)
	    table[get<0>(l.pos[f+j])] [get<1>(l.pos[f+j])] = 0;
      }
    
    //for (auto a : lines)
    //cout << a.str << endl;

    // print
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
	if (table[i][j])
	  printf("%c", table[i][j]);
    printf("\n");
    
    r = 0;
  }

  return 0;
}
