#include "SlidingIndicatorWidget.h"
#include <QTimer>

SlidingIndicatorWidget::SlidingIndicatorWidget(const QList<QPushButton*> &buttonsList, QWidget *parent)
    : QWidget(parent), buttons(buttonsList)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    indicator = new QFrame(this);
    indicator->setFixedHeight(1);
    indicator->setStyleSheet("background-color: #ffffff; border-radius: 1px;");

    for (int i = 0; i < buttons.size(); ++i) {
        QPushButton *btn = buttons[i];
        btn->installEventFilter(this);
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            currentButton = btn;
            animateIndicatorTo(btn);
        });
        if (i == 0)
            currentButton = btn;
    }

    QTimer::singleShot(0, this, [this]() {
        animateIndicatorTo(currentButton, 0);
    });
}

bool SlidingIndicatorWidget::eventFilter(QObject *watched, QEvent *event) {
    if (QPushButton *btn = qobject_cast<QPushButton*>(watched)) {
        if (event->type() == QEvent::Enter) {
            animateIndicatorTo(btn);
        } else if (event->type() == QEvent::Leave) {
            animateIndicatorTo(currentButton);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void SlidingIndicatorWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    animateIndicatorTo(currentButton, 0);
}

void SlidingIndicatorWidget::animateIndicatorTo(QPushButton *target, int duration) {
    if (!target) return;

    QPoint pos = target->pos();
    QRect endRect(pos.x(),
                    pos.y() + target->height(),
                    target->width(),
                    indicator->height());

    if (duration == 0) {
        if (animation) {
            animation->stop();
            animation->deleteLater();
            animation = nullptr;
        }
        indicator->setGeometry(endRect);
        return;
    }

    if (animation) {
        animation->stop();
        animation->deleteLater();
        animation = nullptr;
    }

    animation = new QPropertyAnimation(indicator, "geometry", this);
    connect(animation, &QPropertyAnimation::finished, [this]() {
        animation = nullptr;
    });

    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setStartValue(indicator->geometry());
    animation->setEndValue(endRect);
    animation->start();
}
