#include <stdio.h>
#include "11_divide_conquer_cases.h"

int n1 =  sizeof(dc1) / sizeof(dc1[0]);
int n2 =  sizeof(dc2) / sizeof(dc2[0]);
int n3 =  sizeof(dc3) / sizeof(dc3[0]);

int end(int n){
    return (n == n1 || n == n2 || n == n3) ? n - 1 : -1;
} // return end-index of array.

int divide_conquer(const int arr[], int start, int end){
    if (start == end){
        return arr[start];
    }
    int half = (start + end) / 2;
    int leftmax = divide_conquer(arr, start, half);
    int rightMax = divide_conquer(arr, half + 1, end);

    // Compare Operation
    return (leftmax >= rightMax) ? leftmax : rightMax;
}

int main(void){
// Case 1
    printf("\n배열: [");
    for (int i = 0; i < n1 - 1; i++){
        printf("%d, ", dc1[i]);
    }
    printf("%d", dc1[n1 - 1]);
    printf("]\n");
    printf("최댓값: %d\n", divide_conquer(dc1, 0, end(n1)));
// Case 2
    printf("\n배열: [");
    for (int i = 0; i < n2 - 1; i++){
        printf("%d, ", dc2[i]);
    }
    printf("%d", dc2[n2 - 1]);
    printf("]\n");
    printf("최댓값: %d\n", divide_conquer(dc2, 0, end(n2)));
// Case 3
    printf("\n배열: [");
    for (int i = 0; i < n3 - 1; i++){
        printf("%d, ", dc3[i]);
    }
    printf("%d", dc3[n3 - 1]);
    printf("]\n");
    printf("최댓값: %d\n", divide_conquer(dc3, 0, end(n3)));
}



//==========================================
//
// [LinkedList Style Definition - pointer problem]
// typedef struct _array{
//     int arr[];
//     struct _array *left;
//     struct _array *right;
// } Array;
//
// ==========================================
//
// [Copy Arr to the left/right array]
//     int sizeL = (end / 2);
//     int sizeR = end - sizeL;
//     int left[sizeL];
//     int right[sizeR];
//
//     for (int i = 0; i < left_size; i++){
//     left[i] = arr[i];
// }

// for (int i = 0; i < right_size; i++){
//     right[i] = arr[i];
// }
//
// ==============================================
