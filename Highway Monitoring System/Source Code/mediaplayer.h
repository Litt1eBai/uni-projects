#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QProgressBar>
#include <QWindow>
#include <QSlider>

namespace Ui {
class MediaPlayer;
}

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();

    void initialise(QString filePath);

private:
    void init();

private:
    Ui::MediaPlayer *ui;

    QString filePath;
    QMediaPlayer *player;

};

#endif // MEDIAPLAYER_H
