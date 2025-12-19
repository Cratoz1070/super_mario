// main_window.cpp
#include "main_window.hpp"
#include <QMessageBox>
#include <thread>
#include <chrono>
#include "user_input.hpp"

using namespace std::chrono_literals;
using biv::MainWindow;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui_factory(new QtUIFactory(&game)),
    current_level(new FirstLevel(ui_factory)) {

    // УРОВЕНЬ УЖЕ СОЗДАЛ ОБЪЕКТЫ В СВОЕМ КОНСТРУКТОРЕ
    // current_level->create();  // <-- УДАЛИ ЭТУ СТРОКУ

    setWindowTitle("Super Mario Qt");
    resize(1200, 600);

    QtGameMap* qt_map = ui_factory->get_qt_game_map();

    game_view = new QGraphicsView(qt_map);
    game_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_view->setRenderHint(QPainter::Antialiasing);

    // Увеличиваем масштаб, чтобы было видно маленькие объекты
    game_view->scale(8, 8);
    setCentralWidget(game_view);

    // Проверяем, что Марио создан
    Mario* mario = ui_factory->get_mario();
    if (!mario) {
        qDebug() << "WARNING: Mario not created!";
    }

    game_timer = new QTimer(this);
    connect(game_timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    game_timer->start(16);
}

MainWindow::~MainWindow() {
    delete current_level;
    delete ui_factory;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Left:  // Стрелка ВЛЕВО = карта ВПРАВО (как 'A')
        move_map_right_pressed = true;
        qDebug() << "Left arrow pressed -> Move map RIGHT";
        break;
    case Qt::Key_Right:  // Стрелка ВПРАВО = карта ВЛЕВО (как 'D')
        move_map_left_pressed = true;
        qDebug() << "Right arrow pressed -> Move map LEFT";
        break;
    case Qt::Key_Space:
        jump_pressed = true;
        qDebug() << "Space pressed -> Jump";
        break;
    case Qt::Key_Escape:
        game.finish();
        close();
        break;
    // Также можно оставить поддержку оригинальных клавиш
    case Qt::Key_A:
        move_map_right_pressed = true;
        qDebug() << "A pressed -> Move map RIGHT";
        break;
    case Qt::Key_D:
        move_map_left_pressed = true;
        qDebug() << "D pressed -> Move map LEFT";
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Left:
        move_map_right_pressed = false;
        break;
    case Qt::Key_Right:
        move_map_left_pressed = false;
        break;
    case Qt::Key_Space:
        jump_pressed = false;
        break;
    case Qt::Key_A:
        move_map_right_pressed = false;
        break;
    case Qt::Key_D:
        move_map_left_pressed = false;
        break;
    }
}

biv::os::UserInput MainWindow::processInput() {
    if (keys[Qt::Key_Escape]) {
        return biv::os::UserInput::EXIT;
    }
    if (keys[Qt::Key_Left]) {
        return biv::os::UserInput::MAP_LEFT;
    }
    if (keys[Qt::Key_Right]) {
        return biv::os::UserInput::MAP_RIGHT;
    }
    if (keys[Qt::Key_Space]) {
        return biv::os::UserInput::MARIO_JUMP;
    }

    return biv::os::UserInput::NO_INPUT;
}

void MainWindow::handleUserInput(biv::os::UserInput user_input) {
    Mario* mario = ui_factory->get_mario();
    if (!mario) return;

    switch (user_input) {
    case biv::os::UserInput::MAP_LEFT:
        mario->move_map_left();
        if (!game.check_static_collisions(mario)) {
            game.move_map_left();
        }
        mario->move_map_right();
        break;
    case biv::os::UserInput::MAP_RIGHT:
        mario->move_map_right();
        if (!game.check_static_collisions(mario)) {
            game.move_map_right();
        }
        mario->move_map_left();
        break;
    case biv::os::UserInput::MARIO_JUMP:
        mario->jump();
        break;
    case biv::os::UserInput::EXIT:
        game.finish();
        close();
        break;
    }
}

void MainWindow::updateGameState() {
    // Точная копия из main.cpp
    game.move_objs_horizontally();
    game.check_horizontally_static_collisions();

    game.move_objs_vertically();
    game.check_mario_collision();
    game.check_vertically_static_collisions();

    Mario* mario = ui_factory->get_mario();
    GameMap* game_map = ui_factory->get_game_map();

    if (!mario || !game_map) return;

    if (
        game_map->is_below_map(mario->get_top())
        || !mario->is_active()
        ) {
        current_level->restart();
        mario = ui_factory->get_mario();
        std::this_thread::sleep_for(1000ms);
    }

    if (game.is_level_end()) {
        if (!current_level->is_final()) {
            current_level = current_level->get_next();
            mario = ui_factory->get_mario();
            std::this_thread::sleep_for(1000ms);
            game.start_level();
        } else {
            game.finish();
        }
    }
}

void MainWindow::gameLoop() {
    if (game.is_finished()) {
        game_timer->stop();
        return;
    }

    // Получаем Марио и карту
    Mario* mario = ui_factory->get_mario();
    GameMap* game_map = ui_factory->get_game_map();

    if (!mario || !game_map) return;

    // Отладочный вывод (можно уменьшить частоту)
    static int frame = 0;
    frame++;
    if (frame % 30 == 0) {  // Каждые 30 кадров
        qDebug() << "Frame" << frame
                 << "| Mario: (" << mario->get_left() << "," << mario->get_top() << ")"
                 << "| Active:" << mario->is_active();
    }

    // Обработка непрерывного ввода (движение)
    if (move_map_left_pressed) {
        // Движение карты ВЛЕВО (стрелка ВПРАВО или 'D')
        mario->move_map_left();
        if (!game.check_static_collisions(mario)) {
            game.move_map_left();
        }
        mario->move_map_right();
    }

    if (move_map_right_pressed) {
        // Движение карты ВПРАВО (стрелка ВЛЕВО или 'A')
        mario->move_map_right();
        if (!game.check_static_collisions(mario)) {
            game.move_map_right();
        }
        mario->move_map_left();
    }

    // Обработка прыжка (одноразовое действие)
    if (jump_pressed) {
        mario->jump();
        jump_pressed = false;
    }

    // Обновление состояния игры (физика)
    game.move_objs_horizontally();
    game.check_horizontally_static_collisions();

    game.move_objs_vertically();
    game.check_mario_collision();
    game.check_vertically_static_collisions();

    // ======== ПРОВЕРКА СМЕРТИ МАРИО ========
    // ТОЧНО ТАК ЖЕ КАК В ОРИГИНАЛЬНОМ main.cpp
    if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
        qDebug() << "=== MARIO DIED ===";
        qDebug() << "Reason:";
        if (game_map->is_below_map(mario->get_top())) {
            qDebug() << "- Below map: y =" << mario->get_top()
            << ", map height =" << 29;
        }
        if (!mario->is_active()) {
            qDebug() << "- Not active";
        }

        restart_level();

        // После перезапуска получаем нового Марио
        mario = ui_factory->get_mario();
        if (mario) {
            qDebug() << "New mario at: (" << mario->get_left() << "," << mario->get_top() << ")";
        }

        return; // Прерываем текущий кадр
    }

    // ======== ПРОВЕРКА КОНЦА УРОВНЯ ========
    if (game.is_level_end()) {
        qDebug() << "=== LEVEL COMPLETED ===";

        if (!current_level->is_final()) {
            advance_to_next_level();
        } else {
            game.finish();
            QMessageBox::information(this, "Победа!", "Игра пройдена!");
        }
        return;
    }

    // Обновление графики
    ui_factory->updateAllGraphics();
    game_view->viewport()->update();
}

void MainWindow::restart_level() {
    qDebug() << "=== RESTARTING LEVEL ===";

    // Останавливаем таймер
    game_timer->stop();

    try {
        // 1. Очищаем фабрику (это удалит все объекты из сцены)
        if (ui_factory) {
            ui_factory->clear_data();
            qDebug() << "Factory cleared";
        }

        // 2. Перезапускаем уровень через restart() который вызовет init_data()
        if (current_level) {
            current_level->restart();
            qDebug() << "Level restarted";
        }

        // 3. Перезапускаем состояние игры
        game.start_level();
        qDebug() << "Game level started";

        // 4. Проверяем, что Марио создан
        Mario* mario = ui_factory->get_mario();
        if (mario) {
            qDebug() << "New Mario created at: (" << mario->get_left() << "," << mario->get_top() << ")";
        } else {
            qDebug() << "ERROR: Mario not created after restart!";
            // Создаем Марио вручную как запасной вариант
            ui_factory->create_mario(Coord{.x = 10, .y =10}, 10, 10);
        }

    } catch (const std::exception& e) {
        qDebug() << "EXCEPTION in restart_level: " << e.what();
        QMessageBox::critical(this, "Error", QString("Failed to restart level: ") + e.what());
        // Не закрываем окно, а пытаемся продолжить
        game_timer->start(16);
        return;
    } catch (...) {
        qDebug() << "UNKNOWN EXCEPTION in restart_level";
        QMessageBox::critical(this, "Error", "Unknown error restarting level");
        game_timer->start(16);
        return;
    }

    // 5. Пауза 1 секунда и перезапуск таймера
    QTimer::singleShot(1000, this, [this]() {
        qDebug() << "Resuming game timer...";
        game_timer->start(16);
    });
}

void MainWindow::advance_to_next_level() {
    qDebug() << "=== ADVANCING TO NEXT LEVEL ===";

    game_timer->stop();

    if (current_level) {
        GameLevel* next_level = current_level->get_next();
        if (next_level) {
            delete current_level;
            current_level = next_level;

            // Перезапускаем уровень в игре
            game.start_level();

            // Пауза перед новым уровнем
            QTimer::singleShot(1000, this, [this]() {
                game_timer->start(16);
                qDebug() << "Next level started!";
            });
        }
    }
}
