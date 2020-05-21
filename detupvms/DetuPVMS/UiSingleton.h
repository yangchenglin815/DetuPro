#ifndef UISINGLETON_H
#define UISINGLETON_H

#include <QPointer>
#include <QMutex>

/**  ������CUiSingleton
	  *  ˵����������
	 **/
	template <class T>
	class CUiSingleton
	{
	public:
		// ���ʵ�����Ψһ��ʽ
		static T& Instance();

	protected:
		// ����
		CUiSingleton() {}
		// ����
		virtual ~CUiSingleton() {}
	};

	/** @fn	    inline T& CUiSingleton<T>::Instance()
	 *  @brief	��ȡʵ���Ľӿ�
	 *  @param	void
	 *  @return	T& ���������
	 */
	template <class T>
	inline T& CUiSingleton<T>::Instance()
	{
        static std::auto_ptr<T> s_instance;
		static QMutex m_mutex;

		if (s_instance.get() == NULL)
		{
			QMutexLocker locker(&m_mutex); //! ��������ͬʱ����������ʵ��
									   //! CUiSingleton<T>�������»�����������Ҫ���Ĳ�ͬ����֮��Ļ���
			if (s_instance.get() == NULL) // �ڶ����жϵ�Ŀ�����ڲ������߳��ظ�����
			{
				s_instance = std::auto_ptr<T>(new T);
			}
		}

		return *s_instance.get();
	}

    /**  ������CObjectSingleton
    *  ˵�������ڵ�����
    *  ʹ�ô˵������˽�Qt�ĸ����������Ӷ�������Լ��������ʱ��ı�
    *  ����ѭQt�̰߳�ȫ����
    *  QObject�������������߳��д���,��QWidget���������������߳���ʹ�á�
    *  ���Լ̳�ʵ�ֵĽӿ��迼���̰߳�ȫ��QObject��������֤�̰߳�ȫ
    **/
    template <class T>
    class CObjectSingleton
    {
    public:
        // �������ڵ�����ʽ
        // ����������Ϊ�գ����ֶ����ٵ���
        // ���������븸������˵��������丸���������Զ����٣��û����Կ��ǲ���Ҫ�ֶ�ɾ������
        static T* CreateInstance(QObject* pParent);

        // �������ڵ�����ʽ
        // ������2����Ϊ�գ����ֶ����ٵ���
        // ������2���븸������˵��������丸���������Զ����٣��û����Կ��ǲ���Ҫ�ֶ�ɾ������
        // ����1�ɴ���ָ����������
        template <class U>
        static T* CreateInstance(U u, QObject* pParent)
        {
            // ������������ڣ���������
            if (s_instance.isNull())
            {
                s_instance = new T(u, pParent);
            }

            // ���ش����Ĵ��ڵ���
            return s_instance;
        }
        // �������ڵ���Ψһ��ʽ
        // �˽ӿڲ�ָ������������Qt��ͬ������Ҫ��
        static T* CreateInstance();
        // ���ʴ��ڵ���Ψһ��ʽ���豣֤�䵥���Ѿ�����
        // ���������������ڵ���
        static T* Instance();

        // �ֶ����ٵ���
        // ��ָ����������Բ��õ��ô˽ӿ�
        static void DeleteInstance();

    protected:
        // ����
        CObjectSingleton(QObject* pParent){}
        // ����
        virtual ~CObjectSingleton() {}

    private:
        static QPointer <T> s_instance; // ���ڵ���������ָ�뷽ʽ����
    };

    template <class T>
    QPointer <T> CObjectSingleton<T>::s_instance = 0;

    /** @fn    inline T* CObjectSingleton<T>::CreateInstance(QObject* pParent)
    * @brief �������ڵ����������ڲ�����
    * @param <IN> QObject* pParent - ������.
    * @return T - ģ�����.
    */

    template <class T>
    inline T* CObjectSingleton<T>::CreateInstance(QObject* pParent)
    {
        // ������������ڣ���������
        if (s_instance.isNull())
        {
            s_instance = new T(pParent);
        }

        // ���ش����Ĵ��ڵ���
        return s_instance;
    }

    /** @fn    inline T* CObjectSingleton<T>::CreateInstance()
    * @brief �������ڵ����������ڲ����������ֶ�����
    * @param <IN> none.
    * @return T - ģ�����.
    */
    template <class T>
    inline T* CObjectSingleton<T>::CreateInstance()
    {
        // ������������ڣ���������
        if (s_instance.isNull())
        {
            s_instance = new T;
        }

        return s_instance;
    }

    /** @fn    inline T* CObjectSingleton<T>::Instance()
    * @brief ���ʴ��ڵ���Ψһ��ʽ �豣֤�Ѿ�����
    * @param <IN> none.
    * @return T - ģ�����.
    */
    template <class T>
    inline T* CObjectSingleton<T>::Instance()
    {
        return s_instance;
    }

    /** @fn    inline void CObjectSingleton<T>::DeleteInstance()
    * @brief ���ʴ��ڵ���Ψһ��ʽ �豣֤�Ѿ�����
    * @param <IN> none.
    * @return T - ģ�����.
    */
    template <class T>
    inline void CObjectSingleton<T>::DeleteInstance()
    {
        // ������������ڣ���������
        if (!s_instance.isNull())
        {
            delete s_instance;
            s_instance = NULL;
        }
    }

#endif // UISINGLETON_H
