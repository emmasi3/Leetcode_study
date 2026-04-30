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
	std::cout << OnlyOne << " " << (err ^= OnlyOne) << std::endl;

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

	return 0;
}