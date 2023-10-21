#include "TestQT.h"
#include "EchiquierLogique.h"
#include "Exceptions.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        EchiquierLogique obj;
        obj.checkBoard();
    }
    catch (const PieceException& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
	}
    
    vue::TestQT w;
    w.show();
    return a.exec();
}
