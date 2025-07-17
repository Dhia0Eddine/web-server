#include "../../include/utils/Config.hpp"
#include <algorithm>
#include <cctype>

using namespace HDE;

Config::Config(const std::string& config_file) 
    : config_file_path(config_file) {
    load_config();
}

void Config::trim(std::string& str) {
    // Remove leading whitespace
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    
    // Remove trailing whitespace
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

void Config::parse_line(const std::string& line) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#' || line[0] == ';') {
        return;
    }
    
    // Find the '=' delimiter
    size_t equals_pos = line.find('=');
    if (equals_pos == std::string::npos) {
        return; // Invalid line, skip
    }
    
    // Extract key and value
    std::string key = line.substr(0, equals_pos);
    std::string value = line.substr(equals_pos + 1);
    
    // Trim whitespace
    trim(key);
    trim(value);
    
    // Remove quotes if present
    if (value.length() >= 2 && 
        ((value.front() == '"' && value.back() == '"') || 
         (value.front() == '\'' && value.back() == '\''))) {
        value = value.substr(1, value.length() - 2);
    }
    
    config_data[key] = value;
}

bool Config::load_config() {
    std::ifstream config_file(config_file_path);
    if (!config_file.is_open()) {
        Logger::log("Config file not found: " + config_file_path + ", using defaults", Logger::WARNING);
        return false;
    }
    
    std::string line;
    while (std::getline(config_file, line)) {
        parse_line(line);
    }
    
    config_file.close();
    Logger::log("Configuration loaded from: " + config_file_path, Logger::INFO);
    return true;
}

std::string Config::get_string(const std::string& key, const std::string& default_value) const {
    auto it = config_data.find(key);
    if (it != config_data.end()) {
        return it->second;
    }
    return default_value;
}

int Config::get_int(const std::string& key, int default_value) const {
    auto it = config_data.find(key);
    if (it != config_data.end()) {
        try {
            return std::stoi(it->second);
        } catch (const std::exception& e) {
            Logger::log("Invalid integer value for key '" + key + "': " + it->second, Logger::ERROR);
            return default_value;
        }
    }
    return default_value;
}

bool Config::get_bool(const std::string& key, bool default_value) const {
    auto it = config_data.find(key);
    if (it != config_data.end()) {
        std::string value = it->second;
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        
        if (value == "true" || value == "yes" || value == "1" || value == "on") {
            return true;
        } else if (value == "false" || value == "no" || value == "0" || value == "off") {
            return false;
        } else {
            Logger::log("Invalid boolean value for key '" + key + "': " + it->second, Logger::ERROR);
            return default_value;
        }
    }
    return default_value;
}

bool Config::has_key(const std::string& key) const {
    return config_data.find(key) != config_data.end();
}

void Config::set(const std::string& key, const std::string& value) {
    config_data[key] = value;
}

bool Config::save_config() {
    std::ofstream config_file(config_file_path);
    if (!config_file.is_open()) {
        Logger::log("Failed to open config file for writing: " + config_file_path, Logger::ERROR);
        return false;
    }
    
    for (const auto& pair : config_data) {
        config_file << pair.first << " = " << pair.second << std::endl;
    }
    
    config_file.close();
    Logger::log("Configuration saved to: " + config_file_path, Logger::INFO);
    return true;
}

void Config::print_config() const {
    Logger::log("=== Configuration Settings ===", Logger::INFO);
    for (const auto& pair : config_data) {
        Logger::log(pair.first + " = " + pair.second, Logger::INFO);
    }
    Logger::log("===============================", Logger::INFO);
}
