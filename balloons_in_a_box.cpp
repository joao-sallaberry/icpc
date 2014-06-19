#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define BALLOON_MAX 6
# define PI 3.14159265358979323846

class Point {
public:
  int x, y, z;

  Point() : x(0), y(0), z(0) {}
  Point(int x, int y, int z) : x(x), y(y), z(z) {}
  void setPoint(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  static inline int squared_distance(const Point &a, const Point &b) {
	return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
  }

  static inline double distance(const Point &a, const Point &b) {
	return (sqrt(squared_distance(a,b)));
  }
};

bool operator< (const Point &a, const Point &b) {
  if (a.x != b.x)
    return (a.x < b.x);
  if (a.y != b.y)
    return (a.y < b.y);
  return (a.z < b.z);
}

std::ostream & operator<< (std::ostream & output, const Point & p) {
  output << p.x << " " << p.y << " " << p.z;
  return output;
}

int n_points;
Point corner1, corner2;
Point balloons[BALLOON_MAX];
double rays[BALLOON_MAX];

inline void swap(int *a, int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

bool is_in_box(Point p) {
  if (p.x > corner1.x && p.x < corner2.x &&
      p.y > corner1.y && p.y < corner2.y &&
      p.z > corner1.z && p.z < corner2.z)
    return true;
  return false;
}

double inflate(Point p) {
  double ray, tmp;

  ray = corner2.x - p.x;
  tmp = corner2.y - p.y;
  if (tmp < ray) ray = tmp;
  tmp = corner2.z - p.z;
  if (tmp < ray) ray = tmp;

  tmp = p.x - corner1.x;
  if (tmp < ray) ray = tmp;
  tmp = p.y - corner1.y;
  if (tmp < ray) ray = tmp;
  tmp = p.z - corner1.z;
  if (tmp < ray) ray = tmp;

  for (int i = 0; i < n_points; i++)
    if (rays[i]) {
      double dist = Point::distance(p, balloons[i]);
      if (dist <= rays[i])
        return 0.0; // p is inside another balloon
      if (ray > dist - rays[i])
        ray = dist - rays[i];
    }

  return ray;
}

int main() {
  int case_count = 0;
  double d_volume;
  int i_volume;

  cin >> n_points;
  while (n_points > 0) {
    int x1, y1, z1, x2, y2, z2;
    cin >> x1 >> y1 >> z1;
    cin >> x2 >> y2 >> z2;
    if (x2 < x1) swap(&x1, &x2);
    if (y2 < y1) swap(&y1, &y2);
    if (z2 < z1) swap(&z1, &z2);
    corner1.setPoint(x1, y1, z1);
    corner2.setPoint(x2, y2, z2);
#ifndef ONLINE_JUDGE
    cout << corner1 << endl << corner2 << endl;
#endif
    for (int i = 0; i < n_points; i++) {
      cin >> x1 >> y1 >> z1;
      balloons[i] = Point(x1, y1, z1);
    }
    sort(balloons, balloons + n_points);
    
    do {
      memset(rays, 0, sizeof rays);
      double trial_volume = 0;

      for (int i = 0; i < n_points; i++) {
	if (is_in_box(balloons[i]))
          rays[i] = inflate(balloons[i]); //TODO optimize: compare sum of rays to avoid volume calculation
        trial_volume += 4 * PI * rays[i] * rays[i] * rays[i] / 3;
#ifndef ONLINE_JUDGE
        cout << rays[i] << " ";
#endif
      }
#ifndef ONLINE_JUDGE
      cout << endl;
#endif
      if (trial_volume > d_volume)
	d_volume = trial_volume;
    } while (next_permutation(balloons, balloons + n_points));
      
    // get box volume and round result
    d_volume = (corner2.x - corner1.x) * (corner2.y - corner1.y) * (corner2.z - corner1.z) - d_volume;
    i_volume = (int)d_volume;
    d_volume -= i_volume;
    if (d_volume > 0.5) i_volume++;

    cout << "Box " << ++case_count << ": " << i_volume << endl << endl;

    cin >> n_points;
  }

  return 0;
}
