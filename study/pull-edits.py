#!/usr/bin/env python3
"""발표자료에서 Ctrl+S 로 내려받은 사본의 글자 수정을 원본으로 옮긴다.

Ctrl+S 는 프로젝트 파일이 아니라 Windows 다운로드 폴더에 사본을 떨어뜨린다.
사본은 브라우저가 DOM 을 직렬화한 것이라 그대로 덮어쓰면 안 된다
(이동 점 버튼, visible 클래스, 인라인 style 이 같이 딸려 온다).
그래서 슬라이드 <section> 의 안쪽만 id 로 짝지어 옮긴다.

사용법:  python3 study/pull-edits.py            # 가장 새 사본을 찾아서 옮긴다
         python3 study/pull-edits.py 경로.html  # 특정 사본을 옮긴다
"""
import re, sys, pathlib, glob

SRC = pathlib.Path(__file__).with_name('week04-array-in-c.html')
DL  = pathlib.Path('/mnt/c/Users/benjohnbill/Downloads')

def newest_download():
    files = sorted(glob.glob(str(DL / 'week04-array-in-c*.html')), key=lambda f: pathlib.Path(f).stat().st_mtime)
    if not files:
        sys.exit('다운로드 폴더에 week04-array-in-c*.html 이 없다')
    return pathlib.Path(files[-1])

SECTION = re.compile(r'(<section class="slide[^"]*" id="([^"]+)"[^>]*>)(.*?)(</section>)', re.S)

def slides(html):
    return {m.group(2): m.group(3) for m in SECTION.finditer(html)}

def clean(inner):
    inner = inner.replace('&nbsp;', ' ')
    inner = re.sub(r' contenteditable="[^"]*"', '', inner)
    return inner

copy = pathlib.Path(sys.argv[1]) if len(sys.argv) > 1 else newest_download()
src_html = SRC.read_text()
new = slides(copy.read_text())
changed = []

def swap(m):
    sid = m.group(2)
    if sid in new and clean(new[sid]) != m.group(3):
        changed.append(sid)
        return m.group(1) + clean(new[sid]) + m.group(4)
    return m.group(0)

out = SECTION.sub(swap, src_html)
if changed:
    SRC.write_text(out)
    print(f'{copy.name} → {SRC.name}: 바뀐 슬라이드 {", ".join(changed)}')
else:
    print(f'{copy.name}: 원본과 같다. 바꾼 것 없음')
