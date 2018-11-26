/* Task :
   Даны отрезки. Найти длину прямой, покрытую ровно одним отрезком.
   
   developed by Lev "Crashdown" Vinokurov
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct liner
{
    int pos;
    int type;
    liner(int _pos, int _type)
    {
        pos = _pos;
        type = _type;
    }
    bool operator< (liner b)
    {
        if(pos < b.pos) return true;
        if(b.pos < pos) return false;
        return type < b.type;
    }
};

int main()
{
    vector<liner> linerList;

    int n, left, right;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> left >> right;
        linerList.push_back(liner(left, 2));
        linerList.push_back(liner(right, 1));
    }
    sort(linerList.begin(), linerList.end());


    int cnt = 0;
    int ans = 0;
    int last = 0;
    bool flag = false;

    for(int i = 0; i < n*2; i++)
    {
        if(linerList[i].type == 2) cnt++;
        if(linerList[i].type == 1) cnt--;
        if(cnt == 1 && !flag)
        {
            flag = true;
            last = linerList[i].pos;
        }
        if(flag && cnt != 1)
        {
            ans += linerList[i].pos - last;
            flag = false;
        }
    }
    cout << ans;

    return 0;
}
