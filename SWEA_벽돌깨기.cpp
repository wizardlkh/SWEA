#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<tuple>
#include<stack>
using namespace std;

int T, t, N, W, H, A[16][13], B[16][13], t_brick, broken, m_ans;
int col[5];
int dx[4] = { 1,-1, 0,  0 };
int dy[4] = { 0, 0, 1, -1 };

// 깨트리기
void bfs(int y)
{
	int x = 0;

	// 최초로 0아닌 것 저장
	for (int i = 0; i < H; i++)
		if (B[i][y] != 0)
		{
			x = i;
			break;
		}

	if (B[x][y] == 0)
		return;

	queue < tuple <int, int, int> > xyv;
	xyv.push(make_tuple(x, y, B[x][y]));
	B[x][y] = 0;
	broken++;

	while (!xyv.empty())
	{
		int nx, ny, val;
		tie(x, y, val) = xyv.front();
		xyv.pop();

		for (int i = 0; i < 4; i++) // 4 방향별	
			for (int j = 1; j < val; j++)
			{
				nx = x + (dx[i] * j);
				ny = y + (dy[i] * j);

				if ((0 <= nx && nx < H) && (0 <= ny && ny < W))
				{
					if (B[nx][ny] != 0)
					{
						broken++;
						xyv.push(make_tuple(nx, ny, B[nx][ny]));
						B[nx][ny] = 0; // 큐에 먼저 넣고 0으로 만들기 
					}
				}
				else
					break;
			}
	}

	// 벽돌깬 후 빈칸 땡기기 
	stack<int> draw;
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
			if (B[j][i] != 0)
			{
				draw.push(B[j][i]);
				B[j][i] = 0;
			}

		for (int j = H - 1; j >= 0; j--)
		{
			if (!draw.empty())
			{
				B[j][i] = draw.top();
				draw.pop();
			}
			else
				break;
		}
	}
}

void sel_col(int dep)
{
	if (dep == N)
	{
		// 깬 벽돌 초기화
		broken = 0;

		// 맵 복사
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				B[i][j] = A[i][j];

		// 깨부실 열마다 bfs
		for (int i = 0; i < N; i++)
		{
			if (m_ans == 0)
				return;

			bfs(col[i]);
		}

		// 남은 블록개수가 최소이면 저장
		m_ans = min(m_ans, t_brick - broken);
		return;
	}

	for (int i = 0; i < W; i++)
	{
		// 중복순열 
		col[dep] = i;
		sel_col(dep + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	t = T;
	while (T--)
	{
		m_ans = 2000;
		cin >> N >> W >> H;
		t_brick = 0;

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				cin >> A[i][j];
				if (A[i][j] != 0)
					t_brick++;
			}

		sel_col(0);

		// 정답 출력
		cout << "#" << t - T << ' ' << m_ans << '\n';
	}
	return 0;
}