#include "SoundGenerator.h"

SoundGenerator::SoundGenerator() : lastPlayTime(0.0f) {
    clock.restart();
}

SoundGenerator::~SoundGenerator() {
    cleanup();
}

sf::SoundBuffer SoundGenerator::createPitchedSound(float baseFrequency, float amplitude, float duration) {
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    
    const int sampleRate = 44100;
    const int numSamples = static_cast<int>(duration * sampleRate);
    
    // Add a small fade in/out to prevent clicking
    const int fadeLength = static_cast<int>(0.005f * sampleRate); // 5ms fade
    
    for (int i = 0; i < numSamples; ++i) {
        float time = static_cast<float>(i) / sampleRate;
        float fadeMultiplier = 1.0f;
        
        // Apply fade in/out
        if (i < fadeLength) {
            fadeMultiplier = static_cast<float>(i) / fadeLength;
        }
        else if (i > numSamples - fadeLength) {
            fadeMultiplier = static_cast<float>(numSamples - i) / fadeLength;
        }
        
        float sample = amplitude * fadeMultiplier * 32767.0f * 
                      std::sin(2.0f * M_PI * baseFrequency * time);
        samples.push_back(static_cast<sf::Int16>(sample));
    }
    
    buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate);
    return buffer;
}

float SoundGenerator::mapValueToFrequency(int value, int maxValue, float minFreq, float maxFreq) {
    // Using a higher minimum frequency to avoid bass-heavy sounds
    const float MIN_FREQ = 440.0f;   // A4 note
    const float MAX_FREQ = 1760.0f;  // A6 note
    
    // Linear mapping with slight exponential curve for better distribution
    float normalizedValue = static_cast<float>(value) / maxValue;
    float curvedValue = std::pow(normalizedValue, 1.2f); // Slightly curved distribution
    
    return MIN_FREQ + (MAX_FREQ - MIN_FREQ) * curvedValue;
}

void SoundGenerator::initializeSoundBuffers(int maxValue) {
    cleanup();
    soundBuffers.clear();
    
    for (int i = 1; i <= maxValue; ++i) {
        float frequency = mapValueToFrequency(i, maxValue);
        
        // Gentler amplitude adjustment
        float amplitude = 0.3f; // Lower base amplitude
        if (frequency > 1000.0f) {
            amplitude *= 0.8f; // Slight reduction for higher frequencies
        }
        
        soundBuffers.push_back(createPitchedSound(frequency, amplitude));
    }
}

void SoundGenerator::playSoundForValue(int value) {
    float currentTime = clock.getElapsedTime().asSeconds();
    if (currentTime - lastPlayTime < MIN_TIME_BETWEEN_SOUNDS) {
        return;
    }
    
    sound.stop();
    
    if (value > 0 && value <= soundBuffers.size()) {
        sound.setBuffer(soundBuffers[value - 1]);
        sound.play();
        lastPlayTime = currentTime;
    }
}

void SoundGenerator::stop() {
    sound.stop();
}

void SoundGenerator::cleanup() {
    stop();
    soundBuffers.clear();
}