#include "../template.h"

vector<bool> &prime_table(size_t max_n)
{
    vector<bool> pr(max_n + 1, true);
    pr[0] = false; pr[1] = false;
    for (int i = 2; i * i <= max_n; i++) {
        if (pr[i]) {
            for (int j = i * i; j <= max_n; j += i) pr[i] = false;
        }
    }
    return pr;
}