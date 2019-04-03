#include<iostream>
#include<vector>
using namespace std;
int imap[101][101], T, t, N, L, cnt;
bool install[101][101], go_;
vector<int> ans;
int main()
{
	cin >> T;
	t = T;

	while (T--)
	{
		// 입력
		cin >> N >> L;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> imap[i][j];

		cnt = 0;

		// 경사로 설치 초기화
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				install[i][j] = false;

		// 행검사
		for (int i = 0; i < N; i++)
		{
			go_ = true;

			for (int j = 0; j < N - 1; j++)
			{
				if (imap[i][j] == imap[i][j + 1])
					continue;
				else if (imap[i][j] - imap[i][j + 1] == 1)
				{
					for (int k = j + 1; k < j + 1 + L; k++)
					{
						if (imap[i][k] == imap[i][j + 1] && install[i][k] == false)
							install[i][k] = true;
						else
						{
							go_ = false;
							break;
						}
					}
				}
				else if (imap[i][j] - imap[i][j + 1] == -1)
				{
					for (int k = j; k > j - L; k--)
					{
						if (imap[i][k] == imap[i][j] && install[i][k] == false)
							install[i][k] = true;
						else
						{
							go_ = false;
							break;
						}
					}
				}
				else
					go_ = false;

				if (go_ == false)
					break;
			}
			if (go_ == true)
				cnt++;
		}

		// 경사로 설치 초기화
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				install[i][j] = false;

		// 열검사
		for (int j = 0; j < N; j++)
		{
			go_ = true;

			for (int i = 0; i < N - 1; i++)
			{
				if (imap[i][j] == imap[i + 1][j])
					continue;
				else if (imap[i][j] - imap[i + 1][j] == 1) // 감소
				{
					for (int k = i + 1; k < i + 1 + L; k++)
					{
						if (imap[k][j] == imap[i + 1][j] && install[k][j] == false)
							install[k][j] = true;
						else
						{
							go_ = false;
							break;
						}
					}
				}
				else if (imap[i][j] - imap[i + 1][j] == -1) // 증가
				{
					for (int k = i; k > i - L; k--)
					{
						if (imap[k][j] == imap[i][j] && install[k][j] == false)
							install[k][j] = true;
						else
						{
							go_ = false;
							break;
						}
					}
				}
				else
					go_ = false;

				if (go_ == false)
					break;
			}
			if (go_ == true)
				cnt++;
		}

		ans.push_back(cnt);
	}

	for (int i = 0; i < ans.size(); i++)
		cout << "#" << i + 1 << ' ' << ans[i] << '\n';

	return 0;
}