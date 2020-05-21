#ifndef SUPTABWIDGET_H
#define SUPTABWIDGET_H

#include <QWidget>



namespace Ui {
	class supTabWidget;
}

class supTabWidget : public QWidget
{
	Q_OBJECT

public:

	enum supTabWgtButton
	{
		TabPlay = 0,
		TabRePlay,
		TabDevice,
		TabStorage,
		TabVRMap,
		TabVRView,
		TabIOTPlat,
	};

	supTabWidget(QWidget *parent = 0);
	~supTabWidget();

public: 
	void setTittle(QString tittle, supTabWgtButton type);
	void setSelectedStatus(bool selected);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	private slots:
	void slot_closeTab();
signals:
	//tab上其他通用按钮点击事件
	void TrigSupTabButtonClicked(supTabWidget::supTabWgtButton type);
	void sigOnTabClose(supTabWidget::supTabWgtButton type);

private:
	Ui::supTabWidget *ui;
	supTabWgtButton type_;
};

#endif // SUPTABWIDGET_H
