#pragma once

#include <QtGlobal>

/*
 * WAVE PCM soundfile format (http://soundfile.sapp.org/doc/WaveFormat/)
 * WAVE = RIFF + fmt + data
*/

struct Chunk
{
    char        id[4];
    quint32     size;
};

struct RIFFHeader
{
    Chunk       descriptor;       // Contains the letters "RIFF" in ASCII form
    char        type[4];          // Contains the letters "WAVE"
};

/*
 * The "WAVE" format consists of two subchunks: "fmt " and "data":
 * The "fmt " subchunk describes the sound data's format:
*/

struct FMT
{
    Chunk       descriptor;         // Contains the letters "fmt ", size = 16 for PCM
    quint16     audioFormat;        // PCM = 1 (i.e. Linear quantization)
    quint16     numChannels;        // Mono = 1, Stereo = 2
    quint32     sampleRate;         // Sampling frequency. 8000 Hz, 44100 Hz, etc.
    quint32     byteRate;           // SampleRate * NumChannels * BitsPerSample / 8
    quint16     blockAlign;         // NumChannels * BitsPerSample / 8
    quint16     bitsPerSample;      // bits per sample and channel, (8 bits = 8, 16 bits = 16)
};

struct DATAHeader
{
    Chunk       descriptor;
};

struct CombinedHeader
{
    RIFFHeader  riff;
    FMT         wave;
};
