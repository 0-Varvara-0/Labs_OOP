#include <cstddef>
#include <string>

    class BitArray {
    public:
        BitArray();
        ~BitArray();
        size_t NumElements() const;

        BitArray& set(int n, bool val = true);  
        BitArray& fill_false();
        BitArray& fill_true();

        BitArray& operator&=(const BitArray& b);
        BitArray& operator|=(const BitArray& b);

        BitArray& operator<<=(int n);
        BitArray& operator>>=(int n);
        BitArray operator<<(int n) const;
        BitArray operator>>(int n) const;

        bool any() const;
        bool none() const;
        bool empty() const;

        bool operator[](int i) const;

        int count() const;
        int size() const;

        void swap(BitArray& b);
        void resize(int num_bits, bool value = false);
        void push_back(bool bit = false);

        std::string to_string() const;

    private:
        using ElementType = std::uint64_t;
        const size_t ElementSize = 64u;

        std::size_t _size;
        ElementType* _data;
    };