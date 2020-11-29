#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include <QGLFormat>
#include "support/scenegraph/SupportCanvas3D.h"
#include <QFileDialog>
#include <QMessageBox>
#include "support/camera/CamtransCamera.h"
#include "support/lib/CS123XmlSceneParser.h"
#include "support/scenegraph/SceneviewScene.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //You can make changes to the scene now

    //Adding in the 3D canvas...
    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);

    m_canvas3D = new SupportCanvas3D(qglFormat, this);
    ui->mainGridLayout->addWidget(m_canvas3D, 0, 0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen() {
    // This opens the 3D tab to initialize OGL so parsing
    // the scene doesn't crash. If you can find a better solution
    // feel free to change this.
    QString file = QFileDialog::getOpenFileName(this, QString(), "/course/cs123/data/");
    if (!file.isNull()) {
        if (file.endsWith(".xml")) {
            CS123XmlSceneParser parser(file.toLatin1().data());
            if (parser.parse()) {
                m_canvas3D->loadSceneviewSceneFromParser(parser);
                //ui->showSceneviewInstead->setChecked(true);

                // Set the camera for the new scene
                CS123SceneCameraData camera;
                if (parser.getCameraData(camera)) {
                    camera.pos[3] = 1;
                    camera.look[3] = 0;
                    camera.up[3] = 0;

                    CamtransCamera *cam = m_canvas3D->getCamtransCamera();
                    cam->orientLook(camera.pos, camera.look, camera.up);
                    cam->setHeightAngle(camera.heightAngle);
                }

//                if (settings.useOrbitCamera) {
//                    ui->cameraOrbitCheckbox->setChecked(false);
//                }

            } else {
                QMessageBox::critical(this, "Error", "Could not load scene \"" + file + "\"");
            }
        }
        else {
//            if (!ui->canvas2D->loadImage(file)) {
//                QMessageBox::critical(this, "Error", "Could not load image \"" + file + "\"");
//            } else {
//            }
             QMessageBox::critical(this, "Error", "We don't support non-xml stuff yettt");
        }
    }
}


void MainWindow::on_rednerButton_clicked()
{
    fileOpen();
}
