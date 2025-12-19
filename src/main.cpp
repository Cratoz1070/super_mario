#include <QApplication>
#include "main_window.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // Инициализация настроек (если нужно для Qt)
    // biv::os::init_settings(); // Если эта функция нужна для Qt

    biv::MainWindow main_window;
    main_window.show();

    return app.exec();
}
