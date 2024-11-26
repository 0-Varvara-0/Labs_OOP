#include <iostream>
#include <cstring>

namespace {
    class String {
    public:
        String(const char* str = "");

        ~String();

        String& operator += (const String& right);
        String& operator = (const String& other);

        const char* get_str() const;

    private:
        char* _storage;
        std::size_t _size;
    };

    //Конструктор
    String::String(const char* str)
    {
        _size = strlen(str);
        _storage = new char[_size + 1]; //массив символов
        std::memcpy(_storage, str, _size + 1);
    }

    // Деструктор
    String::~String() {
        delete[] _storage;
    }

    String& String::operator += (const String& right) {
        std::size_t _newSize = _size + right._size;
        char* _newStorage = new char[_newSize + 1];
        std::memcpy(_newStorage, _storage, _newSize + 1);
        std::strcat(_newStorage, right._storage);

        delete[] _storage;
        _storage = _newStorage;
        _size = _newSize + 1;

        return *this;
    }

    /*//Копиконструктор
    String::String(const String & other) {
        _size = other._size;
        _storage = new char[_size + 1];
        std::memcpy(_storage, other._storage, other._size + 1);
    }*/

    //оператор присваивания
    String& String::operator = (const String& other) {
        if (this != &other) {
            delete[] _storage;
            _size = other._size;
            _storage = new char[_size + 1];
            std::memcpy(_storage, other._storage, _size + 1);
        }
        return *this;
    }

    const char* String::get_str() const {
        return _storage;
    }

}

int main()
{
    char str[100];
    std::cin >> str;

    String a(str);
    String b = "!!!";

    a += b;

    std::cout << a.get_str() << std::endl;

    return 0;
}


