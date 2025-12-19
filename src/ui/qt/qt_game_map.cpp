// qt_game_map.cpp
#include "qt_game_map.hpp"
#include <QGraphicsRectItem>

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width, QObject* parent)
    : QGraphicsScene(0, 0, width, height, parent),
    GameMap(height, width) {
    initBackground();
}

QtGameMap::~QtGameMap() {
    remove_objs();
}

void QtGameMap::initBackground() {
    // Создаем фон: небо и вода
    QBrush skyBrush(QColor(135, 206, 235));  // Светло-голубой
    QBrush waterBrush(QColor(65, 105, 225));  // Королевский синий

    // Небо (верхние 26 строк)
    sky_bg = new QGraphicsRectItem(0, 0, GameMap::width, GameMap::height - 3);
    sky_bg->setBrush(skyBrush);
    sky_bg->setPen(Qt::NoPen);
    addItem(sky_bg);

    // Вода (нижние 3 строки)
    water_bg = new QGraphicsRectItem(0, GameMap::height - 3, GameMap::width, 3);
    water_bg->setBrush(waterBrush);
    water_bg->setPen(Qt::NoPen);
    addItem(water_bg);
}

void QtGameMap::clear() noexcept {
    // Не очищаем полностью сцену, а только удаляем игровые объекты
    // Фон сохраняем
    QList<QGraphicsItem*> items_list = items();
    for (QGraphicsItem* item : items_list) {
        // Удаляем только игровые объекты, не фон
        if (item != sky_bg && item != water_bg) {
            removeItem(item);
            delete item;
        }
    }
}

void QtGameMap::refresh() noexcept {
    // В Qt обновление происходит автоматически через update()
    update();
}

void QtGameMap::remove_objs() {
    clear();
}

void QtGameMap::show() const noexcept {
    // В Qt показ осуществляется через QGraphicsView, поэтому здесь ничего не делаем
}

void QtGameMap::addGraphicsItem(QGraphicsItem* item) {
    addItem(item);
}

void QtGameMap::removeGraphicsItem(QGraphicsItem* item) {
    removeItem(item);
}
