#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "comment.h"
#include "viewcommentsdialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_filterButton_clicked();

    void on_sortButton_clicked();

    void on_saveDataButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;

    void loadData();
    void onSearchTextChanged(const QString &text);
    void showContextMenu(const QPoint& pos);
    void onAddCommentActionTriggered();
    void onViewCommentsActionTriggered();
    void onTableViewClicked(const QModelIndex& index);
    void onRemoveRowActionTriggered();
    void setQMenu();
    void onAddRowActionTriggered();
    void castColumnToInt(int columnIndex);
    void castColumnToDate(int columnIndex);
    void onHelpActionTriggered();

    QMap<int, QList<Comment>> commentsMap;
    ViewCommentsDialog viewCommentsDialog;
};
#endif // MAINWINDOW_H
