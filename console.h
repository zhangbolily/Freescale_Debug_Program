#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>

class Console: public QPlainTextEdit
{
    Q_OBJECT

signals:
    void sendData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = 0);

    void setLocalEchoEnabled(bool set);

public slots:
    void putData(const QByteArray &data);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;
};

#endif // CONSOLE_H
