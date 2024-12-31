#include <sstream>
#include <tuple>


namespace Templates {

    template <typename Ch, typename Tr, typename Tuple, std::size_t N>
    struct TuplePrinter
    {
        static void print(std::basic_ostream<Ch, Tr>& os, const Tuple& t)
        {
            TuplePrinter<Ch, Tr, Tuple, N - 1>::print(os, t);
            os << ", " << std::get<N - 1>(t);
        }
    };

    template <typename Ch, typename Tr, typename Tuple>
    struct TuplePrinter<Ch, Tr, Tuple, 1>
    {
        static void print(std::basic_ostream<Ch, Tr>& os, const Tuple& t)
        {
            os << std::get<0>(t);
        }
    };

    template <typename Ch, typename Tr, typename... Args>
    auto operator<<(std::basic_ostream<Ch, Tr>& os,
        const std::tuple<Args...>& t) -> std::basic_ostream<Ch, Tr>&
    {
        os << "(";
        TuplePrinter<Ch, Tr, decltype(t), sizeof...(Args)>::print(os, t);
        os << ")";
        return os;
    }
}