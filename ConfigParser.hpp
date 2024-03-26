#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigParser
{
public:
    bool parse(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value))
            {
                config[key] = value;
            }
            else
            {
                std::cerr << "Error parsing line: " << line << std::endl;
                return false;
            }
        }

        return true;
    }
    std::string get(const std::string &key) const
    {
        auto value = config.find(key);
        if (value != config.end())
        {
            return value->second;
        }
        return "";
    }
    void set(const std::string &key, const std::string &value)
    {
        config[key] = value;
    }

private:
    std::unordered_map<std::string, std::string> config;
};
