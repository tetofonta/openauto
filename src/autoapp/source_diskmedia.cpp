//
// Created by stefano on 2/7/19.
//

#include <source_diskmedia.h>
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

source_diskmedia::source_diskmedia(QLabel * title, QLabel * artist, QLabel * album) {
    this->title = title;
    this->artist = artist;
    this->album = album;
    std::cout << "aaaaaaaaaaaaaaaa" << std::endl;
}

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
    
    char bbuffer[100];
    sprintf(bbuffer, "<html><head/><body><p><span style=\" font-size:28pt; font-weight:600;\">%s</span></p></body></html>", path.c_str());
    this->title->setText(bbuffer);
    sprintf(bbuffer, "<html><head/><body><p><span style=\" font-size:18pt; \">%s</span></p></body></html>", path.c_str());
    this->artist->setText(bbuffer);
    sprintf(bbuffer, "<html><head/><body><p><span style=\" font-size:26pt; font-weight:600;\">%s</span></p></body></html>", path.c_str());
    this->album->setText(bbuffer);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    mpg123_seek(mh, 0, SEEK_END);
    int total = mpg123_tell(mh);
    mpg123_seek(mh, 0, SEEK_SET);

    int prev = 0;

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK && !stopPlaying){
        while(this->isPaused){
            std::cout << "still paused" << std::endl;
            usleep(500000);
        }
        ao_play(dev, (char *) (buffer), done);
        int current = mpg123_tell(mh);
        if((int)(((float)current/(float)total)*100.0f) != prev){
            prev = (int)(((float)current/(float)total)*100.0f) != prev;
        }
    }
}


void source_diskmedia::play(){
    this->isPaused = 0;

    if(!isPlaying && this->playlist.size() != 0){
        isPlaying = 1;
        this->player = std::thread([](source_diskmedia * th){
            while(th->isPlaying) {
                std::cout << "aa" << std::endl;
                th->stopPlaying = 0;
                std::cout << "aa" << std::endl;
                th->newSong(th->playlist[th->current]);
                std::cout << "aa" << std::endl;
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

/*int main(){
    source_diskmedia a = source_diskmedia();
    a.init();
    a.build_playlist(true, "/media/pi/", true);

    while(1){
        int q;
        scanf("%d", &q);
        switch (q){
            case 0:
                a.play();
                break;
            case 1:
                a.pause();
                break;
            case 2:
                a.next();
                break;
            case 3:
                a.back();
        }
    }
    return 0;
}*/
