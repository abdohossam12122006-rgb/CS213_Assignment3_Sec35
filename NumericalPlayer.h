#pragma once
#include "BoardGame_Classes.h" 
#include <vector>
#include <string>

class NumericalPlayer : public Player<char>
{
private:
    std::vector<int> available_numbers;

public:
    NumericalPlayer(char symbol, const std::string& name, const std::vector<int>& numbers)
        : Player<char>(name, symbol, PlayerType::HUMAN), available_numbers(numbers)
    {
    }

    const std::vector<int>& get_available_numbers() const {
        return available_numbers;
    }

    bool is_number_available(int num) const {
        for (int n : available_numbers) {
            if (n == num) return true;
        }
        return false;
    }

    void remove_number(int num) {
        for (size_t i = 0; i < available_numbers.size(); ++i) {
            if (available_numbers[i] == num) {
                available_numbers.erase(available_numbers.begin() + i);
                break;
            }
        }
    }
};