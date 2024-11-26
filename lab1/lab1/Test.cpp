#include <gtest/gtest.h>
#include "bitarray.h"

// Тест конструктора и метода to_string
TEST(BitArrayTest, ConstructorAndToString) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_EQ(a.to_string(), "101010100101010100001111");
}

// Тест метода set
TEST(BitArrayTest, Set) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a.set(0, false);
    EXPECT_EQ(a.to_string(), "001010100101010100001111");

    a.set(23, true);
    EXPECT_EQ(a.to_string(), "0010101001010101000011111");
}

// Тест метода fill_false
TEST(BitArrayTest, FillFalse) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a.fill_false();
    EXPECT_EQ(a.to_string(), "000000000000000000000000");
}

// Тест метода fill_true
TEST(BitArrayTest, FillTrue) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a.fill_true();
    EXPECT_EQ(a.to_string(), "111111111111111111111111");
}

// Тест оператора &=
TEST(BitArrayTest, AndAssign) {
    unsigned char data1[] = { 0xAA, 0x55, 0x0F };
    unsigned char data2[] = { 0xAA, 0x0F, 0x55 };
    size_t size = 24;

    BitArray a(data1, size);
    BitArray b(data2, size);

    a &= b;
    EXPECT_EQ(a.to_string(), "101010100000010100000101");
}

// Тест оператора |=
TEST(BitArrayTest, OrAssign) {
    unsigned char data1[] = { 0xAA, 0x55, 0x0F };
    unsigned char data2[] = { 0xAA, 0x0F, 0x55 };
    size_t size = 24;

    BitArray a(data1, size);
    BitArray b(data2, size);

    a |= b;
    EXPECT_EQ(a.to_string(), "101010100101010101011111");
}

// Тест оператора ^=
TEST(BitArrayTest, XorAssign) {
    unsigned char data1[] = { 0xAA, 0x55, 0x0F };
    unsigned char data2[] = { 0xAA, 0x0F, 0x55 };
    size_t size = 24;

    BitArray a(data1, size);
    BitArray b(data2, size);

    a ^= b;
    EXPECT_EQ(a.to_string(), "000000000101000001011010");
}

// Тест оператора <<=
TEST(BitArrayTest, LeftShiftAssign) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a <<= 2;
    EXPECT_EQ(a.to_string(), "101010010101010000111100");
}

// Тест оператора >>=
TEST(BitArrayTest, RightShiftAssign) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a >>= 2;
    EXPECT_EQ(a.to_string(), "001010101010101000011110");
}

// Тест оператора []
TEST(BitArrayTest, IndexOperator) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[23], 1);
}

// Тест метода any
TEST(BitArrayTest, Any) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_TRUE(a.any());

    a.fill_false();
    EXPECT_FALSE(a.any());
}

// Тест метода none
TEST(BitArrayTest, None) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_FALSE(a.none());

    a.fill_false();
    EXPECT_TRUE(a.none());
}

// Тест метода empty
TEST(BitArrayTest, Empty) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_FALSE(a.empty());

    a.resize(0);
    EXPECT_TRUE(a.empty());
}

// Тест метода count
TEST(BitArrayTest, Count) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_EQ(a.count(), 12);

    a.fill_false();
    EXPECT_EQ(a.count(), 0);
}

// Тест метода size
TEST(BitArrayTest, Size) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    EXPECT_EQ(a.size(), 24);
}

// Тест метода swap
TEST(BitArrayTest, Swap) {
    unsigned char data1[] = { 0xAA, 0x55, 0x0F };
    unsigned char data2[] = { 0xAA, 0x0F, 0x55 };
    size_t size = 24;

    BitArray a(data1, size);
    BitArray b(data2, size);

    a.swap(b);
    EXPECT_EQ(a.to_string(), "101010100000111101010101");
    EXPECT_EQ(b.to_string(), "101010100101010100001111");
}

// Тест метода resize
TEST(BitArrayTest, Resize) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a.resize(32, true);
    EXPECT_EQ(a.to_string(), "10101010010101010000111111111111");

    a.resize(16, false);
    EXPECT_EQ(a.to_string(), "1010101001010101");
}

// Тест метода push_back
TEST(BitArrayTest, PushBack) {
    unsigned char data[] = { 0xAA, 0x55, 0x0F };
    size_t size = 24;
    BitArray a(data, size);

    a.push_back(true);
    EXPECT_EQ(a.to_string(), "1010101001010101000011111");

    a.push_back(false);
    EXPECT_EQ(a.to_string(), "10101010010101010000111110");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}