/* Task :
   Найти, на сколько нулей оканчивается n! = 1 * 2 * 3 * … * n. n ≤ 1000.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int den = 5;
    int cnt = 0;

    while(den <= n)
    {
        cnt += n/den;
        den *= 5;
    }
    cout << cnt;

    return 0;
}
