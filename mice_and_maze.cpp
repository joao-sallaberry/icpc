#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define _DEBUG

#define CELL_MAX 101

unsigned int cells, exit_cell, timer;
unsigned int dist[CELL_MAX][CELL_MAX];


unsigned int dijkstra(unsigned int entry) {
  unsigned int min_dist[CELL_MAX];

  memset(min_dist, -1, CELL_MAX);
  min_dist[entry] = 0;

  // group of unvisited cells
  set<unsigned int> cells_not_visited;
  for (unsigned int i = 1; i < cells; i++)
    cells_not_visited.insert(i);

  while (1) {
    // get nearest unvisited cell
    unsigned int nearest_cell = 0, nearest_distance = -1;
    for (unsigned int i = 1; i < cells; i++)
      if (min_dist[i] < nearest_distance &&
          cells_not_visited.find(i) != cells_not_visited.end()) {
        nearest_cell = i;
        nearest_distance = min_dist[i];
      }
    if (nearest_cell == exit_cell) {
#ifdef _DEBUG
      cout << "rat in cell " << entry << " : " << nearest_distance << endl;
#endif
      return nearest_distance;
    }

    // visit this cell
    for (unsigned int i = 1; i < cells; i++)
      if (min_dist[nearest_cell] + dist[nearest_cell][i] < min_dist[i])
        min_dist[i] = min_dist[nearest_cell] + dist[nearest_cell][i];
    cells_not_visited.erase(nearest_cell);

  }

}


int main() {
  int cases;

  cin >> cases;
  for ( ; cases > 0; cases--) {
    unsigned int connections;
    cin >> cells >> exit_cell >> timer >> connections;

    memset(dist, -1, CELL_MAX*CELL_MAX); // set infinite distance

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
