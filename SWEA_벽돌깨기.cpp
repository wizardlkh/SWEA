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

// ��Ʈ����
void bfs(int y)
{
	int x = 0;

	// ���ʷ� 0�ƴ� �� ����
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

		for (int i = 0; i < 4; i++) // 4 ���⺰	
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
						B[nx][ny] = 0; // ť�� ���� �ְ� 0���� ����� 
					}
				}
				else
					break;
			}
	}

	// ������ �� ��ĭ ����� 
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
		// �� ���� �ʱ�ȭ
		broken = 0;

		// �� ����
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				B[i][j] = A[i][j];

		// ���ν� ������ bfs
		for (int i = 0; i < N; i++)
		{
			if (m_ans == 0)
				return;

			bfs(col[i]);
		}

		// ���� ��ϰ����� �ּ��̸� ����
		m_ans = min(m_ans, t_brick - broken);
		return;
	}

	for (int i = 0; i < W; i++)
	{
		// �ߺ����� 
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

		// ���� ���
		cout << "#" << t - T << ' ' << m_ans << '\n';
	}
	return 0;
}