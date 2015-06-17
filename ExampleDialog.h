#ifndef ZERORESERVEDIALOG_H
#define ZERORESERVEDIALOG_H


#include "ui_ExampleDialog.h"
#include "p3ExampleRS.h"

#include "retroshare-gui/mainpage.h"
#include <QTimer>


class ExampleDialog : public MainPage
{
    Q_OBJECT

public:
    ExampleDialog( QWidget *parent = 0 );
	p3ExampleRS *p3service;


private:

    Ui::ExampleDialog ui;
	QTimer *timer;
private slots:
	void on_timer();

    void on_pushButton_clicked();
};

#endif // ZERORESERVEDIALOG_H
