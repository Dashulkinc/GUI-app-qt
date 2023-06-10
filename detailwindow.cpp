#include "detailwindow.h"
#include "ui_detailwindow.h"

DetailWindow::DetailWindow(const QString& genre, const QString& datePremier,
                           const QString& runtime, const QString& imdb,
                           const QString& language, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailWindow)
{
    ui->setupUi(this);
    ui->genre->setText(genre);
    ui->datePremier->setText(datePremier);
    ui->runtime->setText(runtime);
    ui->imdb->setText(imdb);
    ui->language->setText(language);

    connect(ui->saveButton, &QPushButton::clicked, this, &DetailWindow::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &DetailWindow::reject);
}

DetailWindow::~DetailWindow()
{
    delete ui;
}

QStringList DetailWindow::getModifiedData() const
{
    QStringList newData;
    newData << ui->genre->text() << ui->datePremier->text()
            << ui->runtime->text() << ui->imdb->text() << ui->language->text();
    return newData;
}
