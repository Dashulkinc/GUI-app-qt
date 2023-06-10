#include "helpwindow.h"
#include "QtWidgets/qboxlayout.h"
#include "ui_helpwindow.h"

#include <QTextEdit>

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);

    setWindowTitle("About");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Create the LogoWidget instance
    logoWidget = new LogoWidget(this);

    // Create the label instance
    QTextEdit *plainTextEdit = new QTextEdit(this);
    plainTextEdit->setReadOnly(true);

    // Add the LogoWidget and label to the layout
    layout->addWidget(logoWidget);
    layout->addWidget(plainTextEdit);

    // Set the layout as the main layout for the dialog
    setLayout(layout);

    plainTextEdit->setPlainText("Hello, this application provides information about "
                                "movies on Netflix with their rating on IMDB.\n"
                                "With menu in the upper side of your screen you can add new row and see this window.\n"
                                "You can filter table with desired headers and sort by one desired field and desired order.\n"
                                "If you want to reset table to original, please click Reset table button.\n"
                                "If you want to see more info about field, click once on the cell in the needed row.\n"
                                "There also you can edit row data and save changes.\n"
                                "If you want to add comment to the movie, right-click on the cell in the row and click Add comment.\n"
                                "You can also view comments you added to every movie.\n"
                                "Double click on comment to modify it.\n"
                                "On the Main window you can also remove row by right-clicking on it and clicking on Remove row.");
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
