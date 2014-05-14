#include <iostream>
#include <set>

using namespace std;

set<u_long> primes = {2};
u_long top_checked = 2;

inline bool is_prime(u_long n) { //TODO optimize
  for (u_long i = 2; i < n/2; i++)
    if (n%i == 0) return false;
  primes.insert(n);
  return true;
}

inline u_long find_prime_pair(u_long n, u_long a) {
  u_long b = n - a;
  if (primes.find(b) != primes.end())
    return b;
  if (is_prime(b))
    return b;
  return 0;
}

void print_answer(u_long n, u_long a, u_long b) {
  cout << n << " = " << a << " + " << b << endl;
}

int main() {
  int n;
  bool success;

  while(1) {
    cin >> n;
    if (n == 0) return 0;

    success = false;

    set<u_long>::iterator it;
    for (it = primes.begin(); *it <= n/2; ++it) {
      u_long b = find_prime_pair(n, *it);
      if (b) {
	print_answer(n, *it, b);
	success = true;
	break;
      }
    }

    if (success) continue;

    u_long i = top_checked;
    for( ; i <= n/2; i++) {//TODO skip when correct
      if(is_prime(i)) {
	top_checked = i;
	u_long b = find_prime_pair(n, i);
	if (b) {
	  print_answer(n, i, b);
	  success = true;
	  break;
	}
      }
    }

    if(!success) {
      top_checked = i - 1;
      cout << "Goldbach\'s conjecture is wrong." << endl;
    }

    //for (unsigned long i = 0; i < primes.size(); i++)
  }
  

  return 0;
}
