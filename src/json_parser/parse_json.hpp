#include <nlohmann/json.hpp>
#include "settings.hpp"

#pragma once
int parse_json(const std::string& filename, Problem_Settings& settings);