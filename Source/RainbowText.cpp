#include "RainbowText.h"
#include <QLineEdit>
#include <QPainter>
#include <QStyleOption>

RainbowFilter::RainbowFilter(QLabel* target, int interval, int step)
        : QObject(target), m_label(target), m_offset(0), m_step(step)
    {
        m_label->installEventFilter(this);
        m_timer = new QTimer(this);
        m_timer->setInterval(interval);
        connect(m_timer, &QTimer::timeout, this, &RainbowFilter::advance);
        m_timer->start();
    }

bool RainbowFilter::eventFilter(QObject* obj, QEvent* ev) {
    if (obj == m_label && ev->type() == QEvent::Paint) {
        QStyleOption opt;
        opt.initFrom(m_label);
        QPainter p(m_label);
        m_label->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, m_label);
        const QString txt = m_label->text();
        if (!txt.isEmpty()) {
            QLinearGradient grad(-m_label->width() + m_offset, 0,
                                m_offset, 0);
            grad.setColorAt(0.00, Qt::white);
            grad.setColorAt(0.70, "#3870A6");
            grad.setColorAt(1.00, Qt::white);

            p.setRenderHint(QPainter::Antialiasing);
            p.setFont(m_label->font());
            p.setPen(QPen(QBrush(grad), 0));

            QFontMetrics fm(m_label->font());
            int y = (m_label->height() + fm.ascent() - fm.descent())/2;
            int x = m_label->contentsMargins().left();
            p.drawText(x, y, txt);
        }
        return true;
    }
    return QObject::eventFilter(obj, ev);
}

void RainbowFilter::advance() {
    m_offset += m_step;
    if (m_offset > 2*m_label->width())
        m_offset = 0;
    m_label->update();
}
