# ─────────────────────────────────────────────────────────────
#  week04 빌드 설정
#
#  사용법이 궁금하면 그냥  make  만 치면 된다.
#
#  아래 NAMES / RNAMES / GNAMES / SNAMES 는 손으로 적어 둔 목록이다.
#  find 같은 명령으로 계산하면 zsh 의 탭 완성이 이름을 읽지 못한다.
#  문제 파일이 추가되거나 이름이 바뀌면 이 목록도 함께 고쳐야 한다.
# ─────────────────────────────────────────────────────────────

CC       := gcc
CFLAGS   := -std=gnu17 -Wall -Wextra -Wno-unused-parameter -g -O0
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BIN   := build
VPATH := Data-Structures/Linked_List Data-Structures/Stack_and_Queue Data-Structures/Binary_Tree Data-Structures/Binary_Search_Tree scratch

NAMES  := Q1_A_LL Q2_A_LL Q3_A_LL Q4_A_LL Q5_A_LL Q6_A_LL Q7_A_LL Q1_C_SQ Q2_C_SQ Q3_C_SQ Q4_C_SQ Q5_C_SQ Q6_C_SQ Q7_C_SQ Q1_E_BT Q2_E_BT Q3_E_BT Q4_E_BT Q5_E_BT Q6_E_BT Q7_E_BT Q8_E_BT Q1_F_BST Q2_F_BST Q3_F_BST Q4_F_BST Q5_F_BST play1 play2 play3 play4 play5

RNAMES := r_Q1_A_LL r_Q2_A_LL r_Q3_A_LL r_Q4_A_LL r_Q5_A_LL r_Q6_A_LL r_Q7_A_LL r_Q1_C_SQ r_Q2_C_SQ r_Q3_C_SQ r_Q4_C_SQ r_Q5_C_SQ r_Q6_C_SQ r_Q7_C_SQ r_Q1_E_BT r_Q2_E_BT r_Q3_E_BT r_Q4_E_BT r_Q5_E_BT r_Q6_E_BT r_Q7_E_BT r_Q8_E_BT r_Q1_F_BST r_Q2_F_BST r_Q3_F_BST r_Q4_F_BST r_Q5_F_BST r_play1 r_play2 r_play3 r_play4 r_play5

GNAMES := g_Q1_A_LL g_Q2_A_LL g_Q3_A_LL g_Q4_A_LL g_Q5_A_LL g_Q6_A_LL g_Q7_A_LL g_Q1_C_SQ g_Q2_C_SQ g_Q3_C_SQ g_Q4_C_SQ g_Q5_C_SQ g_Q6_C_SQ g_Q7_C_SQ g_Q1_E_BT g_Q2_E_BT g_Q3_E_BT g_Q4_E_BT g_Q5_E_BT g_Q6_E_BT g_Q7_E_BT g_Q8_E_BT g_Q1_F_BST g_Q2_F_BST g_Q3_F_BST g_Q4_F_BST g_Q5_F_BST g_play1 g_play2 g_play3 g_play4 g_play5

SNAMES := s_Q1_A_LL s_Q2_A_LL s_Q3_A_LL s_Q4_A_LL s_Q5_A_LL s_Q6_A_LL s_Q7_A_LL s_Q1_C_SQ s_Q2_C_SQ s_Q3_C_SQ s_Q4_C_SQ s_Q5_C_SQ s_Q6_C_SQ s_Q7_C_SQ s_Q1_E_BT s_Q2_E_BT s_Q3_E_BT s_Q4_E_BT s_Q5_E_BT s_Q6_E_BT s_Q7_E_BT s_Q8_E_BT s_Q1_F_BST s_Q2_F_BST s_Q3_F_BST s_Q4_F_BST s_Q5_F_BST s_play1 s_play2 s_play3 s_play4 s_play5

LL_LIST  := Q1_A_LL Q2_A_LL Q3_A_LL Q4_A_LL Q5_A_LL Q6_A_LL Q7_A_LL 
SQ_LIST  := Q1_C_SQ Q2_C_SQ Q3_C_SQ Q4_C_SQ Q5_C_SQ Q6_C_SQ Q7_C_SQ 
BT_LIST  := Q1_E_BT Q2_E_BT Q3_E_BT Q4_E_BT Q5_E_BT Q6_E_BT Q7_E_BT Q8_E_BT 
BST_LIST := Q1_F_BST Q2_F_BST Q3_F_BST Q4_F_BST Q5_F_BST 
PLAY_LIST := play1 play2 play3 play4 play5

.DEFAULT_GOAL := help

# ─── 실제 컴파일 규칙 (이 한 줄이 27개 파일 전부를 처리한다) ───
$(BIN)/%: %.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@

$(BIN):
	@mkdir -p $@

# ─── 짧은 이름표 ───
$(NAMES): %: $(BIN)/%
	@echo "→ $(BIN)/$@"

$(RNAMES): r_%: $(BIN)/%
	@./$<

$(GNAMES): g_%: $(BIN)/%
	@gdb -q -x scratch/walk.gdb ./$<

$(SNAMES): s_%: %.c | $(BIN)
	$(CC) $(CFLAGS) $(SANFLAGS) $< -o $(BIN)/$*_san
	@./$(BIN)/$*_san

clean:
	@rm -rf $(BIN)
	@echo "$(BIN)/ 삭제 완료. .c 파일은 그대로."

help:
	@printf '\n'
	@printf '  make %-12s %s\n' 'Q1_A_LL'   '빌드만 (컴파일 확인용)'
	@printf '  make %-12s %s\n' 'r_Q1_A_LL' '빌드 + 실행'
	@printf '  make %-12s %s\n' 'g_Q1_A_LL' '빌드 + gdb 진입'
	@printf '  make %-12s %s\n' 's_Q1_A_LL' '빌드 + 메모리 검사 실행'
	@printf '  make %-12s %s\n' 'clean'     '빌드 결과 삭제'
	@printf '\n  이름 앞부분 입력 후 TAB → 자동 완성\n\n'
	@printf '  %-20s %s\n' 'Linked_List'        '$(LL_LIST)'
	@printf '  %-20s %s\n' 'Stack_and_Queue'    '$(SQ_LIST)'
	@printf '  %-20s %s\n' 'Binary_Tree'        '$(BT_LIST)'
	@printf '  %-20s %s\n' 'Binary_Search_Tree' '$(BST_LIST)'
	@printf '  %-20s %s\n' 'scratch (연습장)'   '$(PLAY_LIST)'
	@printf '\n'

.PHONY: help clean $(NAMES) $(RNAMES) $(GNAMES) $(SNAMES)
