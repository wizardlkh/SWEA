#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
int T, t, N, A[11][11], complete, ans;

struct XY
{
	int x, y, d[2];
};
struct STR
{
	int x, y, v;
};
vector<XY> man;
vector<STR> str;
vector<int> str_n;

void init()
{
	man.clear();
	str.clear();
	str_n.clear();
	ans = 10000000;
}

// ��� ������, ��� �����ؼ� ���, ��� ����������
priority_queue< int, vector<int>, greater<int> > n_arr[2]; // �ð�(=�Ÿ�) , PQ�� �����̹ݴ�� (���� ��������)
queue<int> arr[2];  // ������ �ð�
queue<int> down[2]; // �������� ����� �ð�

void cal_time(int t)
{
	for (int i = 0; i <= 1; i++) // �� ��ܿ� ����
	{
		while (!down[i].empty() && t - down[i].front() >= str[i].v) // ��� ��������
		{
			down[i].pop();
			complete++;
		}

		// �������� ����� 3���� �۾����� ����, ����ϴ� ��� ������������
		while (!arr[i].empty() && arr[i].front() <= t - 1 && down[i].size() < 3) // 1�д���� ��� ��������
		{
			down[i].push(t);
			arr[i].pop();
		}

		while (!n_arr[i].empty() && n_arr[i].top() == t) // ������Ű��
		{
			arr[i].push(t);
			n_arr[i].pop();
		}
	}

	if (complete == man.size())
		ans = min(ans, t);
	else
		cal_time(t + 1);
}

void sel_str()
{
	if (str_n.size() == man.size())
	{
		for (int i = 0; i < man.size(); i++)
		{
			int stair = str_n[i];
			n_arr[stair].push(man[i].d[stair]); // ��� ������ ť�� �ְ�,   
		}
		complete = 0;
		cal_time(0); // �ð����
		return;
	}

	for (int i = 0; i <= 1; i++)
	{
		str_n.push_back(i);
		sel_str();
		str_n.pop_back();
	}
}

int main()
{
	cin >> T;
	t = T;

	while (T--)
	{
		cin >> N;
		init();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> A[i][j];

				if (A[i][j] == 1)
					man.push_back({ i,j, 0, 0 });
				else if (A[i][j] > 1)
					str.push_back({ i, j, A[i][j] });
			}

		for (int j = 0; j < man.size(); j++)
		{
			man[j].d[0] = abs(man[j].x - str[0].x) + abs(man[j].y - str[0].y);
			man[j].d[1] = abs(man[j].x - str[1].x) + abs(man[j].y - str[1].y);
			//cout << man[j].x <<", "<< man[j].y << ", " << man[j].d[0] << ", " << man[j].d[1] << '\n';
		}

		sel_str();
		cout << '#' << t - T << ' ' << ans << '\n';
	}
	return 0;
}