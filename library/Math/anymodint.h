#include "../template.h"

class anymodint
{
public:
    anymodint(ll value = 0) : _value(value >= 0 ? value % mod() : (value % mod()) + mod()) {}

    static void setmod(ll value) { mod() = value; }

    anymodint operator+() const { return *this; }
    anymodint operator-() const { return anymodint(-_value); }

    anymodint &operator+=(const anymodint &rhs) {
        if ((_value += rhs._value) >= mod()) _value -= mod();
        return *this;
    }
    anymodint &operator-=(const anymodint &rhs) {
        if ((_value += mod() - rhs._value) >= mod()) _value -= mod();
        return *this;
    }
    anymodint &operator*=(const anymodint &rhs) {
        (_value *= rhs._value) %= mod();
        return *this;
    }
    anymodint &operator/=(const anymodint &rhs) {
        *this *= rhs.inv();
        return *this;
    }
    anymodint operator+(const anymodint &rhs) const { return anymodint(*this) += rhs; }
    anymodint operator-(const anymodint &rhs) const { return anymodint(*this) -= rhs; }
    anymodint operator*(const anymodint &rhs) const { return anymodint(*this) *= rhs; }
    anymodint operator/(const anymodint &rhs) const { return anymodint(*this) /= rhs; }

    anymodint operator++() { *this += 1; return *this; }
    anymodint operator--() { *this -= 1; return *this; }
    anymodint operator++(int) { anymodint tmp = *this; ++*this; return tmp; }
    anymodint operator--(int) { anymodint tmp = *this; --*this; return tmp; }

    bool operator==(const anymodint &rhs) const { return _value == rhs._value; }
    bool operator!=(const anymodint &rhs) const { return _value != rhs._value; }

    anymodint inv() const {
        ll a = _value, b = mod(), u = 1LL, v = 0LL;
        while (b > 0) {
            ll tmp = a / b;
            a -= tmp * b; swap(a, b);
            u -= tmp * v; swap(u, v);
        }
        return anymodint(u);
    }

    anymodint pow(ll n) const {
        anymodint e = *this, res = 1;
        while (n) {
            if (n & 1) res *= e;
            e *= e, n >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &os, const anymodint &m) {
        os << m._value;
        return os;
    }

    friend istream &operator>>(istream &is, anymodint &m) {
        ll in;
        is >> in;
        m = anymodint(in);
        return is;
    }

private:
    ll _value;
    static ll &mod() { static ll _mod = linf; return _mod; }
};
using mint = anymodint;
