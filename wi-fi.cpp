#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define PREC             10
#define MAX_HOUSES   100000
#define MAX_NUMBERS 1000000*PREC

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
  cout.precision(2);
  while (cases--) {
    cin >> aps >> houses;
    for (int i = 0; i < houses; i++) {
      cin >> house_numbers[i];
      house_numbers[i] *= PREC;
    }
    sort (house_numbers, house_numbers + houses);

    if (aps >= houses) {
      cout << "0.0" << endl;
      continue;
    }

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

    printf ("%.1f\n", max/(float)PREC);

  }

  return 0;
}
