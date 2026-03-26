def main():
    words = set()
    answer = []
    for word in input().split():
        answer.append("YES" if word in words else "NO")
        words.add(word)
    print('\n'.join(answer))


if __name__ == '__main__':
    main()
