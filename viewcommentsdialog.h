#ifndef VIEWCOMMENTSDIALOG_H
#define VIEWCOMMENTSDIALOG_H

#include "comment.h"
#include <QDialog>
#include <QTableWidget>

namespace Ui {
class ViewCommentsDialog;
}

class ViewCommentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCommentsDialog(QWidget *parent = nullptr);
    ~ViewCommentsDialog();

    void populateTable(const QList<Comment>& comments);
    QList<Comment> getEditedData() const;

private:
    Ui::ViewCommentsDialog *ui;
    void onTableDoubleClicked(const QModelIndex& index);
};

#endif // VIEWCOMMENTSDIALOG_H
