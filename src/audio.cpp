#include "audio.h"
#include <iostream>

#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"

namespace MS {

    Audio::Audio() {
        SDL_Init(SDL_INIT_AUDIO);

        SDL_AudioSpec spec;
        spec.format = SDL_AUDIO_S16;
        spec.channels = 2;
        spec.freq = 44100;

        _stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);

        if (_stream) {
            SDL_ResumeAudioStreamDevice(_stream);
        }
    }

    Audio::~Audio() {
        if (_stream) {
            SDL_DestroyAudioStream(_stream);
        }
        SDL_Quit();
    }

    void Audio::playMP3(const std::string filename) {
        if (!_stream) return;

        mp3dec_file_info_t info;
        mp3dec_t dec;
        if (mp3dec_load(&dec, filename.c_str(), &info, nullptr, nullptr) != 0 || !info.buffer) {
            std::cout << filename << std::endl;
            return;
        }

        size_t bytes = info.samples * sizeof(mp3d_sample_t);

        SDL_ClearAudioStream(_stream);
        if (SDL_PutAudioStreamData(_stream, info.buffer, static_cast<int>(bytes)) == 0) {
            std::cerr << "Failed to queue audio data for: " << filename << std::endl;
            free(info.buffer);
            return;
        }
        SDL_ResumeAudioStreamDevice(_stream);
    }

}
