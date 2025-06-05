#include <cstddef>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

template <typename T> 
class Deque {
    vector<T> f_deque, b_deque;

    void CheckIndex(size_t i) const {
        if (i >= Size())
        throw out_of_range("Index is out of range");
    }

public:
    Deque() = default;

    bool Empty() const { return f_deque.empty() && b_deque.empty(); }

    size_t Size() const { return f_deque.size() + b_deque.size(); }

    void Clear() { f_deque.clear(); b_deque.clear();}

    
    const T& operator[] (size_t index) const { 
        return index < f_deque.size() ? f_deque[f_deque.size() - index - 1] : b_deque[index - f_deque.size()]; 
    }

    T& operator[] (size_t index) { 
        return index < f_deque.size() ? f_deque[f_deque.size() - index - 1] : b_deque[index - f_deque.size()]; 
    }

    const T& At(size_t index) const {
       CheckIndex(index);
       return (*this)[index];
    }

    T& At(size_t index) {
       CheckIndex(index);
       return (*this)[index];
    }

    const T& Front() const { return f_deque.empty() ? b_deque.front() : f_deque.back(); }
    T& Front() { return f_deque.empty() ? b_deque.front() : f_deque.back(); }

    const T& Back() const { return b_deque.empty() ? f_deque.front() : b_deque.back(); }
    T& Back() { return b_deque.empty() ? f_deque.front() : b_deque.back(); }

    void PushFront(const T& item) { f_deque.push_back(item);  } 
    void PushBack(const T& item) { b_deque.push_back(item); } 

};

int main(){

    return 0;
}
