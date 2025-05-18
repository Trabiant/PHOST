#pragma once
#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QPropertyAnimation>
#include <QEvent>

class SlidingIndicatorWidget : public QWidget {
    Q_OBJECT
public:
    SlidingIndicatorWidget(const QList<QPushButton*> &buttonsList, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QList<QPushButton*> buttons;
    QPushButton *currentButton = nullptr;
    QFrame *indicator;
    QPropertyAnimation *animation = nullptr;
    void animateIndicatorTo(QPushButton *target, int duration = 200);
};
