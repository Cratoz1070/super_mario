#pragma once

#include <QGraphicsScene>
#include "game_map.hpp"

namespace biv {
class QtGameMap : public QGraphicsScene, public GameMap {
    Q_OBJECT

private:
    QGraphicsRectItem* sky_bg = nullptr;
    QGraphicsRectItem* water_bg = nullptr;

public:
    QtGameMap(const int height, const int width, QObject* parent = nullptr);
    ~QtGameMap();

    void clear() noexcept override;
    void refresh() noexcept override;
    void remove_objs() override;
    void show() const noexcept override;

    void addGraphicsItem(QGraphicsItem* item);
    void removeGraphicsItem(QGraphicsItem* item);

    int get_map_height() const { return GameMap::height; }
    int get_map_width() const { return GameMap::width; }

    void centerViewOn(qreal x, qreal y, QGraphicsView* view);

private:
    void initBackground();
};
}
