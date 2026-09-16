/* 연습장 0. 빈 메모장. 무엇을 써도 되고, 지워도 된다.
   빌드/실행:  make r_play0     gdb:  make g_play0     메모리 검사:  make s_play0

   gdb 를 쓸 때는  break main  →  run  →  next  부터 시작하면 된다.
   자주 쓰는 것:  p 식   p *포인터   p 배열[0]@5   x/4gx 주소   bt   tk 이름 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PRIME_NUMBER, // 0: 소수;
    COMPOSITE_NUMBER, // 1: 합성수;
    NEITHER_NUMBER // 2: Error Cases;
} PrimeType;

static const char *const arr3[] = {
    [PRIME_NUMBER] = "소수",
    [COMPOSITE_NUMBER] = "합성수",
    [NEITHER_NUMBER] = "에러"
};

int arr1[3] = {PRIME_NUMBER, NEITHER_NUMBER, COMPOSITE_NUMBER};
int arr2[] = {[0] = 1, [3] = 2, [1] = 3};
int main(void)
{
	/* 여기부터 */

	printf("\n%d %d %d\n", arr1[0], arr1[1], arr1[2]);
	printf("%d %d %d %d\n", arr2[0], arr2[1], arr2[2], arr2[3]);
	printf("%s %s %s\n", arr3[0], arr3[1], arr3[2]);
	for (int i = 0; i < 3; i++){
	    printf("%s ", arr3[i]);
	} printf("\n");
	printf("%d\n", arr2[1] % arr2[3]);
	/* 여기까지 */
	return 0;
}
