#include "05_recursion_cases.h"
#include <stdio.h>

int factorial(int n){
    if (n == 0 || n == 1){
        return 1; // If `n` is 0 or 1, factorial(n) is 1.
    }

    return (n * factorial(n - 1));
}

int fibonacci(int n){
    if (n == 0){
        return 0;
    }
    else if (n == 1){
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void)
{
    printf("\n=== 팩토리얼 계산 ===\n");
    for (int i = 0; i < fact_upto; i++){
        printf("%d! = %d\n", i, factorial(i));
    }

    printf("\n=== 피보나치 수열 ===\n");
    for (int i = 0; i < fib_upto; i++){
        printf("fib(%d) = %d\n", i, fibonacci(i));
    }
    printf("\n=== 추가 테스트 ===\n");
    printf("%d! = %d\n", fact_extra, factorial(fact_extra));
    printf("fib(%d) = %d\n", fib_extra, fibonacci(fib_extra));
}
