/* Task :
   Дан массив целых чисел A[0..n). Не используя других
   массивов переставить элементы массива A в обратном порядке за O(n).
   n ≤ 10000.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

void reverser(int n, int *a)
{
    int tmp = 0;

    for(int i = 0; i < n/2; i++)
    {
        tmp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = tmp;
    }
}

int main()
{
    int n;
    cin >> n;

    int a[10000];
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    reverser(n,a);

    for(int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}
