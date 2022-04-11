#include <vector>
#include <iostream>

template <typename T>
class RingBuffer {
public:
    enum {
        default_size = 2
    };

    explicit RingBuffer()
            : _size(default_size), _head(_size / 2), _tail(_head) {
        buffer.resize(_size);
        for (auto &i : buffer) i = 0;
    }

    ~RingBuffer() = default;

    bool Is(const T &value) const {
        auto tail = _tail;
        auto head = _head;
        bool is = false;
        while (tail != head) {
            if (buffer[head] == value) {
                is = true;
                break;
            }
            if (++head == _size) {
                head = 0;
            }
        }
        return is;
    }

    void Add(const T &new_value) {
        if (_tail + 1 == _head || (_tail + 1 == _size && _head == 0)) pop_front();
        push_back(new_value);
    }

    void Show() const {
        for (const auto& i : buffer) {
            std::cout << i << ' ';
        }
    }

private:
    void push_back(const T &data) {
        if (++_tail == _size) _tail = 0;
        buffer[_tail] = data;
    }

    void pop_front() {
        buffer[_head] = 0;
        if (++_head == _size) _head = 0;
    }

    std::vector<T> buffer;
    int _size;
    int _head;
    int _tail;
};

int main() {
    RingBuffer<int> rb;
    rb.Add(1);
    rb.Add(2);
    std::cout << rb.Is(1) << ' ';
    std::cout << rb.Is(3) << ' ';
    rb.Add(3);
    rb.Add(4);
    rb.Add(5);
    rb.Add(6);
    rb.Show();
}