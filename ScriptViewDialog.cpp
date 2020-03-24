#include "ScriptViewDialog.h"
#include "ui_ScriptViewDialog.h"

#include <QFileDialog>

ScriptViewDialog::ScriptViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScriptViewDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(onClose()));
    connect(ui->pushButtonSaveAs, SIGNAL(clicked()), this, SLOT(onSaveAs()));
}

ScriptViewDialog::~ScriptViewDialog()
{
    delete ui;
}

void ScriptViewDialog::showScript(const QString &script)
{
    ui->textEditScript->setText(script);

    this->exec();
}

void ScriptViewDialog::onClose()
{
    this->close();
}

void ScriptViewDialog::onSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "", "", tr("Text (*.txt)"));
    QFile file(fileName);
    if( file.open(QIODevice::WriteOnly) ) {
        const QTextDocument* doc = ui->textEditScript->document();
        file.write(doc->toPlainText().toUtf8());
        file.close();
    }
}
