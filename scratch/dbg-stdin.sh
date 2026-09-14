#!/bin/sh
# 디버거에 붙일 stdin 파이프.
#
# Zed 의 WSL 터미널 탭에서 이 스크립트를 먼저 실행한 뒤, 디버그 세션을
# `Q1_A_LL (CodeLLDB, 터미널 입력 파이프)` 항목으로 시작한다.
# 이 창에 입력한 한 줄이 그대로 디버기의 stdin 으로 들어간다.
#
# Windows ConPTY 를 거치지 않고 WSL 안에서 직접 연결되므로,
# 원격 구성에서도 stdin 이 EOF 로 떨어지지 않는다. 종료는 Ctrl+C.
FIFO=/tmp/q1-stdin
[ -p "$FIFO" ] || { rm -f "$FIFO"; mkfifo "$FIFO"; }
echo "stdin 파이프: $FIFO"
echo "디버그 세션을 시작한 뒤, 메뉴 번호를 여기에 입력하세요. (종료: Ctrl+C)"
cat > "$FIFO"
