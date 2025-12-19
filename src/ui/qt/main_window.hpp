// main_window.hpp
#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include "game.hpp"
#include "qt_ui_factory.hpp"
#include "first_level.hpp"
#include "user_input.hpp"
#include "coord.hpp"

namespace biv {
class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Game game;
    QtUIFactory* ui_factory;
    GameLevel* current_level;
    QGraphicsView* game_view;
    QTimer* game_timer;

    bool keys[256] = {false};
    bool move_map_left_pressed = false;   // Движение карты ВЛЕВО ('D' в консоли)
    bool move_map_right_pressed = false;  // Движение карты ВПРАВО ('A' в консоли)
    bool jump_pressed = false;

    void restart_level();
    void advance_to_next_level();

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void updateGameState();
    biv::os::UserInput processInput();
    void handleUserInput(biv::os::UserInput user_input);

private slots:
    void gameLoop();
};
}
