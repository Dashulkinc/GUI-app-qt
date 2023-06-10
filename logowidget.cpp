#include "logowidget.h"
#include <QPainter>

LogoWidget::LogoWidget(QWidget* parent) : QWidget(parent) {
    setFixedSize(300, 300);

    // Load the PNG image
    logoPixmap = QPixmap(":/logo/logo.png");
}

void LogoWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // Draw the logo pixmap onto the widget
    painter.drawPixmap(0, 0, logoPixmap);
}
