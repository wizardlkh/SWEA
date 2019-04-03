#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct BC
{
	int i, x, y, c, p;
};
vector<BC> BCv;



struct BC_ip
{
	int i, p;
};

struct cmp
{
	bool operator()(BC_ip &a, BC_ip &b)
	{
		return a.p < b.p;
	}
};

priority_queue<BC_ip, vector<BC_ip> , cmp> tmap[11][11];
vector<int> mv[2]; 
int T, t, M, A, im, ans = 0, A_i;
int dx[5] = { 0, -1, 0, 1,  0 };
int dy[5] = { 0,  0, 1, 0, -1 };
bool vst[11][11];

void f_map(int i, int x, int y, int c, int p)
{
	int nx, ny, q_s, cnt = 0;

	queue< pair<int, int> > q;
	q.push({ x, y });
	tmap[x][y].push({ i, p });
	vst[x][y] = true;

	while (!q.empty())
	{
		cnt++;

		if (cnt > c)
			return;

		q_s = q.size();
		for (int j = 0; j < q_s; j++)
		{
			x = q.front().first;
			y = q.front().second;
			q.pop();

			for (int k = 1; k < 5; k++)
			{
				nx = x + dx[k];
				ny = y + dy[k];

				if ((0 <= nx && nx < 10) && (0 <= ny && ny < 10))
					if (vst[nx][ny] == false)
					{
						vst[nx][ny] = true;
						q.push({ nx,ny });
						tmap[nx][ny].push({ i,p });

						cout << nx << ", " << ny << ", " << i << '\n';

					}
			}
		}
	}
}

int main()
{
	cin >> T;
	t = T;

	while (T--)
	{
		cin >> M >> A;

		mv[0].push_back(0);
		mv[1].push_back(0);

		for(int i = 0; i < 2; i++)
			for (int j = 0; j < M; j++)
			{
				cin >> im;
				mv[i].push_back(im);
			}

		for (int i = 0; i < A; i++)
		{
			int x, y, c, p;
			cin >> x >> y >> c >> p;
			
			BCv.push_back({i + 1, x-1, y-1, c, p});
		}

		for (int i = 0; i < A; i++) // 각 기지국별 데이터로 tmap 채우기
		{
			for (int j = 0; j < 10; j++)
				for (int k = 0; k < 10; k++)
					vst[j][k] = false;

			f_map(BCv[i].i, BCv[i].x, BCv[i].y, BCv[i].c, BCv[i].p);
		}
			











		int ax = 0, ay = 0 , bx = 9 , by = 9;

		for (int i = 0; i <= M; i++) // i는 시간 
		{
			// A이동
			ax += dx[mv[0][i]];
			ay += dy[mv[0][i]];
			// B이동
			bx += dx[mv[1][i]];
			by += dy[mv[1][i]];
			
			A_i = -1;
			BC_ip rmv;
			int rmved = 0;

			if (!tmap[ax][ay].empty())
			{
				A_i  = tmap[ax][ay].top().i; // 방문된 인덱스 저장

				cout << "시간: " << i << ", A: " << tmap[ax][ay].top().p << "좌표: " << ax << ", " <<  ay << '\n';

				ans += tmap[ax][ay].top().p; // 가장 큰 파워 저장
			}
			while (!tmap[bx][by].empty())
			{
				if (tmap[bx][by].top().i == A_i)
				{
					rmved = 1;
					rmv = tmap[bx][by].top(); // 지울거 백업
					tmap[bx][by].pop();
					continue;
				}

				cout << "시간: " << i << ", B: " << tmap[bx][by].top().p << "좌표: " << bx << ", " << by << '\n';
				ans += tmap[bx][by].top().p; // 가장 큰 파워 저장
				break;
			}

			if(rmved == 1)
				tmap[bx][by].push(rmv); // 지운거 복원
		}
		
		cout << ans << '\n';
	}
	return 0;
}