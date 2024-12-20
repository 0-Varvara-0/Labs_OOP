#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <memory>
#include "Waffile.h"

using namespace Waf;

WavFile::WavFile() : sampleRate(44100), numChannels(1), bitsPerSample(16) {}
WavFile::~WavFile() {}

void WavFile::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    // Читаем заголовок WAV-файла
    WavHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Сохраняем параметры заголовка
    sampleRate = header.sampleRate;
    numChannels = header.numChannels;
    bitsPerSample = header.bitsPerSample;

    // Пропускаем заголовок и читаем данные
    data.clear();
    int16_t sample;
    while (file.read(reinterpret_cast<char*>(&sample), sizeof(sample))) {
        data.push_back(sample);
    }
}

void WavFile::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }

    // Записываем заголовок WAV-файла
    WavHeader header;
    std::memcpy(header.riff, "RIFF", 4);
    std::memcpy(header.wave, "WAVE", 4);
    std::memcpy(header.fmt, "fmt ", 4);
    std::memcpy(header.data, "data", 4);

    header.fmtSize = 16;
    header.audioFormat = 1; // PCM
    header.numChannels = numChannels;
    header.sampleRate = sampleRate;
    header.bitsPerSample = bitsPerSample;
    header.byteRate = sampleRate * numChannels * (bitsPerSample / 8);
    header.blockAlign = numChannels * (bitsPerSample / 8);
    header.dataSize = data.size() * sizeof(int16_t);
    header.fileSize = header.dataSize + sizeof(WavHeader) - 8;

    file.write(reinterpret_cast<char*>(&header), sizeof(header));

    // Записываем данные
    for (const auto& sample : data) {
        file.write(reinterpret_cast<const char*>(&sample), sizeof(sample));
    }
}

std::vector<int16_t>& WavFile::getData() {
    return data;
}

uint32_t WavFile::getSampleRate() const {
    return sampleRate;
}

uint16_t WavFile::getNumChannels() const {
    return numChannels;
}

uint16_t WavFile::getBitsPerSample() const {
    return bitsPerSample;
}

// Mute converter

class MuteConverter : public Converter {
public:
    void setParameters(const std::vector<std::string>& params) override;
    std::vector<int16_t> convert(const std::vector<int16_t>& input, uint32_t sampleRate) override;

private:
    int start;
    int end;
};

void MuteConverter::setParameters(const std::vector<std::string>& params) {
    std::istringstream ss1(params[0]);
    std::istringstream ss2(params[1]);
    ss1 >> start;
    ss2 >> end;
}

std::vector<int16_t> MuteConverter::convert(const std::vector<int16_t>& input, uint32_t sampleRate) {
    std::vector<int16_t> output = input;
    int startSample = start * sampleRate;
    int endSample = end * sampleRate;

    for (int i = startSample; i < endSample; ++i) {
        if (i < output.size()) {
            output[i] = 0;
        }
    }
    return output;
}

// Mixer converter

class MixerConverter : public Converter {
public:
    void setParameters(const std::vector<std::string>& params) override;
    std::vector<int16_t> convert(const std::vector<int16_t>& input, uint32_t sampleRate) override;

private:
    int insertPosition;
    std::vector<int16_t> additionalStream;
};

void MixerConverter::setParameters(const std::vector<std::string>& params) {
    std::istringstream ss1(params[0]);
    ss1 >> insertPosition;

    // Загружаем дополнительный поток из файла
    std::ifstream file(params[1], std::ios::binary);
    file.seekg(44); // Пропускаем заголовок WAV файла
    int16_t sample;
    additionalStream.clear();
    while (file.read(reinterpret_cast<char*>(&sample), sizeof(sample))) {
        additionalStream.push_back(sample);
    }
}

std::vector<int16_t> MixerConverter::convert(const std::vector<int16_t>& input, uint32_t sampleRate) {
    std::vector<int16_t> output = input;
    int insertSample = insertPosition * sampleRate;

    for (size_t i = 0; i < additionalStream.size() && insertSample + i < output.size(); ++i) {
        output[insertSample + i] = (output[insertSample + i] + additionalStream[i]) / 2; // Смешиваем
    }

    return output;
}

// Parser

class ConfigParser {
public:
    ConfigParser(const std::string& filename);
    std::vector<std::pair<std::string, std::vector<std::string>>> parse();

private:
    std::string _filename;
};

ConfigParser::ConfigParser(const std::string& filename) : _filename(filename) {}

std::vector<std::pair<std::string, std::vector<std::string>>> ConfigParser::parse() {
    std::ifstream file(_filename);
    std::vector<std::pair<std::string, std::vector<std::string>>> commands;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        std::vector<std::string> params;
        std::string param;
        while (iss >> param) {
            params.push_back(param);
        }

        commands.emplace_back(command, params);
    }

    return commands;
}

int main() {
    WavFile wav;
    wav.load("input.wav");

    ConfigParser parser("config.txt");
    auto commands = parser.parse();

    std::unique_ptr<Converter> converter;

    for (const auto& c : commands) {
        if (c.first == "mute") {
            converter = std::make_unique<MuteConverter>();
        }
        else if (c.first == "mix") {
            converter = std::make_unique<MixerConverter>();
        }

        converter->setParameters(c.second);
        wav.getData() = converter->convert(wav.getData(), wav.getSampleRate());
    }

    wav.save("output.wav");
    return 0;
}