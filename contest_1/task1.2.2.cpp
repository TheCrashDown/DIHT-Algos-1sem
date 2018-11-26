/* Task :
   Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
   Вначале вводится количество вершин, затем последовательно целочисленные
   координаты всех вершин в порядке обхода по часовой стрелке.
   n < 1000, координаты < 10000.
   Указание. Для вычисления площади n-угольника можно посчитать сумму
   ориентированных площадей трапеций под каждой стороной многоугольника.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int x1,x2,y1,y2,xFirst, yFirst;
    cin >> x1 >> y1;
    xFirst = x1;
    yFirst = y1;

    double square = 0.0;

    for(int i = 0; i < n-1; i++){
        cin >> x2 >> y2;
        square += 1.0*(x2-x1)*(y1+y2)/2;
        x1 = x2;
        y1 = y2;
    }
    square += 1.0*(xFirst - x2)*(y1+yFirst)/2;
    cout << square;


    return 0;
}
