#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qvboxlayout.>
#include <qlabel.h>

class SelectionScreen : public QWidget
{
	Q_OBJECT
public:
	SelectionScreen(QWidget* parent = nullptr);

signals:
	void normalGameRequested();
	void changePawnsRequested();
	void changeBishopsRequested();
private slots:
	void normalGameClicked();
	void changePawnsClicked();
	void changeBishopsClicked();
};