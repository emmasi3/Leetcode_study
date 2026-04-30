#include <iostream>
#include <vector>
/*
* 1、冒泡排序（默认从小到大）-- b站30min
*	写算法也好，一定是先在纸上写出具体的思路，再利用程序提供的工具实现这个思路，对，要记住这一点
* 2、异或运算讲解：35min
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

	return 0;
}