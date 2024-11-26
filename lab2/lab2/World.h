#include <string>
namespace Life {
    class World
    {
    public:
        World(const std::string& filename);
        ~World();

        bool is_stable() const;
        void next_generation();
        void print_world() const;

    private:
        void copy_world();
        int col_live_neighbors(int x, int y) const;

        int _height;
        int _width;
        int _col_to_birth[8];
        int _col_to_survival[8];

        char** _array2D;
        char** _prev_array2D;

        std::string Name;
        std::string Rule;
        int count_S = 0;
        int count_B = 0;
        int generation = 1;
        const char Symbol = 2;
        const char SymbolEmpty = 250;
    };
}