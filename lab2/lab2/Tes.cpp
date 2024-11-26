//#include "gtest/gtest.h"
//#include "World.h"
//#include <fstream>
//#include <string>
//
//// Тест на создание мира из файла
//TEST(WorldTest, CreateWorldFromFile) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile.close();
//
//    World world;
//
//    // Проверяем, что мир создан корректно
//    EXPECT_EQ(world._width, 5);
//    EXPECT_EQ(world._height, 5);
//    EXPECT_EQ(Name, "TestWorld");
//    EXPECT_EQ(Rule, "Rule: B345678/S345678");
//    EXPECT_EQ(world._array2D[2][2], '*');
//    EXPECT_EQ(world._array2D[2][3], '*');
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//// Тест на подсчет живых соседей
//TEST(WorldTest, CountLiveNeighbors) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile << "3 2\n";
//    tempFile.close();
//
//    World world;
//
//    // Проверяем количество живых соседей для разных клеток
//    EXPECT_EQ(world.col_live_neighbors(2, 2), 2);
//    EXPECT_EQ(world.col_live_neighbors(2, 3), 2);
//    EXPECT_EQ(world.col_live_neighbors(3, 2), 1);
//    EXPECT_EQ(world.col_live_neighbors(1, 1), 1);
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//// Тест на стабильность мира
//TEST(WorldTest, IsStable) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile.close();
//
//    World world;
//
//    // Проверяем, что мир нестабилен после создания
//    EXPECT_FALSE(world.is_stable());
//
//    // Копируем текущее состояние в предыдущее
//    world.copy_world();
//
//    // Проверяем, что мир стабилен после копирования
//    EXPECT_TRUE(world.is_stable());
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//// Тест на следующее поколение
//TEST(WorldTest, NextGeneration) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile.close();
//
//    World world;
//
//    // Проверяем, что мир нестабилен после создания
//    EXPECT_FALSE(world.is_stable());
//
//    // Обновляем мир до следующего поколения
//    world.next_generation();
//
//    // Проверяем, что мир изменился
//    EXPECT_FALSE(world.is_stable());
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//// Тест на копирование мира
//TEST(WorldTest, CopyWorld) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile.close();
//
//    World world;
//
//    // Копируем текущее состояние в предыдущее
//    world.copy_world();
//
//    // Проверяем, что мир стабилен после копирования
//    EXPECT_TRUE(world.is_stable());
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//// Тест на печать мира
//TEST(WorldTest, PrintWorld) {
//    // Создаем временный файл с данными для теста
//    std::ofstream tempFile("test_file.txt");
//    tempFile << "5 5\n";
//    tempFile << "TestWorld\n";
//    tempFile << "345678 345678\n";
//    tempFile << "2 2\n";
//    tempFile << "2 3\n";
//    tempFile.close();
//
//    World world;
//
//    // Печатаем мир и проверяем вывод
//    testing::internal::CaptureStdout();
//    world.print_world();
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_NE(output.find("TestWorld"), std::string::npos);
//    EXPECT_NE(output.find("Rule: B345678/S345678"), std::string::npos);
//    EXPECT_NE(output.find("Current generation: 1"), std::string::npos);
//
//    // Удаляем временный файл
//    std::remove("test_file.txt");
//}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}