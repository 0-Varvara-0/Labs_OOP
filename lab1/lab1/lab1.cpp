#include <iostream>
#include "BitArray.h"

BitArray::BitArray() : _size(0), _data(nullptr) {
    // Инициализация массива битов с размером 0
}

BitArray::~BitArray() {
    delete[] _data;
}

size_t BitArray::NumElements() const {
    return (_size + ElementSize - 1) / ElementSize;
}

BitArray& BitArray::fill_false() { // Заполняем весь массив нулями
    size_t numElements = NumElements();
    std::memset(_data, 0x00, numElements * sizeof(ElementType));
    return *this;
}

BitArray& BitArray::fill_true() { // Заполняем весь массив единицами
    size_t numElements = NumElements();
    std::memset(_data, 0xFF, numElements * sizeof(ElementType));
    return *this;
}

BitArray& BitArray::set(int n, bool val) {
    if (n >= 0 && n < _size) {
        size_t elementIndex = n / ElementSize;
        size_t bitIndex = n % ElementSize;
        if (val) {
            _data[elementIndex] |= (ElementType(1) << (ElementSize - 1 - bitIndex));
        }
        else {
            _data[elementIndex] &= ~(ElementType(1) << (ElementSize - 1 - bitIndex));
        }
    }
    return *this;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (_size != b._size) {
        throw "BitArray sizes do not match";
        std::cout << "BitArray sizes do not match" << std::endl;
    }
    else {
        size_t numElements = NumElements();
        for (size_t i = 0; i < numElements; ++i) {
            _data[i] &= b._data[i];
        }
        return *this;
    }
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (_size != b._size) {
        throw "BitArray sizes do not match";
        std::cout << "BitArray sizes do not match" << std::endl;
    }
    else {
        size_t numElements = NumElements();
        for (size_t i = 0; i < numElements; ++i) {
            _data[i] |= b._data[i];
        }
        return *this;
    }
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::operator>>=(int n) {
    size_t numElements = NumElements();
    ElementType* newData = new ElementType[numElements];
    std::memset(newData, 0, numElements * sizeof(ElementType));

    int elementShift = n / ElementSize;
    int bitShift = n % ElementSize;

    for (size_t i = 0; i < _size; ++i) {
        size_t oldIndex = i; //текущий индекс
        size_t newIndex = i + n; //куда должен сдвинут

        if (newIndex >= _size) continue; //Если newIndex выходит за пределы массива, то бит просто игнорируется

        size_t oldElementIndex = oldIndex / ElementSize;
        size_t oldBitIndex = oldIndex % ElementSize;
        size_t newElementIndex = newIndex / ElementSize;
        size_t newBitIndex = newIndex % ElementSize;

        ElementType oldBit = (_data[oldElementIndex] >> (ElementSize - 1 - oldBitIndex)) & 1; //Извлекается значение бита из старого положения с помощью сдвига
        newData[newElementIndex] |= (oldBit << (ElementSize - 1 - newBitIndex)); //этот бит устанавливается в новом положении с помощью сдвига и операции ИЛИ
    }

    std::memcpy(_data, newData, numElements * sizeof(ElementType));
    delete[] newData;
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    size_t numElements = (_size + ElementSize - 1) / ElementSize;
    ElementType* newData = new ElementType[numElements];
    std::memset(newData, 0, numElements * sizeof(ElementType));

    int elementShift = n / ElementSize;
    int bitShift = n % ElementSize;

    for (size_t i = 0; i < _size; ++i) {
        size_t oldIndex = i;
        size_t newIndex = i - n;

        if (newIndex >= _size) continue;

        size_t oldElementIndex = oldIndex / ElementSize;
        size_t oldBitIndex = oldIndex % ElementSize;
        size_t newElementIndex = newIndex / ElementSize;
        size_t newBitIndex = newIndex % ElementSize;

        ElementType oldBit = (_data[oldElementIndex] >> (ElementSize - 1 - oldBitIndex)) & 1;
        newData[newElementIndex] |= (oldBit << (ElementSize - 1 - newBitIndex));
    }

    std::memcpy(_data, newData, numElements * sizeof(ElementType));
    delete[] newData;
    return *this;
}

bool BitArray::operator[](int i) const {
    size_t elementIndex = i / ElementSize;
    size_t bitIndex = i % ElementSize;
    return (_data[elementIndex] >> (ElementSize - 1 - bitIndex)) & 1;
}

bool BitArray::any() const {
    size_t numElements = NumElements();
    for (size_t i = 0; i < numElements; ++i) {
        if (_data[i] != 0) {
            return true; // Если хотя бы один элемент не равен нулю, значит есть хотя бы один истинный бит
        }
    }
    return false; // Если все элементы равны нулю, значит все биты ложные
}

bool BitArray::none() const {
    size_t numElements = NumElements();
    for (size_t i = 0; i < numElements; ++i) {
        if (_data[i] != 0) {
            return false; // Если хотя бы один элемент не равен нулю, значит есть хотя бы один истинный бит
        }
    }
    return true; // Если все элементы равны нулю, значит все биты ложные
}

bool BitArray::empty() const {
    return _size == 0;
}

int BitArray::count() const {
    int count = 0;
    size_t numElements = NumElements();
    for (size_t i = 0; i < numElements; ++i) {
        ElementType element = _data[i];
        while (element) {
            count += element & 1; // Добавляем младший бит к счетчику
            element >>= 1; // Сдвигаем элемент вправо на один бит
        }
    }
    return count;
}

int BitArray::size() const {
    return static_cast<int>(_size);
}

void BitArray::swap(BitArray& b) {
    std::swap(_size, b._size);
    std::swap(_data, b._data);
}

void BitArray::push_back(bool bit) {
    resize(_size + 1, bit);
}

void BitArray::resize(int num_bits, bool value) {
    size_t numElements = NumElements();
    size_t newNumElements = (num_bits + ElementSize - 1) / ElementSize;
    ElementType* newData = new ElementType[newNumElements];
    std::memset(newData, value ? 0xFF : 0x00, newNumElements * sizeof(ElementType)); // Инициализируем новый массив

    if (num_bits <= _size) {
        std::memcpy(newData, _data, newNumElements * sizeof(ElementType));
    }

    if (num_bits > _size) {
        std::memcpy(newData, _data, numElements * sizeof(ElementType));
        for (size_t i = _size; i < num_bits; ++i) {
            size_t elementIndex = i / ElementSize;
            size_t bitIndex = i % ElementSize;
            if (value) {
                newData[elementIndex] |= (ElementType(1) << (ElementSize - 1 - bitIndex)); //устанавливает выбранный бит в 1, и складывает с тек newData (ИЛИ)
            }
            else {
                newData[elementIndex] &= ~(ElementType(1) << (ElementSize - 1 - bitIndex)); //устанавливает выбранный бит в 0, остальные в 1 (~) (если есть хотябы один '0', то с 'И' все умножает на '0')
            }
        }
    }
    delete[] _data;
    _data = newData;
    _size = num_bits;
}

std::string BitArray::to_string() const {
    std::string result;
    result.reserve(_size); // Резервируем память для строки
    for (size_t i = 0; i < _size; ++i) { //проход по каждому биту и добав 0 или 1
        size_t elementIndex = i / ElementSize; //индекс элемента
        size_t bitIndex = i % ElementSize; //индекс бита внутри элемента (0-63)
        ElementType bit = (_data[elementIndex] >> (ElementSize - 1 - bitIndex)) & 1; //извлекает конкретный бит из элемента путем сдвига вправо
        result += (bit ? '1' : '0');
    }
    return result;
}



/*int main() {

    BitArray a(data, size);
    BitArray b(data1, size1);

    std::cout << a.to_string() << std::endl;
    std::cout << b.to_string() << std::endl << std::endl;

    a &= b;

    std::cout << a.to_string() << std::endl;

    return 0;
}*/