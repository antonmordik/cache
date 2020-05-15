#include "Algorithm.h"
#include <algorithm>

void Algorithm::blockedFloydWarshal() {
  // TODO: implement algorithm
}

void Algorithm::traditionalFloydWarshal(int** matrix, int numberOfVert) {
  // TODO: add multithreading for cycle iterations
  for (int k = 0; k < numberOfVert; k++) {
    for (int i = 0; i < numberOfVert; i++) {
      for (int j = 0; j < numberOfVert; j++) {
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }

  return;
}
