#include "Algorithm.h"
#include <algorithm>
#include <thread>
#include <iostream>

struct Indexes {
  int from;
  int to;
  Indexes(int from, int to) {
    this->from = from;
    this->to = to;
  };
};

std::vector<Indexes*> get_divided_indexes(Matrix* matrix) {
  std::vector<Indexes*> result;
  int matrix_size = matrix->get_size();
  int devide_count = matrix->get_number_of_cores();
  if (matrix_size < devide_count) {
    result.push_back(new Indexes(0, matrix_size - 1));
    return result;
  }
  int block_size = matrix_size / devide_count;
  for (int i = 0; i < matrix_size; i += block_size) {
    if (i + block_size - 1 < matrix_size) {
      result.push_back(new Indexes(i, i + block_size - 1));
    } else {
      result.push_back(new Indexes(i, matrix_size - 1));
      break;
    }
  }
  return result;
}

void Algorithm::blocked_floyd_warshall(Matrix* matrix) {
  // TODO: implement algorithm
}

void floyd_warshall_thread_callback(int core_id, Matrix* matrix, int start_index, int end_index) {
  try {
    for (int k = start_index; k <= end_index; k++) {
      for (int i = 0; i < (int)matrix->get_size(); i++) {
        for (int j = 0; j < (int)matrix->get_size(); j++) {
          matrix->set(
            core_id,
            i,
            j,
            std::min(
              matrix->get(core_id, i, j),
              matrix->get(core_id, i, k) + matrix->get(core_id, k, j)
            )
          );
        }
      }
    }
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

void Algorithm::traditional_floyd_warshall(Matrix* matrix, int timeout_seconds) {
  std::vector<Indexes*> indexes = get_divided_indexes(matrix);
  int core_id = 0;
  for (auto &pair: indexes) {
    int from = pair->from;
    int to = pair->to;
    auto result = std::thread(floyd_warshall_thread_callback, core_id, matrix, from, to);
    result.detach();
    core_id++;
  }
  // waiting to get right result in console output
  std::this_thread::sleep_for(std::chrono::seconds(timeout_seconds));
}
