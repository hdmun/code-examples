#include <iostream>

class Object {
public:
    Object(): id(++Object::ObjectId) {}
    virtual void Show() = 0;

    int id;
    static int ObjectId;
};

int Object::ObjectId = 0;

class Monster : public Object {
public:
    virtual void Show() {
        std::cout << "Monster::Show objectId: " << id << std::endl;
    }
};

class User : public Object {
public:
    virtual void Show() {
        std::cout << "User::Show objectId: " << id << std::endl;
    }
};


void static_cast_example()
{
    unsigned int ubyte4 = -1;
    int sbyte4 = static_cast<int>(ubyte4);
    std::cout << "ubyte4: " << ubyte4 << ", sbyte4: " << sbyte4 << std::endl;

    Monster* monster = new Monster();
    monster->Show();

    Object* obj = static_cast<Object*>(monster);
    obj->Show();

    delete monster;
}

void dynamic_cast_example()
{
    Object* obj = new Monster();
    Monster* monster = dynamic_cast<Monster*>(obj);
    monster->Show();

    User* user = dynamic_cast<User*>(obj);
    if (user != nullptr) {
        user->Show();
    }
}


void reinterpret_cast_example()
{
    Object* obj = new Monster();
    Monster* monster = reinterpret_cast<Monster*>(obj);
    monster->Show();
}

int main()
{
    static_cast_example();
    dynamic_cast_example();
    reinterpret_cast_example();

    return 0;
}
