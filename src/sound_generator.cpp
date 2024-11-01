#include "sound_generator.h"

sf::SoundBuffer SoundGenerator::createPitchedSound(float baseFrequency, float amplitude, float duration) {
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    
    const int sampleRate = 44100;
    const int numSamples = static_cast<int>(duration * sampleRate);
    
    for (int i = 0; i < numSamples; ++i) {
        float time = static_cast<float>(i) / sampleRate;
        float sample = amplitude * 32767.0f * std::sin(2.0f * M_PI * baseFrequency * time);
        samples.push_back(static_cast<sf::Int16>(sample));
    }
    
    buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate);
    return buffer;
}

float SoundGenerator::mapValueToFrequency(int value, int maxValue, float minFreq, float maxFreq) {
    float normalizedValue = static_cast<float>(value) / maxValue;
    return minFreq * std::pow(2, normalizedValue * std::log2(maxFreq / minFreq));
}

void SoundGenerator::initializeSoundBuffers(int maxValue) {
    soundBuffers.clear();
    for (int i = 1; i <= maxValue; ++i) {
        float frequency = mapValueToFrequency(i, maxValue);
        soundBuffers.push_back(createPitchedSound(frequency));
    }
}

void SoundGenerator::playSoundForValue(int value) {
    if (value > 0 && value <= soundBuffers.size()) {
        sound.setBuffer(soundBuffers[value - 1]);
        sound.play();
    }
}