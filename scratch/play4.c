/* 연습장 4. Q2 의 alternateMergeLinkedList 를 scanf 메뉴 없이 디버깅하기 위한 하네스.
   빌드/실행:  make r_play4     gdb:  make g_play4     메모리 검사:  make s_play4

   아래 alternateMergeLinkedList 는 오라버니가 쓰신 코드 그대로다.
   [로테] 표시가 붙은 줄만 컴파일이 되도록 최소로 손댄 자리다. 논리는 건드리지 않았다.

   gdb 로 볼 때:
     break alternateMergeLinkedList
     run
     next / print cur1 / print *cur1 / print node / print *node / print i */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
	int size;
	ListNode *head;
} LinkedList;

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

/* ---------------------------------------------------herdr---------------
   여기서부터 하네스. 문제 풀이와 무관한 보조 코드다.
   ------------------------------------------------------------------ */

/* 주소를 짧게 보기 위한 도우미. 뒤 4자리만 남긴다. */
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

/* 배열을 받아 리스트를 만든다. Q2 의 insertNode 대신 쓰는 간단한 버전. */
static void build(LinkedList *ll, const int *arr, int n)
{
	ListNode *tail = NULL;
	ListNode *node;
	int i;

	ll->head = NULL;
	ll->size = 0;

	for (i = 0; i < n; i++) {
		node = malloc(sizeof(ListNode));
		node->item = arr[i];
		node->next = NULL;

		if (ll->head == NULL)
			ll->head = node;
		else
			tail->next = node;

		tail = node;
		ll->size++;
	}
}

/* head 에서 닿는 노드를 전부 찍는다. 고리가 생긴 경우를 대비해 상한을 둔다. */
static void dump(const char *label, LinkedList *ll)
{
	ListNode *cur = ll->head;
	int guard = 0;

	printf("%-6s size=%2d head=%s : ", label, ll->size, a4(ll->head));

	if (cur == NULL)
		printf("(비어 있음)");

	while (cur != NULL) {
		printf("%d(%s) ", cur->item, a4(cur));
		cur = cur->next;
		if (++guard > 30) {
			printf("... 30 개에서 끊었다. 고리가 생겼을 수 있다.");
			break;
		}
	}
	printf("\n");
}

/* 사슬 전체를 반납하고 컨테이너를 비운다. */
static void cleanup(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

static void run_case(const char *title,
                     const int *a, int na,
                     const int *b, int nb)
{
	LinkedList ll1, ll2;

	printf("===== %s =====\n", title);
	build(&ll1, a, na);
	build(&ll2, b, nb);

	printf("[호출 전]\n");
	dump("ll1", &ll1);
	dump("ll2", &ll2);

	alternateMergeLinkedList(&ll1, &ll2);

	printf("[호출 후]\n");
	dump("ll1", &ll1);
	dump("ll2", &ll2);
	printf("\n");

	/* 하네스가 남긴 사슬을 반납한다. 이게 있어야 make s_play4 의 목표가 정확히 0 이 된다.
	   0 이 아니면 남은 것은 전부 alternateMergeLinkedList 쪽 문제다. */
	cleanup(&ll1);
	cleanup(&ll2);
}

int main(void)
{
	/* PDF 의 예시 1: ll1 이 더 짧다. 결과 ll2 에 7 이 남아야 한다. */
	const int a1[] = {1, 2, 3};
	const int b1[] = {4, 5, 6, 7};

	/* PDF 의 예시 2: ll1 이 더 길다. 결과 ll2 는 비어야 한다. */
	const int a2[] = {1, 5, 7, 3, 9, 11};
	const int b2[] = {6, 10, 2, 4};

	run_case("예시 1  ll1=1,2,3   ll2=4,5,6,7", a1, 3, b1, 4);
	run_case("예시 2  ll1=1,5,7,3,9,11   ll2=6,10,2,4", a2, 6, b2, 4);

	return 0;
}

/* ------------------------------------------------------------------
   여기서부터 오라버니 코드. 논리는 원본 그대로.
   ------------------------------------------------------------------ */
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	ListNode *cur1 = ll1->head;
	ListNode *cur2 = ll2->head;
	ListNode *node;
	ListNode *tmp = NULL;
	ListNode *FirstNode = NULL;
	ListNode *prev1 = ll1->head;

	int i, n;
	n = ll1->size + ll2->size;

	for (i = 1; i <= n; i++){
		node = malloc(sizeof(ListNode));
		node->item = 0; // 이거 꼭 필요한가? 그냥 놔뒀다가 자연스럽게 item하고 next 업데이트하면 되지 않나?
		node->next = NULL;

		if (i%2 != 0 || cur2 == NULL){
			if (cur1 == NULL){
			    free(node);
			    break;
			}
			else if (tmp == NULL){
			    FirstNode = node;
			}
			else
			    tmp->next = node;
			node->item = cur1->item;
			cur1 = cur1->next;
			tmp = node;
		}
		else {
			tmp->next = node;
			node->item = cur2->item;
			cur2 = cur2->next;
			ll1->size++;
			ll2->size--;
			tmp = node;
		}
	}
	// ll2에 남아있는 원본 원소들 free() 해주기(다른 함수에서 malloc() 함)
	ListNode *org2 = ll2->head;
	ListNode *temp2;

	while (org2 != cur2) {
	    temp2 = org2->next;
		free(org2);
		org2 = temp2;
	}

	ll2->head = cur2;

	ListNode *OrgFirst = prev1;
	ListNode *temp1;
	while (OrgFirst != NULL) {
	    temp1 = OrgFirst->next;
		free(OrgFirst);
		OrgFirst = temp1;
	}
	ll1->head = FirstNode;
}
