#pragma once
#include <vector>

#ifndef NANOSVG_IMPLEMENTATION
#define NANOSVG_IMPLEMENTATION	// Expands implementation
#endif
#include <nanosvg.h>

#include "Core/CoreTypes.hpp"
#include "Resources/ResourceManager.h"

namespace SvgHelper
{
	[[nodiscard]] inline auto ReadSvg(const std::string& filePath) noexcept -> std::vector<Polygon2D>
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
					f32* p = &path->pts[i * 2];
					poly.emplace_back(p[0], image->height - p[1]);
				}
			}
			polygons.push_back(poly);
		}
		nsvgDelete(image);
		return polygons;
	}
}
