#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Template.h"

using namespace Templates;

template <typename... Args>
class CSVParser
{
public:
    class Iterator;

    CSVParser(std::ifstream& file, std::size_t skipLines = 0,
        char delimiter = ',', char escape = '"')
        : file(file),
        delimiter(delimiter),
        escape(escape),
        lineNumber(skipLines + 1)
    {
        for (std::size_t i = 0; i < skipLines; ++i)
        {
            std::string unused;
            std::getline(file, unused);
        }
    }

    Iterator begin()
    {
        return Iterator(*this);
    }
    Iterator end()
    {
        return Iterator();
    }

    class Iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::tuple<Args...>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator() : parser(nullptr) {}
        Iterator(CSVParser& parser) : parser(&parser), current(parser.getNext())
        {
        }

        Iterator& operator++()
        {
            current = parser->getNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return current != other.current;
        }

        value_type operator*() const
        {
            return current;
        }

    private:
        CSVParser* parser;
        value_type current;
    };

private:
    std::ifstream& file;
    char delimiter;
    char escape;
    std::size_t lineNumber;

    std::tuple<Args...> getNext()
    {
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream lineStream(line);
            std::tuple<Args...> result;
            parseLine(lineStream, result);
            ++lineNumber;
            return result;
        }
        return {};
    }
    template <std::size_t I = 0>
    void parseLine(std::istringstream& lineStream, std::tuple<Args...>& result)
    {
        if constexpr (I < sizeof...(Args))
        {
            std::string cell;
            if (std::getline(lineStream, cell, delimiter))
            {
                // Удаляем экранирующие кавычки, если они есть
                if (!cell.empty() && cell.front() == escape &&
                    cell.back() == escape)
                {
                    cell = cell.substr(1, cell.size() - 2);
                }
                // Проверка на пустую строку или строку с пробелами
                if (cell.empty() ||
                    cell.find_first_not_of(' ') == std::string::npos)
                {
                    throw std::runtime_error(
                        "Error parsing CSV at line " +
                        std::to_string(lineNumber) + ", column " +
                        std::to_string(I + 1) + ": empty cell");
                }
                std::istringstream cellStream(cell);
                if (!(cellStream >> std::get<I>(result)))
                {
                    throw std::runtime_error("Error parsing CSV at line " +
                        std::to_string(lineNumber) +
                        ", column " +
                        std::to_string(I + 1));
                }
                parseLine<I + 1>(lineStream, result);
            }
            else
            {
                throw std::runtime_error("Error parsing CSV at line " +
                    std::to_string(lineNumber) +
                    ": not enough columns");
            }
        }
    }
};

int main()
{
    // Subtask #1: Print Tuple
    std::tuple<int, std::string> testTuple(1, "hello");
    std::cout << "Test Tuple: " << testTuple << std::endl;

    // Subtask #2 and #3: CSV Parser
    std::ifstream file("test.csv");
    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    try
    {
        CSVParser<int, std::string> parser(file, 0, ',', '"');
        std::cout << "CSV Data:" << std::endl;
        for (auto rs : parser)
        {
            std::cout << rs << std::endl;
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}




