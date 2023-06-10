#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QDialog>

namespace Ui {
class DetailWindow;
}

class DetailWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DetailWindow(const QString& genre, const QString& datePremier,
                          const QString& runtime, const QString& imdb,
                          const QString& language, QWidget *parent = nullptr);
    ~DetailWindow();

    QStringList getModifiedData() const;

private:
    Ui::DetailWindow *ui;
};

#endif // DETAILWINDOW_H
