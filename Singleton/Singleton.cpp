//
// Created by timas on 22.07.2021.
//

#include <iostream>
#include <string>

class Singleton {
private:
    std::string unique_string;

    static Singleton* singleton;

    Singleton(const std::string str): unique_string(str) {};

public:
    Singleton(Singleton &other) = delete;

    void operator=(Singleton &other) = delete;

    static Singleton* GetInstance(const std::string& str) {
        if (singleton == nullptr) {
            singleton = new Singleton(str);
        }

        return singleton;
    }

    std::string GetValue() const{
        return unique_string;
    }
};

Singleton* Singleton::singleton= nullptr;

int main() {
    Singleton* ST = Singleton::GetInstance("aaa");
    std::cout << ST->GetValue();

    return 0;
}