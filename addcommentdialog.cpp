#include "addcommentdialog.h"
#include "comment.h"
#include "ui_addcommentdialog.h"

AddCommentDialog::AddCommentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCommentDialog)
{
    ui->setupUi(this);

    for (int i = 1; i <= 10; ++i) {
        ui->rateComboBox->addItem(QString::number(i));
    }

    connect(ui->addCommentButton, &QPushButton::clicked, this, &AddCommentDialog::accept);
    connect(ui->closeButton, &QPushButton::clicked, this, &AddCommentDialog::reject);
}

AddCommentDialog::~AddCommentDialog()
{
    delete ui;
}

QString AddCommentDialog::getUsername() const
{
    return ui->usernameLineEdit->text();
}

QString AddCommentDialog::getComment() const
{
    return ui->commentPlainTextEdit->toPlainText();
}

int AddCommentDialog::getRating() const
{
    return ui->rateComboBox->currentIndex() + 1;
}

void AddCommentDialog::setText(Comment comment)
{
    ui->usernameLineEdit->setText(comment.username);
    ui->commentPlainTextEdit->setPlainText(comment.comment);
    QString rating = QString::number(comment.rating);
    ui->rateComboBox->setCurrentText(rating);
}
