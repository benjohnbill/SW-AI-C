/* 연습장 6. enum 과 문자열 조회표(lookup table). 이름·정수·주소의 세 층.
   빌드/실행:  make r_play6     gdb:  make g_play6     메모리 검사:  make s_play6

   묻는 것은 하나다. 이름은 언제 사라지고, 무엇이 실행 중에 남는가.

     enum 상수  ─ 컴파일 시점에 정수로 바뀌고, 실행 파일에 이름이 남지 않는다.
     조회표     ─ 실행 내내 메모리에 남는 자료. 그래서 실행 중에 고를 수 있다.

   gdb 로 보는 순서:

     break main
     run
     next            (한 단계씩)
     p LIGHT_STR     표 전체를 본다
     p LIGHT_STR[1]  칸 하나를 본다
     p &LIGHT_STR[1] 칸의 주소를 본다
     x/3gx LIGHT_STR 칸 세 개에 든 값(주소)을 날것으로 본다
     p RED           이름이 남아 있는지 확인한다 (디버그 정보에는 남는다)

   문제 09 의 소수 판별과는 무관한 자료를 쓴다. 여기서 익힌 모양만 가져가면 된다. */

#include <stdio.h>

/* ── 1. 값을 적지 않은 enum. 0 부터 1 씩 올라간다. ─────────────────────── */
typedef enum {
	RED,      /* 0 */
	YELLOW,   /* 1 */
	GREEN     /* 2 */
} Light;

/* ── 2. enum 첨자와 1:1 로 맞춘 문자열 조회표 ──────────────────────────── */
static const char *const LIGHT_STR[] = {
	[RED]    = "정지",
	[YELLOW] = "주의",
	[GREEN]  = "진행"
};

/* 같은 내용을 2차원 배열로 담으면 어떻게 달라지는지 비교하려고 둔다.
   칸 크기를 가장 긴 문자열에 맞춰 미리 고정해야 한다. */
static const char LIGHT_ARR[][7] = { "정지", "주의", "진행" };

/* ── 3. 값을 직접 지정한 enum. 조회표가 깨지는 쪽의 예. ────────────────── */
typedef enum {
	HTTP_OK       = 200,
	HTTP_NOTFOUND = 404,
	HTTP_ERROR    = 500
} HttpCode;

#define LIGHT_COUNT ((int)(sizeof LIGHT_STR / sizeof LIGHT_STR[0]))

/* 첨자가 표 밖으로 나가는 경우를 막는다. C 는 대신 막아 주지 않는다. */
static const char *light_name(int i)
{
	if (i < 0 || i >= LIGHT_COUNT)
		return "<범위 밖>";
	return LIGHT_STR[i];
}

static void rule(const char *title)
{
	printf("\n── %s ──────────────────────────────\n", title);
}

int main(void)
{
	/* ── 층 1. 이름은 정수다 ─────────────────────────────────────────── */
	rule("1. enum 상수는 정수다");

	int a = RED;                    /* gdb: next 로 넘긴 뒤 p a */
	int b = GREEN;

	printf("RED=%d  YELLOW=%d  GREEN=%d\n", RED, YELLOW, GREEN);
	printf("int a = RED;  a == 0 은 %s\n", (a == 0) ? "참" : "거짓");
	printf("int b = GREEN; b + 1 = %d  (정수이므로 산술이 된다)\n", b + 1);

	Light bad = (Light)7;           /* 세 상태에 없는 값인데 막히지 않는다 */
	printf("Light bad = 7;  bad = %d  → 이름은 울타리가 아니다\n", (int)bad);

	/* ── 층 2. 표는 메모리에 실재한다 ────────────────────────────────── */
	rule("2. 조회표의 칸 하나는 주소 하나다");

	printf("칸 하나 %zu 바이트, 표 전체 %zu 바이트, 칸 개수 %d\n",
	       sizeof LIGHT_STR[0], sizeof LIGHT_STR, LIGHT_COUNT);

	for (int i = 0; i < LIGHT_COUNT; i++) {
		printf("LIGHT_STR[%d]  칸 주소 %p  칸에 든 값 %p  → \"%s\"\n",
		       i, (void *)&LIGHT_STR[i], (void *)LIGHT_STR[i], LIGHT_STR[i]);
	}

	/* 첨자 연산이 덧셈일 뿐이라는 것을 눈으로 확인한다.
	   아래 두 줄은 같은 곳을 가리켜야 한다. */
	printf("\n&LIGHT_STR[2]              = %p\n", (void *)&LIGHT_STR[2]);
	printf("(시작 주소) + 2 * %zu 바이트 = %p\n",
	       sizeof LIGHT_STR[0],
	       (void *)((const char *)LIGHT_STR + 2 * sizeof LIGHT_STR[0]));

	/* ── 층 3. 포인터 배열과 2차원 배열 ──────────────────────────────── */
	rule("3. 글자를 칸 밖에 두는가, 칸 안에 두는가");

	printf("포인터 배열 LIGHT_STR : 칸 %zu 바이트 × %d = %zu 바이트\n",
	       sizeof LIGHT_STR[0], LIGHT_COUNT, sizeof LIGHT_STR);
	printf("2차원 배열 LIGHT_ARR  : 칸 %zu 바이트 × %d = %zu 바이트\n",
	       sizeof LIGHT_ARR[0],
	       (int)(sizeof LIGHT_ARR / sizeof LIGHT_ARR[0]),
	       sizeof LIGHT_ARR);
	printf("LIGHT_ARR[1] 의 주소 %p  ← 글자가 이 자리에 직접 들어 있다\n",
	       (void *)LIGHT_ARR[1]);
	printf("LIGHT_STR[1] 의 값   %p  ← 글자는 다른 곳에 있고 주소만 담겼다\n",
	       (void *)LIGHT_STR[1]);

	/* ── 층 4. 실행 시점에 칸을 고른다 ───────────────────────────────── */
	rule("4. 실행 중에 정해진 값으로 칸을 고른다");

	/* pick 에 무엇이 들어갈지는 컴파일 시점에 알 수 없다.
	   그래도 표에서 꺼낼 수 있다. 표가 실행 중에도 남아 있기 때문이다.
	   gdb 에서 이 줄에 멈춘 뒤  p pick  으로 확인할 것. */
	for (int step = 0; step < 5; step++) {
		int pick = step % LIGHT_COUNT;
		printf("step=%d  pick=%d  →  %s\n", step, pick, LIGHT_STR[pick]);
	}

	/* ── 층 5. 표 밖으로 나가면 ──────────────────────────────────────── */
	rule("5. 경계는 아무도 검사해 주지 않는다");

	printf("light_name(1) = %s\n", light_name(1));
	printf("light_name(7) = %s   ← 직접 막았으니 살아 있다\n", light_name(7));

	/* 아래 줄의 주석을 풀면 표 밖의 메모리를 주소로 해석해서 넘긴다.
	   경고도 오류도 없이 통과하고, 실행 결과는 정해져 있지 않다.
	   보고 싶으면  make g_play6  로 열어서  p LIGHT_STR[7]  만 해 볼 것.

	   printf("LIGHT_STR[7] = %s\n", LIGHT_STR[7]);  */

	/* ── 층 6. 값을 지정한 enum 은 첨자가 되지 못한다 ────────────────── */
	rule("6. 조회표를 쓸 수 없는 enum");

	printf("HTTP_OK=%d  HTTP_NOTFOUND=%d  HTTP_ERROR=%d\n",
	       HTTP_OK, HTTP_NOTFOUND, HTTP_ERROR);
	printf("이 값들을 첨자로 쓰려면 %d 칸짜리 배열이 필요하고,\n", HTTP_ERROR + 1);
	printf("그중 세 칸만 쓴다. 이런 자리에는 switch 를 쓴다.\n");

	printf("\n");
	return 0;
}

/* ── 직접 해 볼 것 ──────────────────────────────────────────────────────

   1. LIGHT_STR 의 지정 초기자에서 [YELLOW] 줄 하나만 지우고 다시 빌드해 보자.
      칸 개수는 몇으로 나오는가. 그 칸에는 무엇이 들어 있는가.
      (gdb 에서  p LIGHT_STR[1]  로 확인)

   2. enum 에 CYAN 을 RED 와 YELLOW 사이에 끼워 넣어 보자. 표는 고치지 않는다.
      출력이 어떻게 어긋나는가. 지정 초기자를 쓰면 왜 이 사고를 막는가.

   3. 층 4 의 for 문에서 LIGHT_STR[pick] 을 light_name(pick) 으로 바꿔 보자.
      출력이 같은가. 그렇다면 light_name 은 무엇을 더 해 주고 있는가.

   4. 층 5 의 주석 처리된 printf 를 살려서 valgrind 로 돌려 보자
      (make s_play6). 무엇이라고 말하는가.

   ─────────────────────────────────────────────────────────────────────── */
