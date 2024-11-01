#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H

#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>

class SoundGenerator {
private:
    std::vector<sf::SoundBuffer> soundBuffers;
    sf::Sound sound;

    // Private helper methods
    sf::SoundBuffer createPitchedSound(float baseFrequency, float amplitude = 0.5f, float duration = 0.1f);
    float mapValueToFrequency(int value, int maxValue, float minFreq = 220.0f, float maxFreq = 880.0f);

public:
    // Initialize sound buffers for all possible values
    void initializeSoundBuffers(int maxValue);

    // Play sound for a specific value
    void playSoundForValue(int value);
};

#endif // SOUND_GENERATOR_H