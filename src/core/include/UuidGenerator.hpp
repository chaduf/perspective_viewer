#pragma once

#include <array>
#include <cstdint>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace Perspective::core {

    class UuidGenerator {
    public:
        using UuidBytes = std::array<std::uint8_t, 16>;

        static std::string generate() {
            static thread_local std::mt19937_64 engine{ std::random_device{}() };
            std::uniform_int_distribution<std::uint64_t> dist;

            UuidBytes bytes{};
            fillWithRandom(bytes, dist, engine);

            // RFC 4122: version 4 and variant 10x
            bytes[6] = static_cast<std::uint8_t>((bytes[6] & 0x0F) | 0x40);
            bytes[8] = static_cast<std::uint8_t>((bytes[8] & 0x3F) | 0x80);

            return toString(bytes);
        }

    private:
        static void fillWithRandom(UuidBytes& bytes,
                                   std::uniform_int_distribution<std::uint64_t>& dist,
                                   std::mt19937_64& engine) {
            std::size_t idx = 0;
            while (idx < bytes.size()) {
                const std::uint64_t value = dist(engine);
                for (int shift = 0; shift < 8 && idx < bytes.size(); ++shift, ++idx) {
                    bytes[idx] = static_cast<std::uint8_t>(value >> (shift * 8));
                }
            }
        }

        static std::string toString(const UuidBytes& bytes) {
            std::ostringstream oss;
            oss << std::hex << std::setfill('0');

            for (std::size_t i = 0; i < bytes.size(); ++i) {
                oss << std::setw(2) << static_cast<int>(bytes[i]);
                if (i == 3 || i == 5 || i == 7 || i == 9) {
                    oss << '-';
                }
            }
            return oss.str();
        }
    };

} // namespace Perspective::core

