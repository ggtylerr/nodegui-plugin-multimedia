import { checkIfNativeElement, Component, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";
import { ChannelConfig, QAudioFormat, SampleFormat } from "./QAudioFormat";

/**
 * @summary The QAudioDevice class provides an information about audio
 * devices and their functionality.
 * 
 * @remarks QAudioDevice describes an audio device available in the 
 * system, either for input or for playback.
 * 
 * A QAudioDevice is used by Qt to construct classes that communicate 
 * with the device – such as {@link QAudioSource}, and 
 * {@link QAudioSink}. It is also used to determine the input or 
 * output device to use in a capture session or during media playback.
 * 
 * The QAudioDevice instance retains its properties throughout its 
 * lifetime, even if the corresponding physical device is disconnected
 * or its settings are modified. To keep track of updated properties,
 * the user should load new instances of QAudioDevice from 
 * {@link QMediaDevices} when the relevant signals are fired.
 * 
 * You can also query each device for the formats it supports. A
 * format in this context is a set consisting of a channel count,
 * sample rate, and sample type. A format is represented by the 
 * {@link QAudioFormat} class.
 * 
 * The values supported by the device for each of these parameters can
 * be fetched with 
 * {@link QAudioDevice.minimumChannelCount | minimumChannelCount()},
 * {@link QAudioDevice.maximumChannelCount | maximumChannelCount()},
 * {@link QAudioDevice.minimumSampleRate | minimumSampleRate()},
 * {@link QAudioDevice.maximumSampleRate | maximumSampleRate()} and
 * {@link QAudioDevice.supportedSampleFormats | supportedSampleFormats()}. 
 * The combinations supported are dependent on the audio device 
 * capabilities. If you need a specific format, you can check if the
 * device supports it with
 * {@link QAudioDevice.isFormatSupported | isFormatSupported()}. For 
 * instance:
 * 
 * @example
 * {
 *   const sourceFile = new QFile();
 *   sourceFile.setFileName("/tmp/test.raw");
 *   sourceFile.open(QIODevice.ReadOnly);
 *   
 *   const format = new QAudioFormat();
 *   // Set up the format, eg.
 *   format.setSampleRate(44100);
 *   format.setChannelCount(1);
 *   format.setSampleFormat(QAudioFormat.Int16);
 *   
 *   const info = QMediaDevices.defaultAudioOutput();
 *   if (!info.isFormatSupported(format)) {
 *     console.warn("Raw audio format not supported by backend, cannot play audio.");
 *     return;
 *   }
 *   
 *   const audio = new QAudioSink(format);
 *   audio.addEventListener("stateChanged", handleStateChanged);
 *   audio.start(sourceFile);
 * }
 * @remarks
 * The set of available devices can be retrieved from the 
 * {@link QMediaDevices} class.
 * 
 * For instance:
 * @example
 * const devices = QMediaDevices.audioOutputs();
 * for (const device in devices)
 *   console.log(`Device: ${device.description()}`);
 * @remarks
 * In this code sample, we loop through all devices that are able to
 * output sound, i.e., play an audio stream in a supported format. For
 * each device we find, we simply print the deviceName().
 * 
 * See also {@link QAudioSink}, {@link QAudioSource}, and
 * {@link QAudioFormat}.
 * @see https://doc.qt.io/qt-6/qaudiodevice.html for Qt's docs
 */
export class QAudioDevice extends Component {
    /**
     * The native C++ QAudioDevice variable.
     */
    declare native: NativeElement;
    /**
     * Constructs a null QAudioDevice object.
     */
    constructor();
    /**
     * Copy a native QAudioDevice to node bindings.
     * @param nativeElement A native QAudioDevice element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Constructs a copy of *{@link other}*.
     * @param other The QAudioDevice to copy/move from.
     */
    constructor(other: QAudioDevice);
    constructor(arg?: NativeElement | QAudioDevice) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QAudioDevice) {
            native = new addon.QAudioDevice(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QAudioDevice();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QAudioDevice::QAudioDevice()");
        }
        super(native);
    }
    /**
     * Returns the channel configuration of the device.
     * @returns The channel config of the device.
     */
    channelConfiguration(): ChannelConfig {
        return this.native.channelConfiguration();
    }
    /**
     * Returns a human readable name of the audio device.
     * 
     * Use this string to present the device to the user.
     * @returns The name of the device.
     */
    description(): string { return this.native.description(); }
    /**
     * Returns an identifier for the audio device.
     * 
     * Device names vary depending on the platform/audio plugin being
     * used.
     * 
     * They are a unique identifier for the audio device.
     * @returns An ID of the device.
     */
    id(): string { return this.native.id(); }
    /**
     * Returns true if this is the default audio device.
     * @returns Whether the device is default or not.
     */
    isDefault(): boolean { return this.native.isDefault(); }
    /**
     * Returns true if the supplied *{@link settings}* are supported 
     * by the audio device described by this {@link QAudioDevice}.
     * @param settings The format to test against.
     * @returns If the supplied format is supported.
     */
    isFormatSupported(settings: QAudioFormat): boolean {
        return this.native.isFormatSupported(settings);
    }
    /**
     * Returns whether this {@link QAudioDevice} object holds a valid
     * device definition.
     * @returns Whether this device holds a valid definition.
     */
    isNull(): boolean { return this.native.isNull(); }
    /**
     * Returns the maximum number of supported channel counts.
     * 
     * This is typically 1 for mono sound, or 2 for stereo sound.
     * @returns The max number of supported channel counts.
     */
    maximumChannelCount(): number { return this.native.maximumChannelCount(); }
    /**
     * Returns the maximum supported sample rate (in Hertz).
     * @returns The max supported sample rate in Hertz.
     */
    maximumSampleRate(): number { return this.native.maximumSampleRate(); }
    /**
     * Returns the minimum number of supported channel counts.
     * 
     * This is typically 1 for mono sound, or 2 for stereo sound.
     * @returns The min number of supported channel counts.
     */
    minimumChannelCount(): number { return this.native.minimumChannelCount(); }
    /**
     * Returns the minimum supported sample rate (in Hertz).
     * @returns The min supported sample rate in Hertz.
     */
    minimumSampleRate(): number { return this.native.minimumSampleRate(); }
    /**
     * Returns whether this device is an input or output device.
     * @returns The device mode.
     */
    mode(): Mode { return this.native.mode(); }
    /**
     * Returns the default audio format settings for this device.
     * 
     * These settings are provided by the platform/audio plugin being
     * used.
     * 
     * They are also dependent on the {@link QtAudio.Mode} being used.
     * 
     * A typical audio system would provide something like:
     * * Input settings: 48000Hz mono 16 bit.
     * * Output settings: 48000Hz stereo 16 bit.
     * @returns The default format settings for this device.
     */
    preferredFormat(): QAudioFormat { return this.native.preferredFormat(); }
    /**
     * Returns a list of supported sample types.
     * @returns An array of supported sample formats.
     */
    supportedSampleFormats(): SampleFormat[] {
        return this.native.supportedSampleFormats();
    }
    /**
     * Swaps the audio device with the *{@link other}*.
     * @param other The other audio device to swap contents with.
     */
    swap(other: QAudioDevice): void { this.native.swap(other); }
    /**
     * Returns true if this {@link QAudioDevice} class represents the
     * same audio device as *{@link other}*.
     * @param other The other audio device to test against.
     * @returns Whether this device is the same as the other one.
     */
    equals(other: QAudioDevice): boolean { return this.native.equals(other); }
}

/** Describes the mode of this device. */
export enum Mode {
    /** A null device. */
    Null = 0,
    /** An input device. */
    Input = 1,
    /** An output device. */
    Output = 2
}