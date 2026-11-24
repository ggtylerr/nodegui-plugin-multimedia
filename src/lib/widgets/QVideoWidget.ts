import {
    checkIfNativeElement,
    NativeElement,
    QWidget,
    QWidgetSignals,
    QSize,
    AspectRatioMode,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QVideoSink } from "../video/QVideoSink";

/**
 * @summary The QVideoWidget class provides a widget which presents
 * video produced by a media object.
 * @remarks
 * Attaching a QVideoWidget to a {@link QMediaPlayer} or
 * {@link QCamera} allows it to display the video or image output of
 * that object.
 * @example
 * const player = new QMediaPlayer();
 * player.setSource("http://example.com/myclip1.mp4");
 *
 * const videoWidget = new QVideoWidget();
 * player.setVideoOutput(videoWidget);
 *
 * videoWidget.show();
 * player.play();
 * @remarks
 * **Note:** Only a single display output can be attached to a media
 * object at one time.
 * @see also {@link QCamera}, {@link QMediaPlayer}, and
 * {@link QGraphicsVideoItem}.
 * @see https://doc.qt.io/qt-6/qvideowidget.html for Qt's docs.
 */
export class QVideoWidget extends QWidget<QVideoWidgetSignals> {
    /** The native QVideoWidget element. */
    declare native: NativeElement;
    /** Constructs a QVideoWidget instance with no parent. */
    constructor();
    /**
     * Copy a native QVideoWidget to node bindings.
     * @param nativeElement A native QVideoWidget element.
     */
    constructor(native: NativeElement);
    /**
     * Constructs a QVideoWidget instance as a child of
     * *{@link parent}*.
     * @param parent The parent widget.
     */
    constructor(parent: QWidget);
    constructor(arg?: NativeElement | QWidget) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QWidget) {
            native = new addon.QVideoWidget(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QVideoWidget();
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QVideoWidget()",
            );
        }
        super(native);
    }
    /**
     * How video is scaled with respect to its aspect ratio.
     * @returns The video's aspect ratio mode.
     */
    aspectRatioMode(): AspectRatioMode {
        return this.native.aspectRatioMode();
    }
    /**
     * This property holds whether video display is confined to a
     * window or is in full screen.
     * @returns Whether or not the video is full screen.
     */
    isFullScreen(): boolean {
        return this.native.isFullScreen();
    }
    /**
     * Returns the {@link QVideoSink} instance.
     * @returns The widget's video sink instance.
     */
    videoSink(): QVideoSink | null {
        const native: NativeElement | null = this.native.videoSink();
        if (native) return new QVideoSink(native);
        return null;
    }
    /**
     * Returns the size hint for the current back end, if there is
     * one, or else the size hint from {@link QWidget}.
     * @returns The widget's size hint.
     */
    sizeHint(): QSize {
        return new QSize(this.native.sizeHint());
    }
    /**
     * Sets the widget's aspect ratio mode.
     * @param mode The aspect ratio mode to set.
     */
    setAspectRatioMode(mode: AspectRatioMode): void {
        this.native.setAspectRatioMode(mode);
    }
    /**
     * Sets whether the video display is confined to a window or is in
     * full screen.
     * @param fullScreen Whether or not the video is full screen.
     */
    setFullScreen(fullScreen: boolean): void {
        this.native.setFullScreen(fullScreen);
    }
}

/** QVideoWidget's Signals */
export interface QVideoWidgetSignals extends QWidgetSignals {
    /**
     * Signals when the aspect ratio mode changed.
     * @param mode The new aspect ratio mode.
     */
    aspectRatioModeChanged(mode: AspectRatioMode): void;
    /**
     * Signals when the video goes into fullscreen or windowed.
     * @param fullScreen Whether or not the video is full screen.
     */
    fullScreenChanged(fullScreen: boolean): void;
}
