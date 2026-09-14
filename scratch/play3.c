/* 연습장 3. 반복문 하나로 노드 여러 개를 이어 붙이는 방법.
   빌드/실행:  make r_play3     gdb:  make g_play3     메모리 검사:  make s_play3

   보고 싶은 것:
     - node 변수는 한 개뿐인데 왜 노드는 다섯 개가 남는가
     - cur 이 매 바퀴 무엇을 가리키고 있는가
     - cur = node 한 줄을 빼면 무엇이 끊어지는가  (build_broken) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;

/* ---------------------------------------------------------------
   주소를 짧게 보기 위한 도우미. 뒤 4자리만 남긴다.
   호출할 때마다 다른 칸을 쓰므로 printf 하나에 여러 번 넣어도 섞이지 않는다.
   --------------------------------------------------------------- */
static const char *a4(void *p)
{
	static char buf[8][16];
	static int slot = 0;
	char *s = buf[slot];

	slot = (slot + 1) % 8;

	if (p == NULL)
		snprintf(s, 16, " NULL");
	else
		snprintf(s, 16, "..%04lx", (unsigned long)(uintptr_t)p & 0xffff);

	return s;
}

/* head 에서 출발해 next 를 따라가며 닿는 노드를 한 줄로 찍는다. */
static void show_chain(ListNode *head)
{
	ListNode *cur = head;

	if (cur == NULL) {
		printf("(비어 있음)");
		return;
	}
	while (cur != NULL) {
		printf("%s(%d)", a4(cur), cur->item);
		if (cur->next != NULL)
			printf(" -> ");
		cur = cur->next;
	}
}

/* ---------------------------------------------------------------
   제대로 된 버전. 1 부터 n 까지를 담은 사슬을 만들어 입구를 돌려준다.
   --------------------------------------------------------------- */
ListNode *build_chain(int n)
{
	ListNode *head = NULL;   /* 사슬의 입구. 첫 노드를 만들 때 딱 한 번 정해진다. */
	ListNode *cur = NULL;   /* 직전 바퀴에 만든 노드. 이어 붙일 자리를 기억한다. */
	ListNode *node;          /* 이번 바퀴에 만든 노드. 매 바퀴 덮어써진다. */
	int i;

	for (i = 1; i <= n; i++) {
		node = malloc(sizeof(ListNode));   /* 바퀴마다 새 주소가 나온다 */
		node->item = i;
		node->next = NULL;

		printf("  %d 바퀴  malloc 직후  node=%s  head=%s  cur=%s\n",
		       i, a4(node), a4(head), a4(cur));

		if (head == NULL)
			head = node;         /* 첫 바퀴에만. 입구를 적어 둔다. */
		else
			cur->next = node;   /* 직전 노드가 이번 노드를 가리키게 한다 */

		cur = node;             /* '직전' 을 이번 노드로 갱신 */

		printf("          연결 후    node=%s  head=%s  cur=%s\n",
		       a4(node), a4(head), a4(cur));
		printf("          사슬       ");
		show_chain(head);
		printf("\n\n");
	}

	return head;
}

/* ---------------------------------------------------------------
   cur 갱신이 빠진 버전. 첫 바퀴에 세운 cur 이 끝까지 그대로 있다.
   실행하기 전에 먼저 예측할 것: 몇 개의 노드에 닿게 되는가.
   --------------------------------------------------------------- */
ListNode *build_broken(int n)
{
	ListNode *head = NULL;
	ListNode *cur = NULL;
	ListNode *node;
	int i;

	for (i = 1; i <= n; i++) {
		node = malloc(sizeof(ListNode));
		node->item = i;
		node->next = NULL;

		if (head == NULL) {
			head = node;
			cur = node;         /* 첫 바퀴에만 세운다 */
		} else {
			cur->next = node;
		}

		/* cur = node;   <- 일부러 빠뜨렸다. cur 은 영원히 첫 노드를 가리킨다. */

		printf("  %d 바퀴  node=%s  head=%s  cur=%s  사슬  ",
		       i, a4(node), a4(head), a4(cur));
		show_chain(head);
		printf("\n");
	}

	return head;
}

/* head 에서 출발해 닿는 노드를 전부 찍고 개수를 센다. */
void walk(const char *label, ListNode *head)
{
	ListNode *cur = head;
	int count = 0;

	printf("%s: ", label);
	while (cur != NULL) {
		printf("%d(%s) ", cur->item, a4(cur));
		cur = cur->next;
		count++;
	}
	printf("\n  -> 닿은 노드 %d 개\n\n", count);
}

/* 사슬 전체를 반납한다. 다음 노드 주소를 먼저 붙잡아야 한다. */
void destroy(ListNode *head)
{
	ListNode *cur = head;
	ListNode *tmp;

	while (cur != NULL) {
		tmp = cur->next;   /* free 한 뒤에는 cur->next 를 읽을 수 없다 */
		free(cur);
		cur = tmp;
	}
}

int main(void)
{
	ListNode *good, *bad;

	printf("===== build_chain(5) =====\n");
	good = build_chain(5);
	walk("결과", good);

	printf("===== build_broken(5) =====  예측을 먼저 해 볼 것\n");
	bad = build_broken(5);
	printf("\n");
	walk("결과", bad);

	destroy(good);
	destroy(bad);   /* 닿지 못한 노드는 여기서도 반납되지 않는다. make s_play3 로 확인. */

	return 0;
}
