#include "../template.h"

// 最大公約数
#if __cplusplus < 201703L
template <typename M, typename N>
constexpr common_type_t<M, N> gcd(M a, N b) { return (b != 0) ? gcd(b, a % b) : abs(a); }
#endif
template <typename ForwardIt>
constexpr typename iterator_traits<ForwardIt>::value_type
gcd(ForwardIt first, ForwardIt last)
{
    using val_t = typename iterator_traits<ForwardIt>::value_type;
    if (first == last) return static_cast<val_t>(0);
    val_t res = *first;
    while (++first != last) res = gcd(res, *first);
    return res;
}
template <typename T>
constexpr T gcd(initializer_list<T> t) { return gcd(t.begin(), t.end()); }

// 最小公倍数
#if __cplusplus < 201703L
template <typename M, typename N>
constexpr common_type_t<M, N> lcm(M a, N b) { return (a != 0 && b != 0) ? a / gcd(a, b) * b : 0; }
#endif
template <typename ForwardIt>
constexpr typename iterator_traits<ForwardIt>::value_type
lcm(ForwardIt first, ForwardIt last)
{
    using val_t = typename iterator_traits<ForwardIt>::value_type;
    if (first == last) return static_cast<val_t>(0);
    val_t res = *first;
    while (++first != last) res = lcm(res, *first);
    return res;
}
template <typename T>
constexpr T lcm(initializer_list<T> t) { return lcm(t.begin(), t.end()); }
