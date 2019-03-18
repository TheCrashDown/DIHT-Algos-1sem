/* Task :
   Дан массив целых чисел A[0..n), n не превосходит 100 000. Так же задан размер некотрого окна
   (последовательно расположенных элементов массива) в этом массиве k, k<=n.
   Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.
   Скорость работы O(n log n), память O(n).
   
   developed by Crashdown

   (решение с использованием кучи)
*/
#include <iostream>

using namespace std;

struct HeapNode{
    //значение
    int data = 0;
    //ссылка на соответствующий элемент в массиве индексов
    int pointer = 0;
};

void nodeSwap(HeapNode* heap, int first, int second, int* index){

    //меняем значения элементов кучи
    int tmp = heap[first].data;
    heap[first].data = heap[second].data;
    heap[second].data = tmp;

    //меняем соответствующие индексы в массиве индексов
    tmp = index[heap[first].pointer];
    index[heap[first].pointer] = index[heap[second].pointer];
    index[heap[second].pointer] = tmp;

    //меняем у элементов соответствующие значения ссылок
    //на индекс в массиве индексов
    tmp = heap[first].pointer;
    heap[first].pointer = heap[second].pointer;
    heap[second].pointer = tmp;
}

//балансировка вниз
void siftDown(HeapNode* heap, int pos, int heapSize, int* index){

    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    //случай, когда у текущего элемента только один потомок
    if(right >= heapSize){
        right = left;
    }

    //условие выхода : мы в листе
    if(left >= heapSize){
        return;
    }
    //условие выхода : текущий элемент уже сбалансирован
    if(heap[pos].data >= heap[left].data && heap[pos].data >= heap[right].data){
        return;
    }

    int maxChild = (heap[left].data >= heap[right].data) ? left : right;

    nodeSwap(heap, pos, maxChild, index);

    siftDown(heap, maxChild, heapSize, index);
}

//балансировка вверх
void siftUp(HeapNode* heap, int pos, int* index){
      while (heap[pos].data > heap[(pos - 1) / 2].data){

        nodeSwap(heap, pos, (pos - 1) / 2, index);

        pos = (pos - 1) / 2;
        if(pos == 0){
            break;
        }
      }
}


int main()
{
    int n;
    cin >> n;
    HeapNode* heap = new HeapNode[n];


    for(int i = 0; i < n; i++){
        cin >> heap[i].data;
        heap[i].pointer = i;
    }

    //массив индексов. хранит в полях текущие расположения в куче
    //элементов с соответствующими индексами
    int* index = new int[n];
    for(int i = 0 ; i < n; i++){
        index[i] = i;
    }

    int k;
    cin >> k;

    //построение
    for(int i = k / 2 - 1; i >= 0; --i){
        siftDown(heap, i, k, index);
    }

    //запросы на подотрезках
    int pos = 0;
    while(true){
        cout << heap[0].data << " ";

        if(pos >= n - k){
            break;
        }

        heap[index[pos]].data = -(1<<31);

        siftDown(heap, index[pos], k + pos, index);

        siftUp(heap, k + pos, index);

        pos++;
    }


    return 0;
}
