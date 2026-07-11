#include "autonomous/autonSelector.hpp"
#include <cstdint>

extern uint32_t VIRIDIAN;
extern uint32_t NUCLEARGREEN;
extern uint32_t DEEPPURPLE;
extern uint32_t RED;
extern uint32_t BLUE;

extern void createLabel(std::uint32_t boxColor, 
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern void createLargeButton(std::uint32_t boxColor, 
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern void createMediumButton(std::uint32_t boxColor, 
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern void createSmallButton(std::uint32_t boxColor, 
                   char * text,
                   std::int16_t x1, std::int16_t y1);

extern bool detectMediumClick(int16_t dx, int16_t dy);

extern bool detectSmallClick(int16_t dx, int16_t dy);

extern void dialog(int autonID, int autonState, std::string autonName);