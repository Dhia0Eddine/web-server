#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "logger.hpp"

namespace HDE {

class Config {
private:
    std::unordered_map<std::string, std::string> config_data;
    std::string config_file_path;
    
    void trim(std::string& str);
    void parse_line(const std::string& line);
    
public:
    // Constructor with default config file path
    Config(const std::string& config_file = "server.conf");
    
    // Load configuration from file
    bool load_config();
    
    // Get configuration value as string
    std::string get_string(const std::string& key, const std::string& default_value = "") const;
    
    // Get configuration value as integer
    int get_int(const std::string& key, int default_value = 0) const;
    
    // Get configuration value as boolean
    bool get_bool(const std::string& key, bool default_value = false) const;
    
    // Check if key exists
    bool has_key(const std::string& key) const;
    
    // Set configuration value (for runtime changes)
    void set(const std::string& key, const std::string& value);
    
    // Save configuration to file
    bool save_config();
    
    // Print all configuration values (for debugging)
    void print_config() const;
};

}

#endif // CONFIG_HPP
