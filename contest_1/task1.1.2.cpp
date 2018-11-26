/* Task :
   Вывести разложение натурального числа n на простые множители.
   Простые множители должны быть упорядочены по возрастанию и разделены пробелами.
   2 ≤ n ≤ 106.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int den = 2;
    bool flag = false;

    while(den*den <= n){
        while(n % den == 0){
            n /= den;
            cout << den << " ";
            flag = true;
        }
        den++;
    }
    if(n > 1){
        cout << n;
    }

    return 0;
}
