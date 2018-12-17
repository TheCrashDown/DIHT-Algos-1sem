/* Task :
   Даны неотрицательные целые числа n, k и массив целых чисел
   из диапазона [0..109] размера n.
   Требуется найти k-ю порядковую статистику. т.е. напечатать число,
   которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
   
   Решить, используя алгоритм поиска k-й порядковой статистики
   на основе функции Partition из сортировки QuickSort
   
   developed by Crashdown

*/
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

void dataSwap(vector<int>& data, int a, int b){
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

int partition(vector<int>& data, int left, int right){
    if(right - left == 1){
        return left;
    }
    //выбор опорного
    int pivot = left + rand() % (right - left);
    //опорный goto конец массива
    dataSwap(data, pivot, right - 1);
    //индексы (движение обоими начало -> конец)
    int i = left;
    int j = i;
    //шаг алгоритма
    //в начале массива - не большие опорного, потом - строго большие
    while(true){
        //текущий больше опорного; меньше или равен
        if(data[j] > data[right - 1]){
            j++;
        } else {
            dataSwap(data, i, j);
            i++;
            j++;
        }
        //выход, если дошли до конца
        if(j >= right - 1){
            break;
        }
    }
    dataSwap(data, i, right - 1);
    return i;
}

int findStat(vector<int>& data, int k, int left, int right){

    int middle = 0;
    while(true){
        //если в рассматриваемом отрезке 1 или 2
        //элемента, то сделаем вручную
        if(right - left == 1){
            return data[left];
        }
        if(right - left == 2){
            if(data[left] > data[left + 1]){
                dataSwap(data, left, left + 1);
            }
            return data[k];
        }
        //берем опорный элемент, разбиваем массив
        int middle = partition(data, left, right);
        //если на рандом попали - возвращаем результат
        if(middle == k){
            return data[middle];
        }

        //иначе смотрим в какой части массива(слева или справа)
        //находится искомый, и продолжаем поиски там, куда еще не ступала нога человека
        if(middle > k){
            right = middle;
            continue;
        }
        left = middle + 1;
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> data(n);

    for(int i = 0; i < n; i++){
        cin >> data[i];
    }
    cout << findStat(data, k, 0, n);
    return 0;
}
