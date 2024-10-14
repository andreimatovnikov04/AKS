#include <iostream>
#include <gmpxx.h>
#include <cmath>

mpz_class fakt(mpz_class n)
{
    mpz_class ans = 1;
    for (; n > 0; n -= 1)
        ans *= n;
    return ans;
}

mpz_class C(mpz_class n, unsigned int k)
{
    return fakt(n) / (fakt(k) * fakt(n - k));
}

int phi(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

bool binom(int n, mpz_class a, int* coef)
{
    mpz_class d;
    mpz_class count = 0;
    for (unsigned int i = 0; i <= n; ++i)
    {
        mpz_pow_ui(d.get_mpz_t(), a.get_mpz_t(), i);
        mpz_class t = C(n, i) * d;
        coef[i] = t.get_d();
    }
    coef[0] -= 1;
    coef[n] += a.get_d();
    for (unsigned int i = 0; i <= n; ++i)
    {
        if (coef[i] % n == 0) count += 1;
    }
    return count == n + 1;
}
int main()
{
    mpz_class a = 2, n = 1, l = 0;
    unsigned long int b = 2;
    gmp_fscanf(stdin, "%Zi", &n);
    if (n == 1 || n == 2)
    {
        std::cout << "Prime";
        return 0;
    }

    for (mpz_class i = a; i <= n / 2 + 1; i += 1)
    {
        unsigned long int j = b;
        mpz_pow_ui(l.get_mpz_t(), i.get_mpz_t(), j);
        while (n > l)
        {
            j = j + 1;
            mpz_pow_ui(l.get_mpz_t(), i.get_mpz_t(), j);
        }
        if (n == l)
        {
            std::cout << "Composite";
            return 0;
        }
    }
    unsigned long int r = 1;
    mpz_class d;
    mpz_pow_ui(d.get_mpz_t(), n.get_mpz_t(), r);
    while (d % r != 1 || r <= floor(log2(n.get_d()) * log2(n.get_d())))
    {
        r = r + 1;
        mpz_pow_ui(d.get_mpz_t(), n.get_mpz_t(), r);
    }
    mpz_class c;
    for (a = 2; a < r; ++a)
    {
        mpz_gcd(c.get_mpz_t(), a.get_mpz_t(), n.get_mpz_t());
        if (c > 1 && c < n)
        {
            std::cout << "Composite";
            return 0;
        }
    }
    if (n <= r)
    {
        std::cout << "Prime";
        return 0;
    }
    int z = n.get_d();
    int* coef = new int[z + 1];
    for (a = 0; a <= n; a++)
    {
        bool is_prime = binom(n.get_d(), a, coef);
        if (is_prime)
        {
            std::cout << "Prime";
            return 0;
        }
    }
    delete[] coef;
    std::cout << "Composite";
    return 0;
}