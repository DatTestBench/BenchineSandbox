
#include "BenchinePCH.h"
#include "GeneralHelpers.h"
#pragma warning (push, 0)
#include <nanosvg.h>
#pragma warning (pop)
#pragma region HelperFunctions
//MATH HELPERS
//************
[[nodiscard]] auto MathHelper::PolyCenter(const Polygon2D& polygon) noexcept-> const glm::vec2 	// this actually generates the same asm as a simple for loop, but makes it look like I know what I'm doing: https://godbolt.org/z/Z9WeSx
                                                    // And I know this is clang, but MSVC produces 14k lines on O2 :/ https://godbolt.org/z/wphEjY
{
    auto vertexSum = std::accumulate(polygon.cbegin(), polygon.cend(), glm::vec2(), [](const glm::vec2& v1, const glm::vec2& v2) {return v1 + v2;});
    return glm::vec2(vertexSum.x / static_cast<float>(polygon.size()), vertexSum.y / static_cast<float>(polygon.size()));
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
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("JsonHelper::ReadJson()") << "File at location: \"" << fullPath << "\" doesn't exist");
	}
	else
	{
		std::ifstream inputFile(fullPath);
		if (!inputFile.is_open())
		{
			DEBUGONLY(Logger::Log<LEVEL_ERROR>("JsonHelper::ReadJson()") << "Failed to open file at location: \"" << fullPath << "\"");
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
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("JsonHelper::WriteJson()") << "Failed to open file at location: \"" << fullPath << "\"");
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
    struct NSVGimage* image;
    image = nsvgParseFromFile(fullPath.c_str(), "px", 96);\
    
    std::vector<Polygon2D> polygons;
    for (auto shape = image->shapes; shape != nullptr; shape = shape->next)
    {
        Polygon2D poly;
        for (auto path = shape->paths; path != nullptr; path = path->next)
        {
            for (auto i = 0; i < path->npts; ++i)
            {
                float* p  = &path->pts[i*2];
                poly.emplace_back(p[0], image->height - p[1]);
            }
        }
        polygons.push_back(poly);
    }
    nsvgDelete(image);
    return polygons;
}
#pragma endregion HelperFunctions