#include "sound.h"

QAudioFormat Sound::format;

// Credit to jordan9001, https://stackoverflow.com/questions/21310324/play-notification-frequency-x-sound-in-qt-easiest-way
void Sound::create_byte_array(){
    byte_array->resize(seconds * SAMPLE_RATE);

    for (int i = 0; i < (seconds * SAMPLE_RATE); i++) {
        qreal t = (qreal)(frequency * i);
        t = t * FREQ_CONST;
        t = qSin(t);
        // // now we normalize t           Didn't explain in post so idk
        // t *= TG_MAX_VAL;
        (*byte_array)[i] = (quint8)t;
    }
}

Sound::Sound(int num_sides) : frequency(200 + 10*(num_sides-2)), seconds(0.5), byte_array(new QByteArray()){

    create_byte_array();

    input = new QBuffer(byte_array);
    input->open(QIODevice::ReadOnly); // need to close later?

    audio = new QAudioOutput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handle_state_change(QAudio::State)));
}

void Sound::initialize_audio_format(){
    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleSize(8);
    //format.setCodec("audio/pcm");  idk
    // both below im not sure either
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioFormat::
}

void Sound::handle_state_change(QtAudio::State new_state){
    switch(new_state){
        case QAudio::IdleState:
            // Finished playing, reset
            audio->reset();
            break;
        case QAudio::StoppedState:
            qDebug() << audio->error();   // see https://doc.qt.io/qt-5/qaudio.html#Error-enum
            break;
    }
}

void Sound::play_sound(){
    audio->start(input);
}

void Sound::stop_sound(){
    audio->stop();
}
