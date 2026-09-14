/* 연습장 5. 대입문 한 줄이 무엇을 바꾸는가. 연산자 중심.
   빌드/실행:  make r_play5     gdb:  make g_play5     메모리 검사:  make s_play5

   main 의 대입문 한 줄마다 snap() 이 붙어 있다. gdb 에서 next 를 한 번 칠 때마다
   어느 칸이 바뀌었는지 표로 확인하면 된다.

     break main
     run
     next      (반복)

   보는 법: 표의 네 칸 중 무엇이 바뀌었는가.
     p, q      스택에 있는 포인터 변수 두 개
     A, B      heap 에 있는 노드 두 개의 속 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;

static ListNode *A, *B;   /* 표에서 이름을 붙이기 위해 전역으로 둔다 */

/* 주소를 A / B / NULL 같은 이름으로 바꿔 찍는다. 주소 숫자는 눈에 안 들어오니까. */
static const char *nm(ListNode *p)
{
	if (p == NULL) return "NULL";
	if (p == A)    return "A";
	if (p == B)    return "B";
	return "?";
}

static void snap(const char *line, ListNode *p, ListNode *q)
{
	printf("%-22s | p=%-4s q=%-4s | A{item=%d,next=%s}  B{item=%d,next=%s}\n",
	       line, nm(p), nm(q),
	       A->item, nm(A->next),
	       B->item, nm(B->next));
}

/* malloc 은 여기에만 있다. */
static ListNode *make_node(int value)
{
	ListNode *node = malloc(sizeof(ListNode));

	node->item = value;
	node->next = NULL;
	return node;
}

/* free 는 여기에만 있다. */
static void free_node(ListNode *node)
{
	free(node);
}

int main(void)
{
	ListNode *p = NULL;
	ListNode *q = NULL;

	A = make_node(1);
	B = make_node(2);

	printf("실제 주소:  A=%p  B=%p\n\n", (void *)A, (void *)B);
	snap("시작", p, q);

	/* --- 왼쪽에 -> 가 없다. 스택의 변수 칸만 바뀐다. --- */
	p = A;
	snap("p = A;", p, q);

	q = B;
	snap("q = B;", p, q);

	/* --- 왼쪽에 -> 가 있다. heap 의 노드 속이 바뀐다. 변수는 그대로. --- */
	p->item = 7;
	snap("p->item = 7;", p, q);

	p->next = q;
	snap("p->next = q;", p, q);

	/* --- 오른쪽에만 -> 가 있다. heap 에서 읽어 스택에 쓴다. --- */
	q = p->next;
	snap("q = p->next;", p, q);

	/* --- 양쪽 다 변수. heap 은 전혀 안 바뀐다. --- */
	p = q;
	snap("p = q;", p, q);

	/* --- 양쪽 다 -> . heap 에서 읽어 heap 에 쓴다. --- */
	B->item = A->item;
	snap("B->item = A->item;", p, q);

	printf("\n== free ==\n");
	printf("free 전  p 는 %s 를 가리킨다\n", nm(p));
	free_node(B);
	printf("free_node(B) 실행. p 와 q 의 값은 하나도 안 바뀌었다.\n");
	printf("바뀐 것은 B 주소의 소유권이다. 이제 그 주소를 읽으면 규칙 위반이다.\n");

	/* 확인하려면 주석을 풀고  make s_play5  로 실행할 것. */
	/* printf("B->item = %d\n", B->item); */

	free_node(A);
	return 0;
}
