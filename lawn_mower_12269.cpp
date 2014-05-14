#include <iostream>
#include <algorithm>

using namespace std;

int nx;
int ny;
double w;
double halfw;
double px[1000];
double py[1000];


bool check() {
  double curr_p = 0.0;
  for (int i = 0; i < nx; i++) {
    if (curr_p >= px[i] - halfw) {
      curr_p = px[i] + halfw;
      //cout << curr_p << endl;
    }
    else
      return false;
  }
  if (curr_p < 75.0)
    return false;

  curr_p = 0.0;
  for (int i = 0; i < ny; i++) {
    if (curr_p >= py[i] - halfw)
      curr_p = py[i] + halfw;
    else
      return false;
  }
  if (curr_p < 100.0)
    return false;

  return true;
}

int main() {

  while (1) {
    cin >> nx >> ny >> w;
    if (nx == 0 && ny == 0 && w == 0.0)
      return 0;

    for (int i = 0; i < nx; i++)
      cin >> px[i];
    for (int i = 0; i < ny; i++)
      cin >> py[i];

    halfw = w/2;
    sort(px, px+nx);
    sort(py, py+ny);

    for (int i = 0; i < nx; i++)
      cout >> px[i];
    for (int i = 0; i < ny; i++)
      cout >> py[i];

    cout << endl;
    if(check())
      cout << "YES";
    else
      cout << "NO";
  }

  return 0;
}
