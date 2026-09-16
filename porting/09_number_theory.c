#include "09_number_theory_cases.h"
#include <stdio.h>

int len = sizeof(np1) / sizeof(np1[0]);

int gcd(int a, const int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int lcm(const int a, const int b){
    if (a == 0 || b == 0){
        return 0;
    }
    return a * b / gcd(a, b);
}

// ================For Case 4================
typedef struct{
    int gcd;
    int x;
    int y;
} ExtGcd;

ExtGcd extended_gcd(const int a, const int b){
    ExtGcd base = {.gcd = a,.x = 1,.y = 0};
    if (b == 0){
        return base;
    }

    ExtGcd Child = extended_gcd(b, a % b);
    ExtGcd result;
    result.gcd = gcd(a, b);
    result.x = Child.y;
    result.y = Child.x - (a / b) * Child.y;
    return result;
}
// ================For Case 4================

// ===========For Case 5================
typedef enum { // Because of the return type of prime() - int
    PRIME_NUMBER, // 0: 소수;
    COMPOSITE_NUMBER, // 1: 합성수;
    NEITHER_NUMBER // 2: Error Cases;
} PrimeType;

static const char *const PRIME_MAP[] = {
    [PRIME_NUMBER] = "소수",
    [COMPOSITE_NUMBER] = "합성수",
    [NEITHER_NUMBER] = "에러"
};

int prime(const int arr[], int len){
    if (len == 0){ // Error Case : Empty Case
        return NEITHER_NUMBER;
    }

    for (int i = 0; i < len; i++){
        if (arr[i] == 0 || arr[i] == 1){
            return NEITHER_NUMBER; // Error Case : 0, 1 in arr;
        }
        int j = 2;
        while (j <= arr[i]){
            if (arr[i] % j == 0){
                return COMPOSITE_NUMBER; // If j has prime factors, not prime num;
            } j++;
        }
    } return PRIME_NUMBER;
}

int prime2(const int arr[], int n){
    if (arr[n] <= 1){
        return NEITHER_NUMBER;
    } int j = 2;
    while (j < arr[n]){
        if (arr[n] % j == 0){
            return COMPOSITE_NUMBER;
        } j++;
    } return PRIME_NUMBER;
}

// ===========For Case 5=================

int main(void){
// Case 1
    printf("\n=== 테스트 케이스 1 ===\n");
    printf("a = %d, b = %d\n", na1, nb1);
    printf("GCD (재귀): %d\n", gcd(na1, nb1));
    printf("GCD (반복): %d\n", gcd(na1, nb1));
    printf("LCM: %d\n", lcm(na1, nb1));
// Case 2
    printf("\n=== 테스트 케이스 2 ===\n");
    printf("a = %d, b = %d\n", na2, nb2);
    printf("GCD: %d\n", gcd(na2, nb2));
    printf("LCM: %d\n", lcm(na2, nb2));
// Case 3
    printf("\n=== 테스트 케이스 3: 서로소 ===\n");
    printf("a = %d, b = %d\n", na3, nb3);
    printf("GCD: %d\n", gcd(na3, nb3));
    printf("LCM: %d\n", lcm(na3, nb3));
    printf("서로소(coprime): GCD가 %d\n", gcd(na3, nb3));
// Case 4
    printf("\n=== 테스트 케이스 4: 확장 유클리드 ===\n");
    printf("a = %d, b = %d\n", na4, nb4);
    printf("GCD = %d\n", gcd(na4, nb4));
    ExtGcd result = extended_gcd(na4, nb4);
    printf("%d x %d + %d x %d = %d\n", na4, result.x, nb4, result.y, result.gcd);
    printf("검증: %d = %d\n", gcd(na4, nb4), gcd(nb4, (na4 % nb4)));
// Case 5
    printf("\n== 테스트 케이스 5: 소수 판별 ===\n");
    for (int i = 0; i < len; i++){
        printf("%d: %s\n", np1[i], PRIME_MAP[prime2(np1, i)]);
    }
}
