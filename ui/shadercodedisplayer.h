#ifndef SHADERCODEDISPLAYER_H
#define SHADERCODEDISPLAYER_H

#include <QDialog>

namespace Ui {
class ShaderCodeDisplayer;
}

class ShaderCodeDisplayer : public QDialog
{
    Q_OBJECT

public:
    explicit ShaderCodeDisplayer(QWidget *parent = nullptr);
    ~ShaderCodeDisplayer();

private slots:
    void on_closeButton_clicked();

private:
    Ui::ShaderCodeDisplayer *ui;
};

#endif // SHADERCODEDISPLAYER_H
