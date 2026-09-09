def decode_string(text: str) -> str:
    result = []
    chars = list(text)

    while chars:
        if chars[-1] != '#':
            code = int(chars.pop())
            result.append(chr(code - 1 + ord('a')))
        else:
            chars.pop()  # удаляем '#'
            second = int(chars.pop())
            first = int(chars.pop())
            code = first * 10 + second
            result.append(chr(code - 1 + ord('a')))

    return ''.join(reversed(result))


def main() -> None:
    encoded_text = input().strip()
    print(decode_string(encoded_text))


if __name__ == "__main__":
    main()
