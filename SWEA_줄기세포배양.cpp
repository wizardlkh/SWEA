#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Cell
{
	int x, y, age;
};

queue<Cell> c_v[11][2]; // idx-생명력, 번식전/번식후/  
int T,t,N,M,K, cmap[660][660], sum; // cmap-> 입력받은 생명력
int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };

void init()
{
	for (int i = 1; i < 11; i++)
		for (int j = 0; j < 2; j++)
			while (!c_v[i][j].empty())
				c_v[i][j].pop();

	for (int i = 0; i < 660; i++)
		for (int j = 0; j < 660; j++)
			cmap[i][j] = 0;
}

void spawn(Cell c, int vit, int now)
{
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = c.x + dx[i];
		ny = c.y + dy[i];
		
		if (cmap[nx][ny] == 0)
		{
			cmap[nx][ny] = vit; // 맵에 생성 
			c_v[vit][0].push({ nx,ny,now }); // 번식전 큐에 생성 
		}
	}
}

int main()
{
	cin >> T;
	t = T;

	while (T--)
	{
		init();

		cin >> N >> M >> K;
		// 입력
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) 
			{
				cin >> cmap[i + 301][j + 301];

				if (cmap[i + 301][j + 301] != 0)
					c_v[ cmap[i + 301][j + 301] ][0].push( {i+301, j+301, 0 } );
			}
		// 메인
		for (int now = 1; now <= K; now++) // 현재시간: 1시간부터 K시간 까지
		{
			for (int i = 10; i >= 1; i--) // ★i는 생명력 (같은좌표에 번식될때 생명력 높은것만 생성되야함)
			{
				Cell c = { 0,0,0 };

				if(!c_v[i][0].empty())
					c = c_v[i][0].front(); // 산란 전
				while (now - c.age == i+1 && !c_v[i][0].empty() ) // 번식 조건 도달
				{
					c_v[i][1].push(c);
					spawn(c, i, now); // 번식
					c_v[i][0].pop();
					
					if(!c_v[i][0].empty())
						c = c_v[i][0].front(); 
				}

				if(!c_v[i][1].empty())
					c = c_v[i][1].front(); // 산란 후
				while (now - c.age == 2*i && !c_v[i][1].empty() ) // 소멸 조건 도달
				{
					c_v[i][1].pop(); // 소멸

					if (!c_v[i][1].empty())
						c = c_v[i][1].front(); 
				}
			}
		}
		// 살아남은 개체수 
		sum = 0;
		for (int i = 1; i < 11; i++)
			for (int j = 0; j < 2; j++)
				sum += c_v[i][j].size();

		cout << "#" << t - T << ' ' << sum << '\n';
	}
	return 0;
}