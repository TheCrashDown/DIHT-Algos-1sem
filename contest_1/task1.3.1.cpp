/* Task :
   Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
   Для каждого элемента массива B[i] найдите минимальный индекс k минимального 
   элемента массива A, равного или превосходящего
   B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int main(){

    int n,m;
    cin >> n >> m;

    int* a = new int[n];
    int* b = new int[m];

    int left = 0;
    int right = 0;
    int k = 0;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    for(int i = 0; i < m; i++){

        //частный случай: первое число массива А больше текущего элемента В
        if(a[0] >= b[i]){
            cout << 0 << " ";
            continue;
        }

        //частный случай: такого элемента нет
        if(a[n-1] < b[i]){
            cout << n << " ";
            continue;
        }

        //общий случай: бин поиск
        left = 0;
        right = n;

        while(true){
            k = (left + right) / 2;
            if(a[k] >= b[i] && a[k-1] < b[i]){
                cout << k << " ";
                break;
            }
            if(a[k] >= b[i]){
                right = k;
                continue;
            }
            left = k;
        }
    }

    return 0;
}
