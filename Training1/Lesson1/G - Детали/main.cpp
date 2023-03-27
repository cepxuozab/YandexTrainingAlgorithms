#include <iostream>

auto NumberOfDetails(int TotalAlloyWeight, int WorkpieceWeight, int PartWeight, int quantity)
{
    int reminderN = TotalAlloyWeight % WorkpieceWeight;
    int integer_part_total = TotalAlloyWeight / WorkpieceWeight;
    int remainderK = (WorkpieceWeight % PartWeight) * integer_part_total;
    int integer_part_workpiece = (WorkpieceWeight / PartWeight) * integer_part_total;
    if (integer_part_workpiece == 0) {
        return 0;
    }
    quantity += integer_part_workpiece;
    int total_remainder = reminderN + remainderK;
    if (remainderK > 0 && total_remainder >= WorkpieceWeight) {
        return NumberOfDetails(total_remainder, WorkpieceWeight, PartWeight, quantity);
    }
    return quantity;
}

auto main() -> int
{
    int TotalAlloyWeight;
    int WorkpieceWeight;
    int PartWeight;
    std::cin >> TotalAlloyWeight >> WorkpieceWeight >> PartWeight;
    int quantity = 0;
    std::cout << NumberOfDetails(TotalAlloyWeight, WorkpieceWeight, PartWeight, quantity);
}
