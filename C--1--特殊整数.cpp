#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

bool p[1000001] = { false };

bool judge1(int num)
{
	int num1 = num;
	vector<int> v1;
	for (int i = 0; num1 > 0; i++)
	{
		v1.push_back(num1 % 10);
		num1 /= 10;
	}

	for (int i = 0; i < v1.size(); i++)
	{
		num1 += v1[i] * pow(10, v1.size() - i - 1);
	}
	//素数
	if (p[num1])
	{
		return false;
	}
	//回文数
	if (num1 == num)
	{
		return false;
	}

	return true;
}


int main()
{
	p[0] = 1; p[1] = 1;
	//构建素数集合，0为素数
	for (int i = 2; i < 1000001; i++)
	{  
		//如果是素数
		if (!p[i])
		{
			for (int j = i + i; j < 100001; j += i)
			{
				//判断是否已经处理？
				if (p[j])
				{
					continue;
				}
				//没处理的，现在处理
				p[j] = true;
			}
		}
	}

	int m, k, n = 0;
	cin >> m >> k;

	for (int i = m; n < k; i++)//要输出k个反素数
	{
		//先判断素数
		if (!p[i])
		{
			//再判断反素数 && 回文数
			if (judge1(i))
			{
				n++;
				cout << i << endl;
			}
		}
	}

	return 0;
}