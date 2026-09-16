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
CFLAGS   := -std=gnu17 -Wall -Wextra -Wno-unused-parameter -g -O0 -Iporting -MMD -MP
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BIN   := build
VPATH := Data-Structures/Linked_List Data-Structures/Stack_and_Queue Data-Structures/Binary_Tree Data-Structures/Binary_Search_Tree scratch porting

NAMES  := Q1_A_LL Q2_A_LL Q3_A_LL Q4_A_LL Q5_A_LL Q6_A_LL Q7_A_LL Q1_C_SQ Q2_C_SQ Q3_C_SQ Q4_C_SQ Q5_C_SQ Q6_C_SQ Q7_C_SQ Q1_E_BT Q2_E_BT Q3_E_BT Q4_E_BT Q5_E_BT Q6_E_BT Q7_E_BT Q8_E_BT Q1_F_BST Q2_F_BST Q3_F_BST Q4_F_BST Q5_F_BST play0 play1 play2 play3 play4 play5 play6 05_recursion 11_divide_conquer 10_binary_search 09_number_theory 08_bubble_sort 04_brute_force 02_array 01_string 06_backtracking

RNAMES := r_Q1_A_LL r_Q2_A_LL r_Q3_A_LL r_Q4_A_LL r_Q5_A_LL r_Q6_A_LL r_Q7_A_LL r_Q1_C_SQ r_Q2_C_SQ r_Q3_C_SQ r_Q4_C_SQ r_Q5_C_SQ r_Q6_C_SQ r_Q7_C_SQ r_Q1_E_BT r_Q2_E_BT r_Q3_E_BT r_Q4_E_BT r_Q5_E_BT r_Q6_E_BT r_Q7_E_BT r_Q8_E_BT r_Q1_F_BST r_Q2_F_BST r_Q3_F_BST r_Q4_F_BST r_Q5_F_BST r_play0 r_play1 r_play2 r_play3 r_play4 r_play5 r_play6 r_05_recursion r_11_divide_conquer r_10_binary_search r_09_number_theory r_08_bubble_sort r_04_brute_force r_02_array r_01_string r_06_backtracking

GNAMES := g_Q1_A_LL g_Q2_A_LL g_Q3_A_LL g_Q4_A_LL g_Q5_A_LL g_Q6_A_LL g_Q7_A_LL g_Q1_C_SQ g_Q2_C_SQ g_Q3_C_SQ g_Q4_C_SQ g_Q5_C_SQ g_Q6_C_SQ g_Q7_C_SQ g_Q1_E_BT g_Q2_E_BT g_Q3_E_BT g_Q4_E_BT g_Q5_E_BT g_Q6_E_BT g_Q7_E_BT g_Q8_E_BT g_Q1_F_BST g_Q2_F_BST g_Q3_F_BST g_Q4_F_BST g_Q5_F_BST g_play0 g_play1 g_play2 g_play3 g_play4 g_play5 g_play6 g_05_recursion g_11_divide_conquer g_10_binary_search g_09_number_theory g_08_bubble_sort g_04_brute_force g_02_array g_01_string g_06_backtracking

SNAMES := s_Q1_A_LL s_Q2_A_LL s_Q3_A_LL s_Q4_A_LL s_Q5_A_LL s_Q6_A_LL s_Q7_A_LL s_Q1_C_SQ s_Q2_C_SQ s_Q3_C_SQ s_Q4_C_SQ s_Q5_C_SQ s_Q6_C_SQ s_Q7_C_SQ s_Q1_E_BT s_Q2_E_BT s_Q3_E_BT s_Q4_E_BT s_Q5_E_BT s_Q6_E_BT s_Q7_E_BT s_Q8_E_BT s_Q1_F_BST s_Q2_F_BST s_Q3_F_BST s_Q4_F_BST s_Q5_F_BST s_play0 s_play1 s_play2 s_play3 s_play4 s_play5 s_play6 s_05_recursion s_11_divide_conquer s_10_binary_search s_09_number_theory s_08_bubble_sort s_04_brute_force s_02_array s_01_string s_06_backtracking

DNAMES := d_05_recursion d_11_divide_conquer d_10_binary_search d_09_number_theory d_08_bubble_sort d_04_brute_force d_02_array d_01_string d_06_backtracking

VNAMES := v_05_recursion v_11_divide_conquer v_10_binary_search v_09_number_theory v_08_bubble_sort v_04_brute_force v_02_array v_01_string v_06_backtracking

LL_LIST  := Q1_A_LL Q2_A_LL Q3_A_LL Q4_A_LL Q5_A_LL Q6_A_LL Q7_A_LL 
SQ_LIST  := Q1_C_SQ Q2_C_SQ Q3_C_SQ Q4_C_SQ Q5_C_SQ Q6_C_SQ Q7_C_SQ 
BT_LIST  := Q1_E_BT Q2_E_BT Q3_E_BT Q4_E_BT Q5_E_BT Q6_E_BT Q7_E_BT Q8_E_BT 
BST_LIST := Q1_F_BST Q2_F_BST Q3_F_BST Q4_F_BST Q5_F_BST 
PLAY_LIST := play0 play1 play2 play3 play4 play5 play6
PORT_LIST := 05_recursion 11_divide_conquer 10_binary_search 09_number_theory 08_bubble_sort 04_brute_force 02_array 01_string 06_backtracking

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

# ─── porting 전용: diff 채점 ───
$(DNAMES): d_%: $(BIN)/%
	@./$< > $(BIN)/$*.actual 2>&1 || true
	@if diff -u porting/$*_output.txt $(BIN)/$*.actual > $(BIN)/$*.diff; then \
		echo "  ✅ $*  출력 일치"; \
	else \
		echo "  ❌ $*  출력 불일치  (왼쪽 - 기대 / 오른쪽 + 실제)"; \
		echo ""; \
		cat $(BIN)/$*.diff; \
	fi

# ─── porting 전용: 메모리 검사 ───
$(VNAMES): v_%: $(BIN)/%
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$<

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
	@printf '  ── porting (python → C) ─────────────────────────\n'
	@printf '  make %-16s %s\n' 'd_05_recursion' '빌드 + 실행 + 기대 출력과 diff (채점)'
	@printf '  make %-16s %s\n' 'v_05_recursion' '빌드 + valgrind 메모리 검사'
	@printf '  %s\n' '  (r_ / g_ / s_ 도 그대로 쓸 수 있다)'
	@printf '\n  풀이 순서: %s\n' '$(PORT_LIST)'
	@printf '\n'

.PHONY: help clean $(NAMES) $(RNAMES) $(GNAMES) $(SNAMES) $(DNAMES) $(VNAMES)

# ─── 헤더 의존성 자동 반영 ───
#  gcc 가 -MMD 로 남긴 build/*.d 를 읽어 들인다.
#  .c 가 include 한 헤더가 바뀌면 그 파일만 다시 컴파일된다.
#  앞의 - 는 .d 가 아직 없는 첫 빌드에서 오류를 내지 말라는 뜻이다.
-include $(BIN)/*.d
