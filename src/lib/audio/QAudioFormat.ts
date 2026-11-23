import { checkIfNativeElement, Component, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";

/**
 * @summary The QAudioFormat class stores audio stream parameter 
 * information.
 * 
 * @remarks
 * An audio format specifies how data in a raw audio stream is
 * arranged. For example, how the stream is to be interpreted.
 * 
 * QAudioFormat contains parameters that specify how the audio sample
 * data is arranged. These are the frequency, the number of channels,
 * and the sample format. The following table describes these in more
 * detail.
 * 
 * Parameter | Description
 * ----------|------------
 * Sample Rate | Samples per second of audio data in Hertz.
 * Number of channels | The number of audio channels (typically one for mono or two for stereo). These are the amount of consecutive samples that together form one frame in the stream
 * Sample format | The format of the audio samples in the stream
 * 
 * This class is used in conjunction with {@link QAudioSource} or 
 * {@link QAudioSink} to allow you to specify the parameters of the
 * audio stream being read or written, or with {@link QAudioBuffer}
 * when dealing with samples in memory.
 * 
 * ou can obtain audio formats compatible with the audio device used
 * through functions in {@link QAudioDevice}. This class also lets you
 * query available parameter values for a device, so that you can set
 * the parameters yourself. See the {@link QAudioDevice} class
 * description for details. You need to know the format of the audio
 * streams you wish to play or record.
 * 
 * Samples for all channels will be interleaved. One sample for each
 * channel for the same instant in time is referred to as a frame in
 * Qt Multimedia (and other places).
 */
export class QAudioFormat extends Component {
    /**
     * The native C++ QAudioFormat variable.
     */
    declare native: NativeElement;
    /**
     * Constructs a new audio format.
     * 
     * Values are initialized as follows:
     * * {@link QAudioFormat.sampleRate | sampleRate()} = 0
     * * {@link QAudioFormat.channelCount | channelCount()} = 0
     * * {@link QAudioFormat.sampleFormat | sampleFormat()} = 
     * {@link SampleFormat.Unknown}
     */
    constructor();
    /**
     * Copy a native QAudioFormat to node bindings.
     * @param nativeElement A native QAudioFormat element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Constructs a new audio format using *{@link other}*.
     * @param other The QAudioFormat to copy/move from.
     */
    constructor(other: QAudioFormat);
    constructor(arg?: NativeElement | QAudioFormat) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QAudioFormat) {
            native = new addon.QAudioFormat(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QAudioFormat();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QAudioFormat::QAudioFormat()");
        }
        super(native);
    }
    /**
     * Returns the number of bytes required for this audio format for
     * *{@link microseconds}*.
     * 
     * Returns 0 if this format is not valid.
     * 
     * Note that some rounding may occur if *{@link microseconds}* is
     * not an exact fraction of the
     * {@link QAudioFormat.sampleRate | sampleRate()}.
     * 
     * @see also {@link QAudioFormat.durationForBytes | durationForBytes()}.
     * @param microseconds The duration in microseconds.
     * @returns The number of bytes required for the duration.
     */
    bytesForDuration(microseconds: number): number {
        return this.native.bytesForDuration(microseconds); 
    }
    /**
     * Returns the number of bytes required for
     * *{@link frameCount}* frames of this format.
     * 
     * Returns 0 if this format is not valid.
     * 
     * @see also {@link QAudioFormat.bytesForDuration | bytesForDuration()}.
     * @param frameCount The number of frames.
     * @returns The number of bytes required for the # of frames.
     */
    bytesForFrames(frameCount: number): number {
        return this.native.bytesForFrames(frameCount); 
    }
    /**
     * Returns the number of bytes required to represent one frame
     * (a sample in each channel) in this format.
     * 
     * Returns 0 if this format is invalid.
     * @returns The number of bytes required for one frame.
     */
    bytesPerFrame(): number { return this.native.bytesPerFrame(); }
    /**
     * Returns the number of bytes required to represent one sample in
     * this format.
     * 
     * Returns 0 if this format is invalid.
     * @returns The number of bytes required for one sample.
     */
    bytesPerSample(): number { return this.native.bytesPerSample(); }
    /**
     * Returns the current channel configuration.
     * 
     * @see also {@link QAudioFormat.setChannelConfig | setChannelConfig()}.
     * @returns The current channel config.
     */
    channelConfig(): ChannelConfig { return this.native.channelConfig(); }
    /**
     * Returns the current channel count value.
     * 
     * @see also {@link QAudioFormat.setChannelCount | setChannelCount()}.
     * @returns The current channel count.
     */
    channelCount(): number { return this.native.channelCount(); }
    /**
     * Returns the position of a certain audio *{@link channel}*
     * inside an audio frame for the given format. Returns -1 if the
     * channel does not exist for this format or the channel
     * configuration is unknown.
     * @param channel An audio channel position.
     * @returns The offset position of an audio channel.
     */
    channelOffset(channel: AudioChannelPosition): number {
        return this.native.channelOffset(channel);
    }
    /**
     * Returns the number of microseconds represented by 
     * *{@link bytes}* in this format.
     * 
     * Returns 0 if this format is not valid.
     * 
     * Note that some rounding may occur if *{@link bytes}* is not an
     * exact multiple of the number of bytes per frame.
     * 
     * @see also {@link QAudioFormat.bytesForDuration | bytesForDuration()}.
     * @param bytes The amount of raw bytes.
     * @returns The number of microseconds for the # of bytes.
     */
    durationForBytes(bytes: number): number {
        return this.native.durationForBytes(bytes);
    }
    /**
     * Return the number of microseconds represented by 
     * *{@link frameCount}* frames in this format.
     * @param frameCount The number of frames.
     * @returns The number of microseconds for the # of frames.
     */
    durationForFrames(frameCount: number): number {
        return this.native.durationForFrames(frameCount);
    }
    /**
     * Returns the number of frames represented by *{@link byteCount}*
     * in this format.
     * 
     * Note that some rounding may occur if *{@link byteCount}* is not
     * an exact multiple of the number of bytes per frame.
     * 
     * Each frame has one sample per channel.
     * 
     * @see also {@link QAudioFormat.framesForDuration | framesForDuration()}.
     * @param byteCount The amount of raw bytes.
     * @returns The number of frames for the # of bytes.
     */
    framesForBytes(byteCount: number): number {
        return this.native.framesForBytes(byteCount);
    }
    /**
     * Returns the number of frames required to represent 
     * {@link microseconds} in this format.
     * 
     * Note that some rounding may occur if {@link microseconds} is
     * not an exact fraction of the 
     * {@link QAudioFormat.sampleRate | sampleRate()}.
     * @param microseconds The duration in microseconds.
     * @returns The number of frames for a duration of time.
     */
    framesForDuration(microseconds: number): number {
        return this.native.framesForBytes(microseconds);
    }
    /**
     * Returns true if all of the parameters are valid.
     * @returns Whether the format's parameters are valid or not.
     */
    isValid(): boolean { return this.native.isValid(); }
    /**
     * Normalizes the *{@link sample}* value to a number between -1
     * and 1. The method depends on the {@link QAudioFormat}.
     * @param sample The sample value to normalize.
     * @returns A normalized sample value, between -1 and 1.
     */
    normalizedSampleValue(sample: number): number {
        return this.native.normalizedSampleValue(sample);
    }
    /**
     * Returns the current sample format.
     * 
     * @see also {@link QAudioFormat.setSampleFormat | setSampleFormat()}.
     * @returns The current sample format.
     */
    sampleFormat(): number { return this.native.sampleFormat(); }
    /**
     * Returns the current sample rate in Hertz.
     * 
     * @see also {@link QAudioFormat.setSampleRate | setSampleRate()}.
     * @returns The current sample rate.
     */
    sampleRate(): number { return this.native.sampleRate(); }
    /**
     * Sets the channel configuration to *{@link config}*.
     * 
     * Sets the channel configuration of the audio format to one of
     * the standard audio channel configurations.
     * 
     * > **Note:** that this will also modify the channel count.
     * 
     * @see also {@link QAudioFormat.channelConfig | channelConfig()}.
     * @param config The channel config to set the format to.
     */
    setChannelConfig(config: ChannelConfig): void {
        return this.native.setChannelConfig(config);
    }
    /**
     * Sets the channel count to *{@link channels}*. Setting this also
     * sets the channel config to 
     * {@link ChannelConfig.ChannelConfigUnknown | ChannelConfigUnknown}.
     * @see also {@link QAudioFormat.channelCount | channelCount()}.
     * @param channels The channel count to set the format to.
     */
    setChannelCount(channels: number): void {
        return this.native.setChannelCount(channels);
    }
    /**
     * Sets the sample format to *{@link format}*.
     * 
     * @see also {@link QAudioFormat.sampleFormat | sampleFormat()} 
     * and {@link SampleFormat}.
     * @param format The sample format to set the format to.
     */
    setSampleFormat(format: SampleFormat): void {
        return this.native.setSampleFormat(format);
    }
    /**
     * Sets the sample rate to *{@link sampleRate}* in Hertz.
     * @param sampleRate The sample rate to set the format to.
     */
    setSampleRate(sampleRate: number): void {
        return this.native.setSampleRate(sampleRate);
    }
    /**
     * Returns true if audio format *a* is equal to *b*, otherwise
     * returns false.
     * @param other The other format is test against.
     * @returns Whether this format is the equal to the other one.
     */
    equals(other: QAudioFormat): boolean { return this.native.equals(other); }
    /**
     * Returns a default channel configuration for 
     * *{@link channelCount}*.
     * 
     * Default configurations are defined for up to 8 channels, and
     * correspond to standard Mono, Stereo, and Surround
     * configurations. For higher channel counts, this simply uses the
     * first *{@link channelCount}* audio channels defined in
     * {@link AudioChannelPosition}.
     * @param channelCount The amount of channels.
     * @returns A default channel config for the channel count.
     */
    static defaultChannelConfigForChannelCount(channelCount: number): ChannelConfig {
        return addon.QAudioFormat.defaultChannelConfigForChannelCount(channelCount);
    }
}

/**
 * Describes the possible audio channel positions. These follow the
 * standard definition used in the 22.2 surround sound configuration.
 */
export enum AudioChannelPosition {
    /** Unknown position */
    UnknownPosition = 0,
    FrontLeft = 1,
    FrontRight = 2,
    FrontCenter = 3,
    /** Low Frequency Effect channel (Subwoofer) */
    LFE = 4,
    BackLeft = 5,
    BackRight = 6,
    FrontLeftOfCenter = 7,
    FrontRightOfCenter = 8,
    BackCenter = 9,
    LFE2 = 19,
    SideLeft = 10,
    SideRight = 11,
    TopFrontLeft = 13,
    TopFrontRight = 15,
    TopFrontCenter = 14,
    TopCenter = 12,
    TopBackLeft = 16,
    TopBackRight = 18,
    TopSideLeft = 20,
    TopSideRight = 21,
    TopBackCenter = 17,
    BottomFrontCenter = 22,
    BottomFrontLeft = 23,
    BottomFrontRight = 24,
}

/**
 * This enum describes a standardized audio channel layout. The most
 * common configurations are Mono, Stereo, 2.1 (stereo plus low
 * frequency), 5.1 surround, and 7.1 surround configurations.
 */
export enum ChannelConfig {
    /** The channel configuration is not known. */
    ChannelConfigUnknown = 0,
    /** The audio has one center channel. */
    ChannelConfigMono = 1 << AudioChannelPosition.FrontCenter,
    /** The audio has two channels, left and right. */
    ChannelConfigStereo = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight),
    /** 
     * The audio has three channels, left, right and LFE 
     * (low frequency effect). 
     */
    ChannelConfig2Dot1 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.LFE),
    /** The audio has three channels, left, right, and center. */
    ChannelConfig3Dot0 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter),
    /**
     * The audio has four channels, left, right, center, and LFE 
     * (low frequency effect).
     */
    ChannelConfig3Dot1 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter) |
        (1 << AudioChannelPosition.LFE),
    /**
     * The audio has five channels, left, right, center, 
     * {@link AudioChannelPosition.BackLeft | BackLeft}, and 
     * {@link AudioChannelPosition.BackRight | BackRight}.
     */
    ChannelConfigSurround5Dot0 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter) |
        (1 << AudioChannelPosition.BackLeft) |
        (1 << AudioChannelPosition.BackRight),
    /**
     * The audio has 6 channels, left, right, center, LFE,
     * {@link AudioChannelPosition.BackLeft | BackLeft}, and 
     * {@link AudioChannelPosition.BackRight | BackRight}.
     */
    ChannelConfigSurround5Dot1 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter) |
        (1 << AudioChannelPosition.LFE) |
        (1 << AudioChannelPosition.BackLeft) |
        (1 << AudioChannelPosition.BackRight),
    /**
     * The audio has 7 channels, left, right, center, 
     * {@link AudioChannelPosition.BackLeft | BackLeft}, 
     * {@link AudioChannelPosition.BackRight | BackRight},
     * {@link AudioChannelPosition.SideLeft | SideLeft}, and
     * {@link AudioChannelPosition.SideRight | SideRight}.
     */
    ChannelConfigSurround7Dot0 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter) |
        (1 << AudioChannelPosition.BackLeft) |
        (1 << AudioChannelPosition.BackRight) |
        (1 << AudioChannelPosition.SideLeft) |
        (1 << AudioChannelPosition.SideRight),
    /**
     * The audio has 8 channels, left, right, center, LFE,
     * {@link AudioChannelPosition.BackLeft | BackLeft}, 
     * {@link AudioChannelPosition.BackRight | BackRight},
     * {@link AudioChannelPosition.SideLeft | SideLeft}, and
     * {@link AudioChannelPosition.SideRight | SideRight}.
     */
    ChannelConfigSurround7Dot1 = 
        (1 << AudioChannelPosition.FrontLeft) |
        (1 << AudioChannelPosition.FrontRight) |
        (1 << AudioChannelPosition.FrontCenter) |
        (1 << AudioChannelPosition.LFE) |
        (1 << AudioChannelPosition.BackLeft) |
        (1 << AudioChannelPosition.BackRight) |
        (1 << AudioChannelPosition.SideLeft) |
        (1 << AudioChannelPosition.SideRight),
}

/**
 * Qt will always expect and use samples in the endianness of the host
 * platform. When processing audio data from external sources 
 * yourself, ensure you convert them to the correct endianness before
 * writing them to a {@link QAudioSink} or {@link QAudioBuffer}.
 */
export enum SampleFormat {
    /** Not Set */
    Unknown = 0,
    /** Samples are 8 bit unsigned integers */
    UInt8 = 1,
    /** Samples are 16 bit signed integers */
    Int16 = 2,
    /** Samples are 32 bit signed integers */
    Int32 = 3,
    /** Samples are floats */
    Float = 4,
}