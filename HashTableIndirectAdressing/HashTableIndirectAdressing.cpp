//
// Created by timas on 22.07.2021.
//

#include <iostream>
#include <string>
#include <vector>

struct Hasher {
    unsigned int operator()(const std::string &str) const {
        unsigned int hash = 0;
        for (auto i : str) {
            hash = hash * 5 + i;
        }
        return hash;
    }
};

enum status {
    empty,
    del,
    key
};

template<class T>
struct HashTableNode {
    T data;
    status stat;

    HashTableNode() : stat(empty) {}

    explicit HashTableNode(T *d) : data(d), stat(key) {}
};

template<class T, class H>
class HashTable {
    static constexpr int LIMIT = 7;
public:
    explicit HashTable(const H &_hasher);

    HashTable(const HashTable &hasher) = delete;

    HashTable &operator=(const HashTable &hasher) = delete;

    ~HashTable() = default;

    bool Add(const T &d);

    bool Delete(const T &d);

    bool Has(const T &d) const;

    void Show() {
        for (int i = 0; i < table.size(); ++i) {
            std::cout << i << " : " << table[i].data << std::endl;
        }
    }

private:
    H hasher;
    std::vector<HashTableNode<T>> table;

    size_t item_cnt;

    void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable(const H &_hasher): hasher(_hasher), item_cnt(0) {}

template<class T, class H>
bool HashTable<T, H>::Add(const T &d) {
    if (table.empty() || item_cnt * LIMIT > table.size()) {
        growTable();
    }

    unsigned int hash = hasher(d);
    unsigned int hashPos = hash % table.size();
    unsigned int firstDelete = -1;

    if (table[hashPos].stat == empty) {
        table[hashPos].data = d;
        table[hashPos].stat = key;
        item_cnt++;
    } else {
        if (table[hashPos].stat == del) {
            firstDelete = hashPos;
        }
        for (int j = 0; j < table.size(); ++j) {
            if (table[hashPos].data == d && table[hashPos].stat == key) {
                return false;
            }
            hashPos = (hashPos + j + 1) % table.size();
            if (table[hashPos].stat == empty) {
                if (firstDelete == -1) {
                    table[hashPos].data = d;
                    table[hashPos].stat = key;
                } else {
                    table[firstDelete].data = d;
                    table[firstDelete].stat = key;
                }
                item_cnt++;
                return true;
            } else if (firstDelete == -1 && table[hashPos].stat == del) {
                firstDelete = hashPos;
            }
        }
        growTable();
        if (!Add(d)) {
            return false;
        }
    }

    return true;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T &d) {
    unsigned int hash = hasher(d);
    unsigned int hashPos = hash % table.size();

    if (table[hashPos].data == d && table[hashPos].stat == key) {
        table[hashPos].data = "null";
        table[hashPos].stat = del;
        item_cnt--;
        return true;
    } else {
        for (int j = 0; j < table.size(); ++j) {
            hashPos = (hashPos + j + 1) % table.size();
            if (table[hashPos].data == d && table[hashPos].stat == key) {
                table[hashPos].data = "null";
                table[hashPos].stat = del;
                item_cnt--;
                return true;
            }
            if (table[hashPos].stat == empty) {
                return false;
            }
        }
        return false;
    }
}

template<class T, class H>
bool HashTable<T, H>::Has(const T &d) const {
    unsigned int hash = hasher(d);
    unsigned int hashPos = hash % table.size();

    if (table[hashPos].data == d && table[hashPos].stat == key) {
        return true;
    } else {
        for (int j = 0; j < table.size(); ++j) {
            hashPos = (hashPos + j + 1) % table.size();
            if (table[hashPos].data == d && table[hashPos].stat == key) {
                return true;
            }
            if (table[hashPos].stat == empty) {
                return false;
            }
        }
        return false;
    }
}

template<class T, class H>
void HashTable<T, H>::growTable() {
    std::vector<HashTableNode<T>> newTable(std::max(7, static_cast<int>(table.size() * 2)));
    std::vector<HashTableNode<T>> prevTable(table);
    table = std::move(newTable);
    for (int i = 0; i < prevTable.size(); ++i) {
        if (prevTable[i].stat == key) {
            Add(prevTable[i].data);
        }
    }
}

int main() {
    Hasher myHasher;
    HashTable<std::string, Hasher> myHashTable(myHasher);
    char operation;
    std::string newKey;
    while (std::cin >> operation >> newKey) {
        switch (operation) {
            case '+':
                std::cout << (myHashTable.Add(newKey) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (myHashTable.Delete(newKey) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (myHashTable.Has(newKey) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                break;
        }
    }

    return 0;
}
