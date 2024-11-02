#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H

#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>

class SoundGenerator {
private:
    std::vector<sf::SoundBuffer> soundBuffers;
    sf::Sound sound;
    float lastPlayTime;
    const float MIN_TIME_BETWEEN_SOUNDS = 0.05f; // 50ms minimum between sounds
    sf::Clock clock;

    sf::SoundBuffer createPitchedSound(float baseFrequency, float amplitude = 0.5f, float duration = 0.05f);
    float mapValueToFrequency(int value, int maxValue, float minFreq = 220.0f, float maxFreq = 880.0f);

public:
    SoundGenerator();
    ~SoundGenerator();
    void initializeSoundBuffers(int maxValue);
    void playSoundForValue(int value);
    void stop(); // Add a method to stop current sound
    void cleanup(); // Add cleanup method
};

#endif // SOUND_GENERATOR_H