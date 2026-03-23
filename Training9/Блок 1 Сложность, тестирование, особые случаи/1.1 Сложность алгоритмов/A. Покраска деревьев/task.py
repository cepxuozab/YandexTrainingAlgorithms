def main():
    p, v = map(int, input().split())
    q, m = map(int, input().split())
    min_v, max_v = p - v, p + v
    min_m, max_m = q - m, q + m
    if max(min_v, min_m) <= min(max_v, max_m):
        print(max(max_v, max_m) - min(min_v, min_m) + 1)
    else:
        print((max_v - min_v + 1) + (max_m - min_m + 1))


if __name__ == '__main__':
    main()
