#ifndef ALSA_MANAGER
#define ALSA_MANAGER

#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

typedef enum {
    AUDIO_VOLUME_SET,
    AUDIO_VOLUME_GET,
} audio_volume_action;
int alsaVolume(audio_volume_action action, long* outvol);



#endif // ALSA_MANAGER

