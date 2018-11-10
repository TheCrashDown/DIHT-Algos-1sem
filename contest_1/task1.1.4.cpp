/*Дано натуральное число N. Представить N в виде A + B, так,
что НОД(A, B) максимален, A ≤ B. Вывести A и B. Если возможно
несколько ответов - вывести ответ с минимальным A. n ≤ 10 000 000.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int a = 0;
    int b = 0;

    if(n % 2 == 0){
        cout << n / 2 << " " << n / 2;
    }
    else{
        a = (n - 1) / 2;
        b = (n + 1) / 2;
        while(b % a != 0){
            a--;
            b++;
        }
        cout << a << " " << b;
    }

    return 0;
}
