#include "../template.h"
#include "modint.h"

// copy from here

class Combination
{
private:
    vector<mint> _fact, _inv_fact;
    
public:
    Combination(int size) : _fact(size + 1), _inv_fact(size + 1) {
        _fact[0] = 1;
        for (int i = 1; i <= size; i++) _fact[i] = _fact[i-1] * i;
        _inv_fact[size] = _fact[size].inv();
        for (int i = size - 1; i >= 0; i--) _inv_fact[i] = _inv_fact[i+1] * (i+1);
    }

    mint fact(int k) const { return _fact[k]; }
    mint inv_fact(int k) const { return _inv_fact[k]; }

    mint P(int n, int r) {
        if (r < 0 || n < r) return 0;
        else return fact(n) * inv_fact(n - r);
    }

    mint C(int n, int r) {
        if (r < 0 || n < r) return 0;
        else return fact(n) * inv_fact(r) * inv_fact(n - r);
    }

    mint H(int n, int r) {
        if (n < 0 || r < 0) return 0;
        else return r == 0 ? 1 : C(n + r - 1, r);
    }
};