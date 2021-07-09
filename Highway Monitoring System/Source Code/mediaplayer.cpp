#include "mediaplayer.h"
#include "ui_mediaplayer.h"
#include <QDebug>

MediaPlayer::MediaPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MediaPlayer)
{
    ui->setupUi(this);
}

MediaPlayer::~MediaPlayer()
{
    delete ui;
}

void MediaPlayer::initialise(QString filePath)
{
    this->filePath = filePath;
    qDebug() << filePath;
    init();
}


void MediaPlayer::init()
{
    player = new QMediaPlayer(this);
    player->setMedia(QMediaContent(QUrl::fromLocalFile(filePath)));
    player->setVideoOutput(ui->videoWidget);
    player->play();
    connect(this->player, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(this->player, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);

    connect(ui->slider, &QSlider::sliderMoved, this->player, &QMediaPlayer::setPosition);

    connect(ui->playButton, &QAbstractButton::clicked, this, [=](){
        player->play();
    });
    connect(ui->pauseButton, &QAbstractButton::clicked, this, [=](){
       player->pause();
    });

}
