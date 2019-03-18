/* Task :
   Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
   Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
   Время работы O(n + m). n, m ≤ 100000.
   Указание. Обходите массив B от конца к началу.
   
   developed by Crashdown

*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main(){

    int n,m;
    int k = 0;
    int a[100001];
    int b[100001];

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    cin >> m;

    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    cin >> k;

    int cnt = 0;
    int last = 0;
    int i = 0;

    for(int j = m - 1; j >= 0; j--){
            for(int i = last; i < n; i++){
                if(a[i] + b[j] > k){
                    break;
                }
                if(a[i] + b[j] == k){
                    last = i;
                    cnt++;
                    break;
                }
                last = i;

            }
    }

    cout << cnt;




    return 0;
}
