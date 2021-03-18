
#include "BenchinePCH.h"
#include "GeneralHelpers.hpp"

#pragma warning (push, 0)
#include <nanosvg.h>
#pragma warning (pop)
#pragma region HelperFunctions
//MATH HELPERS
//************
[[nodiscard]] auto MathHelper::PolyCenter(const Polygon2D& polygon) noexcept -> glm::vec2 	// this actually generates the same asm as a simple for loop, but makes it look like I know what I'm doing: https://godbolt.org/z/Z9WeSx
																							// And I know this is clang, but MSVC produces 14k lines on O2 :/ https://godbolt.org/z/wphEjY

{
    const auto vertexSum = std::accumulate(polygon.cbegin(), polygon.cend(), glm::vec2(), [](const glm::vec2& v1, const glm::vec2& v2) {return v1 + v2;});
    return glm::vec2(vertexSum.x / static_cast<f32>(polygon.size()), vertexSum.y / static_cast<f32>(polygon.size()));
}


//COLLISION HELPERS
//*****************
[[nodiscard]] constexpr auto CollisionHelper::IsPointInFRect(const glm::vec2& p, const FRect& r) noexcept-> bool
{
    return p.x >= r.Pos.x 
		&& p.x <= r.Pos.x + r.Width
		&& p.y >= r.Pos.y
		&& p.y <= r.Pos.y + r.Height;
}

//JSON HELPER
//***********
[[nodiscard]] auto JsonHelper::ReadJson(const std::string& filePath) noexcept-> json
{
    const auto fullPath = RESOURCES->GetDataPath() + filePath;
	json j{};
	if (!std::filesystem::exists(fullPath))
	{
		LOG(Error, "File at location: {0} doesn't exist", fullPath);
	}
	else
	{
		std::ifstream inputFile(fullPath);
		if (!inputFile.is_open())
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

void JsonHelper::WriteJson(const json& j, const std::string& filePath) noexcept
{
    const auto fullPath = RESOURCES->GetDataPath() + filePath;
	std::ofstream outputFile(fullPath);
	if (!outputFile.is_open())
	{
		LOG(Error, "Failed to open file at location: {0}", fullPath);
	}
	else
	{
		outputFile << j;
		outputFile.close();
	}
}

//SVG HELPER
//**********
[[nodiscard]] auto SvgHelper::ReadSvg(const std::string& filePath) noexcept-> std::vector<Polygon2D>
{
    const auto fullPath = RESOURCES->GetDataPath() + filePath;
	const auto image = nsvgParseFromFile(fullPath.c_str(), "px", 96);
    
    std::vector<Polygon2D> polygons;
    for (auto shape = image->shapes; shape != nullptr; shape = shape->next)
    {
        Polygon2D poly;
        for (auto path = shape->paths; path != nullptr; path = path->next)
        {
            for (auto i = 0; i < path->npts; ++i)
            {
                f32* p  = &path->pts[i*2];
                poly.emplace_back(p[0], image->height - p[1]);
            }
        }
        polygons.push_back(poly);
    }
    nsvgDelete(image);
    return polygons;
}
#pragma endregion HelperFunctions