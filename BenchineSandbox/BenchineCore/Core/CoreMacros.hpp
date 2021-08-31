#pragma once


#if _DEBUG
#define B_DEBUG
#endif 

#define ENUM_TO_C_STR(value) std::string(magic_enum::enum_name(value)).c_str()
#define TO_C_STR(value) std::to_string(value).c_str()
#define C_STR_FROM_VIEW(value) std::string(value).c_str()
#define C_STR_FROM_RAW(value) std::string(value).c_str()

#define DEL_ROF(className) \
className(const className&) = delete; \
className(className&&) noexcept = delete; \
className& operator= (const className&) = delete; \
className& operator= (className&&) noexcept = delete;

template <typename ...Args>
void UNUSED(Args&& ...)
{
}