#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    connect(ui->filterButton, &QPushButton::clicked, this, &FilterDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &FilterDialog::reject);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

QStringList FilterDialog::getFilterData() const
{
    QStringList newData;
    if (ui->title->isChecked())
    {
        newData << ui->title->text();
    }

    if (ui->genre->isChecked())
    {
        newData << ui->genre->text();
    }

    if (ui->premiere->isChecked())
    {
        newData << ui->premiere->text();
    }

    if (ui->runtime->isChecked())
    {
        newData << ui->runtime->text();
    }

    if (ui->imdb->isChecked())
    {
        newData << ui->imdb->text();
    }

    if (ui->language->isChecked())
    {
        newData << ui->language->text();
    }

    return newData;
}
