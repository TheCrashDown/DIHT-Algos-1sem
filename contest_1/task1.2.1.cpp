/*Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j],
где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n). n ≤ 100000.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main(){

    int n;
    cin >> n;

    int a[100001];
    int b[100001];
    int maxA [100001][2];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }

    int currMax = -(1<<31);
    int currMaxInd = 0;
    for(int i = 0; i < n; i++){
        if(a[i] > currMax){
            currMax = a[i];
            currMaxInd = i;
        }
        maxA[i][0] = currMax;
        maxA[i][1] = currMaxInd;
    }

    //переменная currMax теперь будет использоваться не как максимальный
    //элемент на подотрезке, а как максимальная сумма
    currMax = -(1<<31);
    int i0 = 0;
    int j0 = 0;
    for(int i = 0; i < n; i++){
        if(b[i] + maxA[i][0] > currMax){
            i0 = maxA[i][1];
            j0 = i;
            currMax = b[i] + maxA[i][0];
        }
    }

    cout << i0 << " " << j0;

    return 0;
}


