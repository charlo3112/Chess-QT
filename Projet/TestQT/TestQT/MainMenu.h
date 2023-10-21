#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qvboxlayout.>
#include <qlabel.h>

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget* parent = nullptr);
	
signals:
	void newGameRequested();
	void quitRequested();

private slots:
	void newGameClicked();
	void quitClicked();
};
