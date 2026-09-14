# gdb 헬퍼. make g_* 가 자동으로 읽는다.
# 목록을 보려면 gdb 안에서  help user-defined

define walk
  set $p = $arg0
  set $n = 0
  while $p != 0
    printf "  [%d] %p  item=%-3d next=%p\n", $n, $p, $p->item, $p->next
    set $p = $p->next
    set $n = $n + 1
    if $n > 30
      printf "  ... 30 개에서 끊었다. 고리가 생겼을 수 있다.\n"
      loop_break
    end
  end
  printf "  -> 총 %d 개\n", $n
end
document walk
사슬을 따라가며 노드를 전부 찍는다.  사용:  walk FirstNode   walk ll2->head
end

# 이름 주의: vars 는 ~/.config/gdb/varwin.py 의 명령이다. 여기서 다시 정의하지 말 것.

define chains
  printf "새 사슬 (FirstNode 부터):\n"
  walk FirstNode
  printf "원본 ll1 (prev1 부터):\n"
  walk prev1
  printf "ll2 (ll2->head 부터):\n"
  walk ll2->head
end
document chains
세 사슬을 한 번에 찍는다. 반복문 안에서는 새 사슬이 아직 자라는 중이다.
end

# 줄 번호는 파일을 고치면 바뀐다. 중단점은 그때그때 직접 걸 것.
#   break alternateMergeLinkedList
#   break play4.c:<줄번호>
