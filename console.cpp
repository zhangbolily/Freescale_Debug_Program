#include "console.h"
#include <QScrollBar>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(true)
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    connect(this, SIGNAL(sendData(QByteArray)),
            this, SLOT(putData(const QByteArray)));

}

void Console::putData(const QByteArray &data)
{
    insertPlainText(QString(data));

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    int line = 0;
    QString str;
    QByteArray str_byte;

    switch (e->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    case Qt::Key_Return:{
        QPlainTextEdit::keyPressEvent(e);

        line = this->blockCount() - 2;
        line = this->document()->lineCount() - 2;
        qDebug()<<line;
        str = this->document()->findBlockByLineNumber(line).text();        //找到了新的方法来获取这一行的内容。
        str.append('\n');
        str_byte = str.toLocal8Bit();

        emit sendData(str_byte);
        break;
    }
    default:
        if (localEchoEnabled)
        {
            QPlainTextEdit::keyPressEvent(e);
//            str.append(e->text().toLocal8Bit());      //暂时注释掉，我们用别的方法来获取这一行的内容。
            break;
        }
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
