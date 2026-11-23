import { checkIfNativeElement, Component, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QAudioFormat } from "./QAudioFormat";

/**
 * @summary The QAudioBuffer class represents a collection of audio 
 * samples with a specific format and sample rate.
 * 
 * @remarks 
 * QAudioBuffer is used by the {@link QAudioDecoder} class to hand 
 * decoded audio data over to the application. An audio buffer 
 * contains data in a certain {@link QAudioFormat} that can be queried 
 * using {@link QAudioBuffer.format | format()}. It is also tagged 
 * with timing and duration information.
 * 
 * To access the data stored inside the buffer, use the 
 * {@link QAudioBuffer.data | data()} or 
 * {@link QAudioBuffer.constData | constData()} methods.
 * 
 * Audio buffers are explicitly shared, in most cases, you should 
 * call {@link QAudioBuffer.detach | detach()} before modifying the 
 * data.
 * 
 * @see https://doc.qt.io/qt-6/qaudiobuffer.html for Qt's Docs
 */
export class QAudioBuffer extends Component {
    /**
     * The native C++ QAudioBuffer variable.
     */
    declare native: NativeElement;
    /**
     * Create a new, empty, invalid buffer.
     */
    constructor();
    /**
     * Copy a native QAudioBuffer to node bindings.
     * @param nativeElement A native QAudioBuffer element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Creates a new audio buffer from *{@link other}*. Audio buffers 
     * are explicitly shared, you should call 
     * {@link QAudioBuffer.detach | detach()} on the buffer to make a 
     * copy that can then be modified.
     * @param other The audio buffer to copy/move from.
     */
    constructor(other: QAudioBuffer);
    /**
     * Creates a new audio buffer from the supplied *{@link data}*, in 
     * the given *{@link format}*. The format will determine how the 
     * number and sizes of the samples are interpreted from the data.
     * 
     * If the supplied data is not an integer multiple of the 
     * calculated frame size, the excess data will not be used.
     * 
     * This audio buffer will copy the contents of data.
     * 
     * *{@link startTime}* (in microseconds) indicates when this 
     * buffer starts in the stream. If this buffer is not part of a 
     * stream, set it to -1.
     * @param data The raw audio sample data.
     * @param format The audio format used to interpret data.
     * @param startTime The time this buffer starts at in the stream, 
     * measured in microseconds. Default is -1.
     */
    constructor(data: Buffer, format: QAudioFormat, startTime?: number);
    /**
     * Creates a new audio buffer with space for *{@link numFrames}* 
     * frames of the given *{@link format}*. The individual samples 
     * will be initialized to the default for the format.
     * 
     * *{@link startTime}* (in microseconds) indicates when this 
     * buffer starts in the stream. If this buffer is not part of a 
     * stream, set it to -1.
     * @param numFrames The number of audio frames to allocate space 
     * for.
     * @param format The audio format used to interpret data.
     * @param startTime The time this buffer starts at in the stream, 
     * measured in microseconds. Default is -1.
     */
    constructor(numFrames: number, format: QAudioFormat, startTime?: number);
    constructor(
        arg?: NativeElement | Buffer | number | QAudioBuffer,
        format?: QAudioFormat,
        start?: number
    ) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QAudioBuffer) {
            native = new addon.QAudioBuffer(arg.native);
        } else if (Buffer.isBuffer(arg) && format) {
            native = new addon.QAudioBuffer(arg, format.native, start);
        } else if (typeof arg === 'number' && format) {
            native = new addon.QAudioBuffer(arg, format.native, start);
        } else if (arguments.length === 0) {
            native = new addon.QAudioBuffer();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QAudioBuffer::QAudioBuffer()");
        }
        super(native);
    }
    /**
     * Returns a copy of this buffer's raw audio data.
     * 
     * Unlike Qt's constData(), which returns a pointer into the
     * buffer, this binding returns an independent copy as a Node.JS
     * Buffer. You can read and modify this copy, but changes will not
     * affect this QAudioBuffer.
     * 
     * The data is returned as raw bytes, no checking is done. Use
     * {@link QAudioBuffer.format | format()} to interpret the 
     * samples.
     * 
     * @returns A buffer containing a copy of the audio data. If it's
     * invalid or has no data, you'll get an empty Buffer instead.
     * @example
     * const data: Buffer = buffer.constData();
     */
    constData(): Buffer { return this.native.constData(); }
    /**
     * This is an alias for 
     * {@link QAudioBuffer.constData | constData()}, only included for
     * ease of porting and convenience.
     * 
     * In C++, data() and constData() exist to distinguish writable
     * from read-only access to the buffer's memory. With the way JS
     * bindings are written, this distinction does not exist on the JS
     * side.
     * 
     * See {@link QAudioBuffer.constData | constData()}'s docs for 
     * more details.
     * @returns A buffer containing a copy of the audio data. If it's
     * invalid or has no data, you'll get an empty Buffer instead.
     * @example
     * const data: Buffer = buffer.data();
     */
    data(): Buffer { return this.native.data();}
    /**
     * Detaches this audio buffers from other copies that might share
     * data with it.
     */
    detach(): void { this.native.detach(); }
    /**
     * Returns the duration of audio in this buffer, in microseconds.
     * 
     * This depends on the {@link QAudioBuffer.format | format()}, and
     * the frameCount().
     * @returns The duration of audio in this buffer, measured in 
     * microseconds.
     */
    duration(): number { return this.native.duration(); }
    /**
     * Returns the {@link QAudioFormat | format} of this buffer.
     * 
     * Several properties of this format influence how the
     * {@link QAudioBuffer.duration | duration()} or byteCount() are
     * calculated from the frameCount().
     * @returns The format of this buffer.
     */
    format(): QAudioFormat { return this.native.format(); }
    /**
     * Returns true if this is a valid buffer. A valid buffer has more
     * than zero frames in it and a valid format.
     * @returns `true` if the buffer has a valid format and more than
     * 0 frames. `false` otherwise.
     */
    isValid(): boolean { return this.native.isValid(); }
    /**
     * Returns the time in a stream that this buffer starts at (in 
     * microseconds).
     * 
     * If this buffer is not part of a stream, this will return -1.
     * @returns The start time of this buffer within the stream, in
     * microseconds, otherwise -1 if it's not part of one.
     */
    startTime(): number { return this.native.startTime(); }
    /**
     * Swaps the audio buffer with *{@link other}*.
     * @param other The audio buffer to swap contents with.
     */
    swap(other: QAudioBuffer): void { this.native.swap(other.native); }
}