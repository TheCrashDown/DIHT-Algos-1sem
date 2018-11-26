/* Task :
   Дан массив строк. Количество строк не больше 100000. Отсортировать массив методом 
   поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. 
   Последний символ строки = ‘0’.
   
   Решить, используя алгоритм MSD - сортировки по символам строки.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int k = 256;

void countingSort(string* data, int* cnt, int n, int currByte){
    //массив с количествами вхождений
    for(int i = 0; i < k; ++i){
        cnt[i] = 0;
    }
    //подсчет количеств вхождений
    for(int i = 0; i < n; ++i){
        ++cnt[data[i][currByte]];
    }
    //поиск начал групп одинаковых по текущему разряду элементов
    int sum = 0;
    for(int i = 0; i < k; ++i){
        int tmp = cnt[i];
        cnt[i] = sum;
        sum += tmp;
    }
    //записывааем во временный массив в нужном порядке
    string* tmp = new string[n];
    for(int i = 0; i < n; ++i){
        tmp[ cnt[ data[i][currByte] ]++ ] = data[i];
    }
    //копируем из временного в старый
    for(int i = 0; i < n; ++i){
        data[i] = tmp[i];
    }
    delete[] tmp;
}

void MSDSort(string* data, int n, int currByte){
    if(n <= 1){
        return;
    }
    //массив с количествами вхождений
    int* cnt = new int[k + 1];
    cnt[k] = n - 1;

    countingSort(data, cnt, n, currByte);

    for(int i = 0; i < k; ++i){
        MSDSort(data + cnt[i], cnt[i + 1] - cnt[i], currByte + 1);
    }
    delete[] cnt;
}

int main() {
    string s;
    cin >> s;
    int n = 0;
    vector<string> data(n);
    while(!cin.eof()){
        data.push_back(s);
        n++;
        cin >> s;
    }
    MSDSort(data.data(), n, 0);

    for(int i = 0; i < n; i++){
        cout << data[i] << "\n";
    }

    return 0;
}
