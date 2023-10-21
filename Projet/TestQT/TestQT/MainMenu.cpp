#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setAlignment(Qt::AlignCenter);
	layout->setSpacing(20);

	QLabel *title = new QLabel("Chess :)", this);
	QFont titleFont = title->font();
	titleFont.setPointSize(50);
	title->setFont(titleFont);
	title->move(205, 100);
	layout->addWidget(title);


	QPushButton* newGameButton = new QPushButton("New Game", this);
	newGameButton->setMinimumWidth(150);
	layout->addWidget(newGameButton);
	newGameButton->move(240, 200);
	connect(newGameButton, &QPushButton::clicked, this, &MainMenu::newGameClicked);

	QPushButton* quitButton = new QPushButton("Quit", this);
	quitButton->setMinimumWidth(150);
	layout->addWidget(quitButton);
	quitButton->move(240, 260);
	connect(quitButton, &QPushButton::clicked, this, &MainMenu::quitClicked);

	setStyleSheet("QPushButton { font-size: 18px; color: #328930; } QLabel { color: #444; }");
}

void MainMenu::newGameClicked() {
	emit newGameRequested();
}
void MainMenu::quitClicked() {
	emit quitRequested();
}