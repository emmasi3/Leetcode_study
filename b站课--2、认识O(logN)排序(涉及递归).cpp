#include <iostream>
#include <vector>

/*
* 1、递归行为 -- 20min，去看老师画的图，很精髓，敲代码时，先把算法搞清楚，再去着手实现
* 
* 2、归并排序(利用递归) -- 38min，这玩意就是要看图，不看图，我反正有点想不通递归的操作
* 
*/

/*
* @brief 递归排序 -- 一个无序的数组，找到 “指定区间” 的最大值
*/
static int process(std::vector<int>& arr, int L, int R)
{
	// 终止 “传递” 的条件，直到不可分时，即 L == R 时
	if (L == R)
	{
		return arr[L];
	}

	// 找到 L,R 中点索引 -- 因为 L + R 有时候会溢出，导致 / 2 结果出错，但是用 R - L 不会溢出, >> 1 表示 / 2
	int mid = L + ((R - L) >> 1);

	// 递归找左区间最大值
	int leftMax = process(arr, L, mid);
	// 递归找右区间最大值
	int rightMax = process(arr, mid + 1, R);

	// 返回 max(leftMax, rightMax); 两个区间最大值即为 -- 总区间最大值
	return leftMax > rightMax ? leftMax : rightMax;
}


/*
* @brief 归并 -- 将已经排好序的 [L ~ M] [M + 1 ~ R] 两个区间进行整合排序，最终给出 arr[L ~ R] 一整个区间的有序数组
*/
static void merge(std::vector<int>& arr, int L, int M, int R)
{
	// 用一个额外的数组接收 2 个区间排好序的数组，然后再复制给 arr 对应的区间 [L ~ R]
	std::vector<int> help;
	// 左区间索引
	int left = L;
	// 右区间索引
	int right = M + 1;

	// 一旦一方越界，直接结束循环，将未越界的直接拷贝进 help
	while (left <= M && right <= R)
	{
		if (arr[left] <= arr[right])
		{
			// 放入时 ++ 递增索引
			help.push_back(arr[left++]);
		}
		else
		{
			// 放入时 ++ 递增索引
			help.push_back(arr[right++]);
		}
	}

	// 处理越界情况
	while (left <= M)
	{
		help.push_back(arr[left++]);
	}

	while (right <= M)
	{
		help.push_back(arr[right++]);
	}

	// 将 help 归并完成的 [L ~ R] 数组给到原数组
	for (auto& i : help)
	{
		arr[L++] = i;
	}
}

/*
* @brief 归并排序
*/
static void process2(std::vector<int>& arr, int L, int R)
{
	if (L == R)
	{
		return;
	}
	// 计算中点(以左边为准)
	int mid = L + ((R - L) >> 1);
	// 排左区间
	process2(arr, L, mid);
	// 排右区间
	process2(arr, mid + 1, R);
	// “归并” 左右区间
	merge(arr, L, mid, R);
}

int main()
{
	// test_process
	{
		std::vector<int> arr{ 4, 5, 6, 22, 7, 16, 12, 0 };
		int arr_max = process(arr, 0, arr.size() - 1);
		std::cout << arr_max << std::endl;
	}

	// test_process2
	{
		std::vector<int> arr{ 4, 8, 10, 7, 1, 6, 0, 44, 21, 28 };
		process2(arr, 0, arr.size() - 1);
		for (int& i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}