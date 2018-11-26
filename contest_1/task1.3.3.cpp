/* Task :
   Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
   A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
   Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
   В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
   элемента B[i-1]. n, k ≤ 10000.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int main(){

    int n,m;
    cin >> n >> m;

    int a[10001];
    int b[10001];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    int last = 0;
    int left = 0;
    int right = n;
    int pos = 0;

    for(int i = 0; i < m; i++){

        left = last;
        right = n;

        if(a[0] > b[i] || a[n-1] < b[i]){
            continue;
        }

        while(true){

            pos = (left + right)/2;

            if(a[pos] == b[i]){
                cout << b[i] << " ";
                last = pos;
                break;
            }

            if((a[pos] < b[i] && a[pos+1] > b[i]) || (a[pos] > b[i] && a[pos-1] < b[i])){
                break;
            }

            if(a[pos] > b[i]){
                right = pos;
                continue;
            }
            left = pos;

        }

    }





    return 0;
}
