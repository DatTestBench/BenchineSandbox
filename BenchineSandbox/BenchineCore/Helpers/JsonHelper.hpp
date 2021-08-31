#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include "Debugging/Logger.hpp"
#include "json/json.hpp"
using json = nlohmann::json;

#include "Resources/ResourceManager.h"

namespace JsonHelper
{
	[[nodiscard]] inline auto ReadJson(const std::string& filePath) noexcept-> json
	{
		const auto fullPath = RESOURCES->GetDataPath() + filePath;
		json j{};
		if (!std::filesystem::exists(fullPath))
		{
			LOG(Error, "File at location: {0} doesn't exist", fullPath);
		}
		else
		{
			if (std::ifstream inputFile(fullPath); !inputFile.is_open())
			{
				LOG(Error, "Failed to open file at location: {0}", fullPath);
			}
			else
			{
				inputFile >> j;
				inputFile.close();
				return j;
			}
		}
		return j;
	}

	inline void WriteJson(const json& j, const std::string& filePath) noexcept
	{
		const auto fullPath = RESOURCES->GetDataPath() + filePath;
		if (std::ofstream outputFile(fullPath); !outputFile.is_open())
		{
			LOG(Error, "Failed to open file at location: {0}", fullPath);
		}
		else
		{
			outputFile << j;
			outputFile.close();
		}
	}
}
