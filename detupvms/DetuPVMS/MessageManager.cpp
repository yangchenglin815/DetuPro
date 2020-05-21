#include "MessageManager.h"
#include "feedback.h"
#include "DetuPVMS.h"

MessageManager::MessageManager(QObject *parent)
    : QObject(parent)
{

}

MessageManager::~MessageManager()
{

}

void MessageManager::SetMainWindow(DetuPVMS* main_window)
{
    main_window_ = main_window;
}

void MessageManager::ShowMessage(const QString& info, int width, int height, bool show_mask)
{
	Feedback tip(main_window_);
	tip.setContent("border-image:url(:/image/image/caesura.png", info);
	tip.exec();


}

void MessageManager::ShowMessageWithCheckbox(const QString& info, const QString& key, int width , int height , bool show_mask )
{

}

int MessageManager::ShowDialogMessage(const QString& info, const QString& right_btn_str, const QString& left_btn_str, int width, int height)
{

	return 0;
}

int MessageManager::ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str , const QString& left_btn_str, bool show_right_btn, bool show_left_btn, int width, int height)
{

	return 0;
}

int MessageManager::ShowCustomBtnDialogMessage(const QString& info, const QString& right_btn_str , const QString& mid_btn_str, const QString& left_btn_str /*= QString()*/, bool show_right_btn /*= true*/, bool show_mid_btn /*= true*/, bool show_left_btn /*= true*/, int width /*= 400*/, int height /*= 200*/)
{

	return 0;
}

DetuPVMS* MessageManager::GetMainWindow()
{
    return main_window_;
}

void MessageManager::OnShowMessage(const QString& info)
{

}
