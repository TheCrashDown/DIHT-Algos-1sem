/*На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого
отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

Решить, используя сортировку кучей.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>
#include <vector>

using namespace std;

struct Event{
    int data = 0;
    int type = 0;
    //0 - начало отрезка
    //1 - конец отрезка
    Event(int _data = 0, int _type = 0){
        data = _data;
        type = _type;
    }

    bool operator< (Event b){
        if(data < b.data){
            return true;
        }
        if(data == b.data && type < b.type){
            return true;
        }
        return false;
    }
};

void siftDown(vector<Event>& heap, int pos, int heapSize){

    int left = 2 * pos + 1;
    int right =  2 * pos + 2;

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

    Event tmp = heap[minChild];
    heap[minChild] = heap[pos];
    heap[pos] = tmp;

    siftDown(heap, minChild, heapSize);
}

int main()
{
    int n;
    cin >> n;
    int left = 0;
    int right = 0;

    vector<Event> heap;
    heap.resize(n * 2);

    for(int i = 0; i < n * 2; i += 2){
        cin >> left >> right;
        heap[i] = Event(left, 0);
        heap[i + 1] = Event(right, 1);
    }
    for(int i = n - 1; i >= 0; --i){
        siftDown(heap, i, n * 2);
    }
    int cnt = 0;
    //толщина слоя покраски
    int coloredLayer = 0;
    //флаг, указывающий на то идет ли сййчас
    //закрашенная область
    bool currentIsColored = false;
    //начало покрашенного отрезка
    int startColored = 0;

    for(int i = 0; i < n * 2; i++){
        (heap[0].type == 0) ? coloredLayer++ : coloredLayer--;

        if(coloredLayer > 0 && !currentIsColored){
            currentIsColored = true;
            startColored = heap[0].data;
        }
        if(currentIsColored && coloredLayer == 0){
            cnt += heap[0].data - startColored;
            currentIsColored = false;
        }

        heap[0] = heap[n * 2 - i - 1];
        siftDown(heap, 0, n * 2 - i - 1);
    }

    if(coloredLayer > 0){
        cnt++;
    }
    cout << cnt;
    return 0;
}
