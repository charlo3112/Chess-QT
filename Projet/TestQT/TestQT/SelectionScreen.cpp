#include "SelectionScreen.h"

SelectionScreen::SelectionScreen(QWidget* parent) : QWidget(parent) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(20);

	QLabel* title = new QLabel("Configuration", this);
	QFont titleFont = title->font();
	titleFont.setPointSize(50);
	title->setFont(titleFont);
	title->move(120, 100);
	layout->addWidget(title);

	QPushButton *normalGameButton = new QPushButton("Normal Game", this);
	normalGameButton->setMinimumWidth(150);
	layout->addWidget(normalGameButton);
	normalGameButton->move(240, 200);
	QPushButton *changePawns = new QPushButton("Change Pawns", this);
	changePawns->setMinimumWidth(150);
	layout->addWidget(changePawns);
	changePawns->move(240, 260);
	QPushButton *changeBishops = new QPushButton("Change Bishops", this);
	changeBishops->setMinimumWidth(150);
	layout->addWidget(changeBishops);
	changeBishops->move(240, 320);


	connect(normalGameButton, &QPushButton::clicked, this, &SelectionScreen::normalGameClicked);
	connect(changePawns, &QPushButton::clicked, this, &SelectionScreen::changePawnsClicked);
	connect(changeBishops, &QPushButton::clicked, this, &SelectionScreen::changeBishopsClicked);
	setStyleSheet("QPushButton { font-size: 18px; color: #14148c; } QLabel { color: #444; }");

}

void SelectionScreen::normalGameClicked() {
	emit normalGameRequested();
}

void SelectionScreen::changePawnsClicked() {
	emit changePawnsRequested();
}

void SelectionScreen::changeBishopsClicked() {
	emit changeBishopsRequested();
}