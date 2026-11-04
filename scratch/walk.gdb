# week04 전용 gdb 설정. make g_* 가 자동으로 읽는다.
# 명령 하나의 설명은 gdb 안에서  help 이름.  help user-defined 는 일부만 보여 준다.
#
# 여기에는 이번 주차의 변수 이름에 묶인 것만 둔다. 타입 이름을 모르는 범용 도구는
# ~/.config/gdb/ (gdbinit 과 *.py) 에 있고, 그쪽은 malloc-lab 과 Pintos 로 그대로 따라간다.
#   dbg / vars / out    TUI 배치: 소스 크게 / 소스+값 / 프로그램 출력
#   tk EXPR             값 하나를 한 행에 고정 (tk -l 은 그 주소에 고정)
#   itk / utk N         목록 / N행 삭제. 범위는 utk 1..4, utk 6..
#   tk walk EXPR N      사슬 앞 N 개를 한 행씩
#   tk deep EXPR N      EXPR 이 닿는 구조체 전부, N 단계
#   tk tri[0..5]        원소나 멤버를 한 행씩 (tk each PATTERN)
#   walk EXPR [FIELD]   사슬을 한 번 출력 (walk.py)
#   each [/FMT] PATTERN 원소나 멤버를 한 번 출력
#   snap / snaps / back 이름 붙인 체크포인트 (snap.py)
#   rerun               다시 컴파일한 바이너리로 재실행
#
# 아래 *watch 는 감시 표현을 한 번에 거는 묶음이다. 범위 밖 이름은 track 이
# <not in scope> 행으로 남기므로, 지금 없는 변수가 섞여 있어도 해가 없다.

# *watch 묶음이 공통으로 쓰는 창 설정.
# cmdwin 은 터미널이 허용하는 만큼만 명령 창을 키운다 (인자 없이 쓰면 터미널 높이의 약 3분의 1, 최소 4줄).
# 고정 숫자를 쓰면 짧은 터미널에서 gdb 가 조용히 거부한다.
define watchwin
  vars
  cmdwin
end
document watchwin
vars 레이아웃을 띄우고 명령 창 높이를 터미널에 맞춘다.
*watch 묶음이 끝에서 부른다. 다른 높이를 원하면 cmdwin 20 처럼 쓴다.
end

define llwatch
  tk cur
  tk cur->item
  tk cur->next
  tk prev
  watchwin
end
document llwatch
연결 리스트용 감시 묶음: cur, cur->item, cur->next, prev.
Q7_A_LL 은 정의가 ptrhead (소문자 h) 라서 tk *ptrhead 를 따로 걸어야 한다.
end

define sqwatch
  tk s->ll.size
  tk s->ll.head
  tk q->ll.size
  tk q->ll.head
  watchwin
end
document sqwatch
스택 / 큐용 감시 묶음. 매개변수가 포인터인 경우를 전제한다.
Q4_C_SQ 는 지역 변수 Stack s 라서 점으로 써야 한다: tk s.ll.size
end

define btwatch
  tk node
  tk node->item
  tk node->left
  tk node->right
  watchwin
end
document btwatch
이진 트리용 감시 묶음: node 와 세 필드.
Q4_E_BT 는 정의 쪽 매개변수 이름이 root 다. 파일을 먼저 확인할 것.
end

define bstwatch
  tk root
  tk root->item
  tk root->left
  tk root->right
  watchwin
end
document bstwatch
이진 탐색 트리용 감시 묶음: root 와 세 필드.
보조 큐를 따라갈 때는 다음 포인터 이름이 next 가 아니라 nextPtr 이다:
  walk qn nextPtr
end

define chains
  printf "새 사슬 (FirstNode 부터):\n"
  walk FirstNode
  printf "원본 ll1 (prev1 부터):\n"
  walk prev1
  printf "ll2 (ll2->head 부터):\n"
  walk ll2->head
end
document chains
Q2_A_LL / play4 의 세 사슬을 한 번에 찍는다.
반복문 안에서는 새 사슬이 아직 자라는 중이다.
end

# 줄 번호는 파일을 고치면 바뀐다. 중단점은 그때그때 직접 걸 것.
#   break alternateMergeLinkedList
#   break play4.c:<줄번호>
# 함수 이름으로 걸어 두면 rerun 후에도 그대로 붙는다.
