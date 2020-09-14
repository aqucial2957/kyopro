#include "../template.h"

map<ll, int> factorize(ll n)
{
    map<ll, int> mp;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            mp[i]++; n /= i;
        }
    }
    if (n != 1) mp[n] = 1;
    return mp;
}