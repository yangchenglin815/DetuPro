#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		if (m_pInstance == NULL) {
			Lock lock;
			if (m_pInstance == NULL) {
				m_pInstance = new T();
				atexit(Destroy);
			}
			return *m_pInstance;
		}
		return *m_pInstance;
	}

protected:
	Singleton(void) {}
	~Singleton(void) {}

private:
	Singleton(const Singleton& rhs) {}
	Singleton& operator = (const Singleton& rhs) {}

	void Destroy()
	{
		if (m_pInstance != NULL)
			delete m_pInstance;
		m_pInstance = NULL;
	}

	static T* volatile m_pInstance;
};

template <typename T>
T* Singleton<T>::m_pInstance = NULL;

#endif
