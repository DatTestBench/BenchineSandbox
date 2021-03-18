#pragma once
#include <nameof/nameof.hpp>

template<class T>
inline void SafeDelete(T& pObject)
{
	if (pObject != nullptr)
	{
		delete pObject;
		pObject = nullptr;
	}
	else
		LOG(Warning, "Trying to delete object {0} which is already nullptr", NAMEOF_TYPE_EXPR(pObject));
}

template<class T>
inline void SafeDelete(T* pObject)
{
	if (pObject != nullptr)
	{
		delete pObject;
		pObject = nullptr;
	}
	else
		LOG(Warning, "Trying to delete object {0} which is already nullptr", NAMEOF_TYPE_EXPR(pObject));
}