
// Чтобы все узлы решётки (включая середины сторон клеток) имели целые
// координаты, вся геометрия считается в масштабе x2. Каждая клетка 1x1
// делится диагоналями на 4 маленьких треугольника ("юниты"); любой
// допустимый треугольник Андрея описывается битовой маской юнитов, которые
// он целиком покрывает.

#include <array>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace echpochmak {

namespace {
struct Point {
    int x = 0;
    int y = 0;
};
}  // namespace

// Удвоенная ориентированная площадь треугольника (a, b, c).
// Знак определяет ориентацию обхода, ноль — вырожденность.
static auto signedArea2(const Point& a, const Point& b, const Point& c) -> int {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Точка p лежит внутри треугольника (a, b, c) или на его границе.
static auto isInsideTriangle(const Point& p, const Point& a, const Point& b, const Point& c)
    -> bool {
    const int s1 = signedArea2(a, b, p);
    const int s2 = signedArea2(b, c, p);
    const int s3 = signedArea2(c, a, p);
    return (s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0);
}

static auto isAxisAlignedOrDiagonal(int dx, int dy) -> bool {
    return dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy);
}

static auto squaredDistance(const Point& p, const Point& q) -> int {
    const int dx = q.x - p.x;
    const int dy = q.y - p.y;
    return dx * dx + dy * dy;
}

static auto isIsosceles(const Point& a, const Point& b, const Point& c) -> bool {
    const int d1 = squaredDistance(a, b);
    const int d2 = squaredDistance(b, c);
    const int d3 = squaredDistance(c, a);
    return d1 == d2 || d2 == d3 || d3 == d1;
}

namespace {
// Треугольник-кандидат: тройка вершин (в исходном, неудвоенном масштабе)
// вместе с битовой маской покрываемых им юнитов.
struct Candidate {
    std::uint64_t unitMask = 0;
    std::array<Point, 3> vertices{};
};
}  // namespace

namespace {
// Решает задачу упаковки коробки N x M эчпочмаками поверх K уже
// занятых треугольников, используя точное покрытие с мемоизацией.
class Solver {
public:
    Solver(int boxWidth, int boxHeight)
        : width_(boxWidth)
        , height_(boxHeight)
        , unitCount_(4 * boxWidth * boxHeight) {
        buildUnitTriangles();
    }

    // Помечает треугольник (в исходных координатах) как уже занятый.
    void markOccupied(const Point& a, const Point& b, const Point& c) {
        occupiedMask_ |= computeUnitMask(scaled(a), scaled(b), scaled(c));
    }

    void solve() {
        generateCandidates();
        groupCandidatesByUnit();
        minimalCount_ = solveFrom(occupiedMask_);
        reconstructSolution();
    }

    auto minimalCount() const -> int {
        return minimalCount_;
    }
    auto solution() const -> const std::vector<std::array<Point, 3>>& {
        return solution_;
    }

private:
    using UnitTriangle = std::array<Point, 3>;

    static auto scaled(const Point& p) -> Point {
        return {.x = p.x * 2, .y = p.y * 2};
    }

    auto fullMask() const -> std::uint64_t {
        return unitCount_ == 64 ? ~std::uint64_t{0} : (std::uint64_t{1} << unitCount_) - 1;
    }

    // Разбивает каждую клетку 1x1 (в масштабе x2 занимает 2x2) на четыре
    // треугольника диагоналями, проведёнными из центра клетки.
    void buildUnitTriangles() {
        unitTriangles_.resize(unitCount_);
        for (int row = 0; row < height_; ++row) {
            for (int col = 0; col < width_; ++col) {
                const Point bottomLeft{.x = 2 * col, .y = 2 * row};
                const Point bottomRight{.x = 2 * col + 2, .y = 2 * row};
                const Point topLeft{.x = 2 * col, .y = 2 * row + 2};
                const Point topRight{.x = 2 * col + 2, .y = 2 * row + 2};
                const Point center{.x = 2 * col + 1, .y = 2 * row + 1};

                const int base = 4 * (row * width_ + col);
                unitTriangles_[base + 0] = {bottomLeft, bottomRight, center};
                unitTriangles_[base + 1] = {bottomRight, topRight, center};
                unitTriangles_[base + 2] = {topRight, topLeft, center};
                unitTriangles_[base + 3] = {topLeft, bottomLeft, center};
            }
        }
    }

    // Маска юнитов, полностью лежащих внутри треугольника (a, b, c)
    // (координаты уже в масштабе x2).
    auto computeUnitMask(const Point& a, const Point& b, const Point& c) const -> std::uint64_t {
        std::uint64_t mask = 0;
        for (int i = 0; i < unitCount_; ++i) {
            const auto& unit = unitTriangles_[i];
            if (isInsideTriangle(unit[0], a, b, c) && isInsideTriangle(unit[1], a, b, c)
                && isInsideTriangle(unit[2], a, b, c)) {
                mask |= std::uint64_t{1} << i;
            }
        }
        return mask;
    }

    // Перебирает все тройки узлов решётки и оставляет только допустимые
    // треугольники Андрея: невырожденные, равнобедренные, со сторонами,
    // параллельными стороне коробки или диагоналям под 45 градусов.
    // Кандидаты с одинаковой маской дублируют друг друга — оставляем один.
    void generateCandidates() {
        std::vector<Point> latticePoints;
        latticePoints.reserve(static_cast<std::size_t>(width_ + 1) * (height_ + 1));
        for (int y = 0; y <= height_; ++y) {
            for (int x = 0; x <= width_; ++x) {
                latticePoints.push_back({.x = x * 2, .y = y * 2});
            }
        }

        std::set<std::uint64_t> seenMasks;
        const int n = static_cast<int>(latticePoints.size());
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    tryAddCandidate(latticePoints[i], latticePoints[j], latticePoints[k],
                                    seenMasks);
                }
            }
        }
    }

    void tryAddCandidate(const Point& a, const Point& b, const Point& c,
                         std::set<std::uint64_t>& seenMasks) {
        if (signedArea2(a, b, c) == 0) {
            return;  // вырожденный треугольник
        }
        if (!isAxisAlignedOrDiagonal(b.x - a.x, b.y - a.y)
            || !isAxisAlignedOrDiagonal(c.x - b.x, c.y - b.y)
            || !isAxisAlignedOrDiagonal(a.x - c.x, a.y - c.y)) {
            return;  // сторона не параллельна стороне коробки и не диагональ 45°
        }
        if (!isIsosceles(a, b, c)) {
            return;
        }

        const std::uint64_t mask = computeUnitMask(a, b, c);
        if (mask == 0 || !seenMasks.insert(mask).second) {
            return;  // не покрывает ни одного юнита либо такая маска уже встречалась
        }

        candidates_.push_back(
            {.unitMask = mask,
             .vertices = {Point{.x = a.x / 2, .y = a.y / 2}, Point{.x = b.x / 2, .y = b.y / 2},
                          Point{.x = c.x / 2, .y = c.y / 2}}});
    }

    // Для каждого юнита запоминаем индексы кандидатов, которые его покрывают —
    // это ускоряет перебор в solveFrom.
    void groupCandidatesByUnit() {
        candidatesByUnit_.assign(unitCount_, {});
        for (int idx = 0; std::cmp_less(idx, candidates_.size()); ++idx) {
            std::uint64_t mask = candidates_[idx].unitMask;
            while (mask != 0) {
                const int bit = std::countr_zero(mask);
                candidatesByUnit_[bit].push_back(idx);
                mask &= mask - 1;
            }
        }
    }

    // Минимальное число треугольников, чтобы дополнить уже покрытую маску
    // `covered` до полного покрытия коробки. Мемоизируется по маске состояния;
    // лучший следующий кандидат для каждой маски сохраняется в bestChoice_
    // для последующего восстановления ответа.
    auto solveFrom(std::uint64_t covered) -> int {
        const std::uint64_t full = fullMask();
        if (covered == full) {
            return 0;
        }

        if (const auto it = memo_.find(covered); it != memo_.end()) {
            return it->second;
        }

        // Всегда закрываем первый непокрытый юнит — этого достаточно для
        // корректности (он должен быть покрыт хоть каким-то кандидатом)
        // и резко сокращает перебор.
        const int uncoveredUnit = std::countr_zero(~covered & full);

        int best = std::numeric_limits<int>::max();
        int bestCandidateIdx = -1;
        for (const int idx : candidatesByUnit_[uncoveredUnit]) {
            const Candidate& candidate = candidates_[idx];
            if (candidate.unitMask & covered) {
                continue;  // пересекается с уже покрытой областью
            }
            const int total = 1 + solveFrom(covered | candidate.unitMask);
            if (total < best) {
                best = total;
                bestCandidateIdx = idx;
            }
        }

        memo_[covered] = best;
        if (bestCandidateIdx >= 0) {
            bestChoice_[covered] = bestCandidateIdx;
        }
        return best;
    }

    void reconstructSolution() {
        std::uint64_t covered = occupiedMask_;
        const std::uint64_t full = fullMask();
        while (covered != full) {
            const int idx = bestChoice_.at(covered);
            const Candidate& candidate = candidates_[idx];
            solution_.push_back(candidate.vertices);
            covered |= candidate.unitMask;
        }
    }

    int width_;
    int height_;
    int unitCount_;

    std::vector<UnitTriangle> unitTriangles_;
    std::vector<Candidate> candidates_;
    std::vector<std::vector<int>> candidatesByUnit_;

    std::uint64_t occupiedMask_ = 0;
    std::unordered_map<std::uint64_t, int> memo_;
    std::unordered_map<std::uint64_t, int> bestChoice_;

    int minimalCount_ = 0;
    std::vector<std::array<Point, 3>> solution_;
};
}  // namespace

}  // namespace echpochmak

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int m = 0;
    int k = 0;
    std::cin >> n >> m >> k;

    echpochmak::Solver solver(n, m);
    for (int i = 0; i < k; ++i) {
        int x1, y1, x2, y2, x3, y3;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        solver.markOccupied({.x = x1, .y = y1}, {.x = x2, .y = y2}, {.x = x3, .y = y3});
    }

    solver.solve();

    std::cout << solver.minimalCount() << '\n';
    for (const auto& triangle : solver.solution()) {
        for (int i = 0; i < 3; ++i) {
            if (i) {
                std::cout << ' ';
            }
            std::cout << triangle[i].x << ' ' << triangle[i].y;
        }
        std::cout << '\n';
    }

    return 0;
}