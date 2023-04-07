#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>
[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using namespace std;
using ll = long long;
struct Segment // Структура для горизонтального отрезка 
{
    int xl, xr, y, type;
    Segment(int xl, int xr, int y, int type) : xl(xl), xr(xr), y(y), type(type) {} // Конструктор 
    bool operator<(const Segment& segment) const
    {
        // Оператор < для сортировки отрезков 
        return y < segment.y;
    }
};

int main()
{
    int n; // Количество прямоугольников 
    cin >> n;
    vector<int> x; // Вектор для x-координат 
    vector<Segment> seg; // Вектор для горизонтальных отрезков 
    for (int i = 0; i < n; ++i)
    {
        // Считываем прямоугольники 
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2; // x1, y1 - левый нижний угол, x2, y2 - правый верхний 
        // Добавляем x-координаты в отдельный вектор 
        x.push_back(x1);
        x.push_back(x2); // Нижний отрезок открывает прямоугольник, 
        seg.push_back(Segment(x1, x2, y1, 1)); // а верхний - закрывает 
        seg.push_back(Segment(x1, x2, y2, -1));
    }
    sort(x.begin(), x.end()); // Сортируем координаты 
    sort(seg.begin(), seg.end()); // и отрезки 
    ll answer = 0;
    // Суммарная площадь - ответ на задачу 
    for (int i = 1; i < 2 * n; ++i)
    {
        // Перебираем вертикальную полосу 
        int prevY = 0, cnt = 0;
        // Переменные для координаты первого открытого 
        // прямоугольника и количества открытых прямоугольников 
        for (int j = 0; j < 2 * n; ++j)
        {
            // Перебираем горизонтальный отрезок 
            if (seg[j].xr <= x[i - 1] || seg[j].xl >= x[i])
            {
                // Если отрезок не пересекает текущую полосу – 
                // пропускаем его 
                continue;
            }
            if (cnt == 0)
            {
                // Если текущий отрезок - первый, запоминаем его 
                prevY = seg[j].y;
            }
            cnt += seg[j].type; // Увеличиваем или уменьшаем кол-во открытых отрезков 
            if (cnt == 0)
            {
                // Если все прямоугольники закрылись – прибавляем их площадь
                answer += (ll)(seg[j].y - prevY) * (ll)(x[i] - x[i - 1]);
            }
        }
    }
    cout << answer;
    return 0;
}