#include <gtest/gtest.h>
#include "BitArray.h" // Подключаем заголовочный файл с объявлением класса BitArray

// Тест конструктора и метода to_string
TEST(BitArrayTest, ConstructorAndToString) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_EQ(a.to_string(), "101010100101010100001111");
}

// Тест метода set
TEST(BitArrayTest, Set) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a.set(0, false);
    EXPECT_EQ(a.to_string(), "001010100101010100001111");

    a.set(23, true);
    EXPECT_EQ(a.to_string(), "001010100101010100001111");
}

// Тест метода fill_false
TEST(BitArrayTest, FillFalse) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a.fill_false();
    EXPECT_EQ(a.to_string(), "000000000000000000000000");
}

// Тест метода fill_true
TEST(BitArrayTest, FillTrue) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a.fill_true();
    EXPECT_EQ(a.to_string(), "111111111111111111111111");
}

// Тест оператора &=
TEST(BitArrayTest, AndAssign) {
    std::uint64_t data1[] = { 0xAA550F0000000000 };
    std::uint64_t data2[] = { 0xAA0F550000000000 };
    size_t size = 24;

    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data1[0] >> (63 - i)) & 1);
    }

    BitArray b;
    b.resize(size);
    for (size_t i = 0; i < size; ++i) {
        b.set(i, (data2[0] >> (63 - i)) & 1);
    }

    a &= b;
    EXPECT_EQ(a.to_string(), "101010100000010100000101");
}

// Тест оператора |=
TEST(BitArrayTest, OrAssign) {
    std::uint64_t data1[] = { 0xAA550F0000000000 };
    std::uint64_t data2[] = { 0xAA0F550000000000 };
    size_t size = 24;

    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data1[0] >> (63 - i)) & 1);
    }

    BitArray b;
    b.resize(size);
    for (size_t i = 0; i < size; ++i) {
        b.set(i, (data2[0] >> (63 - i)) & 1);
    }

    a |= b;
    EXPECT_EQ(a.to_string(), "101010100101111101011111");
}

// Тест оператора <<=
TEST(BitArrayTest, LeftShiftAssign) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a <<= 2;
    EXPECT_EQ(a.to_string(), "101010010101010000111100");
}

// Тест оператора >>=
TEST(BitArrayTest, RightShiftAssign) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a >>= 2;
    EXPECT_EQ(a.to_string(), "001010101001010101000011");
}

// Тест оператора []
TEST(BitArrayTest, IndexOperator) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[23], 1);
}

// Тест метода any
TEST(BitArrayTest, Any) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_TRUE(a.any());

    a.fill_false();
    EXPECT_FALSE(a.any());
}

// Тест метода none
TEST(BitArrayTest, None) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_FALSE(a.none());

    a.fill_false();
    EXPECT_TRUE(a.none());
}

// Тест метода empty
TEST(BitArrayTest, Empty) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_FALSE(a.empty());

    a.resize(0);
    EXPECT_TRUE(a.empty());
}

// Тест метода count
TEST(BitArrayTest, Count) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_EQ(a.count(), 12);

    a.fill_false();
    EXPECT_EQ(a.count(), 0);
}

// Тест метода size
TEST(BitArrayTest, Size) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    EXPECT_EQ(a.size(), 24);
}

// Тест метода swap
TEST(BitArrayTest, Swap) {
    std::uint64_t data1[] = { 0xAA550F0000000000 };
    std::uint64_t data2[] = { 0xAA0F550000000000 };
    size_t size = 24;

    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data1[0] >> (63 - i)) & 1);
    }

    BitArray b;
    b.resize(size);
    for (size_t i = 0; i < size; ++i) {
        b.set(i, (data2[0] >> (63 - i)) & 1);
    }

    a.swap(b);
    EXPECT_EQ(a.to_string(), "101010100000111101010101");
    EXPECT_EQ(b.to_string(), "101010100101010100001111");
}

// Тест метода resize
TEST(BitArrayTest, Resize) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a.resize(32, true);
    EXPECT_EQ(a.to_string(), "10101010010101010000111111111111");

    a.resize(16, false);
    EXPECT_EQ(a.to_string(), "1010101001010101");
}

// Тест метода push_back
TEST(BitArrayTest, PushBack) {
    std::uint64_t data[] = { 0xAA550F0000000000 };
    size_t size = 24;
    BitArray a;
    a.resize(size);
    for (size_t i = 0; i < size; ++i) {
        a.set(i, (data[0] >> (63 - i)) & 1);
    }

    a.push_back(true);
    EXPECT_EQ(a.to_string(), "1010101001010101000011111");

    a.push_back(false);
    EXPECT_EQ(a.to_string(), "10101010010101010000111110");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}