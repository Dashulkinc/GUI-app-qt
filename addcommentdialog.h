#ifndef ADDCOMMENTDIALOG_H
#define ADDCOMMENTDIALOG_H

#include "comment.h"
#include <QDialog>

namespace Ui {
class AddCommentDialog;
}

class AddCommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCommentDialog(QWidget *parent = nullptr);
    ~AddCommentDialog();

    QString getUsername() const;
    QString getComment() const;
    int getRating() const;
    void setText(Comment comment);

private slots:

private:
    Ui::AddCommentDialog *ui;
};

#endif // ADDCOMMENTDIALOG_H
