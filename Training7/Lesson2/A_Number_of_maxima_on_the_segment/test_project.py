import subprocess
import os
import sys

# Ожидаемый результат вывода
expected_output = "2 2\n5 1\n"

# Пути
project_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(project_dir, "build")
input_file_path = os.path.join(project_dir, "input.txt")
executable_name = "main.exe" if os.name == "nt" else "main"
exe_path = os.path.join(build_dir, executable_name)

# Создаём build-папку
os.makedirs(build_dir, exist_ok=True)

# Генерируем make-файлы (для MSYS2 — используем явный генератор)
print("# Запускаем CMake...")
cmake_cmd = ["cmake", "-G", "MSYS Makefiles", project_dir]
cmake_result = subprocess.run(cmake_cmd, cwd=build_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

if cmake_result.returncode != 0:
    print("❌ Ошибка при выполнении CMake:")
    print(cmake_result.stdout)
    print(cmake_result.stderr)
    sys.exit(1)

# Сборка проекта
print("# Собираем проект...")
make_result = subprocess.run(["make"], cwd=build_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

if make_result.returncode != 0:
    print("❌ Ошибка при сборке проекта:")
    print(make_result.stdout)
    print(make_result.stderr)
    sys.exit(1)

# Проверка наличия input.txt
if not os.path.exists(input_file_path):
    print(f"❌ Файл input.txt не найден по пути: {input_file_path}")
    sys.exit(1)

# Запуск программы с input.txt как ввод
print("# Запускаем программу с input.txt...")
try:
    with open(input_file_path, "r") as infile:
        run_result = subprocess.run(
            [exe_path],
            stdin=infile,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            timeout=5
        )
except subprocess.TimeoutExpired:
    print("❌ Программа выполнялась слишком долго и была прервана.")
    sys.exit(1)

if run_result.returncode != 0:
    print("❌ Ошибка при выполнении программы:")
    print(run_result.stderr)
    sys.exit(1)

# Сравнение вывода
actual_output = run_result.stdout.strip()
expected_output = expected_output.strip()

print("# Ожидаемый вывод:")
print(expected_output)
print("# Фактический вывод:")
print(actual_output)

if actual_output == expected_output:
    print("✅ Тест пройден успешно!")
else:
    print("❌ Тест не пройден.")
    sys.exit(1)
