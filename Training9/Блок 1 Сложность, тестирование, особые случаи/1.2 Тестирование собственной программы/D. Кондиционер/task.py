def main() -> None:
    t_room, t_cond = map(int, input().split())
    mode = input().strip()

    match mode:
        case "fan":
            result = t_room
        case "freeze":
            result = min(t_room, t_cond)
        case "heat":
            result = max(t_room, t_cond)
        case "auto":
            result = t_cond
        case _:
            result = t_room

    print(result)


if __name__ == "__main__":
    main()
