//
// Created by stefano on 2/7/19.
//

#include "source_diskmedia.h"
#include <string>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <zconf.h>
#include <random>

void listFiles(std::string path, std::string extension, std::vector<std::string> * ret, int rec) {
    if(rec == 0) return;

    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR)
                listFiles(path + f->d_name + "/", extension, ret, rec - 1);

            if (f->d_type == DT_REG)
                if(std::equal(extension.rbegin(), extension.rend(), std::string(f->d_name).rbegin())) ret->push_back(path + f->d_name);
        }
        closedir(dir);
    }
}

source_diskmedia::source_diskmedia() {}

void source_diskmedia::build_playlist(bool recursive, char * path, bool random){
    this->playlist.clear();
    listFiles(path, ".mp3", &(this->playlist), recursive ? 100 : 1);
    if(random){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(playlist.begin(), playlist.end(), g);
    }

    for(std::string i : this->playlist) std::cout << i << std::endl;
}

void source_diskmedia::init(){
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
}

void source_diskmedia::newSong(std::string path){
    /* open the file and get the decoding format */
    mpg123_open(mh, path.c_str());
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK && !stopPlaying){
        while(this->isPaused);
        ao_play(dev, (char *) (buffer), done);
    }
}


void source_diskmedia::play(){
    this->isPaused = 0;

    if(!isPlaying && this->playlist.size() != 0){
        isPlaying = 1;
        this->player = std::thread([](source_diskmedia * th){
            while(th->isPlaying) {
                th->stopPlaying = 0;
                th->newSong(th->playlist[th->current]);
                th->current = (th->current + 1) % th->playlist.size();
            }
        }, this);
    }
}

void source_diskmedia::pause(){
    this->isPaused = 1;
}

void source_diskmedia::next(){
    this->stopPlaying = 1;
}

void source_diskmedia::back(){
    this->current -= 2;
    if(current < 0) current = this->playlist.size() - 1;
    this->stopPlaying = 1;
}

void source_diskmedia::stop() {
    this->isPlaying = 0;
    this->stopPlaying = 1;
}

void source_diskmedia::restart(){
    this->current -= 1;
    this->stopPlaying = 1;
}
