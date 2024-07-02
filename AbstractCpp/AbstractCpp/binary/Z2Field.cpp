#include "Z2Field.h"
#include <exception>

uint8_t Z2Field::getInverseByPlus(uint8_t element)
{
    return (element ^ 1) & 1;
}

uint8_t Z2Field::getInverseByMultiply(uint8_t element)
{
    if (element == _zero) throw std::exception("You can't get 0 inverse in Field");
    return element;
}

uint8_t Z2Field::getZero()
{
    return 0;
}

uint8_t Z2Field::getOne()
{
    return 1;
}

uint8_t Z2Field::getSum(uint8_t a, uint8_t b)
{
    return (a ^ b) & 1;
}

uint8_t Z2Field::getMultiply(uint8_t a, uint8_t b)
{
    return a & b;
}
