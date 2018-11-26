/* Task :
   Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
   Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
   ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000..
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main(){

    int n;
    cin >> n;

    int a[110001];
    int b[1001];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    int left = 0;
    int right = n;
    int pos = 0;

    for(int i = 0; i < m; i++){

        left = 0;
        right = n;

        //проверки, что искомый элемент - первый/последний
        if(a[0] > b[i]){
            cout << 0 << " ";
            continue;
        }
        if(a[n-1] < b[i]){
            cout << n-1 << " ";
            continue;
        }

        //бин поиск
        while(true){
            pos = (left + right) / 2;
            //b[i] лежит между а[pos] и a[pos-1]
            if(a[pos] > b[i] && b[i] > a[pos-1]){
                if(a[pos] - b[i] < b[i] - a[pos-1]){
                    cout << pos << " ";
                }
                else{
                    cout << pos-1 << " ";
                }
                break;
            }
            //b[i] лежит между а[pos] и a[pos+1]
            if(a[pos+1] > b[i] && b[i] > a[pos]){
                if(a[pos+1] - b[i] < b[i] - a[pos]){
                    cout << pos+1 << " ";
                }
                else{
                    cout << pos << " ";
                }
                break;
            }
            //b[i] == a[pos], при этом a[i] первый/единственный в серии
            if(a[pos] == b[i] && a[pos-1] < b[i]){
                cout << pos << " ";
                break;
            }
            //проверки бин поиска
            if(a[pos] >= b[i]){
                right = pos;
                continue;
            }
            left = pos;
        }
    }

    return 0;
}
