#pragma once
#include <filesystem>
#include <unordered_map>

#include "Debugging/Logger.hpp"

class BaseLoader
{
public:
	BaseLoader() = default;
	virtual ~BaseLoader() = default;
	DEL_ROF(BaseLoader)

	static void SetDataPath(const std::string& dataPath) { m_DataPath = dataPath; }
	[[nodiscard]] static auto GetDataPath() noexcept -> std::string { return m_DataPath; }
	virtual void ReleaseResources() = 0;
protected:
	static std::string m_DataPath;
};

template <class Resource>
class ResourceLoader : public BaseLoader
{
public:
	ResourceLoader() = default;
	virtual ~ResourceLoader() override = default;
	DEL_ROF(ResourceLoader)

	Resource* GetResource(const std::string& filePath)
	{
		// Look if the resource already exists
		for (auto& [name, resource] : m_pResources)
		{
			if (name.compare(filePath) == 0)
			{
				return resource.get();
			}
		}

		// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
		if (!std::filesystem::exists(m_DataPath + filePath))
		{
			LOG(Error, "File at following location not found {0}", m_DataPath + filePath);
			return nullptr;
		}

		if (Resource* pResource = Load(filePath))
		{
			m_pResources.try_emplace(filePath, pResource);
			return pResource;
		}
		
		LOG(Error, "Somehow we got here, this wasn't supposed to happen, resource is nullptr");
		return nullptr;
	}

	void ReleaseResources() override
	{
		LOG(Debug, "Releasing nothing");
		// TODO, test if the smart pointers actually clear everything properly
//		for (auto& resource : m_pResources | std::views::values)
//		{
//			Release(resource);
//		}
//		m_pResources.clear();
	}

protected:
	virtual Resource* Load(const std::string& filePath) = 0;
	static std::unordered_map<std::string_view, std::unique_ptr<Resource>> m_pResources;
};

template <class Resource>
std::unordered_map<std::string_view, std::unique_ptr<Resource>> ResourceLoader<Resource>::m_pResources = std::unordered_map<std::string_view, std::unique_ptr<Resource>>();