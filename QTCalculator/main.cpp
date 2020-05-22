#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /**
     * Обратите внимание что больше в этом файле ничего нет
     * То есть по сути Вы должны показать главное окно между объявлением
     * приложения QApplication и вызовом функции a.exec()
     * 
     * Весь остальной код в классе Window
     */
    Window mainApp;
    mainApp.show();
    return a.exec();
}
