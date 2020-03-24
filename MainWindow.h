#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum
{
    TableColumn_Def     = 0,
    TableColumn_Inc     = 1,
    TableColumn_IncPer  = 2,
    TableColumn_Base    = 3,
    TableColumn_Width   = 4,
    TableColumn_Range   = 5,
    TableColumn_Min     = 6,
    TableColumn_Max     = 7,

    TableColumn_Count   = 8
};

class QTableWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    void initExampleAlarm();
    void initExampleEvent();

    void addParameter(QTableWidget *widget);
    void delParameter(QTableWidget *widget);
    void connectNewParamToSetExample(const QTableWidget *widget, const char *slot);

    QString makeAlarmScript() const;
    QString makeEventScript() const;
    QString makeAddress(const QString &addrFormat, const QTableWidget *tableWidget, int sequence) const;

private slots:
    void onGenerateAlarm();
    void setAlarmExampleLabels();
    void onAddAlarmDevParam();
    void onDelAlarmDevParam();
    void onAddAlarmVirParam();
    void onDelAlarmVirParam();

    void onGenerateEvent();
    void setEventExampleLabels();
    void onAddEventDevParam();
    void onDelEventDevParam();
    void onAddEventVirParam();
    void onDelEventVirParam();
};

#endif // MAINWINDOW_H
