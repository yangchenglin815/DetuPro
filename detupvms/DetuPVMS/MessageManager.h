/************************************************
 * \file MessageManager.h
 *
 * \author LiChangLing
 * \date 2017
 * ȫ�ֵ�������Ϣ������
 ************************************************/
#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "UiSingleton.h"

#define  MessageManagerIns MessageManager::Instance()

class DetuPVMS;

//��Ϣ������
class MessageManager : public QObject, public CUiSingleton<MessageManager>
{
    Q_OBJECT
    friend class CUiSingleton<MessageManager>;
public:
   
    ~MessageManager();

    //���½ӿ�ֻ�����̵߳��ã�����
    
	void SetMainWindow(DetuPVMS* main_window);

    //ȫ�ֵ�����ʾ��
    void ShowMessage(const QString& info, int width = 400, int height = 200, bool show_mask = true);

    void ShowMessageWithCheckbox(const QString& info, const QString& key, int width = 400, int height = 200, bool show_mask = true);

    //ȫ�ֵ�����ʾ�򣬷���reject����accept
    int ShowDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& left_btn_str = QString(), int width = 400, int height = 200);

    //ȫ�ֵ�����ʾ�򣬷���reject����accept, ���Զ��尴ť�Ƿ���ʾ
    int ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& left_btn_str = QString(), bool show_right_btn = true, bool show_left_btn = true, int width = 400, int height = 200);

    //ȫ�ֵ�����ʾ�򣬷���reject����accept, ���Զ��尴ť�Ƿ���ʾ�������м䰴ť
    int ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& mid_btn_str = QString(), const QString& left_btn_str = QString(), bool show_right_btn = true, bool show_mid_btn = true, bool show_left_btn = true, int width = 400, int height = 200);

	DetuPVMS* GetMainWindow();

public slots:
    //�����첽����,ͨ���źŲ�
    void OnShowMessage(const QString& info);

signals:
    void SignalForSetMask(QWidget*);

private:
    MessageManager(QObject *parent = NULL);

	DetuPVMS* main_window_;
};

#endif // MESSAGEMANAGER_H
