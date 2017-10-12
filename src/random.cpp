#include "random.hpp"

namespace {

std::random_device device;
std::mt19937 generator(device());

} // namespace

std::mt19937& gen()
{
    return generator;
}