import {
    checkIfNativeElement,
    NativeElement,
    QObject,
    QObjectSignals,
    QSize,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QVideoFrame } from "./QVideoFrame";

/**
 * @summary The QVideoSink class represents a generic sink for video
 * data.
 * @remarks
 * The QVideoSink class can be used to retrieve video data on a frame
 * by frame basis from Qt Multimedia.
 *
 * QVideoSink will provide individual video frames to the application
 * developer through the
 * {@link QVideoSinkSignals.videoFrameChanged | videoFrameChanged()}
 * signal.
 *
 * The video frame can then be used to read out the data of those
 * frames and handle them further. When using {@link QPainter}, the
 * {@link QVideoFrame} can be drawing using the
 * {@link QVideoFrame.paint | paint()} method.
 *
 * {@link QVideoFrame} objects can consume a significant amount of
 * memory or system resources and should thus not be held for longer
 * than required by the application.
 *
 * @see also {@link QMediaPlayer} and {@link QMediaCaptureSession}.
 * @see https://doc.qt.io/qt-6/qvideosink.html for Qt's docs.
 */
export class QVideoSink extends QObject<QVideoSinkSignals> {
    /**
     * The native C++ QVideoSink variable.
     */
    declare native: NativeElement;
    /**
     * Create a new QVideoSink object with no parent.
     */
    constructor();
    /**
     * Copy a native QVideoSink to node bindings.
     * @param nativeElement A native QVideoSink element.
     */
    constructor(native: NativeElement);
    /**
     * Constructs a new QVideoSink object with *{@link parent}*.
     * @param parent A parent QObject.
     */
    constructor(parent: QObject);
    constructor(arg?: NativeElement | QObject) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QObject) {
            native = new addon.QVideoSink(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QVideoSink();
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QVideoSink()",
            );
        }
        super(native);
    }
    /**
     * Sets the current *{@link subtitle}* text.
     *
     * @see also {@link QVideoSink.subtitleText | subtitleText()}.
     * @param subtitle The text to set the subtitle to.
     */
    setSubtitleText(subtitle: string): void {
        this.native.setSubtitleText(subtitle);
    }
    /**
     * Sets the current video *{@link frame}*.
     *
     * @see also {@link QVideoSink.videoFrame | videoFrame()}.
     * @param frame The frame to set.
     */
    setVideoFrame(frame: QVideoFrame): void {
        this.native.setVideoFrame(frame.native);
    }
    /**
     * Returns the current subtitle text.
     * @returns The current subtitle text.
     */
    subtitleText(): string {
        return this.native.subtitleText();
    }
    /**
     * Returns the current video frame.
     * @see also {@link QVideoSink.setVideoFrame | setVideoFrame()}.
     * @returns The current frame.
     */
    videoFrame(): QVideoFrame {
        return new QVideoFrame(this.native.videoFrame());
    }
    /**
     * Returns the size of the video currently being played back. If
     * no video is being played, this method returns an invalid size.
     * @returns The current video size.
     */
    videoSize(): QSize {
        return new QSize(this.native.videoSize());
    }
}

/** QVideoSink's Signals */
export interface QVideoSinkSignals extends QObjectSignals {
    /**
     * Signals when the subtitle text has changed.
     * @param subtitleText The subtitle that changed.
     */
    subtitleTextChanged(subtitleText: string): void;
    /**
     * Signals when the video frame has changed.
     * @param frame The QVideoFrame that changed. Native Element.
     */
    videoFrameChanged(frame: NativeElement): void;
    /** Signals when the video size has changed. */
    videoSizeChanged(): void;
}
