#include "shadercodedisplayer.h"
#include "ui_shadercodedisplayer.h"

ShaderCodeDisplayer::ShaderCodeDisplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShaderCodeDisplayer)
{
    ui->setupUi(this);
}

ShaderCodeDisplayer::~ShaderCodeDisplayer()
{
    delete ui;
}

void ShaderCodeDisplayer::on_closeButton_clicked()
{
    this->close();
}
