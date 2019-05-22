#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"

extern GameController * gc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Background
    QPixmap pix(":/images/Resources/background1.png");
    ui->label_pic->setPixmap(pix);
    ui->label_pic->setScaledContents(true);

    setFocusPolicy(Qt::NoFocus);

    // ALL OF THE CODE BELOW COULD, AND SHOULD BE DEALT WITH THROUGH QT'S FORM DESIGN EDITOR (visually),
    // BUT FOR THE SAKE OF WRITTING MORE CODE FOR THE PROJECT WE'LL DO IT THIS WAY

    // Init button
    ui->newGameButton->setText("New Game");
    ui->newGameButton->setFont(QFont("terminal",12));

    ui->exitButton->setText("Exit");
    ui->exitButton->setFont(QFont("terminal",12));

    // Init difficulty slider + label
    ui->difficultySlider->setMaximum(9);
    ui->difficultySlider->setMinimum(1);
    ui->difficultySlider->setPageStep(1);
    ui->difficultyLabel->setText(QString("Difficulty: ") + QString::number(ui->difficultySlider->value()));
    ui->difficultyLabel->setFont(QFont("terminal",16));
    ui->difficultyLabel->setStyleSheet("QLabel { color : white; }");

    ui->label->setText("DX BALL");
    ui->label->setFont(QFont("impact",72));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_difficultySlider_valueChanged(int value)
{
    ui->difficultyLabel->setText(QString("Difficulty: ") + QString::number(value));
}

void MainWindow::on_newGameButton_clicked()
{
    hide();
    gc = new GameController(ui->difficultySlider->value());
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
