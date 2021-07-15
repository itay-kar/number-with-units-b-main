#pragma once
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <stdbool.h>
#include <unordered_map>

namespace ariel{
class NumberWithUnits
{

private:
    double _Num_size;
    std::string _Num_unit;
    static std::unordered_map<std::string, std::unordered_map<std::string, double>> Units;

public:
    NumberWithUnits(double num, std::string unit)
    {
        if (Units.find(unit) == Units.end())
        {
            throw std::invalid_argument("Unit is not matching units in the txt file please check again.");
        }
        _Num_size = num;
        _Num_unit = unit;
    };

    static void read_units(std::ifstream &file);
    NumberWithUnits operator+(const NumberWithUnits &b);
    NumberWithUnits operator-(const NumberWithUnits &b);
    NumberWithUnits &operator-=(const NumberWithUnits &b);
    NumberWithUnits &operator+=(const NumberWithUnits &b);
    bool operator>(const NumberWithUnits &b) const;
    bool operator<=(const NumberWithUnits &b) const;
    bool operator==(const NumberWithUnits &b) const;
    bool operator!=(const NumberWithUnits &b) const;
    bool operator<(const NumberWithUnits &b) const;
    bool operator>=(const NumberWithUnits &b) const;

    friend NumberWithUnits operator*(double n, const NumberWithUnits &obj);
    NumberWithUnits operator*(double n) const;

    NumberWithUnits operator-() const;
    NumberWithUnits operator+();

    friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &obj);
    friend std::istream &operator>>(std::istream &os, NumberWithUnits &obj);
    NumberWithUnits operator++(int);
    NumberWithUnits& operator++();
    NumberWithUnits operator--(int);
    NumberWithUnits& operator--();
};
}