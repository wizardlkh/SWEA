#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
int T, t, N, M, A[21][21], ans;
struct Home
{
	int x, y;
};

vector<Home> h;

void init()
{
	ans = 0;
	h.clear();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	t = T;

	while (T--)
	{
		init();

		cin >> N >> M;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> A[i][j];

				if (A[i][j] == 1)
					h.push_back({ i,j });
			}

		for (int i = 0; i < N + 1; i++) // coverage
		{
			for (int j = 0; j < N; j++) // 보안회사 중심위치
				for (int k = 0; k < N; k++)
				{
					int temp = -((i + 1)*(i + 1) + (i*i)); // 이익
					int hn = 0; // 서비스 제공받은 집수

					for (int l = 0; l < h.size(); l++)
						if (abs(h[l].x - j) + abs(h[l].y - k) <= i)
						{
							temp += M;
							hn++;
						}

					if (temp < 0) // 손해본 경우
						continue;

					ans = max(ans, hn);
				}
		}
		cout << '#' << t - T << ' ' << ans << '\n';
	}
	return 0;
}