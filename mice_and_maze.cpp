#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define CELL_MAX 101

unsigned int cells, exit_cell, timer;
unsigned int dist[CELL_MAX][CELL_MAX];
unsigned int min_dist[CELL_MAX];

unsigned int dijkstra(unsigned int entry) {
  min_dist[entry] = 0;

  vector<unsigned int> cells_not_checked;
  for (unsigned int i = 1; i < cells; i++)
    cells_not_checked.push_back(i);

  for (unsigned int i = 1; i < cells; i++)
    if (dist[entry][i] < min_dist[i])
      min_dist[i] = dist[entry][i];

  while() {
    // get shortest node
    unsigned int shortest_cell = 0, shortest_distance = -1;
    for (unsigned int i = 1; i < cells; i++)
      if(min_dist[i] < shortest_distance) {
        shortest_cell = i;
        shortest_distance = dist[entry][i];
      }

    for (unsigned int i = 1; i < cells; i++)
      if (dist[shortest_cell][i] < min_dist[i])
        min_dist[i] = dist[entry][i];


  }

}


int main() {
  int cases;

  cin >> cases;
  for ( ; cases > 0; cases--) {
    unsigned int connections;
    cin >> cells >> exit_cell >> timer >> connections;

    memset(dist, -1, CELL_MAX*CELL_MAX); // set infinity distance
    memset(min_dist, -1, CELL_MAX);

    for ( ; connections > 0; connections--) {
      unsigned int a, b, distance;
      cin >> a >> b >> distance;
      dist[a][b] = distance;
    }

    unsigned int successes = 0;
    for (unsigned int i = 1; i <= cells; i++)
      if (dijkstra(i) <= timer)
        successes++;

    cout << successes << endl;

  }

  return 0;
}
