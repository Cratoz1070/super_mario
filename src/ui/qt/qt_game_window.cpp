#include "qt_game_window.hpp"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>
#include "qt_game_map.hpp"
#include "qt_user_input.hpp"

QtGameWindow::QtGameWindow(biv::QtGameMap* scene, QWidget* parent)
    : QMainWindow(parent) {

    setWindowTitle("Super Mario Qt");
    resize(1200, 600);

    game_view = new QGraphicsView(scene);
    game_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_view->setRenderHint(QPainter::Antialiasing);

    int scale = 15;
    game_view->scale(scale, scale);

    game_view->centerOn(scene->get_map_width() / 2, scene->get_map_height() / 2);

    game_view->setFocus();
    game_view->setFocusPolicy(Qt::StrongFocus);

    setCentralWidget(game_view);

    game_view->installEventFilter(this);
}

QGraphicsView* QtGameWindow::getView() const {
    return game_view;
}

bool QtGameWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == game_view) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            keyPressEvent(keyEvent);
            return true;
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            keyReleaseEvent(keyEvent);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void QtGameWindow::keyPressEvent(QKeyEvent* event) {
    biv::os::set_key_state(event->key(), true);
    QMainWindow::keyPressEvent(event);
}

void QtGameWindow::keyReleaseEvent(QKeyEvent* event) {
    biv::os::set_key_state(event->key(), false);
    QMainWindow::keyReleaseEvent(event);
}

void QtGameWindow::closeEvent(QCloseEvent* event) {
    biv::os::reset_keys();
    QMainWindow::closeEvent(event);
}
