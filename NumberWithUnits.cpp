#include "NumberWithUnits.hpp"
#include <iostream>
#include <istream>
#include <unordered_map>

using namespace std;

namespace ariel
{
  std::unordered_map<std::string, std::unordered_map<std::string, double>> NumberWithUnits::Units;

  void NumberWithUnits::read_units(std::ifstream &file)
  {
    std::string unit_a;
    std::string unit_b;
    std::string temp_str;

    double measure;
    while (file.good())
    {
      file >> measure >> unit_a >> unit_b >> measure >> unit_b;
      if (Units.find(unit_a) == Units.end())
      {
        Units[unit_a][unit_b] = measure;
      }

      if (Units.find(unit_b) == Units.end())
      {
        Units[unit_b][unit_a] = (1 / measure);
      }

      else
      {
        Units.at(unit_a)[unit_b] = measure;
        Units.at(unit_b)[unit_a] = measure;
      }
    }
  }

  NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &b)
  {
    if (this->_Num_unit == b._Num_unit)
    {
      return NumberWithUnits(this->_Num_size - b._Num_size, this->_Num_unit);
    }
    else if (Units.at(this->_Num_unit).find(b._Num_unit) != Units.at(this->_Num_unit).end())
    {
      double temp = Units.at(b._Num_unit).at(this->_Num_unit) * b._Num_size;
      return NumberWithUnits(this->_Num_size - temp, this->_Num_unit);
    }
    else
      throw std::invalid_argument("Units are not from the same type\n");
  }

  NumberWithUnits NumberWithUnits::operator-() const
  {
    return NumberWithUnits(0 - this->_Num_size, this->_Num_unit);
  }
  NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &b)
  {
    if (this->_Num_unit == b._Num_unit)
    {
      this->_Num_size -= b._Num_size;
      return *this;
    }
    else if (Units.at(this->_Num_unit).find(b._Num_unit) != Units.at(this->_Num_unit).end())
    {
      double temp = Units.at(b._Num_unit).at(this->_Num_unit) * b._Num_size;
      this->_Num_size -= temp;
      return *this;
    }
    else
      throw std::invalid_argument("Units are not from the same type\n");
  }
  NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &b)
  {
    if (this->_Num_unit == b._Num_unit)
    {
      this->_Num_size += b._Num_size;
      return *this;
    }
    else if (Units.at(this->_Num_unit).find(b._Num_unit) != Units.at(this->_Num_unit).end())
    {
      double temp = Units.at(b._Num_unit).at(this->_Num_unit) * b._Num_size;
      this->_Num_size += temp;
      return *this;
    }
    else
      throw std::invalid_argument("Units are not from the same type\n");
  }
  bool NumberWithUnits::operator>(const NumberWithUnits &b) const
  {
    if (this->_Num_unit == b._Num_unit)
    {
      if (this->_Num_size > b._Num_size)
      {
        return true;
      }
      return false;
    }

    else if (Units.at(this->_Num_unit).find(b._Num_unit) != Units.at(this->_Num_unit).end())
    {
      double temp = Units.at(b._Num_unit).at(this->_Num_unit) * b._Num_size;
      if (this->_Num_size > temp)
      {
        return true;
      }
      return false;
    }
    else
      throw std::invalid_argument("Units are not from the same type\n");
  }
  bool NumberWithUnits::operator!=(const NumberWithUnits &b) const
  {
    return !(*this == b);
  }
  bool NumberWithUnits::operator<=(const NumberWithUnits &b) const
  {
    if (*this > b)
    {
      return false;
    }
    return true;
  }
  bool NumberWithUnits::operator==(const NumberWithUnits &b) const
  {
    if (*this > b || b > *this)
    {
      return false;
    }
    return true;
  }

  NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &b)
  {
    if (this->_Num_unit == b._Num_unit)
    {
      return NumberWithUnits(b._Num_size + this->_Num_size, this->_Num_unit);
    }
    else if (Units.at(this->_Num_unit).find(b._Num_unit) != Units.at(this->_Num_unit).end())
    {
      double temp = Units.at(b._Num_unit).at(this->_Num_unit) * b._Num_size;
      return NumberWithUnits(temp + this->_Num_size, this->_Num_unit);
    }
    else
      throw std::invalid_argument("Units are not from the same type\n");
  }

  NumberWithUnits NumberWithUnits::operator+() { return *this; }

  NumberWithUnits NumberWithUnits::operator*(double n) const { return NumberWithUnits(this->_Num_size * n, this->_Num_unit); }

  NumberWithUnits operator*(double n, const NumberWithUnits &obj) { return NumberWithUnits(obj._Num_size * n, obj._Num_unit); }

  std::ostream &operator<<(std::ostream &os, const NumberWithUnits &obj)
  {
    os << obj._Num_size << "[" << obj._Num_unit << "]" << endl;
    return os;
  }

  std::istream &operator>>(std::istream &os, NumberWithUnits &obj)
  {

    std::string size = "";
    std::string unit = "";
    char b;
    while (os.get(b))
    {
      while (b != '[' && b != ' ')
      {
        size += b;
        os.get(b);
      }

      while (b == ' ' || b == '[')
      {
        os.get(b);
      }

      while (b != ']' && b != ' ')
      {
        unit += b;
        os.get(b);
      }
      break;
    }

    if (obj.Units.find(unit) != obj.Units.end())
    {
      obj._Num_size = std::stof(size);
      obj._Num_unit = unit;
      return os;
    }

    else
      throw std::invalid_argument("Units are not in Units format , invalid operation.\n Exit \n");
  }

  bool NumberWithUnits::operator<(const NumberWithUnits &b) const { return b > *this; }
  bool NumberWithUnits::operator>=(const NumberWithUnits &b) const { return b < *this; }

  NumberWithUnits NumberWithUnits::operator++(int)
  {
    NumberWithUnits temp = NumberWithUnits(this->_Num_size, this->_Num_unit);
    this->_Num_size += 1;
    return temp;
  }
  NumberWithUnits &NumberWithUnits::operator++()
  {
    this->_Num_size += 1;
    return *this;
  }
  NumberWithUnits NumberWithUnits::operator--(int)
  {
    NumberWithUnits temp = NumberWithUnits(this->_Num_size, this->_Num_unit);
    this->_Num_size -= 1;
    return temp;
  }
  NumberWithUnits &NumberWithUnits::operator--()
  {
    this->_Num_size -= 1;
    return *this;
  }
}