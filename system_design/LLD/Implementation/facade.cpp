/*
Link: https://refactoring.guru/design-patterns/facade


Same Video Conversion example
*/



#include<bits/stdc++.h>

using namespace std;

//some third party video library
class VideoFile {
    public:
        string name;
        VideoFile(string _name) {
            this->name = _name;
        }
        virtual ~VideoFile() {}
};

class VideoCodec {
    public:
        VideoCodec() {}
        virtual string compressedCodecFormat() = 0;
};

class MPEG4CompressionCodec : public VideoCodec {
    public:
        MPEG4CompressionCodec() {}
        string compressedCodecFormat() override {
            return "MPEG4CompressionCodec";
        }
};

class OggCompressionCodec : public VideoCodec {
    public:
        OggCompressionCodec() {}
        // some more complex logic
        string compressedCodecFormat() override {
            return "OggCompressionCodec";
        }
};

class CodecFactory {
    public:
        CodecFactory() {}
        string extract() {
            cout<<"Extraction Done"<<endl;
            return "source codec";
        }
};

class BitrateReader {
    public:
        static string read(string filename, string sourceCodec) {
            cout<<"Bitrate Reader read the file with name "<<filename<<" with codec "<<sourceCodec<<endl;
            return "filename: " + filename + " codex: " + sourceCodec;
        }

        static string convert(string buffer, VideoCodec* codec) {
            string newCodec = codec->compressedCodecFormat();
            cout<<"BItrate Reader conversion done"<<endl;
            return buffer + " converted to " + newCodec;
        }

};

class AudioMixer {
    public:
        void fix() {
            cout<<"Audio Mixer fixed the audio of new file"<<endl;
        }
};

class VideoConverterFacade {
    public:
        VideoFile* convert(string filename, string format) {
            VideoFile* file = new VideoFile(filename);
            string sourceCodec = CodecFactory().extract();
            VideoCodec* destinationCodec;
            if(format == "mp4")
                destinationCodec = new MPEG4CompressionCodec();
            else
                destinationCodec = new OggCompressionCodec();
            string buffer = BitrateReader::read(filename, sourceCodec);
            string result = BitrateReader::convert(buffer, destinationCodec);
            AudioMixer* audioMixer = new AudioMixer();
            audioMixer->fix();

            delete destinationCodec;
            delete audioMixer;

            return new VideoFile(result);
        }

        void save(VideoFile* file) {
            cout<<"File saved with details: "<<file->name<<endl;
        }
};

int main() {
    VideoConverterFacade* convFacade = new VideoConverterFacade();
    VideoFile* file = convFacade->convert("funny-cats-video.ogg", "mp4");
    convFacade->save(file);
    return 0;
}