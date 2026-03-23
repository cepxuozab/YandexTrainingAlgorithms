def get_entrance_and_floor(flat_no: int, flats_on_floor: int, floors: int) -> tuple[int, int]:
    floor_before = (flat_no - 1) // flats_on_floor
    entrance = floor_before // floors + 1
    floor = floor_before % floors + 1
    return entrance, floor


def check(k1: int, m: int, k2: int, p2: int, n2: int, flats_on_floor: int) -> tuple[int, int]:
    entrance2, floor2 = get_entrance_and_floor(k2, flats_on_floor, m)
    if entrance2 == p2 and floor2 == n2:
        return get_entrance_and_floor(k1, flats_on_floor, m)
    return -1, -1


def main() -> None:
    k1, m, k2, p2, n2 = map(int, input().split())

    ent = -1
    floor = -1
    good_flag = False

    for flat_on_floor in range(1, 1_000_001):
        n_ent, n_floor = check(k1, m, k2, p2, n2, flat_on_floor)

        if n_ent != -1:
            good_flag = True

            if ent == -1:
                ent, floor = n_ent, n_floor
            elif ent != n_ent and ent != 0:
                ent = 0
            elif floor != n_floor and floor != 0:
                floor = 0

    if good_flag:
        print(ent, floor)
    else:
        print(-1, -1)


if __name__ == "__main__":
    main()
