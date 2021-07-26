//
// Created by timas on 26.07.2021.
//

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

class IObserver {
public:
    virtual ~IObserver()= default;;
    virtual void Update(const std::string& new_str) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

class Subject: public ISubject {
private:
    std::list<IObserver*> observer_list;

public:
    void Attach(IObserver* observer) override {
        observer_list.push_back(observer);
    }

    void Detach(IObserver* observer) override {
        observer_list.remove(observer);
    }

    void Notify() override {
        for (auto obs : observer_list) {
            obs->Update("Updated");
        }
    }

    void BusinessLogic() {
        Notify();
    }
};

class Observer: public IObserver {
private:
    std::string cur_str;
    Subject& subject;

public:
    Observer(Subject& subject): subject(subject) {
        subject.Attach(this);
    }

    void Update(const std::string& new_str) override {
        cur_str = new_str;
    }

    void Remove_from_the_list() {
        subject.Detach(this);
    }
};

int main() {
    std::unique_ptr<Subject> subject = std::make_unique<Subject>();
    std::unique_ptr<Observer> observer1 = std::make_unique<Observer>(*subject);
    std::unique_ptr<Observer> observer2 = std::make_unique<Observer>(*subject);
    std::unique_ptr<Observer> observer3 = std::make_unique<Observer>(*subject);
    subject->BusinessLogic();
    observer1->Remove_from_the_list();
    return 0;
}