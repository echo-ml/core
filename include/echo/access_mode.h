#pragma once

namespace echo {
namespace access_mode {
struct readonly_t {};
struct readwrite_t {};
struct raw_t {};
constexpr readonly_t readonly{};
constexpr readwrite_t readwrite{};
constexpr raw_t raw{};
}
}
