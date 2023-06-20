#include "mainwindow.h"
#include "addcommentdialog.h"
#include "addrowdialog.h"
#include "comment.h"
#include "detailwindow.h"
#include "filterdialog.h"
#include "helpwindow.h"
#include "sortdialog.h"
#include "ui_mainwindow.h"
#include "viewcommentsdialog.h"

#include <QFile>
#include <QStandardItemModel>
#include <QRegularExpression>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadData();
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::showContextMenu);
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onTableViewClicked);

    setQMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setQMenu()
{
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenu = menuBar->addMenu("File");

    // Create a new QAction object for your new action
    QAction* addRowAction = new QAction("Add Row", this);
    QAction* helpAction = new QAction("Help", this);

    // Connect the triggered signal of the new action to a slot
    connect(addRowAction, &QAction::triggered, this, &MainWindow::onAddRowActionTriggered);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelpActionTriggered);

    fileMenu->addAction(addRowAction);
    fileMenu->addAction(helpAction);
    setMenuBar(menuBar);
}

void MainWindow::onHelpActionTriggered()
{
    HelpWindow *dialog = new HelpWindow(this);
    dialog->exec();
}

void MainWindow::onAddRowActionTriggered()
{
    AddRowDialog dialog(this);
    dialog.setWindowTitle("Add Movie Data");
    if (dialog.exec() == QDialog::Accepted) {
        QStringList newData = dialog.getData();
        QAbstractItemModel* model = ui->tableView->model();

        // Insert a new row at the beginning
        model->insertRow(0);

        // Iterate over the fields in the QStringList and set the data for each cell
        for (int i = 0; i < newData.size(); ++i) {
            QModelIndex index = model->index(0, i);  // Row 0, Column i
            model->setData(index, newData.at(i));
        }
    } else {
        dialog.close();
    }
}

void MainWindow::loadData()
{
    QStandardItemModel* model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

    // Open the CSV file
    QString filePath = ":/dataset/netflix.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        // Failed to open the file
        return;
    }

    // Read the contents of the CSV file
    QTextStream in(&file);
    if (!in.atEnd())
    {
        QString headerLine = in.readLine();
        QStringList headers = headerLine.split(',');

        // Remove double quotes from the headers, if any
        for (QString& header : headers)
        {
            header = header.remove('\"');
        }

        // Set the headers for the table model
        model->setHorizontalHeaderLabels(headers);
    }

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields;

        // Parse the line using the double-quote as a delimiter
        int startPos = 0;
        bool inQuotes = false;
        for (int i = 0; i < line.length(); ++i)
        {
            if (line.at(i) == '\"')
            {
                inQuotes = !inQuotes;
            }
            else if (line.at(i) == ',' && !inQuotes)
            {
                QString field = line.mid(startPos, i - startPos);
                field = field.remove('\"'); // Remove double quotes from the field
                fields.append(field);
                startPos = i + 1;
            }
        }

        // Add the last field
        QString lastField = line.mid(startPos);
        lastField = lastField.remove('\"'); // Remove double quotes from the last field
        fields.append(lastField);

        // Add the parsed row to the table model
        QList<QStandardItem *> rowItems;
        for (const QString &field : fields)
        {
            QStandardItem *item = new QStandardItem(field);
            rowItems.append(item);
        }

        model->appendRow(rowItems);
    }

    // Close the file
    file.close();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QString premiereDateStr = model->index(row, 2).data().toString();
        QDateTime premiereDate = QDateTime::fromString(premiereDateStr, "MMMM d, yyyy");
        QString formattedPremiereDate = premiereDate.toString("dd.MM.yyyy");

        // Update the model with the formatted premiere date
        model->setData(model->index(row, 2), formattedPremiereDate);
    }

    for (int column = 1; column < 6; ++column) {
        if (column != 0 && column != 4) {
            ui->tableView->setColumnHidden(column, true);
        }
    }

    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onTableViewClicked(const QModelIndex& index) {
    if (index.isValid()) {
        int row = index.row();

        // Retrieve the data for the clicked row
        QString movieTitle = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
        QString movieGenre = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
        QString moviePremier = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
        QString movieRuntime = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
        QString movieIMDB = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();
        QString movieLanguage = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();

        // Open the DetailWindow dialog
        DetailWindow detailDialog(movieGenre, moviePremier, movieRuntime, movieIMDB, movieLanguage, this);
        detailDialog.setWindowTitle(movieTitle);
        if (detailDialog.exec() == QDialog::Accepted) {
            QStringList editedData = detailDialog.getModifiedData();

            ui->tableView->model()->setData(ui->tableView->model()->index(row, 1), editedData[0]);
            ui->tableView->model()->setData(ui->tableView->model()->index(row, 2), editedData[1]);
            ui->tableView->model()->setData(ui->tableView->model()->index(row, 3), editedData[2]);
            ui->tableView->model()->setData(ui->tableView->model()->index(row, 4), editedData[3]);
            ui->tableView->model()->setData(ui->tableView->model()->index(row, 5), editedData[4]);
        } else {
            detailDialog.close();
        }
    }
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    // Get the model of the QTableView
    QAbstractItemModel* model = ui->tableView->model();

    // Convert the search text to lowercase for case-insensitive matching
    QString searchTextLower = text.toLower();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        QModelIndex titleIndex = model->index(row, 0);
        QModelIndex genreIndex = model->index(row, 1);

        QString title = titleIndex.data(Qt::DisplayRole).toString().toLower();
        QString genre = genreIndex.data(Qt::DisplayRole).toString().toLower();

        // Check if the search text is found in either the first or second column
        bool match = title.contains(searchTextLower) || genre.contains(searchTextLower);

        // Show or hide the row based on the match result
        ui->tableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_filterButton_clicked()
{
    FilterDialog dialog(this);
    dialog.setWindowTitle("Filter By Fields");
    if (dialog.exec() == QDialog::Accepted) {
        QStringList newData = dialog.getFilterData();
        QHeaderView* header = ui->tableView->horizontalHeader();

        // Iterate over the header sections
        for (int i = 0; i < header->count(); ++i) {
            // Get the current header section's name
            QString sectionName = header->model()->headerData(i, Qt::Horizontal).toString();

            if (newData.contains(sectionName)) {
                header->setSectionHidden(i, false);
            } else {
                header->setSectionHidden(i, true);
            }
        }
    } else {
        dialog.close();
    }
}

void MainWindow::castColumnToInt(int columnIndex)
{
    QStandardItemModel* sortModel = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (!sortModel) {
        return;  // Invalid model, do nothing
    }

    // Get the column index to cast to integer
    int columnIndexSort = columnIndex;

    for (int row = 0; row < sortModel->rowCount(); ++row) {
        QModelIndex index = sortModel->index(row, columnIndexSort);
        QVariant value = sortModel->data(index);

        // Convert the value to integer if it is a valid string
        bool ok;
        int intValue = value.toString().toInt(&ok);
        if (ok) {
            sortModel->setData(index, intValue);
        }
    }
}

void MainWindow::castColumnToDate(int columnIndex)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (!model) {
        return;  // Invalid model, do nothing
    }
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, columnIndex);
        QVariant value = model->data(index);

        // Convert the value to QDate if it is a valid string
        QDate date = QDate::fromString(value.toString(), "dd.MM.yyyy");
        if (date.isValid()) {
            model->setData(index, date);
        }
    }
}

void MainWindow::on_sortButton_clicked()
{
    SortDialog dialog(this);
    dialog.setWindowTitle("Sort Data");
    if (dialog.exec() == QDialog::Accepted) {
        QString field = dialog.getField();
        QString order = dialog.getOrder();
        Qt::SortOrder sortOrder;
        if (order == "Ascending") {
            sortOrder = Qt::AscendingOrder;
        } else {
            sortOrder = Qt::DescendingOrder;
        }

        castColumnToInt(3);
        castColumnToDate(2);

        QAbstractItemModel* model = ui->tableView->model();

        // Get the column index for the selected field
        int columnIndex = -1;
        for (int i = 0; i < model->columnCount(); ++i) {
            QString columnName = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
            if (columnName == field) {
                columnIndex = i;
                break;
            }
        }

        if (columnIndex != -1) {
            // Sort the model based on the selected column and order
            model->sort(columnIndex, sortOrder);
        }

    } else {
        dialog.close();
    }
}

void MainWindow::on_saveDataButton_clicked()
{
    QFile file(QStandardPaths::locate(QStandardPaths::DesktopLocation, ""));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Failed to open the file for writing.");
    }
    // QString filePath = QFileDialog::getSaveFileName(this, "Save CSV File", "", "CSV Files (*.csv)");

    // if (filePath.isEmpty())
    //     return;

    // QFile file(filePath);
    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    // {
    //     QMessageBox::warning(this, "Error", "Failed to open the file for writing.");
    //     return;
    // }

    QTextStream stream(&file);

    // Write the headers
    QStringList headers;
    for (int column = 0; column < ui->tableView->model()->columnCount(); ++column)
    {
        headers.append(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    }
    stream << headers.join(",") << "\n";

    // Write the data
    for (int row = 0; row < ui->tableView->model()->rowCount(); ++row)
    {
        QStringList rowData;
        for (int column = 0; column < ui->tableView->model()->columnCount(); ++column)
        {
            QString data = ui->tableView->model()->index(row, column).data().toString();
            // Remove any double quotes from the data
            data.remove("\"");
            rowData.append(data);
        }
        stream << rowData.join(",") << "\n";
    }

    file.close();

    QMessageBox::information(this, "Save Successful", "Data saved to CSV file.");
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    QTableView* tableView = ui->tableView;

    QModelIndex index = tableView->indexAt(pos);

    if (index.isValid()) {
        // If a valid index is obtained, create a context menu for the table view
        QMenu contextMenu(tableView);

        // Create an "Add Comment" action and connect it to the onAddCommentActionTriggered slot
        QAction* addCommentAction = new QAction("Add Comment", this);
        connect(addCommentAction, &QAction::triggered, this, &MainWindow::onAddCommentActionTriggered);

        // Create a "View Comments" action and connect it to the onViewCommentsActionTriggered slot
        QAction* viewCommentsAction = new QAction("View Comments", this);
        connect(viewCommentsAction, &QAction::triggered, this, &MainWindow::onViewCommentsActionTriggered);

        // Create a "Remove Row" action and connect it to the onRemoveRowActionTriggered slot
        QAction* removeRowAction = new QAction("Remove Row", this);
        connect(removeRowAction, &QAction::triggered, this, &MainWindow::onRemoveRowActionTriggered);

        // Add the actions to the context menu
        contextMenu.addAction(addCommentAction);
        contextMenu.addAction(viewCommentsAction);
        contextMenu.addAction(removeRowAction);

        // Show the context menu at the global position calculated from the given position
        contextMenu.exec(tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::onRemoveRowActionTriggered()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();

        ui->tableView->model()->removeRow(row);
    }
}

void MainWindow::onAddCommentActionTriggered()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        AddCommentDialog dialog(this);
        dialog.setWindowTitle("Add New Comment");
        if (dialog.exec() == QDialog::Accepted) {
            Comment comment;
            comment.username = dialog.getUsername();
            comment.comment = dialog.getComment();
            comment.rating = dialog.getRating();
            int row = index.row();
            commentsMap[row].append(comment);
        }
    }
}

void MainWindow::onViewCommentsActionTriggered() {
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        int row = index.row();
        QList<Comment> comments = commentsMap[row];

        if (comments.isEmpty()) {
            QMessageBox::information(this, "No Comments", "No comments for this movie.");
        } else {
            ViewCommentsDialog dialog(this);
            dialog.populateTable(comments);
            if (dialog.exec() == QDialog::Accepted) {
                QList<Comment> editedData = dialog.getEditedData();

                // Update the comments in the QMap for the selected row
                QList<Comment> editedComments;
                for (const Comment& commentData : editedData) {
                    Comment editedComment;
                    editedComment.comment = commentData.comment;
                    editedComment.username = commentData.username;
                    editedComment.rating = commentData.rating;
                    editedComments.append(editedComment);
                }

                commentsMap[row] = editedComments;
            }
        }
    }
}

void MainWindow::on_resetButton_clicked()
{
    loadData();
}

