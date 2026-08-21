#include "parse_json.hpp"
#include <fstream>
#include <iostream>
int parse_json(const std::string& filename, Problem_Settings& settings) {
    // Read the JSON file
    std::ifstream file(filename);
    nlohmann::json config;
    file >> config;

    try {
        settings.its = config.value("its", 100);
        settings.x_min = config.value("x_min", -2.0);
        settings.x_max = config.value("x_max", 1.0);
        settings.y_min = config.value("y_min", -1.0);
        settings.y_max = config.value("y_max", 1.0);
        settings.nx = config.value("nx", 256);
        settings.ny = config.value("ny", 256);

        return 0; // Return 0 to indicate success
    }
    catch (const nlohmann::json::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            return -1;
    }
}

