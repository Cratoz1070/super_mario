#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QCloseEvent>

namespace biv {
class QtGameMap;
}

class QtGameWindow : public QMainWindow {
    Q_OBJECT

private:
    QGraphicsView* game_view;

public:
    QtGameWindow(biv::QtGameMap* scene, QWidget* parent = nullptr);
    QGraphicsView* getView() const;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};
