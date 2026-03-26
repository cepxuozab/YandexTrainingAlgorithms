from collections import defaultdict
import sys


def main() -> None:
    accounts = defaultdict(int)

    # Читаем все строки до конца ввода
    for line in sys.stdin:
        line = line.strip()
        if not line:  # Пропускаем пустые строки
            continue
        command = line.split()
        if command[0] == "DEPOSIT":
            accounts[command[1]] += int(command[2])
        elif command[0] == "WITHDRAW":
            accounts[command[1]] -= int(command[2])
        elif command[0] == "BALANCE":
            name = command[1]
            print(accounts[name] if name in accounts else "ERROR")
        elif command[0] == "TRANSFER":
            from_name, to_name, amount = command[1], command[2], int(command[3])
            accounts[from_name] -= amount
            accounts[to_name] += amount
        elif command[0] == "INCOME":
            percent = int(command[1])
            for key, val in accounts.items():
                if val > 0:
                    accounts[key] = val + int(val * percent / 100)


if __name__ == "__main__":
    main()
