#include <iostream>
#include <string>

class Node
{
public:
    ~Node() = default;
    virtual void print(int indent = 0) const = 0;
    virtual void print2() const = 0;
};




class Op : public Node
{
public:
    Op(char operation, Node* left, Node* right) : _operation(operation), _left(left), _right(right) {}

    void print(int indent = 0) const {
        std::cout << std::string(indent, ' ') << _operation << std::endl;
        _left->print(indent + 2);
        _right->print(indent + 2);
    }

    void print2() const {
        _left->print2();
        _right->print2();
        std::cout << _operation << " ";
    }

private:
    char _operation;
    Node* _left;
    Node* _right;
};


class Number : public Node {
public:
    Number(int value) : _value(value) {}
    void print(int indent = 0) const {
        std::cout << std::string(indent, ' ') << _value << std::endl;
    }

    void print2() const {
        std::cout << _value << " ";
    }

private:
    int _value;
};


class Parser {
public:
    Parser(std::string& text) : text(text), pos(0) {};

    Node* parse() {
        return parseSum();
    }

private:
    const std::string& text;
    size_t pos;


    Node* parseSum() // + -
    {
        Node* left = parseMul(); //(*/ )
        while (pos < text.size() && (text[pos] == '+' || text[pos] == '-'))
        {
            char op = text[pos++];
            Node* right = parseFactor();// (*/ )
            left = new Op(op, left, right);
        }
        return left;

    }

    Node* parseMul() // * /
    {
        Node* left = parseFactor(); //(())
        while (pos < text.size() && (text[pos] == '*' || text[pos] == '/'))
        {
            char op = text[pos++];
            Node* right = parseFactor(); //(())
            left = new Op(op, left, right);
        }
        return left;

    }


    Node* parseFactor() {
        if (text[pos] == '(') {
            pos++;
            Node* expr = parseSum();
            pos++;
            return expr;
        }
        else if (isdigit(text[pos])) {
            int value = 0;
            while (pos < text.size() && isdigit(text[pos])) { //превращаем несколько цифр подряд в одно число
                value = value * 10 + (text[pos++] - '0');
            }
            return new Number(value);
        }
    }
};






int main() {
    std::string input = "(5+3)*2";
    Parser parser(input);

    try {
        Node * tree = parser.parse();
        tree->print2();

    }
    catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
