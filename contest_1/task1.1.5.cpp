/*Вывести квадраты натуральных чисел от 1 до n, используя только O(n)
операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int curr = 0;

    for(int i = 0; i < n; i++)
    {
        curr += i + i + 1;
        cout << curr << " ";
    }

    return 0;
}
