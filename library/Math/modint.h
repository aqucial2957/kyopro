/*
 * "mod 取り構造体"
 * last revised on: 2020/03/13
 */

#include "../template.h"

// copy from here
template <ll mod>
class modint
{
public:
    constexpr modint(ll value = 0) : _value(value >= 0 ? value % mod : (value % mod) + mod) {}

    constexpr modint operator+() const { return *this; }
    constexpr modint operator-() const { return modint(-_value); }

    constexpr modint &operator+=(const modint &rhs) {
        if ((_value += rhs._value) >= mod) _value -= mod;
        return *this;
    }
    constexpr modint &operator-=(const modint &rhs) {
        if ((_value += mod - rhs._value) >= mod) _value -= mod;
        return *this;
    }
    constexpr modint &operator*=(const modint &rhs) {
        (_value *= rhs._value) %= mod;
        return *this;
    }
    constexpr modint &operator/=(const modint &rhs) {
        *this *= rhs.inv();
        return *this;
    }
    constexpr modint operator+(const modint &rhs) const { return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const { return modint(*this) /= rhs; }

    constexpr modint operator++() { *this += 1; return *this; }
    constexpr modint operator--() { *this -= 1; return *this; }
    constexpr modint operator++(int) { modint tmp = *this; ++*this; return tmp; }
    constexpr modint operator--(int) { modint tmp = *this; --*this; return tmp; }

    constexpr bool operator==(const modint &rhs) const { return _value == rhs._value; }
    constexpr bool operator!=(const modint &rhs) const { return _value != rhs._value; }

    constexpr modint inv() const {
        ll a = _value, b = mod, u = 1LL, v = 0LL;
        while (b > 0) {
            ll tmp = a / b;
            a -= tmp * b; swap(a, b);
            u -= tmp * v; swap(u, v);
        }
        return modint(u);
    }

    constexpr modint pow(ll n) const {
        modint e = *this, res = 1;
        while (n) {
            if (n & 1) res *= e;
            e *= e, n >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &os, const modint &m) {
        os << m._value;
        return os;
    }

    friend istream &operator>>(istream &is, modint &m) {
        ll in;
        is >> in;
        m = modint(in);
        return is;
    }

private:
    ll _value;
};
using mint = modint<1000000007>;
