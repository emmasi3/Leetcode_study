#include <iostream>
#include <vector>

/*
* 1、递归行为 -- 20min，去看老师画的图，很精髓，敲代码时，先把算法搞清楚，再去着手实现
* 
* 2、归并排序(利用递归) -- 38min，这玩意就是要看图，不看图，我反正有点想不通递归的操作
* 
* 3、小和问题(利用归并思想) -- 1:05:02，
*	 逆序对问题，统计一个数组中有多少个逆序对，逆序对: 一个元素的右边若有比它小的数，则为一个逆序对
*    {3,4,1,5,6}; 以3为例，有 (3,1) 一对，然后遍历就好，这样效率不行
*	 修改小和问题的解决方法即可，只是统计数量而已
* 
* 4、荷兰国旗问题 -- 1:40:00 左右或者以前
*	（1）要求：时间复杂度 O(N)，空间复杂度 O(1)
*	（2）要求同 (1), 分3个区间
* 
* 5、快速排序 -- 2:06:00
*	（1）1.0 --               -- O(N2)
*	（2）2.0 -- 基于荷兰问题	  -- O(N2)
*	（3）3.0 -- 时间复杂度最优 -- O(N * logN)
*/

static void swap_(std::vector<int>& arr, int i, int j)
{
	// 本来就相等，不用交换，但是我担心的不是这个，而是 i == j 时，回归零，因为你后续修改的是同一块内存，第一步就直接归零了，后续步骤没意义
	// 但是同一块内存上的值也必定相等，所以在 arr[i] == arr[j] 时，直接返回，两种情况都避免了，当然，第一种情况，不会引发风险，只是没必要交换
	if (arr[i] == arr[j])
	{
		return;
	}

	arr[i] = arr[i] ^ arr[j];
	arr[j] = arr[i] ^ arr[j];
	arr[i] = arr[i] ^ arr[j];
}

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

/*
* @brief 小和问题归并排序方法
*/
static int Small_merge(std::vector<int>& arr, int L, int mid, int R)
{
	std::vector<int> help;	// 辅助容器
	int left = L;			// 左区间索引
	int right = mid + 1;	// 右区间索引
	int ret = 0;			// 小和

	while (left <= mid && right <= R)
	{
		// 左区间 < 右区间 指定元素，拷贝left并给到help
		if (arr[left] < arr[right])
		{
			ret += ((R - right + 1) * arr[left]);
			help.push_back(arr[left]);
			++left;
		}
		// 左区间 >= 右区间 指定元素，优先拷贝右区间(这样右指针就不用回退)
		else
		{
			help.push_back(arr[right]);
			++right;
		}
	}

	// 塞剩余的数据，到这里不用
	while (left <= mid)
	{
		help.push_back(arr[left++]);
	}

	while (right <= R)
	{
		help.push_back(arr[right++]);
	}

	// 将 help 同步到 arr
	for (int& i : help)
	{
		arr[L++] = i;
	}

	return ret;
}

static int Small_process(std::vector<int>& arr, int L, int R)
{
	if (L == R)
	{
		// 仅剩一个元素时，直接返回 0，因为小和问题中，1个元素没法比较，那么 “小和” 也就是0
		return 0;
	}

	// 计算中点
	int mid = L + ((R - L) >> 1);

	return Small_process(arr, L, mid) + Small_process(arr, mid + 1, R) + Small_merge(arr, L, mid, R);
}

/*
* @brief 小和问题
*/
static int Small_num(std::vector<int>& arr)
{
	if (arr.empty() || arr.size() < 2)
	{
		return 0;
	}

	return Small_process(arr, 0, arr.size() - 1);
}

/*
* @brief 荷兰国旗问题（1） -- 划分算法 {<= num, > num}
* @param int num 指定的数字
* @return left 返回 <= 区间最后一个元素索引
*/
static int partition_0(std::vector<int>& arr, int num)
{
	if (arr.empty() || arr.size() < 2)
		return 0;
	// 左区间索引，从 -1 开始，也就是 <= num 的区间
	int left = -1;

	for (int i = 0; i < arr.size(); ++i)
	{
		// 找到之后直接调换位置，++left推进左区间
		if (arr[i] <= num)
		{
			swap_(arr, i, left + 1);
			++left;
		}
	}

	return left;
}

/*
* @brief 荷兰国旗问题（2） -- 划分算法 {< num, == num, > num}
* @param int num 指定的数字
*/
static void partition(std::vector<int>& arr, int num)
{
	if (arr.empty() || arr.size() < 2)
		return;

	int left = -1;				// < 区间索引
	int right = arr.size();		// > 区间索引

	// 退出条件，直到 i 与 right > 区间相遇
	for (int i = 0; i < right; ++i)
	{
		// < num，交换位置(< 区间下一个)，并扩展 < 区间
		if (arr[i] < num)
		{
			swap_(arr, i, (left++) + 1);
			continue;
		}
		// == num，不做修改，查看下一个元素
		else if (arr[i] == num)
		{
			continue;
		}
		// > num，交换位置(> 区间下一个)，并扩展 > 区间，并查看交换过来的元素(即 --i)
		else
		{
			swap_(arr, i, (right--) - 1);
			--i;
			continue;
		}
	}

}

/*
* @brief 划分指定数组指定区间的元素 <=, >
* @param left 左边界
* @param num 右边界
*/
static int Q_S_partition(std::vector<int>& arr, int L, int num)
{
	if (arr.empty() || arr.size() < 2)
		return 0;
	// 左区间索引，从 L - 1 开始，重新计算 <= arr[num] 的区间末尾索引
	int left = L - 1;

	for (int i = L; i < num; ++i)
	{
		// 找到之后直接调换位置，++left推进左区间
		if (arr[i] <= arr[num])
		{
			swap_(arr, i, left + 1);
			++left;
		}
	}

	return left;
}

/*
* @brief 快速排序 -- 1
*/
static void Quick_Sort_1(std::vector<int>& arr, int L, int R)
{
	if (L < R)
	{
		// 获取 <= 区间最后一个元素的索引
		int left = Q_S_partition(arr, L, R);
		// 交换最后一个与 > 区间第一个（因为交换完之后，换回来的还是一个 > R 的数字）
		swap_(arr, R, left + 1);
		// 继续对 <= 和 > 区间分别划分
		Quick_Sort_1(arr, L, left);
		Quick_Sort_1(arr, left + 1, R);
	}

	// 直到 L == R，什么都不做，因为只有一个元素，递归退出条件
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

	// test_Small_num
	{
		std::vector<int> arr{ 1,3,4,2,5,7 };
		std::cout << "小和：" << Small_num(arr) << std::endl;
	}

	// test_partition_0
	{
		std::vector<int> arr{ 4,8,4,5,9,10,7,6,4,12 };
		int num = 9;
		partition_0(arr, num);
		for (int& i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	// test_partition
	{
		//std::vector<int> arr{ 4, 9, 4, 3, 7, 4, 8, 4, 1, 6, 4, 2, 9, 4 };
		std::vector<int> arr{ 4, 9, 4, 3, 7, 4, 8, 4, 1, 6, 4, 2, 9, 4 };
		int num = 4;
		partition(arr, num);
		for (int& i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	// test_Quick_Sort_1
	{
		std::vector<int> arr{ 4, 7, 1, 8, 9, 2, 4 ,5, 6,6, 47, 25 };
		Quick_Sort_1(arr, 0, arr.size() - 1);
		for (int& i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}