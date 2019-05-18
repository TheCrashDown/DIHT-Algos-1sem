/*  Task:
    Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
    Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.

    developed by Crashdown
	
*/

#include <iostream>
#include <vector>


long long count(int n){

	//	столбцы - размер основания, строки - сумма кубиков в пирамидке
	std::vector< std::vector<long long> > dp;

	dp.resize(n + 1);
	for(int i = 0; i < n + 1; ++i){
		dp[i].resize(n + 1);
	}

	for(int i = 0; i < n + 1; ++i)
	{
		for(int j = 0; j <= i; ++j)
		{
			//	нули (база динамики)
			if(i == 0 || j == 0){
				dp[i][j] = 0;
				continue;
			}
			//	главная диагональ (база динамики)
			if(i == j){
				dp[i][j] = 1;
				continue;
			}
			//	переход - для каждого основания считаем сумму того, что может стоять над ним
			dp[i][j] = 0;
			for(int k = 0; k < j; ++k){
				dp[i][j] += dp[i - j][k];
			}
		}
	}

	/*	ответ - сумма значение в строке n - т.е. сумма возможных пирамид
		размера n со всевозможными основаниями
	*/
	long long ans = 0;
	for(int i = 0; i < n + 1; ++i){
		ans += dp[n][i];
	}
	return ans;
}


int main()
{
	int n = 0;

	std::cin >> n;

	std::cout << count(n);

 	return 0;
}
