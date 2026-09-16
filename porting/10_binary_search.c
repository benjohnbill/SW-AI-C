// 반복문 버전으로 다시 만들기(Python 참고)

#include <stdio.h>
#include "10_binary_search_cases.h"

int n1 =  sizeof(bs1) / sizeof(bs1[0]);
int n2 =  sizeof(bs2) / sizeof(bs2[0]);
int n3 =  sizeof(bs3) / sizeof(bs3[0]);

int last(int n){
    return (n == n1 || n == n2 || n == n3) ? n - 1 : -1;
} // return end-index of array.

int binary_search(const int arr[], int start, int end, int target){
    if (start > end){
        return -1; // Base Case.
    }

    int half = (start + end) / 2;
    if (target > arr[half]){
        return binary_search(arr, half + 1, end, target);
    } else if (target < arr[half]){
        return binary_search(arr, start, half - 1, target);
    } else {
        return half;
    }
}

// ===================== Iteration Version =======================
// int binary_search(const int arr[], int start, int end, int target){
//     if (start > end){
//         return -1; // Base Case.
//     }


//     while (start <= end){
//         int half = (start + end) / 2;
//         if (target > arr[half]){
//             start = half + 1;
//         } else if (target < arr[half]){
//             end = half - 1;
//         } else {
//             return half;
//         }
//     }
//     return -1;
// }
// ===========================================================

int main(void){
// Case 1
    printf("\n배열: [");
    for (int i = 0; i < n1 - 1; i++){
        printf("%d, ", bs1[i]);
    }
    printf("%d", bs1[n1 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", tg1);
    printf("결과: 인덱스 %d\n", binary_search(bs1, 0, last(n1), tg1));
// Case 2
    printf("\n배열: [");
    for (int i = 0; i < n2 - 1; i++){
        printf("%d, ", bs2[i]);
    }
    printf("%d", bs2[n2 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", tg2);
    printf("결과: 인덱스 %d\n", binary_search(bs2, 0, last(n2), tg2));
// Case 3
    printf("\n배열: [");
    for (int i = 0; i < n3 - 1; i++){
        printf("%d, ", bs3[i]);
    }
    printf("%d", bs3[n3 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", tg3);
    printf("결과: 인덱스 %d\n", binary_search(bs3, 0, last(n3), tg3));
}
