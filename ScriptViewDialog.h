#ifndef SCRIPTVIEWDIALOG_H
#define SCRIPTVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class ScriptViewDialog;
}

class ScriptViewDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ScriptViewDialog(QWidget *parent = 0);
    ~ScriptViewDialog();

    void showScript(const QString &script);
    
private:
    Ui::ScriptViewDialog *ui;

private slots:
    void onClose();
    void onSaveAs();
};

#endif // SCRIPTVIEWDIALOG_H
