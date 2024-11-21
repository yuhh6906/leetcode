#include <iostream>
#include <vector>
using namespace std;

void quickSort(std::vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    /* Partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };

    /* Recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
/* 冒泡排序*/
void BubbleSort(vector<int>& arr, int n) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if(arr[i] > arr[j]) swap(arr[i], arr[j]);
        }
    }
}

/*选择排序（Selection Sort）
 * 这个算法就是我们笔算排序用的算法。在一组数中找出最小的一个排在第一个位置，然后在剩下的数中找一个次小的排在第二位*/
void SelectionSort(vector<int>& arr, int n) {
    int minindex = 0;
    for (int i = 0; i < arr.size() - 1; ++i) {
        minindex = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if(arr[j] < arr[minindex]){
                minindex = j;
            }
        }
        if(minindex != i){
            swap(arr[i], arr[minindex]);
        }
    }
}

/*插入排序（Insertion Sort）
 * 将原来待排序的数组划分成两个区域，即无序区和有序区，有序区开始只包含第一个元素，其右侧剩下的元素均处于无序区。
 * 每次对无序区第一个元素进行排序，即将无序区第一个元素和有序区最后一个元素比较（由后向前比较），
 * 如果比较过程中出现两者比较后需要交换位置则交换其位置，然后向前移一位继续俩俩比较，直到前面没有可以比较元素则停止，排序结束
*/
void InsertionSort(vector<int>& arr, int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; --j) {
            if(arr[j] < arr[j - 1]){
                swap(arr[j], arr[j-1]);
            } else{
                break;
            }
        }
    }
}

int main() {
    std::vector<int> vec = {3, 123, 6, 9, 10, 0, 2, 1};
//    quickSort(vec, 0, vec.size() - 1);
//    BubbleSort(vec, vec.size());
//    SelectionSort(vec,  vec.size());


    InsertionSort(vec,  vec.size());
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}