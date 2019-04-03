#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
int T, N, A[105][105], temp, ox, oy, ans = 0;
vector< pair<int, int> > worm[12];
int dx[4] = { -1,  0, 1,  0 };
int dy[4] = { 0,  1, 0, -1 }; // 북동남서

struct XYD
{
	int x, y, d;
};

queue< XYD > q;
void dfs(int x, int y, int d);

void bounce(int &d, int bl)
{
	if (bl == 1 && (d == 2 || d == 3))
	{
		if (d == 2)
			d -= 1;
		else
			d = (d + 1) % 4;
	}
	else if (bl == 2 && (d == 1 || d == 3))
	{
		d = (d + 1) % 4;
	}
	else if (bl == 3 && (d == 0 || d == 1))
	{
		if (d == 0)
			d += 3;
		else
			d += 1;
	}
	else if (bl == 4 && (d == 1 || d == 2))
	{
		if (d == 1)
			d -= 1;
		else
			d += 1;
	}
	else // 나머지 모든 경우 -> 반대로 튕겨나올 경우
	{
		d = (d + 2) % 4;
	}

	//q.push({ x,y,d });
}

void d_bounce(int &d, int bl)
{
	if (bl == 1 && (d == 2 || d == 3))
	{
		if (d == 2)
			d -= 1;
		else
			d = (d + 1) % 4;
	}
	else if (bl == 2 && (d == 0 || d == 3))
	{
		if (d == 0)
			d += 1;
		else
			d -= 1;
	}
	else if (bl == 3 && (d == 0 || d == 1))
	{
		if (d == 0)
			d += 3;
		else
			d += 1;
	}
	else if (bl == 4 && (d == 1 || d == 2))
	{
		if (d == 1)
			d -= 1;
		else
			d += 1;
	}
	else // 나머지 모든 경우 -> 반대로 튕겨나올 경우
	{
		d = (d + 2) % 4;
	}

	//dfs(x, y, d);
	//return;
}

void dfs(int x, int y, int d)
{
	int nx, ny;

	do {
		
		nx = x + dx[d];
		ny = y + dy[d];
		
		x = nx;
		y = ny;

		if (6 <= A[nx][ny] && A[nx][ny] <= 10) // 웜홀
		{
			if (worm[A[nx][ny]][0].first == nx && worm[A[nx][ny]][0].second == ny)
			{
				nx = worm[A[nx][ny]][1].first;
				ny = worm[A[nx][ny]][1].second;
			}
			else
			{
				nx = worm[A[nx][ny]][0].first;
				ny = worm[A[nx][ny]][0].second;
			}				
		}
		else if (1 <= A[nx][ny] && A[nx][ny] <= 5) // 블록
		{
			temp++;
			d_bounce(d, A[nx][ny]); // 방향만 바뀜 
		}

	} while ( !(nx == ox && ny == oy) && !A[nx][ny] == -1 );// 시작점 도착, 블랙홀
}

/*
// 구슬 출발
void bfs(int x, int y, int d)
{
	int nx, ny, wx, wy; // 출발점 저장
	q.push({ x,y,d });

	while (!q.empty())
	{
		x = q.front().x;
		y = q.front().y;
		d = q.front().d;
		q.pop();

		nx = x + dx[d];
		ny = y + dy[d];

		if ((nx == ox && ny == oy) || A[nx][ny] == -1) // 시작점 or 블랙홀 종료
			return;

		if (A[nx][ny] == 0) // 빈공간
		{
			q.push({ nx,ny, d });
			continue;
		}

		if (A[nx][ny] >= 6) // 웜홀
		{
			if (worm[A[nx][ny]][0] == make_pair(nx, ny))
			{
				wx = worm[A[nx][ny]][1].first;
				wy = worm[A[nx][ny]][1].second;
			}
			else
			{
				wx = worm[A[nx][ny]][0].first;
				wy = worm[A[nx][ny]][0].second;
			}
			q.push({ wx, wy, d });
			continue;
		}

		if (A[nx][ny] <= 5) // 블록
		{
			temp++;
			bounce(nx, ny, d, A[nx][ny]);
		}
	}
}
*/

void init()
{
	ans = 0;

	for (int i = 6; i <= 10; i++)
		worm[i].clear();
}

int main()
{
	cin >> T;

	for (int m = 1; m <= T; m++)
	{
		cin >> N;

		init();

		// 입력 및 웜홀 저장
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				cin >> A[i][j];

				if (6 <= A[i][j] && A[i][j] <= 10)
					worm[A[i][j]].push_back(make_pair(i, j));
			}

		// 외곽에 5채우기
		for (int j = 0; j <= N + 1; j++)
		{
			A[0][j] = 5;
			A[N + 1][j] = 5;
			A[j][0] = 5;
			A[j][N + 1] = 5;
		}

		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				for (int k = 0; k < 4; k++)
					if (A[i][j] == 0)
					{
						temp = 0;
						ox = i;
						oy = j;
						//bfs(i, j, k);
						dfs(i, j, k);
						ans = max(ans, temp);
					}

		cout << "#" << m << " " << ans << '\n';
	}
	return 0;
}