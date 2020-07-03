#pragma once
#include <unordered_map>
#include <string_view>

#include <filesystem>
#include "Debugging/Logger.h"
#include "Helpers/GeneralHelpers.h"
class BaseLoader
{
public:
	BaseLoader() = default;
	virtual ~BaseLoader() = default;
	DEL_ROF(BaseLoader)

	static void SetDataPath(const std::string& dataPath) { m_DataPath = dataPath; }
	[[nodiscard]] auto GetDataPath() const noexcept-> const std::string& { return m_DataPath; }
	virtual void ReleaseResources() = 0;
protected:
	static std::string m_DataPath; // due to the need of appending this with the specific resource path, usage of string_view is impossible
private:

};

template <class T>
class ResourceLoader : public BaseLoader
{
public:
	ResourceLoader() = default;
	virtual ~ResourceLoader() override = default;
	DEL_ROF(ResourceLoader)

	T* GetResource(const std::string& filePath)
	{
		for (std::pair<std::string_view, T*> pResource : m_pResources)
		{
			if (pResource.first.compare(filePath) == 0)
			{
				return pResource.second;
			}
		}

		// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
		if (!std::filesystem::exists(m_DataPath + filePath))
		{
			DEBUGONLY(Logger::Log<LEVEL_ERROR>("ContentManager::GetResource()") << "file at following location not found\n" << m_DataPath + filePath);
			return nullptr;
		}

		T* pResource = Load(filePath);
		if (pResource != nullptr)
		{
			m_pResources.try_emplace(filePath, pResource);
		}
		return pResource;
	}

	void ReleaseResources() override
	{
		for (std::pair<std::string_view, T*> pResource : m_pResources)
		{
			Release(pResource.second);
		}
		m_pResources.clear();
	}
	
protected:
	virtual T* Load(const std::string& filePath) = 0;
	virtual void Release(T* pResource) = 0;
	static std::unordered_map<std::string_view, T*> m_pResources;
};

template <class T>
std::unordered_map<std::string_view, T*> ResourceLoader<T>::m_pResources = std::unordered_map<std::string_view, T*>();