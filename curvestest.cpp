#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thing.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

#include <iostream>
#include <string>
#include <cstdio>

void SaveFramesFromVideo(const std::string &videoFilePath, const std::string &outputPrefix) {
    AVFormatContext *formatContext = nullptr;
    AVCodecContext *codecContext = nullptr;
    AVFrame *frame = nullptr;
    AVFrame *frameRGB = nullptr;
    uint8_t *buffer = nullptr;
    struct SwsContext *swsContext = nullptr;

    // Initialize FFmpeg
    if (avformat_open_input(&formatContext, videoFilePath.c_str(), nullptr, nullptr) != 0) {
        std::cerr << "Could not open video file." << std::endl;
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        std::cerr << "Could not find stream info." << std::endl;
        return;
    }

    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        std::cerr << "Could not find a video stream." << std::endl;
        return;
    }

    AVCodecParameters *codecParameters = formatContext->streams[videoStreamIndex]->codecpar;
    const AVCodec *codec = avcodec_find_decoder(codecParameters->codec_id);
    if (!codec) {
        std::cerr << "Codec not found." << std::endl;
        return;
    }

    codecContext = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        std::cerr << "Could not copy codec parameters." << std::endl;
        return;
    }

    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        std::cerr << "Could not open codec." << std::endl;
        return;
    }

    frame = av_frame_alloc();
    frameRGB = av_frame_alloc();

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 32);
    buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 32);

    swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt,
                                codecContext->width, codecContext->height, AV_PIX_FMT_RGB24,
                                SWS_BILINEAR, nullptr, nullptr, nullptr);

    AVPacket packet;
    int frameCount = 0;

    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == videoStreamIndex) {
            if (avcodec_send_packet(codecContext, &packet) == 0) {
                while (avcodec_receive_frame(codecContext, frame) == 0) {
                    sws_scale(swsContext, (const uint8_t *const *)frame->data, frame->linesize, 0, codecContext->height, frameRGB->data, frameRGB->linesize);

                    std::string filename = outputPrefix + std::to_string(frameCount++) + ".png";
                    stbi_write_png(filename.c_str(), codecContext->width, codecContext->height, 3, frameRGB->data[0], frameRGB->linesize[0]);
                    std::cout << "Saved frame: " << filename << std::endl;
                }
            }
        }
        av_packet_unref(&packet);
    }

    av_free(buffer);
    av_frame_free(&frameRGB);
    av_frame_free(&frame);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);

    std::cout << "Finished extracting frames." << std::endl;
}

int main() {
    SaveFramesFromVideo("video.mp4", "frame_");
    return 0;
}
