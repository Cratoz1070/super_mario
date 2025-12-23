#include <thread>
#include <chrono>

#include "qt_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"
#include "user_input.hpp"

#include <QApplication>
#include <QTimer>
#include "qt_game_window.hpp"

int main(int argc, char *argv[]) {
    // 1. Инициализация Qt приложения
    QApplication app(argc, argv);

    // 2. Установка параметров игры
    using namespace std::chrono_literals;
    biv::os::init_settings();

    biv::Game game;
    biv::UIFactory* ui_factory = new biv::QtUIFactory(&game);
    biv::GameMap* game_map = ui_factory->get_game_map();
    biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
    biv::Mario* mario = ui_factory->get_mario();

    // 3. Создание QtGameMap и окна
    biv::QtGameMap* qt_game_map = dynamic_cast<biv::QtGameMap*>(game_map);

    QtGameWindow window(qt_game_map);
    window.show();

    // Получаем указатель на QtUIFactory для вызова updateAllGraphics
    biv::QtUIFactory* qt_ui_factory = dynamic_cast<biv::QtUIFactory*>(ui_factory);

    // 4. Основной игровой цикл
    QTimer gameTimer;
    bool gameRunning = true;
    int frameCount = 0;

    gameTimer.setInterval(16); //

    QObject::connect(&gameTimer, &QTimer::timeout, [&]() {
        frameCount++;

        // 5. Проверка того, не окончена ли игра
        if (!gameRunning || game.is_finished()) {
            gameTimer.stop();
            app.quit();
            return;
        }

        // 6. Получение пользовательского ввода
        biv::os::UserInput user_input = biv::os::get_user_input();

        // Обработка ввода
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
            gameRunning = false;
            break;
        }

        // 7. Обновление внутреннего состояния игры
        game.move_objs_horizontally();
        game.check_horizontally_static_collisions();

        game.move_objs_vertically();
        game.check_mario_collision();
        game.check_vertically_static_collisions();

        if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
            game_level->restart();
            mario = ui_factory->get_mario();
            std::this_thread::sleep_for(1000ms);
        }

        if (game.is_level_end()) {
            if (!game_level->is_final()) {
                game_level = game_level->get_next();
                mario = ui_factory->get_mario();
                std::this_thread::sleep_for(1000ms);
                game.start_level();
            } else {
                game.finish();
                gameRunning = false;
            }
        }

        // 8. Обновление изображения на экране
        qt_ui_factory->updateAllGraphics();

        window.getView()->centerOn(mario->get_left() + (mario->get_right() - mario->get_left()) / 2,
                                   mario->get_top() + (mario->get_bottom() - mario->get_top()) / 2);

        qt_game_map->update();

        window.getView()->viewport()->update();
    });

    // Запускаем игровой цикл
    gameTimer.start();

    // 9. Завершение
    int result = app.exec();

    delete game_level;
    delete ui_factory;

    return result;
}
