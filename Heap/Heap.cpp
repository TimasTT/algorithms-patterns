#include <iostream>
#include <vector>

template <class T>
struct DefaultComp {
    bool operator()(const T& left, const T& right) {
        return left <= right;
    }
};

template <class T, class Comp = DefaultComp<T>>
class Heap {
public:
    Heap(): array(nullptr), size(0), capacity(0) {}

    Heap(T& arr, size_t arr_size) {
        heapify(arr, arr_size);
        array = arr;
        std::copy(arr, arr + arr_size, array);
        size = arr_size;
        capacity = size;
    }

    Heap(Heap& heap) {
        delete [] array;
        array = new T(heap.size);
        std::copy(heap.array, heap.array + heap.size, array);
        size = heap.size;
        capacity = heap.capacity;
    };

    Heap(const Heap& heap) {
        delete [] array;
        array = new T(heap.size);
        std::copy(heap.array, heap.array + heap.size, array);
        size = heap.size;
        capacity = heap.capacity;
    };

    ~Heap() {
        delete [] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    Heap& operator=(Heap const& heap) {
        delete [] array;
        array = new T(heap.size);
        std::copy(heap.array, heap.array + heap.size, array);
        size = heap.size;
        capacity = heap.capacity;
        return *this;
    }

    void push(const T& value) {
        if (capacity == size) {
            resize(std::max(capacity * 2, capacity + 2));
        }
        array[size++] = value;
        sift_up(size - 1);
    }

    void pop_top() {
        array[0] = array[size - 1];
        size--;
        sift_down();
    }

    const T& get_top() const {
        return array[0];
    }

    bool is_empty() {
        if (size == 0) {
            return true;
        } else {
            return false;
        }
    }

    size_t get_size() const {
        return size;
    }

    void show() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << array[i] << ' ';
        }
    }

private:
    void resize(size_t new_capacity) {
        T* new_arr = new T[new_capacity];
        std::copy(array, array + size, new_arr);
        delete [] array;
        array = new_arr;
        capacity = new_capacity;
    }

    void sift_up(size_t pos, Comp comp = Comp()) {
        size_t cur_pos = pos;
        if (size < 2) {
            return;
        }
        while(cur_pos != 0) {
            if (comp(array[cur_pos], array[(cur_pos - 1) / 2])) {
                std::swap(array[cur_pos], array[(cur_pos - 1) / 2]);
                cur_pos = (cur_pos - 1) / 2;
            } else {
                break;
            }
        }
    }

    void sift_down(Comp comp = Comp()) {
        int cur_pos = 0;
        while(cur_pos * 2 + 1 < size) {
            if (cur_pos * 2 + 2 < size) {
                if (comp(array[cur_pos * 2 + 1], array[cur_pos * 2 + 2])) {
                    if (comp(array[cur_pos * 2 + 1], array[cur_pos])) {
                        std::swap(array[cur_pos], array[cur_pos * 2 + 1]);
                        cur_pos = cur_pos * 2 + 1;
                    } else {
                        break;
                    }
                } else {
                    if (comp(array[cur_pos * 2 + 2], array[cur_pos])) {
                        std::swap(array[cur_pos], array[cur_pos * 2 + 2]);
                        cur_pos = cur_pos * 2 + 2;
                    } else {
                        break;
                    }
                }
            } else {
                if (comp(array[cur_pos * 2 + 1], array[cur_pos])) {
                    std::swap(array[cur_pos], array[cur_pos * 2 + 1]);
                    cur_pos = cur_pos * 2 + 1;
                } else {
                    break;
                }
            }
        }
    }

    void heapify(T& arr, size_t& array_size) {
        for (size_t i = array_size / 2; i >= 0; ++i) {
            sift_up();
        }
    }

    size_t size;
    size_t capacity;
    T* array;
};

void fill_int_heap_stdin(Heap<int>& heap) {
    size_t heap_size;
    std::cin >> heap_size;
    for (size_t i = 0; i < heap_size; ++i) {
        int value;
        std::cin >> value;
        heap.push(value);
    }
}

size_t quick_sum_int(Heap<int>& my_heap) {
    size_t size = 0;
    size_t first_val, second_val;
    while(my_heap.get_size() > 1) {
        first_val = my_heap.get_top();
        my_heap.pop_top();

        second_val = my_heap.get_top();
        my_heap.pop_top();

        my_heap.push(first_val + second_val);

        size += first_val + second_val;
    }

    return size;
}

void test_1() {
    Heap<int> my_heap;
    for (int i = 0; i < 20; ++i) {
        my_heap.push(i);
    }
    for (int i = 0; i < 10; ++i) {
        my_heap.push(i + 1);
        my_heap.pop_top();
    }
    my_heap.show();
}

int main() {
    //test_1();
    Heap<int> my_heap;
    fill_int_heap_stdin(my_heap);
    std::cout << quick_sum_int(my_heap);

    return 0;
}