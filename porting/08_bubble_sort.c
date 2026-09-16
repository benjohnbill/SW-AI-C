#include <stdio.h>
#include "08_bubble_sort_cases.h"

int ed(const int arr []){
    return  (arr == bb1) ? (int)(sizeof(bb1) / sizeof(bb1[0])) - 1 :
            (arr == bb2) ? (int)(sizeof(bb2) / sizeof(bb2[0])) - 1 :
            (arr == bb3) ? (int)(sizeof(bb3) / sizeof(bb3[0])) - 1 :
                            -1; // If not three of them, return 0.
}

void bbSort(int arr [], int n){ // Sorting original array with Pointer.
    for (int i = 0; i < n; i++){ // !! ed(arr) can't be defined.
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j+1]){
                int tmp = arr[j]; // temporary arr[j].
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main(void){
// Case 1 (before)
    printf("\n=== 테스트 케이스 1 ===\n");
    printf("정렬 전: [");
    for (int i = 0; i < ed(bb1); i++){
        printf("%d, ", bb1[i]);
    } printf("%d", bb1[ed(bb1)]);
    printf("]\n");

// Case 1 (after)
    int copy1 [ed(bb1)+1];
    for (int i = ed(bb1); i >= 0; i--){
        copy1[i] = bb1[i];
    } // Copy the bb1 array, for not changing the Original bb1 from .h file (const).
    bbSort(copy1, ed(bb1)+1);
    printf("정렬 후: [");
    for (int i = 0; i < ed(bb1); i++){
        printf("%d, ", copy1[i]);
    } printf("%d", copy1[ed(bb1)]);
    printf("]\n");

// Case 2 (before)
    printf("\n=== 테스트 케이스 2: 이미 정렬됨 ===\n");
    printf("정렬 전: [");
    for (int i = 0; i < ed(bb2); i++){
        printf("%d, ", bb2[i]);
    } printf("%d", bb2[ed(bb2)]);
    printf("]\n");

// Case 2 (after)
    int copy2 [ed(bb2)+1];
    for (int i = ed(bb2); i >= 0; i--){
        copy2[i] = bb2[i];
    } // Copy the bb2 array, for not changing the Original bb2 from .h file (const).
    bbSort(copy2, ed(bb2)+1);
    printf("정렬 후: [");
    for (int i = 0; i < ed(bb2); i++){
        printf("%d, ", bb2[i]);
    } printf("%d", copy2[ed(bb2)]);
    printf("]\n");

// Case 3 (before)
    printf("\n=== 테스트 케이스 3: 역순 ===\n");
    printf("정렬 전: [");
    for (int i = 0; i < ed(bb3); i++){
        printf("%d, ", bb3[i]);
    } printf("%d", bb3[ed(bb3)]);
    printf("]\n");

// Case 3 (after)
    int copy3 [ed(bb3)+1];
    for (int i = ed(bb3); i >= 0; i--){
        copy3[i] = bb3[i];
    } // Copy the bb3 array, for not changing the Original bb3 from .h file (const).
    bbSort(copy3, ed(bb3)+1);
    printf("정렬 후: [");
    for (int i = 0; i < ed(bb3); i++){
        printf("%d, ", copy3[i]);
    } printf("%d", copy3[ed(bb2)]);
    printf("]\n");
}
