import { checkIfNativeElement, Component, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";

/**
 * @summary The QPlaybackOptions class enables low-level control of
 * media playback options.
 * @remarks
 * QPlaybackOptions gives low-level control of media playback options.
 * Although we strongly recommend to rely on the default settings of
 * {@link QMediaPlayer}, QPlaybackOptions can be used to optimize
 * media playback to specific use cases where the default options are
 * not ideal.
 * 
 * Note that options are hints to the media backend, and may be
 * ignored if they are not supported by the current media format or
 * codec.
 * 
 * Playback options rely on support in the media backend. Availability
 * is documented per option.
 * 
 * @see also {@link QMediaPlayer}.
 * @see https://doc.qt.io/qt-6/qplaybackoptions.html for Qt's Docs.
 */
export class QPlaybackOptions extends Component {
    /**
     * The native C++ QPlaybackOptions variable.
     */
    declare native: NativeElement;
    /**
     * Constructs an empty playback options.
     */
    constructor();
    /**
     * Copy a native QPlaybackOptions to node bindings.
     * @param nativeElement A native QPlaybackOptions element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Move-constructs an instance of QPlaybackOptions.
     * @param other The QPlaybackOptions to copy/move from.
     */
    constructor(other: QPlaybackOptions);
    constructor(arg?: NativeElement | QPlaybackOptions) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QPlaybackOptions) {
            native = new addon.QPlaybackOptions(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QPlaybackOptions();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QPlaybackOptions()");
        }
        super(native);
    }
    /**
     * Determines the network timeout used for socket I/O operations
     * with some network formats.
     * 
     * This option is only supported with the FFmpeg media backend.
     * @returns The network timeout.
     */
    networkTimeout(): number { return this.native.networkTimeout(); }
    /**
     * Determines if {@link QMediaPlayer} should optimize for robust
     * high quality video playback (default), or low latency
     * streaming.
     * 
     * This option is only supported with the FFmpeg media backend.
     * @returns The playback intent.
     */
    playbackIntent(): PlaybackIntent {
        return this.native.playbackIntent();
    }
    /**
     * Resets the network timeout used for socket I/O operations with
     * some network formats.
     * 
     * This option is only supported with the FFmpeg media backend.
     */
    resetNetworkTimeout(): void { this.native.resetNetworkTimeout(); }
    /**
     * Resets the playback intent, which is if {@link QMediaPlayer}
     * should optimize for robust high quality video playback 
     * (default), or low latency streaming.
     * 
     * This option is only supported with the FFmpeg media backend.
     */
    resetPlaybackIntent(): void { this.native.resetPlaybackIntent(); }
    /**
     * Resets the probe size, which defines the amount of data (in 
     * bytes) to analyze in order to gather stream information before 
     * media playback starts.
     * 
     * A larger probeSize value can give more robust playback but may 
     * increase latency. Conversely, a smaller probeSize can reduce 
     * latency but might miss some stream details. The default 
     * probeSize is -1, and the actual probeSize is determined by the 
     * media backend.
     * 
     * This option is only supported with the FFmpeg media backend.
     */
    resetProbeSize(): void { this.native.resetProbeSize(); }
    /**
     * Sets the network timeout used for socket I/O operations with
     * some network formats.
     * 
     * This option is only supported with the FFmpeg media backend.
     * @param timeout The network timeout.
     */
    setNetworkTimeout(timeout: number): void {
        this.native.setNetworkTimeout(timeout);
    }
    /**
     * Sets the playback intent, which is if {@link QMediaPlayer}
     * should optimize for robust high quality video playback 
     * (default), or low latency streaming.
     * 
     * This option is only supported with the FFmpeg media backend.
     */
    setPlaybackIntent(intent: PlaybackIntent): void {
        this.native.setPlaybackIntent(intent);
    }
}

/**
 * Configures the intent of media playback, to focus on either high
 * quality playback or low latency media streaming.
 */
export enum PlaybackIntent {
    /**
     * The intent is robust and high quality media playback, enabling
     * sufficient buffering to prevent glitches during playback.
     */
    Playback = 0,
    /** 
     * Buffering is reduced to optimize for low latency streaming, but
     * with a higher likelihood of lost frames or other glitches
     * during playback.
     */
    LowLatencyStreaming = 1,
}