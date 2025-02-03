#include "task_lib.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdint.h>

using namespace std;

void inputProcess(char* input_data) {
    vector<uint8_t> numbers;

    for (size_t i = 0; i < strlen(input_data); i++) {
        int num = input_data[i] - '0';
        numbers.push_back(num);
    }

    sort(numbers.begin(), numbers.end(), greater<uint8_t>());

    string result;

    for (uint8_t number : numbers) {
        if (number % 2 == 0) {
            result += "KB";
        }
        else {
            result += (char)(number + '0');
        }
    }

    strcpy(input_data, result.c_str());
}

int sumDigits(char* input_data) {
    uint16_t sum = 0;

    for (size_t i = 0; i < strlen(input_data); i++) {
        if (isdigit(input_data[i])) {
            sum += input_data[i] - '0';
        }
    }

    return sum;
}

bool checkNumber(int sum) {
    return (sum > 9 && sum % 32 == 0);
}