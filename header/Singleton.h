#pragma once

template <typename Derived>
class Singleton {
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static Derived& getInstance() {
        static DerivedInstance instance;
        return instance;
    }
private:
    class DerivedInstance : public Derived {
    public:
        DerivedInstance() : Derived() {}
    };
};