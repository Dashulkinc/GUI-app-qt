#include "viewcommentsdialog.h"
#include "addcommentdialog.h"
#include "comment.h"
#include "ui_viewcommentsdialog.h"

ViewCommentsDialog::ViewCommentsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewCommentsDialog)
{
    ui->setupUi(this);

    setWindowTitle("View Comments");

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({ "Username", "Comment", "Rating" });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &ViewCommentsDialog::onTableDoubleClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &ViewCommentsDialog::accept);
}

ViewCommentsDialog::~ViewCommentsDialog()
{
    delete ui;
}

void ViewCommentsDialog::populateTable(const QList<Comment>& comments)
{
    ui->tableWidget->setRowCount(comments.size());

    for (int i = 0; i < comments.size(); ++i) {
        const Comment& comment = comments.at(i);

        QTableWidgetItem *usernameItem = new QTableWidgetItem(comment.username);
        QTableWidgetItem *commentItem = new QTableWidgetItem(comment.comment);
        QTableWidgetItem *ratingItem = new QTableWidgetItem(QString::number(comment.rating));

        ui->tableWidget->setItem(i, 0, usernameItem);
        ui->tableWidget->setItem(i, 1, commentItem);
        ui->tableWidget->setItem(i, 2, ratingItem);
    }
}

void ViewCommentsDialog::onTableDoubleClicked(const QModelIndex& index) {
    if (index.isValid()) {
        int row = index.row();

        // Get the data from the selected row
        QTableWidgetItem* usernameItem = ui->tableWidget->item(row, 0);
        QTableWidgetItem* commentItem = ui->tableWidget->item(row, 1);
        QTableWidgetItem* ratingItem = ui->tableWidget->item(row, 2);

        Comment comment;
        comment.username = usernameItem->text();
        comment.comment = commentItem->text();
        comment.rating = ratingItem->text().toInt();

        // Open the AddCommentDialog for editing
        AddCommentDialog editDialog(this);
        editDialog.setText(comment);
        editDialog.setWindowTitle("Modify Comment");
        if (editDialog.exec() == QDialog::Accepted) {
            // Get the edited data from the AddCommentDialog
            QString editedUsername = editDialog.getUsername();
            QString editedComment = editDialog.getComment();
            int editedRating = editDialog.getRating();

            // Update the row in the table with the edited data
            usernameItem->setText(editedUsername);
            commentItem->setText(editedComment);
            ratingItem->setText(QString::number(editedRating));
        } else {
            editDialog.close();
        }
    }
}

QList<Comment> ViewCommentsDialog::getEditedData() const {
    QList<Comment> editedData;
    int rowCount = ui->tableWidget->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem* usernameItem = ui->tableWidget->item(row, 0);
        QTableWidgetItem* commentItem = ui->tableWidget->item(row, 1);
        QTableWidgetItem* ratingItem = ui->tableWidget->item(row, 2);

        Comment comment;
        comment.username = usernameItem->text();
        comment.comment = commentItem->text();
        comment.rating = ratingItem->text().toInt();

        // Append the edited data as a single string
        editedData.append(comment);
    }

    return editedData;
}
