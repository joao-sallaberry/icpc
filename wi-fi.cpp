#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_HOUSES   100000
#define MAX_NUMBERS 1000000

int aps, houses;
int house_numbers[MAX_HOUSES];

bool check_with_distance(int min_dist) {
  int aps_left = aps;
  int current_dist = house_numbers[0];
  int current_house = 0;
  
  while (1) {
    current_dist += 2 * min_dist;
    aps_left--;
    while (house_numbers[current_house] <= current_dist) {
      if (current_house >= (houses-1))
	return true;
      current_house++;
    }
    current_dist = house_numbers[current_house];
    if (!aps_left)
      return false;
  }
  
}

int main() {
  int cases;

  cin >> cases;
  while (cases--) {
    cin >> aps >> houses;
    for (int i = 0; i < houses; i++)
      cin >> house_numbers[i];
    sort (house_numbers, house_numbers + houses);
    //TODO if more aps than houses
    int min = 0;
    int max = MAX_NUMBERS;
    int mean;
    while (max - min > 1) {
      mean = (max + min) / 2;
#ifndef ONLINE_JUDGE
      cout << "test " << max << " " << min <<  endl; 
#endif
      check_with_distance(mean) ? max = mean : min = mean;
    }

    cout << max << endl;

  }

  return 0;
}
