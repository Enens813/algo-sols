def ant_position(w, h, p, q, t):
    # x, y 좌표를 각각 2w, 2h 주기 내에서 변환
    x = (p + t) % (2 * w)
    y = (q + t) % (2 * h)

    # 반사 적용 (경계를 넘었을 경우 대칭 변환)
    if x > w:
        x = 2 * w - x
    if y > h:
        y = 2 * h - y

    return x, y

# 입력 받기
w, h = map(int, input().split())
p, q = map(int, input().split())
t = int(input())

# 결과 출력
x, y = ant_position(w, h, p, q, t)
print(x, y)
