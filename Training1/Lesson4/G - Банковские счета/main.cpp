#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>

enum class OperationType {
    DEPOSIT,
    WITHDRAW,
    INCOME,
    BALANCE,
    TRANSFER
};

std::istream& operator>>(std::istream& input, OperationType& op);

struct Operation {
    OperationType type;
    std::string person;
    std::string person_to_transfer;
    int cnt = 0;
};

std::istream& operator>>(std::istream& input, Operation& op);

class Accounts {
    std::unordered_map<std::string, int64_t> accounts;

public:
    void Deposit(std::string const& name, int sum);
    void Income(int persent);
    void Withdraw(std::string const& name, int sum);
    void Transfer(std::string const& from, std::string const& to, int sum);
    auto Balanse(std::string const& name) const->std::optional<int64_t>;
};

void BankOperations(std::istream& input = std::cin);

auto main() -> int
{
    BankOperations();
}

std::istream& operator>>(std::istream& input, OperationType& op)
{
    std::string operation;
    input >> operation;
    if (operation == "DEPOSIT")
        op = OperationType::DEPOSIT;
    if (operation == "WITHDRAW")
        op = OperationType::WITHDRAW;
    if (operation == "INCOME")
        op = OperationType::INCOME;
    if (operation == "BALANCE")
        op = OperationType::BALANCE;
    if (operation == "TRANSFER")
        op = OperationType::TRANSFER;
    return input;
}

std::istream& operator>>(std::istream& input, Operation& op)
{
    input >> op.type;
    switch (op.type) {
    case OperationType::DEPOSIT:
        input >> op.person >> op.cnt;
        break;
    case OperationType::WITHDRAW:
        input >> op.person >> op.cnt;
        break;
    case OperationType::INCOME:
        input >> op.cnt;
        break;
    case OperationType::TRANSFER:
        input >> op.person >> op.person_to_transfer >> op.cnt;
        break;
    default:
        input >> op.person;
        break;
    }
    return input;
}

void Accounts::Deposit(std::string const& name, int sum)
{
    accounts[name] += sum;
}

void Accounts::Income(int persent)
{
    for (auto& sum : accounts | std::views::values) {
        if (sum > 0) {
            double s = sum;
            s += s / 100.0 * persent;
            sum = s;
        }
    }
}

void Accounts::Withdraw(std::string const& name, int sum)
{
    accounts[name] -= sum;
}

void Accounts::Transfer(std::string const& from, std::string const& to, int sum)
{
    accounts[from] -= sum;
    accounts[to] += sum;
}

auto Accounts::Balanse(std::string const& name) const -> std::optional<int64_t>
{
    auto it = accounts.find(name);
    if (it != accounts.end()) {
        return it->second;
    }
    return std::nullopt;
}

void BankOperations(std::istream& input)
{
    auto account = std::make_unique<Accounts>();
    for (Operation op; input >> op;) {
        switch (op.type) {
        case OperationType::DEPOSIT:
            account->Deposit(op.person, op.cnt);
            break;
        case OperationType::WITHDRAW:
            account->Withdraw(op.person, op.cnt);
            break;
        case OperationType::INCOME:
            account->Income(op.cnt);
            break;
        case OperationType::TRANSFER:
            account->Transfer(op.person, op.person_to_transfer, op.cnt);
            break;
        default:
            auto balance = account->Balanse(op.person);
            if (balance.has_value()) {
                std::cout << balance.value() << '\n';
            }
            else {
                std::cout << "ERROR" << '\n';
            }
            break;
        }
    }
}
