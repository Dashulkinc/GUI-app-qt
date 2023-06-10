#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "logowidget.h"
#include <QDialog>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

private:
    Ui::HelpWindow *ui;
    LogoWidget* logoWidget;
};

#endif // HELPWINDOW_H
