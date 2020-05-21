#ifndef SETADMINWGT_H
#define SETADMINWGT_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

namespace Ui {
class setAdminWgt;
}

class setAdminWgt : public QWidget
{
    Q_OBJECT

public:
    explicit setAdminWgt(QWidget *parent = 0);
    ~setAdminWgt();
signals:
	void sigonClose();
	void sigonConfirm();
protected:
	void keyPressEvent(QKeyEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
	void showEvent(QShowEvent *event);
private slots:
void slot_saveAdmin();
void slotOnRegisterUser(std::string user, std::string passwd, std::string cUuid, short result);
private:
	void initConnect();
	void init();
private:
    Ui::setAdminWgt *ui;
};

#endif // SETADMINWGT_H
