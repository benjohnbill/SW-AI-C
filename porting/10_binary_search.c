// 반복문 버전으로 다시 만들기(Python 참고)

#include <stdio.h>
#include "10_binary_search_cases.h"

int n1 =  sizeof(case1) / sizeof(case1[0]);
int n2 =  sizeof(case2) / sizeof(case2[0]);
int n3 =  sizeof(case3) / sizeof(case3[0]);

int last(int n){
    return (n == n1 || n == n2 || n == n3) ? n - 1 : -1;
} // return end-index of array.

int binary_search(const int arr[], int start, int end, int target){
    if (start > end){
        return -1;
    }
    // if (start == end){
    //     if (target == arr[start]){
    //         return start;
    //     } else{ // Not in Index - Error.
    //         return -1;
    //     } // half -1로 인해서 왜 지워졌는 지 생각
    // } // Base Case.

    int half = (start + end) / 2;
    if (target > arr[half]){
        return binary_search(arr, half + 1, end, target);
    } else if (target < arr[half]){
        return binary_search(arr, start, half - 1, target);
    } else {
        return half;
    }
}

int main(void){
// Case 1
    printf("\n배열: [");
    for (int i = 0; i < n1 - 1; i++){
        printf("%d, ", case1[i]);
    }
    printf("%d", case1[n1 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", case1_target);
    printf("결과: 인덱스 %d\n", binary_search(case1, 0, last(n1), case1_target));
// Case 2
    printf("\n배열: [");
    for (int i = 0; i < n2 - 1; i++){
        printf("%d, ", case2[i]);
    }
    printf("%d", case2[n2 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", case2_target);
    printf("결과: 인덱스 %d\n", binary_search(case2, 0, last(n2), case2_target));
// Case 3
    printf("\n배열: [");
    for (int i = 0; i < n3 - 1; i++){
        printf("%d, ", case3[i]);
    }
    printf("%d", case3[n3 - 1]);
    printf("]\n");
    printf("찾는 값: %d\n", case3_target);
    printf("결과: 인덱스 %d\n", binary_search(case3, 0, last(n3), case3_target));
}
