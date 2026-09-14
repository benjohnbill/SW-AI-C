/* 연습장 2. 구조체가 메모리에서 어떤 모양으로 놓이는지 눈으로 보는 예제.
   빌드/실행:  make r_play2     gdb:  make g_play2     메모리 검사:  make s_play2

   숫자를 바꿔 가며 실험해 볼 것:
     - ListNode 안에서 item 과 next 의 순서를 바꾸면 sizeof 가 어떻게 되는가
     - int item 을 char item 으로 바꾸면 offsetof(next) 가 어떻게 되는가 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>   /* offsetof 를 쓰려면 필요하다 */

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;

int main(void)
{
	/* --- 1. 선언만으로 정해지는 것들. 아직 메모리는 하나도 안 잡혔다. --- */
	printf("sizeof(int)        = %zu\n", sizeof(int));
	printf("sizeof(ListNode *) = %zu\n", sizeof(ListNode *));
	printf("sizeof(ListNode)   = %zu   <- item 4 + next 8 = 12 가 아니다\n", sizeof(ListNode));
	printf("offsetof(item)     = %zu\n", offsetof(ListNode, item));
	printf("offsetof(next)     = %zu   <- 4 가 아니다. 사이에 패딩 4바이트\n\n",
	       offsetof(ListNode, next));

	/* --- 2. 여기서 처음으로 실물 상자가 생긴다. --- */
	ListNode *a = malloc(sizeof(ListNode));
	a->item = 1;
	a->next = NULL;

	printf("a        (a 칸에 담긴 값)   = %p\n", (void *)a);
	printf("&a->item (item 칸의 주소)   = %p   <- a 와 같다 (offset 0)\n", (void *)&a->item);
	printf("&a->next (next 칸의 주소)   = %p   <- a 보다 8 크다\n", (void *)&a->next);
	printf("a->item  (item 칸의 값)     = %d\n", a->item);
	printf("a->next  (next 칸의 값)     = %p\n\n", (void *)a->next);

	/* --- 3. free 는 상자를 반납한다. a 칸의 값은 그대로 남는다. --- */
	free(a);
	printf("free(a) 직후 a 칸의 값      = %p   <- 지워지지 않았다\n", (void *)a);

	/* 여기서 a->item 을 읽으면 규칙 위반이다.
	   확인하고 싶으면 아래 줄의 주석을 풀고 make s_play2 로 실행할 것. */
	/* printf("a->item = %d\n", a->item); */

	a = NULL;   /* 쪽지를 찢는다. 이제 실수로 써도 바로 죽는다. */
	return 0;
}
