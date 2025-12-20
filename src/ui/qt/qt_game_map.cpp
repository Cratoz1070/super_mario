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
    QBrush skyBrush(QColor(135, 206, 235));  
    QBrush waterBrush(QColor(65, 105, 225));  

    sky_bg = new QGraphicsRectItem(0, 0, GameMap::width, GameMap::height - 3);
    sky_bg->setBrush(skyBrush);
    sky_bg->setPen(Qt::NoPen);
    addItem(sky_bg);

    water_bg = new QGraphicsRectItem(0, GameMap::height - 3, GameMap::width, 3);
    water_bg->setBrush(waterBrush);
    water_bg->setPen(Qt::NoPen);
    addItem(water_bg);
}

void QtGameMap::clear() noexcept {
    QList<QGraphicsItem*> items_list = items();
    for (QGraphicsItem* item : items_list) {
        if (item != sky_bg && item != water_bg) {
            removeItem(item);
            delete item;
        }
    }
}

void QtGameMap::refresh() noexcept {
    update();
}

void QtGameMap::remove_objs() {
    clear();
}

void QtGameMap::show() const noexcept {

}

void QtGameMap::addGraphicsItem(QGraphicsItem* item) {
    addItem(item);
}

void QtGameMap::removeGraphicsItem(QGraphicsItem* item) {
    removeItem(item);
}
