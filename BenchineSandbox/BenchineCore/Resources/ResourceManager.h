#pragma once
#include <map>
#include <typeindex>

#include "Helpers/Singleton.hpp"
#include "Resources/ResourceLoader.h"
#include "Helpers/Concepts.hpp"

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	explicit ResourceManager(Token) {}
	virtual ~ResourceManager();
	void Initialize(const std::string& dataPath);

	[[nodiscard]] constexpr auto GetDataPath() const noexcept -> const std::string& { return m_DataPath; }

	template <typename ResourceType, IsResourceLoader LoaderType>
	static void AddLoader()
	{
		m_Loaders[std::type_index(typeid(ResourceType))] = std::make_unique<LoaderType>();
	}
	
	template <class ResourceType>
	static ResourceType* Load(const std::string& resourcePath)
	{
		// todo this is a bit messy,is there a C++17/20 way to improve this?
		return static_cast<ResourceLoader<ResourceType>*>(
			m_Loaders.at(std::type_index(typeid(ResourceType))).get())->GetResource(resourcePath);
	}

private:
	std::string m_DataPath;
	static std::map<std::type_index, std::unique_ptr<BaseLoader>> m_Loaders;
};
