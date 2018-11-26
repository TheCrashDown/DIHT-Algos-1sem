/* Task :
   Дан массив натуральных чисел A[0..n), n не превосходит 100 000.
   Так же задан размер некотрого окна (последовательно расположенных элементов массива) в
   этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести значение
   максимума в окне. Скорость работы O(n log n), память O(n).
   
   developed by Lev "Crashdown" Vinokurov
   (решение с использованием дерева отрезков)
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int a[100001];
int tree[400005];

//дерево отрезков: построение
void tBuild (int pos, int left, int right){
    if(left == right){
        tree[pos] = a[left];
        return;
    }
    int middle = (left + right) / 2;
    tBuild (pos*2 + 1, left, middle);
    tBuild (pos*2 + 2, middle + 1, right);
    int res1 = tree[pos*2 + 1];
    int res2 = tree[pos*2 + 2];
    tree[pos] = max(res1, res2);
}

//дерево отрезков: запрос максимума на окне
int tMax (int pos, int left, int right, int windowLeft, int windowRight){
    if(left > windowRight || right < windowLeft){
        return -(1<<31);
    }
    if(windowLeft <= left && right <= windowRight){
        return tree[pos];
    }
    int middle = (left + right) / 2;
    int res1 = tMax (pos*2 + 1, left, middle, windowLeft, windowRight);
    int res2 = tMax (pos*2 + 2, middle + 1, right, windowLeft, windowRight);
    return max (res1, res2);
}


int main(){

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int k;
    cin >> k;

    tBuild(0,0,n - 1);

    for(int i = 0; i < n - k + 1; i++){
        cout << tMax(0, 0, n-1, i, i + k - 1) << " ";
    }

    return 0;
}
