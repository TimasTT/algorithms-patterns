//
// Created by timas on 26.07.2021.
//

#include <iostream>
#include <vector>

class O {
public:
    using DataType = std::vector<int>;

    O(){
        values.push_back(1);
    }
private:
    DataType values;
}; //wtf

int main() {
    O a;
    return 0;
}
