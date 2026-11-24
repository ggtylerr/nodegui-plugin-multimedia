#include <napi.h>

#include "audio/qaudiobuffer_wrap.h"
#include "audio/qaudiobufferoutput_wrap.h"
#include "audio/qaudiodevice_wrap.h"
#include "audio/qaudioformat_wrap.h"
#include "audio/qaudiooutput_wrap.h"
#include "misc/qmediametadata_wrap.h"
#include "misc/qmediatimerange_wrap.h"
#include "playback/qmediaplayer_wrap.h"
#include "playback/qplaybackoptions_wrap.h"
#include "video/qabstractvideobuffer_wrap.h"
#include "video/qvideoframe_wrap.h"
#include "video/qvideoframeformat_wrap.h"
#include "video/qvideosink_wrap.h"
#include "widgets/qvideowidget_wrap.h"

Napi::Object Main(Napi::Env env, Napi::Object exports) {\
    // Audio
    QAudioBufferWrap::init(env, exports);
    QAudioBufferOutputWrap::init(env, exports);
    QAudioDeviceWrap::init(env, exports);
    QAudioFormatWrap::init(env, exports);
    QAudioOutputWrap::init(env, exports);
    // Misc
    QMediaMetaDataWrap::init(env, exports);
    QMediaTimeRangeWrap::init(env, exports);
    // Playback
    QMediaPlayerWrap::init(env, exports);
    QPlaybackOptionsWrap::init(env, exports);
    // Video
    QAbstractVideoBufferWrap::init(env, exports);
    QVideoFrameWrap::init(env, exports);
    QVideoFrameFormatWrap::init(env, exports);
    QVideoSinkWrap::init(env, exports);
    // Widgets
    QVideoWidgetWrap::init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
