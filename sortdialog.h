#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>

namespace Ui {
class SortDialog;
}

class SortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = nullptr);
    ~SortDialog();

    QString getOrder() const;
    QString getField() const;

private:
    Ui::SortDialog *ui;
};

#endif // SORTDIALOG_H
