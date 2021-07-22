//
// Created by timas on 22.07.2021.
//

#include <iostream>
#include <string>
#include <memory>
#include <utility>

class Command {
public:
    virtual ~Command() = default;

    virtual void Execute() const = 0;
};

class SimpleCommand: public Command {
private:
    std::string str;

public:
    SimpleCommand(const std::string str): str(str) {}

    void Execute() const override {
        std::cout << str;
    }
};

template<class T>
class Receiver {
public:
    void DoSmth(const T& value) const {
        std::cout << value;
    }
};

template<class T>
class ComplexCommand: public Command {
private:
    Receiver<std::string> receiver;

    std::string str1;
    std::string str2;

public:
    ComplexCommand(Receiver<std::string> receiver1, std::string str1, std::string str2): receiver(receiver1),
                    str1(std::move(str1)), str2(std::move(str2)) {}

    void Execute() const override {
        receiver.DoSmth(str1);
        receiver.DoSmth(str2);
    }
};

class Invoker {
private:
    std::unique_ptr<Command> command1;
    std::unique_ptr<Command> command2;

public:
    void SetCommand1(std::unique_ptr<Command> command) {
        command1 = std::move(command);
    }

    void SetCommand2(std::unique_ptr<Command> command) {
        command2 = std::move(command);
    }

    void Do() {
        command1->Execute();
        command2->Execute();
    }
};

int main() {
    std::unique_ptr<Command> command = std::make_unique<ComplexCommand<std::string>>(Receiver<std::string>(),
                                                                                "lll", "mmm");
    std::unique_ptr<Invoker> Inv = std::make_unique<Invoker>();
    Inv->SetCommand1(std::move(command));

    std::unique_ptr<Command> command1 = std::make_unique<SimpleCommand>("kkk");
    Inv->SetCommand2(std::move(command1));

    Inv->Do();

    return 0;
}