#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int T, t, D, W, K, m[14][21], ans, pass, stop, temp[14][21];
vector<int> ans_v;

void pass_f(int col, int row, int AB, int con_num) // 0A, 1B, 성능검사 
{
	if (col == W)
	{
		pass = 1;
		stop = 1;
		return; // ★ 안넣으면 배열 인덱스 초과해서 참조됨
	}
		
	if (m[row][col] == AB) // 이전행 AB값과 같으면 num++
		con_num++;
	else
		con_num = 1; // 다르면 num = 1

	AB = m[row][col]; // AB를 현재행값으로 변경

	if (row < D - 1 && con_num < K && (D - row) + con_num > K)
		pass_f(col, row + 1, AB, con_num);
	else if (row < D && con_num == K)
		pass_f(col + 1, 0, -1, 1);
}

void drug(int d_num, int dep, int M_change) // 현재 시약처리수, 현재 row, 최대 시약처리수
{
	if (d_num == M_change)
	{
		pass = 0;
		pass_f(0, 0, -1, 1);

		if (pass == 1)
			ans = min(ans, M_change);	
			
		return;
	}
	else if (dep == D)
		return;

	drug(d_num, dep + 1, M_change);

	if (d_num < M_change)
	{
		for (int i = 0; i < W; i++)
			m[dep][i] = 0;
		drug(d_num + 1, dep + 1, M_change);

		for (int i = 0; i < W; i++)
			m[dep][i] = 1;
		drug(d_num + 1, dep + 1, M_change);

		for (int i = 0; i < W; i++)
			m[dep][i] = temp[dep][i];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	
	while (T--)
	{
		cin >> D >> W >> K;

		ans = 10000000;

		for (int i = 0; i < D; i++)
			for (int j = 0; j < W; j++)
			{
				cin >> m[i][j];
				temp[i][j] = m[i][j];
			}
				
		if (K == 1)
			ans_v.push_back(0);
		else 
		{
			for (int i = 0; i <= K; i++) // 투입할 약품 개수
			{
				stop = 0;

				drug(0, 0, i);
				
				if (stop == 1)
					break;
			}
				
			ans_v.push_back(ans);
		}
	}

	for (int i = 0; i < ans_v.size(); i++)
		cout << '#' << i+1 << ' ' << ans_v[i] << '\n';

	return 0;
}