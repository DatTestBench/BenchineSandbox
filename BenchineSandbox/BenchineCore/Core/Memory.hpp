#pragma once
#include "nameof/nameof.hpp"

template <class T>
bool SafeDeleteInternal(T& pObject)
{
	if (pObject != nullptr)
	{
		delete pObject;
		pObject = nullptr;
		return true;
	}
	return false;
}

template <class T>
bool SafeDeleteInternal(T* pObject)
{
	if (pObject != nullptr)
	{
		delete pObject;
		pObject = nullptr;
		return true;
	}
	return false;
}

#define MEM_SAFE_DELETE_LOG_REASON

#define NUM_ARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value

#define SafeDelete(pObject) \
	LOG_CONDITIONAL(!SafeDeleteInternal(pObject), Warning, "Trying to delete {0} with {1} which is already nullptr.", NAMEOF(pObject), NAMEOF_TYPE_EXPR(pObject))

#ifdef MEM_SAFE_DELETE_LOG_REASON
// The braces need to be there as LOG can expand to multiple statements (UNUSED(LogLevel::level); UNUSED(__VA_ARGS__))
#	define SafeDeleteNoWarn(pObject, ...) \
		if constexpr (NUM_ARGS(__VA_ARGS__) == 0) \
		{ \
			LOG(Warning, "Using SafeDeleteNoWarn without providing a reason for discarding warning. Please consider adding a reason."); \
		} \
		else \
		{ \
			LOG(Info, "SafeDeleteNoWarn: {0}", __VA_ARGS__); \
		} \
		SafeDeleteInternal(pObject)
#else
#	define SafeDeleteNoWarn(pObject, ...) \
	if constexpr (NUM_ARGS(__VA_ARGS__) == 0) \
	{ \
		LOG(Warning, "Using SafeDeleteNoWarn without providing a reason for discarding warning \n. Please consider adding a reason."); \
	} \
	SafeDeleteInternal(pObject)
#endif
