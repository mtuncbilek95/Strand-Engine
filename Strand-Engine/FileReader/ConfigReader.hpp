// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <nlohmann/json.hpp>

namespace Strand
{
// @brief This class represents a reader that is used to read editor specifications from a json file.
class ConfigReader
{
public:
    ConfigReader(const std::string& configFile)
    {
        std::ifstream file(configFile);
        if(!file.is_open()) {
            std::cout << "Config file not found. Creating default config file." << std::endl;
            CreateDefaultConfig();
            return;
        }

        file >> Config_;
    }

    ~ConfigReader() = default;

    std::string GetApplicationName()
    {
        return Config_.at("EngineInfo").at("ApplicationName").get<std::string>();
    }

    XMINT2 GetWindowSize()
    {
        return XMINT2(Config_.at("EngineInfo").at("WindowSize").at(0).get<int>(),
                      Config_.at("EngineInfo").at("WindowSize").at(1).get<int>());
    }

    bool GetFullscreen()
    {
        if(Config_.at("EngineInfo").at("Fullscreen").is_null())
            return false;
        else if(!Config_.at("EngineInfo").at("Fullscreen").is_boolean())
            return false;
        else
            return Config_.at("EngineInfo").at("Fullscreen").get<bool>();
    }

    bool GetVSync()
    {
        if(Config_.at("EngineInfo").at("VSync").is_null())
            return true;
        else if(!Config_.at("EngineInfo").at("VSync").is_boolean())
            return true;
        else
            return Config_.at("EngineInfo").at("VSync").get<bool>();

    }

    uint32_t GetBuffering()
    {
        if(Config_.at("EngineInfo").at("Buffering").is_null())
            return 0;
        else if(!Config_.at("EngineInfo").at("Buffering").is_number_integer())
            return 0;
        else if(Config_.at("EngineInfo").at("Buffering").get<uint32_t>() < 0)
            return 0;
        else if(Config_.at("EngineInfo").at("Buffering").get<uint32_t>() > 3)
            return 3;
        else
            return Config_.at("EngineInfo").at("Buffering").get<uint32_t>();
    }

    uint32_t GetTargetFPS()
    {
        if(Config_.at("EngineInfo").at("Target FPS").get<uint32_t>() < 0)
            return 60;
        else if(Config_.at("EngineInfo").at("Target FPS").get<uint32_t>() > 144)
            return 144;
        else
            return Config_.at("EngineInfo").at("Target FPS").get<uint32_t>();
    }

private:
    void CreateDefaultConfig()
    {
        nlohmann::json defaultConfig = {
                {"EngineInfo", {
                                       {"ApplicationName", "Strand Engine"},
                                       {"WindowSize", {1280, 720}},
                                       {"Fullscreen", false},
                                       {"VSync", true},
                                       {"Target FPS", 60},
                                       {"MSAA", 0},
                                       {"Buffering", 3}
                               }}
        };

        std::ofstream file("Config.json");
        file << std::setw(4) << defaultConfig << std::endl;
        file.close();

        Config_ = defaultConfig;

        std::cout << "Default config file created." << std::endl;
    }

private:
    nlohmann::json Config_;
};

} // Strand
