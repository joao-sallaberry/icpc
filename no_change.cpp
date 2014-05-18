#include <iostream>
#include <algorithm>

using namespace std;

vector<int> coins;

bool can_pay(int value, int coin, int can_use) {
    //no more coin types left
    if (coin >= coins.size())
	return false;
    
    // can pay with this coin
    int coin_value = coins[coin];
    if (value%coin_value == 0 && can_use >= value/coin_value)
	return true;

    // pay the rest with other coins
    int max_use = min(value/coin_value, can_use);
    for ( ; max_use > 0; max_use--) {
	if (can_pay(value - max_use * coin_value, coin + 1, max_use))
	    return true;
    }
    
    return false;
}

int main() {
    int cases;
    int value, coin_types;

    cin >> cases;
    for ( ; cases > 0; cases--) {
	cin >> value >> coin_types;
	
	for ( ; coin_types > 0; coin_types--) {
	    int tmp;
	    cin >> tmp;
	    coins.push_back(tmp);
	}

	if (can_pay(value, 0, 100000))
	    cout << "YES" << endl;
	else
	    cout << "NO" << endl;
	cout << endl;
	
    }
    
    return 0;
}
