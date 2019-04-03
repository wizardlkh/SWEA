#include<iostream>
#include<set>
#include<queue>
using namespace std;
int T, t, N, M, R, C, L, A[51][51], ans;
int dx[4] = { -1, 0, 1,  0 };
int dy[4] = { 0, 1, 0, -1 };
bool vst[51][51];

set<int> Tunn[8];

struct XY
{
	int x, y;
};

void bfs(int x, int y, int t)
{
	int nx, ny, qs, tn;
	queue<XY> q;

	q.push({ x,y });
	vst[x][y] = true;
	ans++;

	while (!q.empty() && t < L)
	{
		qs = q.size();
		for (int i = 0; i < qs; i++)
		{
			x = q.front().x;
			y = q.front().y;
			q.pop();

			tn = A[x][y];

			for (auto it = Tunn[tn].begin(); it != Tunn[tn].end(); it++) // *it는 방향 0123
			{
				nx = x + dx[*it];
				ny = y + dy[*it];

				if ((0 <= nx && nx < N) && (0 <= ny && ny < M))
					if (A[nx][ny] != 0 && vst[nx][ny] == false)
						if (Tunn[A[nx][ny]].find((*it + 2) % 4) != Tunn[A[nx][ny]].end())
						{
							q.push({ nx,ny });
							vst[nx][ny] = true;
							ans++;
						}
			}
		}
		t++;
	}
}

void init()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			vst[i][j] = false;

	ans = 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	t = T;

	// 파이프 방향 저장
	for (int i = 0; i<4; i++)
		Tunn[1].insert(i);
	for (int i = 0; i < 3; i += 2)
		Tunn[2].insert(i);
	for (int i = 1; i <= 3; i += 2)
		Tunn[3].insert(i);
	for (int i = 0; i < 2; i++)
		Tunn[4].insert(i);
	for (int i = 1; i <= 2; i++)
		Tunn[5].insert(i);
	for (int i = 2; i <= 3; i++)
		Tunn[6].insert(i);
	for (int i = 0; i <= 3; i += 3)
		Tunn[7].insert(i);

	while (T--)
	{
		cin >> N >> M >> R >> C >> L;
		init();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> A[i][j];

		bfs(R, C, 1);

		/*
		for (int i = 0; i < N; i++)
		{
		for (int j = 0; j < M; j++)
		cout << vst[i][j] << ' ';
		cout << '\n';
		}
		*/

		cout << '#' << t - T << ' ' << ans << '\n';
	}
	return 0;
}