/* 연습장 1. 과제 파일이 아니다. 마음대로 고치고 지워도 된다.
   빌드/실행:  make r_play1     gdb:  make g_play1     메모리 검사:  make s_play1 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;


int main(void)
{
	ListNode *a = malloc(sizeof(ListNode));
	ListNode *b = malloc(sizeof(ListNode));
	a->item = 1; a->next = b;
	b->item = 2; b->next = NULL;

	ListNode *cur = a;

	printf("before: cur=%p  cur->item=%d  cur->next=%p\n",
	       (void *)cur, cur->item, (void *)cur->next);
	cur = cur->next;

	printf("after : cur=%p  cur->item=%d  cur->next=%p\n",
	       (void *)cur, cur->item, (void *)cur->next);

	free(a);
	free(b);
	return 0;
}
