#ifndef THELASTDINOSAUR_H
#define THELASTDINOSAUR_H

#include "Constants.h"

//Configuration variables
int window_height;
int window_width;

//Timing and tracking
sf::Clock fr_clock;
sf::Time elapsed;
float elapsed_ms;

//To Load configuration
const char* config = {"Config.xml"};
pugi::xml_document doc;
pugi::xml_parse_result result;

#endif
