#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Cell
{
	int x, y, age;
};

queue<Cell> c_v[11][2]; // idx-�����, ������/������/  
int T,t,N,M,K, cmap[660][660], sum; // cmap-> �Է¹��� �����
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
			cmap[nx][ny] = vit; // �ʿ� ���� 
			c_v[vit][0].push({ nx,ny,now }); // ������ ť�� ���� 
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
		// �Է�
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) 
			{
				cin >> cmap[i + 301][j + 301];

				if (cmap[i + 301][j + 301] != 0)
					c_v[ cmap[i + 301][j + 301] ][0].push( {i+301, j+301, 0 } );
			}
		// ����
		for (int now = 1; now <= K; now++) // ����ð�: 1�ð����� K�ð� ����
		{
			for (int i = 10; i >= 1; i--) // ��i�� ����� (������ǥ�� ���ĵɶ� ����� �����͸� �����Ǿ���)
			{
				Cell c = { 0,0,0 };

				if(!c_v[i][0].empty())
					c = c_v[i][0].front(); // ��� ��
				while (now - c.age == i+1 && !c_v[i][0].empty() ) // ���� ���� ����
				{
					c_v[i][1].push(c);
					spawn(c, i, now); // ����
					c_v[i][0].pop();
					
					if(!c_v[i][0].empty())
						c = c_v[i][0].front(); 
				}

				if(!c_v[i][1].empty())
					c = c_v[i][1].front(); // ��� ��
				while (now - c.age == 2*i && !c_v[i][1].empty() ) // �Ҹ� ���� ����
				{
					c_v[i][1].pop(); // �Ҹ�

					if (!c_v[i][1].empty())
						c = c_v[i][1].front(); 
				}
			}
		}
		// ��Ƴ��� ��ü�� 
		sum = 0;
		for (int i = 1; i < 11; i++)
			for (int j = 0; j < 2; j++)
				sum += c_v[i][j].size();

		cout << "#" << t - T << ' ' << sum << '\n';
	}
	return 0;
}