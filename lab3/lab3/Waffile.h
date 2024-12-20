#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

namespace Waf {

    // Структура для хранения заголовка WAV-файла
    struct WavHeader {
        char riff[4];             // "RIFF"
        uint32_t fileSize;        // Размер файла минус 8 байт
        char wave[4];             // "WAVE"
        char fmt[4];              // "fmt "
        uint32_t fmtSize;         // Размер fmt-блока (16 для PCM)
        uint16_t audioFormat;     // Формат аудио (1 для PCM)
        uint16_t numChannels;     // Количество каналов
        uint32_t sampleRate;      // Частота дискретизации
        uint32_t byteRate;        // Байт/сек
        uint16_t blockAlign;      // Блок выравнивания
        uint16_t bitsPerSample;   // Бит на сэмпл
        char data[4];             // "data"
        uint32_t dataSize;        // Размер данных
    };

    class WavFile { // Класс для работы с WAV-файлами
    public:
        WavFile();
        ~WavFile();

        void load(const std::string& filename); // Загрузка WAV-файла
        void save(const std::string& filename); // Сохранение WAV-файла
        std::vector<int16_t>& getData();        // Получение данных аудио

        uint32_t getSampleRate() const;         // Получение частоты дискретизации
        uint16_t getNumChannels() const;        // Получение количества каналов
        uint16_t getBitsPerSample() const;      // Получение бит на сэмпл

    private:
        std::vector<int16_t> data;              
        uint32_t sampleRate;                    // Частота дискретизации
        uint16_t numChannels;                   // Количество каналов
        uint16_t bitsPerSample;                 // Бит на сэмпл
    };

    class Converter { // Базовый класс для конвертеров
    public:
        virtual void setParameters(const std::vector<std::string>& params) = 0;
        virtual std::vector<int16_t> convert(const std::vector<int16_t>& input, uint32_t sampleRate) = 0;
    };

}