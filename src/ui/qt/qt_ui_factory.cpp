#include "qt_ui_factory.hpp"
#include <algorithm>

using namespace biv;

QtUIFactory::QtUIFactory(Game* game) : UIFactory(game) {
    create_game_map();
}

QtUIFactory::~QtUIFactory() {
    clear_data();
    delete game_map;
}

void QtUIFactory::clear_data() {

    if (game_map) {
        game_map->remove_objs(); 
    }

    if (game) {
        game->remove_objs();
    }

    all_qt_objects.clear();
    boxes.clear();
    full_boxes.clear();
    ships.clear();
    enemies.clear();
    flying_enemies.clear();
    jumping_enemies.clear();
    moneys.clear();

    mario = nullptr;
}

void QtUIFactory::add_qt_object(QtUIObject* obj) {
    all_qt_objects.push_back(obj);
    if (game_map) {
        game_map->addItem(obj);
    }
}

void QtUIFactory::create_box(
    const Coord& top_left, const int width, const int height
    ) {
    QtBox* box = new QtBox(top_left, width, height);
    boxes.push_back(box);
    add_qt_object(box);

    game->add_map_movable(box);
    game->add_static_obj(box);
}

void QtUIFactory::create_enemy(
    const Coord& top_left, const int width, const int height
    ) {
    QtEnemy* enemy = new QtEnemy(top_left, width, height);
    enemies.push_back(enemy);
    add_qt_object(enemy);

    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
}

void QtUIFactory::create_flying_enemy(
    const Coord& top_left, const int width, const int height
    ) {
    QtFlyingEnemy* enemy = new QtFlyingEnemy(top_left, width, height);
    flying_enemies.push_back(enemy);
    add_qt_object(enemy);

    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
}

void QtUIFactory::create_jumping_enemy(
    const Coord& top_left, const int width, const int height
    ) {
    QtJumpingEnemy* enemy = new QtJumpingEnemy(top_left, width, height);
    jumping_enemies.push_back(enemy);
    add_qt_object(enemy);

    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
}

void QtUIFactory::create_full_box(
    const Coord& top_left, const int width, const int height
    ) {
    QtFullBox* full_box = new QtFullBox(top_left, width, height, this);
    full_boxes.push_back(full_box);
    add_qt_object(full_box);

    game->add_collisionable(full_box);
    game->add_map_movable(full_box);
    game->add_static_obj(full_box);
}

void QtUIFactory::create_mario(
    const Coord& top_left, const int width, const int height
    ) {
    if (mario) {
        game->remove_collisionable(mario);
        game->remove_movable(mario);
        game->remove_mario();
        auto it = std::find(all_qt_objects.begin(), all_qt_objects.end(), mario);
        if (it != all_qt_objects.end()) {
            all_qt_objects.erase(it);
        }
        if (game_map) {
            game_map->removeItem(mario);
        }
        delete mario;
    }

    mario = new QtMario(top_left, width, height);
    add_qt_object(mario);

    game->add_collisionable(mario);
    game->add_movable(mario);
    game->add_mario(mario);
}

void QtUIFactory::create_money(
    const Coord& top_left, const int width, const int height
    ) {
    QtMoney* money = new QtMoney(top_left, width, height);
    moneys.push_back(money);
    add_qt_object(money);

    game->add_map_movable(money);
    game->add_movable(money);
    game->add_collisionable(money);
}

void QtUIFactory::create_ship(
    const Coord& top_left, const int width, const int height
    ) {
    QtShip* ship = new QtShip(top_left, width, height);
    ships.push_back(ship);
    add_qt_object(ship);

    game->add_map_movable(ship);
    game->add_static_obj(ship);
}

biv::GameMap* QtUIFactory::get_game_map() {
    return game_map;
}

biv::Mario* QtUIFactory::get_mario() {
    return mario;
}

void QtUIFactory::updateAllGraphics() {
    for (auto obj : all_qt_objects) {
        obj->updatePosition();
        obj->updateGraphics();
    }
}

void QtUIFactory::create_game_map() {
    game_map = new QtGameMap(29, 120);
}

