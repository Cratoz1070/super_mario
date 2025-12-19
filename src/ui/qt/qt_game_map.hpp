// qt_game_map.hpp
#pragma once

#include <QGraphicsScene>
#include "game_map.hpp"

namespace biv {
class QtGameMap : public QGraphicsScene, public GameMap {
    Q_OBJECT

private:
    // Фон для карты
    QGraphicsRectItem* sky_bg = nullptr;
    QGraphicsRectItem* water_bg = nullptr;

public:
    QtGameMap(const int height, const int width, QObject* parent = nullptr);
    ~QtGameMap();

    // Реализация абстрактных методов GameMap
    void clear() noexcept override;
    void refresh() noexcept override;
    void remove_objs() override;
    void show() const noexcept override;

    // Методы для добавления/удаления объектов
    void addGraphicsItem(QGraphicsItem* item);
    void removeGraphicsItem(QGraphicsItem* item);

    // Получение размеров
    int get_map_height() const { return GameMap::height; }
    int get_map_width() const { return GameMap::width; }

private:
    // Инициализация фона
    void initBackground();
};
}
