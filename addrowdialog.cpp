#include "addrowdialog.h"
#include "ui_addrowdialog.h"

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &AddRowDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddRowDialog::reject);
}

AddRowDialog::~AddRowDialog()
{
    delete ui;
}

QStringList AddRowDialog::getData() const
{
    QStringList newData;
    newData << ui->title->text() << ui->genre->text() << ui->premier->text()
            << ui->runtime->text() << ui->imdb->text() << ui->language->text();

    QDate premierDate = QDate::fromString(ui->premier->text(), "dd.MM.yyyy");
    if (!premierDate.isValid())
    {
        QMessageBox::warning(this, "Ошибка", "Неверный формат даты в поле 'premier'");
        return QStringList();
    }

    return newData;
}
