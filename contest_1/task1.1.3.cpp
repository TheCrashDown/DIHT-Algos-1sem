/* Task :
   Даны четыре неотрицательных числа a, b, c и d.
   Сложить две рациональные дроби a/b и c/d, а их результат представить
   в виде несократимой дроби m/n. Вывести числа m и n. a, b, c, d ≤ 1000.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    if(b==0) return a;
    return gcd(b, a%b);
}

int main()
{
    int a,b,c,d;
    cin >> a >> b >> c >> d;

    int m = a*d + c*b;
    int n = b*d;

    int den = gcd(max(m,n), min(m,n));

    cout << m/den << " " << n/den;


    return 0;
}

