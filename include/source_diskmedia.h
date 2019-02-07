//
// Created by stefano on 2/7/19.
//

#ifndef OPENAUTO_SOURCE_DISKMEDIA_H
#define OPENAUTO_SOURCE_DISKMEDIA_H


#include <vector>
#include <string>
#include <ao/ao.h>
#include <mpg123.h>
#include <thread>

class source_diskmedia {

    std::vector<std::string> playlist;

    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    std::thread player;
    int isPlaying = 0;
    int isPaused = 1;
    int stopPlaying = 0;
    int current = 0;

    void newSong(std::string path);

public:
    source_diskmedia();

    void build_playlist(bool recursive, char *path, bool random);

    void init();

    void play();

    void pause();

    void next();

    void back();

    void stop();

    void restart();
;

};


#endif //OPENAUTO_SOURCE_DISKMEDIA_H
