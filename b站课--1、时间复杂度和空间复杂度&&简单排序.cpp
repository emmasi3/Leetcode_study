#include <iostream>
#include <vector>
/*
* 1、冒泡排序（默认从小到大）-- b站30min
*	写算法也好，一定是先在纸上写出具体的思路，再利用程序提供的工具实现这个思路，对，要记住这一点
* 
* 2、异或运算讲解：35min
* 
* 3、异或运算的面试题，60min，可参考 b站课--1 两种图片，辅助理解，但是 (2) 图中的代码是有问题的，看这里的就行
* 
* 4、插入排序 -- 1:15:00，虽然理论的时间复杂度是一样的，但是实际测试肯定是 “插入排序” 更优一点，因为：
*	冒泡排序强制执行完规定的次数，但是插入排序会在合适的地方退出循环，只有最坏的情况才会执行完规定的次数
* 
* 5、二分查找
*	(1) 在一个有序(递增)的数组中，找一个数字
*	(2) 在一个有序(递增)的数组中，找 >=num 的最左侧的值。(解释: 0111222445667，找2，则下标最终为 4，这就是最左侧的值)
*/


/*
* @brief 交换数组 arr i、j位置的数字 -- 用异或 ^ 运算快一些，没有额外的内存开销
* @note i != j，若违背，则该位置会被置为0
*/
static void swap_(std::vector<int>& arr, int i, int j)
{
	arr[i] = arr[i] ^ arr[j];
	arr[j] = arr[i] ^ arr[j];
	arr[i] = arr[i] ^ arr[j];
}

static void bubbleSort(std::vector<int>& arr)
{
	if (arr.empty() || arr.size() < 2)
	{
		return;
	}

	for (int i = arr.size() - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			// 比较前一位与后一位，按断是否要交换
			if (arr[j] > arr[j + 1])
			{
				// 交换位置
				swap_(arr, j, j + 1);
			}
		}
	}

}

/*
* @brief 异或题目
* @param arr，要符合题目要求
* @note（1）现在有一个数组，里面有两种数字数量为 “奇数”，其余数字的数量都为 “偶数”，问：这两种数字都是什么
*/
static void printOddTimersNum2(std::vector<int>& arr)
{
	if (arr.empty() || arr.size() < 2) return;

	// 使用 err 记录整体异或后的值，也就是 a ^ b，这俩需要知道的数字
	int err = 0;
	for (auto& i : arr)
	{
		err ^= i;
	}
	// 任取 a 和 b 位不同的那一位（& 运算）
	int right_1 = err & (~err + 1);

	// 用来接收 a、b 中任意一个的变量
	int OnlyOne = 0;

	// 得到 a、b 中的任意一个
	for (auto& i : arr)
	{
		// 用 & 条件筛出，在该位置为 1 的 arr 中的数，
		if ((i & right_1) == right_1)
		{
			OnlyOne ^= i;
		}
	}

	// 得到另一个
	std::cout << OnlyOne << " " << (err ^ OnlyOne) << std::endl;
}

/*
* @brief 插入排序算法实现
*/
static void InsertionSort(std::vector<int>& arr)
{
	if (arr.empty() || arr.size() < 2) return;

	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = i; j > 0; --j)
		{
			// 这里可以提前退出，因为跟着 i 位置最近的一个数值，一定是前面最大的，既然已经比最大的还要大或者相等，就不用再次
			// 比较后续的了，无意义
			if (arr[j] >= arr[j - 1])
				break;

			// 看是否比前一位小
			if (arr[j] < arr[j - 1])
			{
				// 交换指定位置
				swap_(arr, j, j - 1);
			}
		}
	}

}

/*
* @brief 二分查找 -- (1)
*/
static bool binaryFindNum(std::vector<int>& arr, int num)
{
	if (arr.empty()) return false;

	// 左区间索引
	int left = 0;
	// 右区间索引
	int right = arr.size() - 1;

	// i 从中间位置开始，退出条件 left 与 right 相邻时，更新语句：i 始终位于 left、right 中间
	for (int i = (left + right) / 2; left + 1 != right; i = (left + right) / 2)
	{
		// 如果找到，直接退出
		if (arr[i] == num)
		{
			std::cout << i << std::endl;
			return true;
		}
		// 当前位置位于 num 右边，则将 i 置为右区间索引
		else if (arr[i] > num)
		{
			right = i;
		}
		// 当前位置位于 num 左边，则将 i 置为做区间索引
		else
		{
			left = i;
		}
	}

	std::cout << "not find " << num << " in this arr!";
	return false;
}

int main()
{
	// test_swap_()
	{
		std::vector<int> arr{ 4,3 };
		swap_(arr, 0, 1);
		for (auto& i : arr)
		{
			std::cout << i;
		}
		std::cout << std::endl;
	}

	// test_bubbleSort
	{
		std::vector<int> arr_bubbleSort{ 8, 5, 78, 25, 22 ,65 ,10 };
		bubbleSort(arr_bubbleSort);
		for (auto& i : arr_bubbleSort)
		{
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}

	// test_printOddTimersNum2 异或运算算法题
	{
		std::vector<int> arr{ 5, 8, 8, 8, 6, 6, 7, 7, 4, 4, 4, 4 };
		printOddTimersNum2(arr);
	}

	// test_InsertionSort
	{
		std::vector<int> arr{ 4, 6, 0, 1, 55, 23, 11, 22, 7};
		InsertionSort(arr);
		for (auto& i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	// test_binaryFindNum
	{
		std::vector<int> arr{ 4,6,10,22,44,44,44,52};
		bool ret = binaryFindNum(arr, 7);
	}

	return 0;
}