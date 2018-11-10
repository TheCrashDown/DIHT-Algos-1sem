/*Дан массив целых чисел в диапазоне [0..1e9]. Размер массива кратен 10 и ограничен 
сверху значением 2.5 * 1e7 элементов. Все значения массива являются элементами 
псевдо-рандомной последовательности. Необходимо отсортировать элементы массива за 
минимально время и вывести каждый десятый элемент отсортированной последовательности.

Решить, используя сортировку, основанную на QuickSort.
Минимальный набор оптимизаций, который необходимо реализовать:
1. Оптимизация ввода/вывода
2. Оптимизация выбора опорного элемента
3. Оптимизация Partition
4. Оптимизация рекурсии
5. Оптимизация концевой рекурсии

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>
#include <vector>
#include <stdint.h>

const int MAX_RECURSION_DEPTH = 32;

void insertionSort(std::vector<int>& data, int left, int right){
    for(int i = left + 1; i < right; i++){
        for(int j = i; j > left && data[j] < data[j - 1]; j--){
            std::swap(data[j], data[j - 1]);
        }
    }
}

int xorShift(int left, int right){
    static int x = 534523;
    x ^= x >> 4;
    x ^= x << 8;
    x ^= x >> 15;
    x ^= x << 16;
    x ^= x >> 23;
    x ^= x << 42;
    if(x < 0){
        x *= -1;
    }
    return left + x % (right - left - 1);
}

int partition(std::vector<int>& data, int left, int right){
    if(right - left == 1){
        return left;
    }
    int pivot = xorShift(left, right);
    std::swap(data[pivot], data[right - 1]);
    int i = left;
    int j = i;
    while(true){
        if(data[j] > data[right - 1]){
            j++;
        } else {
            std::swap(data[i], data[j]);
            i++;
            j++;
        }
        if(j >= right - 1){
            break;
        }
    }
    std::swap(data[i], data[right - 1]);
    return i;
}

void quickSort(std::vector<int>& data, int left, int right){
    int* stackLeft = new int[MAX_RECURSION_DEPTH];
    int* stackRight = new int[MAX_RECURSION_DEPTH];
    int currDepth = 0;

    while(true){
        if(right - left <= 50){
            insertionSort(data, left, right);
            if(currDepth == 0){
                delete[] stackLeft;
                delete[] stackRight;
                break;
            }
            currDepth--;
            left = stackLeft[currDepth];
            right = stackRight[currDepth];
            continue;
        }
        int pivot = partition(data, left, right);
        stackLeft[currDepth] = pivot;
        stackRight[currDepth] = right;
        right = pivot;
        currDepth++;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n = 0;
    std::vector<int> data;
    int tmp;
    std::cin >> tmp;
    while(!std::cin.eof()){
        data.push_back(tmp);
        n++;
        std::cin >> tmp;
    }
    quickSort(data, 0, n);

    for(int i = 9; i < n; i += 10){
        std::cout << data[i] << " ";
    }

    return 0;
}
