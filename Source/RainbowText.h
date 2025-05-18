#pragma once
#include <QEvent>
#include <QObject>
#include <QLabel>
#include <QTimer>

class RainbowFilter : public QObject {
    Q_OBJECT
public:
    explicit RainbowFilter(QLabel* target, int interval = 50, int step = 5);

protected:
    bool eventFilter(QObject* obj, QEvent* ev) override;

private slots:
    void advance();

private:
    QLabel* m_label;
    QTimer* m_timer;
    int m_offset;
    int m_step;
};
