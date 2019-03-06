/* Task :
   Дана последовательность целых чисел a1...an и натуральное число k, такое что
   для любых i, j: если j >= i + k, то a[i] <= a[j].
   Требуется отсортировать последовательность. Последовательность может быть очень длинной.
   Время работы O(n * log(k)). Доп. память O(k).
   
   Решить, используя алгорим слияния.
   
   developed by Crashdown

*/
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    int pos;
    Node(int _data = 0, int _pos = 0){
        data = _data;
        pos = _pos;
    }
    bool operator< (Node second){
        return data < second.data;
    }
};

void siftDown(vector<Node>& heap, int pos, int heapSize)
{
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    if(right >= heapSize){
        right = left;
    }
    if(left >= heapSize){
        return;
    }
    if(heap[pos] < heap[left] && heap[pos] < heap[right]){
        return;
    }
    int minChild = (heap[left] < heap[right]) ? left : right;

    swap(heap[minChild], heap[pos]);

    siftDown(heap, minChild, heapSize);

}

void kWaysMerge(vector<Node>& node, vector<Node>& heap, int n, int k){
    int sortedPart = 0;
    int heapSize = k;
    while(heapSize > 0)
    {
        node[sortedPart++] = heap[0];

        //текущая последовательность еще не закончилась
        if(heap[0].pos + k < n){
            //вместо элемента ставим следующий за ним
            //из этой последовательности
            heap[0] = node[heap[0].pos + k];
            siftDown(heap, 0, heapSize);
        }
        //текущая последовательность закончилась
        else{
            //заменяем этот элемент на другой элемент
            //из кучи, уменьшаем размер кучи
            heap[0] = heap[--heapSize];
            siftDown(heap, 0, heapSize);
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    int tmp = 0;
    //считывание массива
    vector<Node> node(n);
    for(int i = 0; i < n; ++i){
        cin >> tmp;
        node[i] = Node(tmp, i);
    }
    //будем рассматривать последовательности чисел
    //0 k 2k 3k 4k...
    //1 k+1 2k+1 3k+1...
    //по условию начиная с (i+k)го элемента все не меньше текущего
    //поэтому все такие последовательности будут возрастать, и на них
    //можно использовать k путевое слияние

    //собираем кучу из первых элементов
    vector<Node> heap(k);
    for(int i = 0; i < k; i++){
        heap[i] = node[i];
    }
    for(int i = k / 2 - 1; i >= 0; --i){
        siftDown(heap, i, k);
    }

    kWaysMerge(node, heap, n, k);

    for(int i = 0; i < n; ++i){
        cout << node[i].data << " ";
    }

    return 0;
}
