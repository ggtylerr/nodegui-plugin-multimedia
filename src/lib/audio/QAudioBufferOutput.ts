import {
    checkIfNativeElement,
    NativeElement,
    QObject,
    QObjectSignals,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QAudioBuffer } from "./QAudioBuffer";
import { QAudioFormat } from "./QAudioFormat";

/**
 * @summary The QAudioBufferOutput class is used for capturing audio
 * data provided by {@link QMediaPlayer}.
 *
 * @remarks
 * QAudioBufferOutput can be set to {@link QMediaPlayer} in order to
 * receive audio buffers decoded by the media player. The received
 * audio data can be used for any processing or visualization.
 *
 * See also {@link QMediaPlayer},
 * {@link QMediaPlayer.setAudioBufferOutput}, and
 * {@link QAudioBuffer}.
 * @see https://doc.qt.io/qt-6/qaudiobufferoutput.html for Qt's
 * Docs
 */
export class QAudioBufferOutput extends QObject<QAudioBufferOutputSignals> {
    /**
     * The native C++ QAudioBufferOutput variable.
     */
    declare native: NativeElement;
    /**
     * Create a new, empty, invalid buffer output.
     */
    constructor();
    /**
     * Copy a native QAudioBufferOutput to node bindings.
     * @param nativeElement A native QAudioBufferOutput element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Constructs a new QAudioBufferOutput object with
     * *{@link parent}*.
     *
     * The audio format of output audio buffers will depend on the
     * source media file and the inner audio decoder in
     * {@link QMediaPlayer}.
     * @param parent The parent QObject of this QAudioBufferOutput.
     */
    constructor(parent: QObject);
    /**
     * Constructs a new QAudioBufferOutput with audio {@link format}.
     *
     * If the specified *format* is valid, it will be the format of
     * output audio buffers. Otherwise, the format of output audio
     * buffers will depend on the source media file and the inner
     * audio decoder in {@link QMediaPlayer}.
     * @param format The audio format of the output audio buffers.
     */
    constructor(format: QAudioFormat);
    /**
     * Constructs a new QAudioBufferOutput with audio {@link format}
     * and {@link parent}.
     *
     * If the specified *format* is valid, it will be the format of
     * output audio buffers. Otherwise, the format of output audio
     * buffers will depend on the source media file and the inner
     * audio decoder in {@link QMediaPlayer}.
     * @param format he audio format of the output audio buffers.
     * @param parent The parent QObject of this QAudioBufferOutput.
     */
    constructor(format: QAudioFormat, parent: QObject);
    constructor(
        arg?: NativeElement | QObject | QAudioFormat,
        object?: QObject,
    ) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QObject) {
            native = new addon.QAudioBufferOutput(arg.native);
        } else if (arg instanceof QAudioFormat) {
            if (!object) {
                native = new addon.QAudioBufferOutput(arg.native);
            } else {
                native = new addon.QAudioBufferOutput(
                    arg.native,
                    object.native,
                );
            }
        } else if (arguments.length === 0) {
            native = new addon.QAudioBufferOutput();
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QAudioBufferOutput::QAudioBufferOutput()",
            );
        }
        super(native);
    }
    /**
     * Gets the audio format specified in the constructor.
     *
     * If the format is valid, it specifies the format of output
     * audio buffers.
     * @returns The audio format specified in the constructor.
     */
    format(): QAudioFormat {
        return new QAudioFormat(this.native.format());
    }
}

/**
 * QAudioBufferOutput's Signals
 */
export interface QAudioBufferOutputSignals extends QObjectSignals {
    /**
     * Signals that a new audio buffer has been received from
     * {@link QMediaPlayer}.
     * @param buffer The audio buffer received. Native Element.
     */
    audioBufferReceived: (buffer: NativeElement) => void;
}
