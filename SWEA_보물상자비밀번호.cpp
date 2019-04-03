#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct cmp
{
	bool operator()(const int &a, const int &b)
	{
		return a > b;
	}
};

int T,t, N, K, qt, ans = 0, num;
vector<int> A;
set<int, cmp> Big;
string input;

void init()
{
	Big.clear();
	input.clear();
	A.clear();
}

int main()
{
	cin >> T;
	t = T;
	while (T--)
	{
		init();

		// 입력버퍼 초기화
		//fflush(stdin);

		cin >> N >> K;

		A.assign(N+1,0);
		qt = N / 4; 

		//input.clear();
		cin >> input;


		// A에 10진수로 저장
		for (int i = 0; i < N; i++)
		{
			if (input[i] <= '9')
				A[i] = input[i] - '0';
			else
				A[i] = input[i] - 'A' + 10;
		}


		for (int i = 0; i < qt; i++) // 회전 횟수
		{
			// 0 -> (0+ 1*(N-1)) % N, (0+ 2*(N-1)) % N  
			int s_idx;
			s_idx = (i * (N - 1)) % N;
			
			for (int j = s_idx; j < s_idx + N; j+= qt) // 시작 인덱스부터 끝까지 순회
			{
				num = 0;
				for(int k=0; k<qt; k++) // 한 변 순회 
					num += A[(j+k)%N] * pow(16, qt-1 -k);

				Big.insert(num);
			}
		}

		for (set<int, cmp>::iterator it = Big.begin(); it != Big.end(); it++)
		{
			K--;
			if (K == 0)
				ans = *it;
		}
		cout << "#" << t - T << ' ' << ans << '\n';
	}
	return 0;
}