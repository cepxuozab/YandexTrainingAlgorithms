import subprocess
import os
import sys
import shutil
from pathlib import Path

def is_tool(name):
    """Проверяем, что исполняемый файл доступен в PATH."""
    from shutil import which
    return which(name) is not None

def normalize_output(text):
    """Нормализация вывода для сравнения."""
    return '\n'.join(
        line.rstrip()
        for line in text.strip().splitlines()
        if line.strip() != ''
    )

def run_test_case(exe_path, input_path, expected_output_path):
    """Запускает один тестовый случай."""
    # Читаем ожидаемый вывод
    with open(expected_output_path, 'r') as f:
        expected_output = normalize_output(f.read())

    # Запускаем программу
    try:
        with open(input_path, 'r') as infile:
            result = subprocess.run(
                [exe_path],
                stdin=infile,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=5
            )
    except subprocess.TimeoutExpired:
        return False, "Timeout expired", ""

    if result.returncode != 0:
        return False, f"Program exited with code {result.returncode}", result.stderr

    actual_output = normalize_output(result.stdout)
    return actual_output == expected_output, actual_output, expected_output

def main():
    # Пути
    project_dir = Path(__file__).parent
    build_dir = project_dir / "build"
    tests_dir = project_dir / "tests"
    executable_name = "main.exe" if os.name == "nt" else "main"
    exe_path = build_dir / executable_name

    # Создаём build-папку
    build_dir.mkdir(exist_ok=True)

    # Выбираем генератор и команду сборки
    if is_tool("ninja"):
        cmake_generator = "Ninja"
        build_cmd = ["ninja"]
        print("# Ninja найден, используем генератор Ninja")
    else:
        cmake_generator = "MinGW Makefiles"
        build_cmd = ["make"]
        print("# Ninja не найден, используем генератор MinGW Makefiles")

    # Генерируем файлы сборки
    print("# Запускаем CMake...")
    cmake_cmd = ["cmake", "-G", cmake_generator, str(project_dir)]
    cmake_result = subprocess.run(cmake_cmd, cwd=build_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    if cmake_result.returncode != 0:
        print("❌ Ошибка при выполнении CMake:")
        print(cmake_result.stdout)
        print(cmake_result.stderr)
        sys.exit(1)

    # Сборка проекта
    print("# Собираем проект...")
    make_result = subprocess.run(build_cmd, cwd=build_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    if make_result.returncode != 0:
        print("❌ Ошибка при сборке проекта:")
        print(make_result.stdout)
        print(make_result.stderr)
        sys.exit(1)

    # Находим все тестовые случаи
    test_cases = []
    for test_dir in tests_dir.iterdir():
        if test_dir.is_dir():
            input_file = test_dir / "input.txt"
            output_file = test_dir / "expected_output.txt"
            if input_file.exists() and output_file.exists():
                test_cases.append((test_dir.name, input_file, output_file))

    if not test_cases:
        print("❌ Не найдено ни одного тестового случая!")
        sys.exit(1)

    # Запускаем тесты
    print(f"\n# Найдено {len(test_cases)} тестовых случаев")
    failed_tests = 0

    for test_name, input_path, expected_output_path in test_cases:
        print(f"\n=== Тест '{test_name}' ===")
        success, actual_output, expected_output = run_test_case(exe_path, input_path, expected_output_path)

        if success:
            print("✅ Успех!")
        else:
            failed_tests += 1
            print("❌ Ошибка!")
            print("Ожидаемый вывод:")
            print(expected_output)
            print("Фактический вывод:")
            print(actual_output)

    # Итоги
    print(f"\n# Итоги: {len(test_cases) - failed_tests} прошло, {failed_tests} не прошло")

    if failed_tests == 0:
        shutil.rmtree(build_dir)  # Удаляем папку build
        sys.exit(0)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()