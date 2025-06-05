#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate();
    T* TryAllocate();

    void Deallocate(T* object);

    ~ObjectPool();

private:
    set<T*> allocated_objs;
    queue<T*> released_objs;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
    if (released_objs.empty()) {
        released_objs.push(new T);
    }
    auto ret = released_objs.front();
    released_objs.pop();
    allocated_objs.insert(ret);
    return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
    if (released_objs.empty()) {
        return nullptr;
    }
    return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
    if (allocated_objs.find(object) == allocated_objs.end()) {
        throw invalid_argument("");
    }
    allocated_objs.erase(object);
    released_objs.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
    for (auto x : allocated_objs) {
        delete x;
    }
    while (!released_objs.empty()) 
    {
        auto x = released_objs.front();
        released_objs.pop();
        delete x;
    }
}

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
