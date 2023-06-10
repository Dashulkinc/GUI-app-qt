#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &SortDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SortDialog::reject);

    QStringList fields = {"Title", "Genre", "Premiere", "Runtime", "IMDB Score", "Language"};
    QStringList order = {"Ascending", "Descending"};
    ui->fieldComboBox->addItems(fields);
    ui->orderComboBox->addItems(order);
}

SortDialog::~SortDialog()
{
    delete ui;
}

QString SortDialog::getField() const
{
    return ui->fieldComboBox->currentText();
}

QString SortDialog::getOrder() const
{
    return ui->orderComboBox->currentText();
}
