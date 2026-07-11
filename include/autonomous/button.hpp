#include "autonomous/autonSelector.hpp"
#include <cstdint>

extern void createButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern void createAutonButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern void createColorButton(std::uint32_t boxColor, std::uint32_t textColor,
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern bool detectAutonClick(int16_t dx, int16_t dy);

extern bool detectColorClick(int16_t dx, int16_t dy);