#pragma once
// Templated singleton, using a token to circumvent having to make instances friend of the base singleton (having the child constructor public), while still making sure the child can only be initialized once using a token struct
// Based on this rather interesting stackexchange answer: https://codereview.stackexchange.com/a/173942
template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T(token());
		return m_pInstance;
	}
	static void Destroy()
	{
		delete GetInstance();
	}
	DEL_ROF(Singleton)

protected:
	static T* m_pInstance;
	struct token {};
	Singleton() = default;
};

template <typename T>
T* Singleton<T>::m_pInstance = nullptr;