//
// Created by timas on 12.04.2022.
//

#include <deque>
#include <algorithm>
#include <iostream>

template <typename T>
class RingBufferDeq {
private:
    std::deque<T> buffer;

public:
    enum {
        default_size = 2
    };

    RingBufferDeq() = default;
    ~RingBufferDeq() = default;
    RingBufferDeq(const RingBufferDeq&) = delete;
    void operator=(const RingBufferDeq&) = delete;

    void Add(const T& value) {
        if (buffer.size() == default_size) {
            buffer.pop_front();
        }
        buffer.push_back(value);
    }

    bool Contains(const T& value) {
        bool contains = false;
        if (std::find(buffer.begin(), buffer.end(), value) != buffer.end()) {
            contains = true;
        }
        return contains;
    }

    void Show() {
        for (const auto& i : buffer) {
            std::cout << i << ' ';
        }
    }
};

int main() {
    RingBufferDeq<int> rb;
    rb.Add(1);
    rb.Show(); std::cout << std::endl;
    rb.Contains(2) ? std::cout << "true" : std::cout << "false"; std::cout << std::endl;
    rb.Add(2);
    rb.Show(); std::cout << std::endl;
    rb.Add(3);
    rb.Show(); std::cout << std::endl;
    rb.Add(4);
    rb.Show(); std::cout << std::endl;
    rb.Add(5);
    rb.Show(); std::cout << std::endl;
    return 0;
}