#include <iostream>
#include <vector>
#include <map>
#include <memory>


int g_sn = 0;
bool g_echo = false;

class Foo {
public:
    Foo() : sn(++g_sn) {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    virtual ~Foo() {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    int sn;
};


class Array {
public:
    Array() {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    Array(std::vector<std::shared_ptr<Foo>> elem) : elem(elem) {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    virtual ~Array() {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;

        elem.clear();
    }

    void push_back(std::shared_ptr<Foo> foo) {
        elem.push_back(foo);
    }

    void print() {
        for (auto& item : elem) {
            std::cout << item->sn << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<Foo>> elem;
};


class Map {
public:
    Map() {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    virtual ~Map() {
        if (g_echo) std::cout << __FUNCTION__ << std::endl;
    }

    void push(const char* key, std::shared_ptr<Foo> foo) {
        auto iter = map.find(key);
        if (iter == map.end()) {
            Array arr;
            arr.push_back(foo);
            map.insert(std::make_pair(key, arr));
        }
        else {
            iter->second.push_back(foo);
        }
    }

    Array get(const char* key) {
        Array arr;
        auto iter = map.find(key);
        if (iter == map.end()) {
            return arr;
        }
        return iter->second;
    }

private:
    std::map<const char*, Array> map;
};


Map g_map;

Array getKey(const char* key)
{
    if (g_echo) std::cout << "start " << __FUNCTION__ << std::endl << std::endl;

    Array arr;
    arr = g_map.get(key);
    
    if (g_echo) std::cout << std::endl << "end " << __FUNCTION__ << std::endl << std::endl;

    return arr;  // ~Array
}


int main()
{
    g_map.push("key-1", std::make_shared<Foo>(Foo()));
    g_map.push("key-1", std::make_shared<Foo>(Foo()));
    g_map.push("key-2", std::make_shared<Foo>(Foo()));

    g_echo = true;

    auto arr = getKey("key-1");

    if (g_echo) std::cout << "after arr.print(); " << std::endl;

    arr.print();

    g_echo = false;
    return 0;
}
