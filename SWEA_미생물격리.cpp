#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int T, t, N, M, K, x, y, n, d, ans, A[101][101];
int dx[4] = { -1, 0, 1,  0 }; // 북동남서
int dy[4] = { 0, 1, 0, -1 };

struct Bio
{
	int x, y, n, d;
};
struct ND
{
	int n, d;
};

vector<Bio> bio;

vector<ND> pq[101][101]; // 인덱스는 결합할 좌표
ND nd[101][101]; // 최대n의 d 저장

void move(int t)
{
	int nx, ny;



	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			nd[i][j].n = 0;
			nd[i][j].d = 0;
			pq[i][j].clear();
		}

	for (int i = 0; i < bio.size(); i++)
	{
		nx = bio[i].x + dx[bio[i].d];
		ny = bio[i].y + dy[bio[i].d];

		if (nd[nx][ny].n < bio[i].n)
		{
			nd[nx][ny].n = bio[i].n;
			nd[nx][ny].d = bio[i].d;
		}

		pq[nx][ny].push_back({ bio[i].n, bio[i].d });
	}
	bio.clear();

	// 시약에 닿은 것 처리
	for (int i = 0; i < N; i++)
	{
		ND a;

		//
		if (!pq[0][i].empty())
		{
			a = pq[0][i][0];
			a.n /= 2;
			a.d = (a.d + 2) % 4;

			if (a.n == 0)
				continue;

			bio.push_back({ 0, i, a.n, a.d });
			pq[0][i].clear();
		}

		//
		if (!pq[N - 1][i].empty())
		{
			a = pq[N - 1][i][0];
			a.n /= 2;
			a.d = (a.d + 2) % 4;

			if (a.n == 0)
				continue;

			bio.push_back({ N - 1, i, a.n, a.d });
			pq[N - 1][i].clear();
		}

		//
		if (!pq[i][0].empty())
		{
			a = pq[i][0][0];
			a.n /= 2;
			a.d = (a.d + 2) % 4;

			if (a.n == 0)
				continue;

			bio.push_back({ i, 0, a.n, a.d });
			pq[i][0].clear();
		}

		//
		if (!pq[i][N - 1].empty())
		{
			a = pq[i][N - 1][0];
			a.n /= 2;
			a.d = (a.d + 2) % 4;

			if (a.n == 0)
				continue;

			bio.push_back({ i, N - 1, a.n, a.d });
			pq[i][N - 1].clear();
		}
	}

	// 시약 안닿은거 처리
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++)
		{
			if (pq[i][j].size() == 0)
				continue;

			int sum = 0;
			int n_d = nd[i][j].d; // n이 가장 큰 군집의 방향

			for (int k = 0; k < pq[i][j].size(); k++)
				sum += pq[i][j][k].n;

			pq[i][j].clear();
			bio.push_back({ i,j, sum, n_d });
		}

	if (t != M)
		move(t + 1);
	else
		for (int i = 0; i < bio.size(); i++)
			ans += bio[i].n;
}

void init()
{
	bio.clear();
	ans = 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	t = T;

	while (T--)
	{
		cin >> N >> M >> K;
		init();

		for (int i = 0; i < K; i++)
		{
			cin >> x >> y >> n >> d;

			if (d == 1)
				d = 0;
			else if (d == 4)
				d = 1;

			bio.push_back({ x, y, n, d });
		}
		move(1);
		cout << '#' << t - T << ' ' << ans << '\n';
	}
	return 0;
}