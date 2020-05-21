/************************************************
 * \file MessageManager.h
 *
 * \author LiChangLing
 * \date 2017
 * 全局弹出框消息管理类
 ************************************************/
#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "UiSingleton.h"

#define  MessageManagerIns MessageManager::Instance()

class DetuPVMS;

//消息管理类
class MessageManager : public QObject, public CUiSingleton<MessageManager>
{
    Q_OBJECT
    friend class CUiSingleton<MessageManager>;
public:
   
    ~MessageManager();

    //以下接口只能主线程调用！！！
    
	void SetMainWindow(DetuPVMS* main_window);

    //全局调用提示框
    void ShowMessage(const QString& info, int width = 400, int height = 200, bool show_mask = true);

    void ShowMessageWithCheckbox(const QString& info, const QString& key, int width = 400, int height = 200, bool show_mask = true);

    //全局调用提示框，返回reject或者accept
    int ShowDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& left_btn_str = QString(), int width = 400, int height = 200);

    //全局调用提示框，返回reject或者accept, 可以定义按钮是否显示
    int ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& left_btn_str = QString(), bool show_right_btn = true, bool show_left_btn = true, int width = 400, int height = 200);

    //全局调用提示框，返回reject或者accept, 可以定义按钮是否显示，包括中间按钮
    int ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str = QString(), const QString& mid_btn_str = QString(), const QString& left_btn_str = QString(), bool show_right_btn = true, bool show_mid_btn = true, bool show_left_btn = true, int width = 400, int height = 200);

	DetuPVMS* GetMainWindow();

public slots:
    //可以异步调用,通过信号槽
    void OnShowMessage(const QString& info);

signals:
    void SignalForSetMask(QWidget*);

private:
    MessageManager(QObject *parent = NULL);

	DetuPVMS* main_window_;
};

#endif // MESSAGEMANAGER_H
