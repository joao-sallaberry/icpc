#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string m_sentence;
vector<string> dict;
map<char,string> morse;

void make_morse_map() {
    morse['A'] = ".-";
    morse['B'] = "-...";
    morse['C'] = "-.-.";
    morse['D'] = "-..";
    morse['E'] = ".";
    morse['F'] = "..-.";
    morse['G'] = "--.";
    morse['H'] = "....";
    morse['I'] = "..";
    morse['J'] = ".---";
    morse['K'] = "-.-";
    morse['L'] = ".-..";
    morse['M'] = "--";
    morse['N'] = "-.";
    morse['O'] = "---";
    morse['P'] = ".--.";
    morse['Q'] = "--.-";
    morse['R'] = ".-.";
    morse['S'] = "...";
    morse['T'] = "-";
    morse['U'] = "..-";
    morse['V'] = "...-";
    morse['W'] = ".--";
    morse['X'] = "-..-";
    morse['Y'] = "-.--";
    morse['Z'] = "--..";
}

void get_sentences(int offset, string output) {
    if (offset == m_sentence.size()) {
	//cout << output << endl;
	return;
    }	

    for (char c = 'A'; c <= 'Z'; c++) {
	if (m_sentence.compare(offset, morse[c].size(), morse[c]) == 0)
	    get_sentences(offset + morse[c].size(), output + c);
    }
}


int main() {
    int cases;
    int words;

    make_morse_map();

    cin >> cases;
    for ( ; cases > 0; cases--) {
	cin >> m_sentence >> words;
	
	for ( ; words > 0; words--) {
	    string tmp;
	    cin >> tmp;
	    dict.push_back(tmp);
	}

	cout << m_sentence << endl;

	get_sentences(0, "");
	
    }

    return 0;
}
