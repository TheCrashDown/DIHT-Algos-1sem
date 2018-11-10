/*Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся
незамкнутую ломаную, проходящую через все эти точки.
Указание: стройте ломаную в порядке возрастания x-координаты.
Если имеются две точки с одинаковой x-координатой, то расположите раньше
ту точку, у которой y-координата меньше.

Решить, используя сортировку вставками.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>
#include <vector>

using namespace std;

struct Point{
    int x;
    int y;

    Point(int _x = 0, int _y = 0){
        x = _x;
        y = _y;
    }

    bool operator< (Point second){
        if(x < second.x){
           return true;
        }
        if(x == second.x && y < second.y){
            return true;
        }
        return false;
    }
};

void insertionSort(vector<Point>& data, int n){
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0 && data[j] < data[j - 1]; j--){
            swap(data[j], data[j - 1]);
        }
    }
}

int main()
{
    int n = 0;
    cin >> n;
    vector<Point> data;
    data.resize(n);

    for(int i = 0; i < n; i++){
        int currX = 0;
        int currY = 0;
        cin >> currX >> currY;
        data[i] = Point(currX, currY);
    }

    insertionSort(data, n);

    for(int i = 0; i < n; i++){
        cout << data[i].x << " " << data[i].y << "\n";
    }

    return 0;
}
