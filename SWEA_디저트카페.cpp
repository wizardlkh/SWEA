#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
int T, t, N, A[21][21], ans, cnt, fx, fy;
int dx[4] = { -1, 1,  1, -1 };
int dy[4] = { 1, 1, -1, -1 }; // 0,1 놓고, 0만큼 2, 1만큼 3 놓기
set<int> s;

void f_M01(int x, int y, int &M0, int &M1)
{
	int nx = x, ny = y;
	do {
		M0++;
		nx += dx[0];
		ny += dy[0];
	} while ((0 <= nx && nx < N) && (0 <= ny && ny < N));

	nx = x;
	ny = y;
	do {
		M1++;
		nx += dx[1];
		ny += dy[1];
	} while ((0 <= nx && nx < N) && (0 <= ny && ny < N));
}

// depth가 방향 
void move(int d, int x, int y, int M0, int M1) // 0, 2 -> M0번, 1,3 -> M1번
{
	int nx = x, ny = y, stop = 0;

	if (d % 2 == 0)
	{
		for (int i = 1; i <= M0; i++)
		{
			nx += dx[d];
			ny += dy[d];
			if (!(0 <= nx && nx < N) || !(0 <= ny && ny < N) || s.find(A[nx][ny]) != s.end())// 아웃 바운드
			{
				stop = 1;
				break;
			}
			s.insert(A[nx][ny]);
			cnt++;
		}

		if (stop == 1)
			return;
		else
			move(d + 1, nx, ny, M0, M1);
	}
	else if (d % 2 == 1)
	{
		for (int i = 1; i <= M1; i++)
		{
			nx += dx[d];
			ny += dy[d];
			if (!(0 <= nx && nx < N) || !(0 <= ny && ny < N) || s.find(A[nx][ny]) != s.end())// 아웃 바운드
			{
				stop = 1;
				break;
			}
			s.insert(A[nx][ny]);
			cnt++;
		}

		if (stop == 1)
		{
			if (nx == fx && ny == fy)
				ans = max(ans, cnt);

			return;
		}
		else
			move(d + 1, nx, ny, M0, M1);
	}
}

void init()
{
	ans = -1;

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	t = T;

	while (T--)
	{
		cin >> N;
		init();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> A[i][j];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				int M0 = -1, M1 = -1;
				f_M01(i, j, M0, M1);
				//cout << i << ", " << j << ": " << M0 << ", " << M1 << '\n';

				for (int k = 1; k <= M0; k++) // 0방향 이동
					for (int l = 1; l <= M1; l++) // 1방향 이동	
					{
						cnt = 1;
						s.clear();
						s.insert(A[i][j]);
						fx = i;
						fy = j;

						move(0, i, j, k, l);
					}
			}
		cout << '#' << t - T << ' ' << ans << '\n';
	}
	return 0;
}