#include <iostream>
#include <vector>
#include <cstdint>

template<typename T>
class Heap {
    private:
    std::vector<T> tree;
    void siftUp(uint64_t index) {
        if (index == 0) return;
        uint64_t par = (index - 1) / 2;
        if (tree[par] > tree[index]) {
            std::swap(tree[parent], tree[index])
            siftUp(par);
        }
    }
    void siftDown(uint64_t index) {
        uint64_t left = 2 * index + 1, right = 2 * index + 2;
        if (right > tree.size()) return;
        if (right == tree.size()) right = left;
        uint64_t minChild = tree[left] < tree[right] ? left : right;
        if (tree[index] > tree[minChild]) {
            std::swap(tree[index], tree[minChild]);
            siftDown(minChild);
        }
    }
    void heapify() {
        for (uint64_t i = tree.size() / 2; i < tree.size(); --i) siftUp(i);
    }
    public:
    Heap() = default;
    explicit Heap(const std::vector<T>& arr) : tree(arr) {heapify();}
    void insert(T value) {
        tree.push_back(value);
        siftUp(tree.size() - 1);
    }
    T getMin() {
        T result = tree.front();
        tree.front() = tree.back();
        tree.pop_back();
        siftDown(0);
        return result;
    }   
};