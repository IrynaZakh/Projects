#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
public: 
    Table(size_t rows, size_t cols) {
        Resize(rows, cols);
    }

    const vector<T>& operator [] (size_t idx) const {
        return v_data[idx];
    }
    vector<T>& operator [] (size_t idx) {
        return v_data[idx];
    }

    void Resize(size_t rows, size_t cols) {
        v_data.resize(rows);
        for (auto& row : v_data) {
            row.resize(cols);
        }
    }

    pair<size_t, size_t> Size() const {
        return {v_data.size(),(v_data.empty() ? 0 : v_data[0].size())};
    }

private:
    vector<vector<T>> v_data;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}