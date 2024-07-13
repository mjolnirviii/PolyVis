#ifndef SOUND_H
#define SOUND_H

#include <QByteArray>
#include <QBuffer>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QtMath>
#include <QDebug>

class Sound : public QObject {

public:
    // different sound depending on number of sides, start at 200 hz, move by 10?
    Sound(int num_sides); // parent qobject parameter?

    static void initialize_audio_format();
    void play_sound();
    void stop_sound();

private:
    QByteArray* byte_array;
    QBuffer* input;
    QAudioOutput* audio;
    static QAudioFormat format;// const?

    static const int SAMPLE_RATE = 1000; // mess around
    static constexpr qreal FREQ_CONST = 2 * M_PI / SAMPLE_RATE;

    qreal frequency;
    qreal seconds; // i think not constant cause what if ball speed is super fast we might need to adjust

    void create_byte_array();

private slots:
    void handle_state_change(QAudio::State);

};

#endif // SOUND_H
