/*Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения
массива строго возрастают, а на интервале [m, n-1] строго убывают.
Найти m за O( log m ).
2 ≤ n ≤ 10000.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>
using namespace std;

//смысл решать задачу за O(log), если мы получаем O(n) уже на операции считывания массива ?)))

int main()
{
    int n;
    cin >> n;

    int a[10000];

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int left = 0;
    int right = n;
    int m = 0;

	//частный случай: n = 2
    if(n == 2)
    {
        if(a[0] > a[1])
        {
            cout << 0;
        }
        else
        {
            cout << 1;
        }
    }
	//частный случай: m - нулевое число
    else if (a[0] > a[1])
    {
        cout << 0;
    }
	//частный случай: m - последнее число
    else if(a[n-1] > a[n-2])
    {
        cout << n-1;
    }
	//общий случай (бин поиск)
    else
    {
        while(true)
        {
            m = (left+right)/2;
            if(a[m] > a[m-1] && a[m] > a[m+1])
                break;
            if(a[m] > a[m-1])
            {
                left = m;
                continue;
            }
            right = m;
        }

        cout << m;
    }

    return 0;
}
