import {
    checkIfNativeElement,
    NativeElement,
    QObject,
    QObjectSignals,
    QUrl,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QAudioBufferOutput } from "../audio/QAudioBufferOutput";
import { QAudioOutput } from "../audio/QAudioOutput";
import { QMediaMetaData } from "../misc/QMediaMetaData";
import { QMediaTimeRange } from "../misc/QMediaTimeRange";
import { QPlaybackOptions } from "./QPlaybackOptions";
import { QVideoSink } from "../video/QVideoSink";

/**
 * @summary The QMediaPlayer class allows the playing of a media
 * files.
 * @remarks
 * The QMediaPlayer class is a high level media playback class. It can
 * be used to playback audio of video media files. The content to
 * playback is specified as either a QUrl object or a string.
 *
 * @example
 * const player = new QMediaPlayer();
 * const audioOutput = new QAudioOutput();
 * player.setAudioOutput(audioOutput);
 * const positionLabel = new QLabel();
 * player.addEventListener("positionChanged", (position: number) => {
 *   positionLabel.setText(position);
 * });
 * player.setSource("file:///Users/me/Music/coolsong.mp3");
 * audioOutput.setVolume(0.5);
 * player.play();
 *
 * @remarks
 * {@link QVideoWidget} can be used with QMediaPlayer for video
 * rendering.
 *
 * @see also {@link QVideoWidget}.
 * @see https://doc.qt.io/qt-6/qmediaplayer.html for Qt's docs.
 */
export class QMediaPlayer extends QObject<QMediaPlayerSignals> {
    /** The native QMediaPlayer element. */
    declare native: NativeElement;
    /** Cached VideoOutput object. */
    private _videoOutput: QObject | null = null;
    /** Constructs a QMediaPlayer instance with no parent. */
    constructor();
    /**
     * Copy a native QVideoSink to node bindings.
     * @param nativeElement A native QVideoSink element.
     */
    constructor(native: NativeElement);
    /**
     * Constructs a QMediaPlayer instance as a child of
     * *{@link parent}*.
     * @param parent The parent object.
     */
    constructor(parent: QObject);
    constructor(arg?: NativeElement | QObject) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QObject) {
            native = new addon.QMediaPlayer(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QMediaPlayer();
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QMediaPlayer()",
            );
        }
        super(native);
    }
    /**
     * Returns the currently active audio track.
     *
     * By default, the first available audio track will be chosen.
     * @returns The currently active audio track.
     */
    activeAudioTrack(): number {
        return this.native.activeAudioTrack();
    }
    /**
     * Returns the currently active subtitle track.
     *
     * Subtitles are disabled by default. (`-1`)
     * @returns The currently active subtitle track.
     */
    activeSubtitleTrack(): number {
        return this.native.activeSubtitleTrack();
    }
    /**
     * Returns the currently active video track.
     *
     * By default, the first available video track will be chosen.
     * @returns The currently active video track.
     */
    activeVideoTrack(): number {
        return this.native.activeVideoTrack();
    }
    /**
     * This property holds the output audio buffer used by the media
     * player.
     *
     * If {@link QAudioBufferOutput} is specified and the media source
     * contains an audio stream, the media player, it will emit the
     * signal {@link QAudioBufferOutput.audioBufferReceived} with
     * audio buffers containing decoded audio data. At the end of the
     * audio stream, `QMediaPlayer` emits an empty
     * {@link QAudioBuffer}.
     *
     * `QMediaPlayer` emits outputs audio buffers at the same time as
     * it pushes the matching data to the audio output if it's
     * specified. However, the sound can be played with a small delay
     * due to audio bufferization.
     *
     * The format of emitted audio buffers is taken from the specified
     * *output* or from the matching audio stream if the *output*
     * returns an invalid format. Emitted audio data is not scaled
     * depending on the current playback rate.
     *
     * Potential use cases of utilizing `QAudioBufferOutput` with
     * `QMediaPlayer` might be:
     * - Audio visualization. If the playback rate of the media player
     * is not 1, you may scale the output image dimensions, or image
     * update interval according to the requirements of the
     * visualizer.
     * - Any AI sound processing, e.g. voice recognition.
     * - Sending the data to external audio output. Playback rate
     * changing, synchronization with video, and manual flushing on
     * stopping and seeking should be considered. We don't recommend
     * using the audio buffer output for this purpose unless you have
     * a strong reason for this.
     * @returns The output audio buffer used by the player.
     */
    audioBufferOutput(): QAudioBufferOutput | null {
        const native: NativeElement | null =
            this.native.audioBufferOutput();
        if (native) return new QAudioBufferOutput(native);
        return null;
    }
    /**
     * This property holds the audio output device used by the media
     * player.
     * @returns The audio output device used by the player.
     */
    audioOutput(): QAudioOutput | null {
        const native: NativeElement | null =
            this.native.audioOutput();
        if (native) return new QAudioOutput(native);
        return null;
    }
    /**
     * Lists the set of available audio tracks inside the media.
     *
     * The `QMediaMetaData` returned describes the properties of
     * individual tracks.
     *
     * Different audio tracks can, for example, contain audio in
     * different languages.
     * @returns An array of audio tracks.
     */
    audioTracks(): QMediaMetaData[] {
        const els: NativeElement[] = this.native.audioTracks();
        let out: QMediaMetaData[] = [];
        for (const el of els) out.push(new QMediaMetaData(el));
        return out;
    }
    /**
     * Returns a number between 0 and 1 when buffering data.
     *
     * 0 means that there is no buffered data available, playback is
     * usually stalled in this case. Playback will resume once the
     * buffer reaches 1, meaning enough data has been buffered to be
     * able to resume playback.
     *
     * `bufferProgress()` will always return 1 for local files.
     * @returns The buffering progress as a number between 0 and 1.
     */
    bufferProgress(): number {
        return this.native.bufferProgress();
    }
    /**
     * Returns a {@link QMediaTimeRange} describing the currently
     * buffered data.
     *
     * When streaming media from a remote source, different parts of
     * the media file can be available locally. The returned
     * {@link QMediaTimeRange} object describes the time ranges that
     * are buffered and available for immediate playback.
     *
     * @see also {@link QMediaTimeRange}.
     * @returns A time range describing the currently buffered data.
     */
    bufferedTimeRange(): QMediaTimeRange {
        return new QMediaTimeRange(this.native.bufferedTimeRange());
    }
    /**
     * Returns the duration of the current media in ms.
     *
     * Returns 0 if the media player doesn't have a valid media file
     * or stream. For live streams, the duration usually changes
     * during playback as more data becomes available.
     * @returns The media duration in ms.
     */
    duration(): number {
        return this.native.duration();
    }
    /**
     * Returns the current error state.
     * @returns The player's error state.
     */
    error(): Error {
        return this.native.error();
    }
    /**
     * This property holds a string describing the current error
     * condition in more detail.
     * @returns A string with more error details.
     */
    errorString(): string {
        return this.native.errorString();
    }
    /**
     * This property holds whether the media contains audio.
     * @returns If the media has audio.
     */
    hasAudio(): boolean {
        return this.native.hasAudio();
    }
    /**
     * This property holds whether the media contains video.
     * @returns If the media has video.
     */
    hasVideo(): boolean {
        return this.native.hasVideo();
    }
    /**
     * Returns true if the media player is supported on this platform.
     * @returns If the player is supported.
     */
    isAvailable(): boolean {
        return this.native.isAvailable();
    }
    /**
     * This property holds whether the media is playing.
     * @see also {@link QMediaPlayer.playbackState | playbackState()}
     * and {@link PlaybackState}.
     * @returns If the player is playing.
     */
    isPlaying(): boolean {
        return this.native.isPlaying();
    }
    /**
     * Returns true if the media is seekable. Most file based media
     * files are seekable, but live streams usually are not.
     * @see also {@link QMediaPlayer.position | position()}.
     * @returns If the media is seekable.
     */
    isSeekable(): boolean {
        return this.native.isSeekable();
    }
    /**
     * Determines how often the media is played before the player
     * stops. Default value is 1.
     * @returns How many times the media is played.
     */
    loops(): number {
        return this.native.loops();
    }
    /**
     * This property holds the status of the current media stream.
     *
     * The stream status describes how the playback of the current
     * stream is progressing.
     *
     * By default this property is {@link MediaStatus.NoMedia}.
     * @returns The current media's status.
     */
    mediaStatus(): MediaStatus {
        return this.native.mediaStatus();
    }
    /**
     * Returns meta data for the current media used by the media
     * player.
     *
     * Meta data can contain information such as the title of the
     * video or its creation date.
     *
     * > **Note:** The windows implementation provides metadata only
     * for media located on the local file system.
     * @returns The current media's meta data.
     */
    metaData(): QMediaMetaData {
        return new QMediaMetaData(this.native.metaData());
    }
    /**
     * Returns the state of pitch compensation.
     * @see also {@link QMediaPlayer.setPitchCompensation | setPitchCompensation()}.
     * @returns The player's pitch compensation state.
     */
    pitchCompensation(): boolean {
        return this.native.pitchCompensation();
    }
    /**
     * Returns availability of pitch compensation of the current
     * backend.
     * @return If pitch compensation is available.
     */
    pitchCompensationAvailability(): PitchCompensationAvailability {
        return this.native.pitchCompensationAvailability();
    }
    /**
     * Advanced playback options used to configure media playback and
     * decoding.
     *
     * This property exposes the {@link QPlaybackOptions} API that
     * gives low-level control of media playback options. Although we
     * strongly recommend to rely on the default settings of
     * {@link QMediaPlayer}, this API can be used to optimize media
     * playback for specific use cases where the default options are
     * not ideal.
     *
     * Playback options take effect the next time
     * {@link QMediaPlayer.setSource | setSource()} is called.
     * @returns The player's playback options.
     */
    playbackOptions(): QPlaybackOptions {
        return new QPlaybackOptions(this.native.playbackOptions());
    }
    /**
     * Returns the current playback rate.
     * @returns The player's playback rate.
     */
    playbackRate(): number {
        return this.native.playbackRate();
    }
    /**
     * Returns the {@link PlaybackState}.
     * @returns The player's playback state.
     */
    playbackState(): PlaybackState {
        return this.native.playbackState();
    }
    /**
     * This property holds the playback position of the current media.
     *
     * The value is the current playback position, expressed in
     * milliseconds since the beginning of the media. Periodically,
     * changes in the position will be indicated with the
     * {@link QMediaPlayer.positionChanged | positionChanged()}
     * signal.
     * @returns The media's position, in ms.
     */
    position(): number {
        return this.native.position();
    }
    /**
     * Sets the currently active audio track.
     *
     * Set *{@link index}* to `-1` to disable all audio tracks.
     * @param index The audio track to set.
     */
    setActiveAudioTrack(index: number): void {
        this.native.setActiveAudioTrack(index);
    }
    /**
     * Sets the currently active subtitle track.
     *
     * Set *{@link index}* to `-1` to disable subtitles.
     * @param index The subtitle track to set.
     */
    setActiveSubtitleTrack(index: number): void {
        this.native.setActiveSubtitleTrack(index);
    }
    /**
     * Sets the currently active video track.
     *
     * Set *{@link index}* to `-1` to disable all video tracks.
     * @param index The video track to set.
     */
    setActiveVideoTrack(index: number): void {
        this.native.setActiveVideoTrack(index);
    }
    /**
     * Sets an audio buffer *{@link output}* to the media player.
     * @see {@link QMediaPlayer.audioBufferOutput | audioBufferOutput()}
     * for more details.
     * @param output The audio buffer output to set.
     */
    setAudioBufferOutput(output: QAudioBufferOutput): void {
        this.native.setAudioBufferOutput(output.native);
    }
    /**
     * Sets the audio output device used by the media player.
     *
     * The current audio output to be used when playing back media.
     * Setting a new audio output will replace the currently used
     * output.
     *
     * Setting this property to `null` will disable any audio output.
     * @param output The audio output device to set.
     */
    setAudioOutput(output: QAudioOutput): void {
        this.native.setAudioOutput(output.native);
    }
    /**
     * Determines how often the media is played before the player
     * stops. Set to {@link Loops.Infinite} to loop the current media
     * file forever.
     *
     * The default value is `1`. Setting this property to `0` has no
     * effect.
     * @param loops The number of times the media is played.
     */
    setLoops(loops: number): void {
        this.native.setLoops(loops);
    }
    /**
     * This property holds the video output to be used by the media
     * player.
     *
     * A media player can only have one video output attached, so
     * setting this property will replace the previously connected
     * video output.
     *
     * Setting this property to `null` will disable video output.
     * @param output The video output object to set.
     */
    setVideoOutput(output: QObject | null): void {
        // Caching video output object since it's a bit iffy on
        // bindings
        this._videoOutput = output;
        this.native.setVideoOutput(output ? output.native : null);
    }
    /**
     * Sets *{@link sink}* to be the {@link QVideoSink} instance to
     * retrieve video data.
     *
     * @see also {@link QMediaPlayer.videoSink | videoSink()}.
     * @param sink The video sink to set.
     */
    setVideoSink(sink: QVideoSink): void {
        // Null out cached video output since it detaches when a
        // video sink is set
        this._videoOutput = null;
        this.native.setVideoSink(sink.native);
    }
    /**
     * This property holds the active media source being used by the
     * player object.
     *
     * The player object will use the QUrl (converted from a string)
     * for selection of the content to be played.
     *
     * By default this property has an empty string (from a null QUrl)
     * @returns The active source used by the player.
     */
    source(): string {
        return this.native.source();
    }
    /**
     * Lists the set of available subtitle tracks inside the media.
     *
     * The {@link QMediaMetaData} in the array describes the
     * properties of individual tracks.
     *
     * @returns An array of subtitle tracks.
     */
    subtitleTracks(): QMediaMetaData[] {
        const els: NativeElement[] = this.native.subtitleTracks();
        let out: QMediaMetaData[] = [];
        for (const el of els) out.push(new QMediaMetaData(el));
        return out;
    }
    /**
     * This property holds the video output to be used by the media
     * player.
     *
     * A media player can only have one video output attached, so
     * setting this property will replace the previously connected
     * video output.
     *
     * @returns The video output object.
     */
    videoOutput(): QObject | null {
        return this._videoOutput;
    }
    /**
     * Returns the {@link QVideoSink} instance.
     *
     * @see also {@link QMediaPlayer.setVideoSink | setVideoSink()}.
     * @returns The video sink instance.
     */
    videoSink(): QVideoSink | null {
        const native: NativeElement | null = this.native.videoSink();
        if (native) return new QVideoSink(native);
        return null;
    }
    /**
     * Lists the set of available video tracks inside the media.
     *
     * The {@link QMediaMetaData} in the array describes the
     * properties of individual tracks.
     *
     * @returns An array of video tracks.
     */
    videoTracks(): QMediaMetaData[] {
        const els: NativeElement[] = this.native.videoTracks();
        let out: QMediaMetaData[] = [];
        for (const el of els) out.push(new QMediaMetaData(el));
        return out;
    }
    /**
     * Pause playing the current source.
     *
     * @see also {@link QMediaPlayer.play | play()} and
     * {@link QMediaPlayer.stop | stop()}.
     */
    pause(): void {
        this.native.pause();
    }
    /**
     * Start or resume playing the current source.
     *
     * @see also {@link QMediaPlayer.pause | pause()} and
     * {@link QMediaPlayer.stop | stop()}.
     */
    play(): void {
        this.native.play();
    }
    /**
     * Reset playback options back to default.
     *
     * @see also {@link QMediaPlayer.playbackOptions | playbackOptions()}.
     */
    resetPlaybackOptions(): void {
        this.native.resetPlaybackOptions();
    }
    /**
     * Sets the state (*{@link enabled}* or disabled) of pitch
     * compensation. This only has an effect if the audio pitch
     * compensation can be configured on the backend at runtime.
     *
     * @see also {@link QMediaPlayer.pitchCompensation | pitchCompensation()}.
     * @param enabled Whether pitch compensation is enabled.
     */
    setPitchCompensation(enabled: boolean): void {
        this.native.setPitchCompensation(enabled);
    }
    /**
     * Set the playback options used by the player.
     *
     * @see also {@link QMediaPlayer.playbackOptions | playbackOptions()}.
     * @param options The playback options to set.
     */
    setPlaybackOptions(options: QPlaybackOptions): void {
        this.native.setPlaybackOptions(options.native);
    }
    /**
     * Sets the playback rate of the current media.
     *
     * This value is a multiplier applied to the media's standard
     * playback rate. By default this value is 1.0, indicating that
     * the media is playing at the standard speed. Values higher than
     * 1.0 will increase the playback speed, while values between 0.0
     * and 1.0 results in slower playback. Negative playback rates are
     * not supported.
     *
     * Not all playback services support change of the playback rate.
     * It is framework defined as to the status and quality of audio
     * and video while fast forwarding or rewinding.
     * @param rate The playback rate to set it to.
     */
    setPlaybackRate(rate: number): void {
        this.native.setPlaybackRate(rate);
    }
    /**
     * Sets the playback position of the current media.
     *
     * The value is the current playback position, expressed in
     * milliseconds since the beginning of the media.
     *
     * If the {@link QMediaPlayer.isSeekable | seekable} property is
     * true, this property can be set to milliseconds.
     *
     * @param position The playback position to set it to, in ms.
     */
    setPosition(position: number): void {
        this.native.setPosition(position);
    }
    /**
     * Sets the active media source being used by the player object.
     *
     * The player object will use the {@link QUrl} (or a string
     * representing a new QUrl) for selection of the content to be
     * played.
     *
     * Setting this property to a null QUrl will cause the player to
     * discard all information relating to the current media source
     * and to cease all I/O operations related to that media.
     * @see also {@link QUrl}.
     * @param source Either a string or a QUrl to set as the source
     * for the player.
     */
    setSource(source: string | QUrl): void {
        this.native.setSource(source);
    }
    /**
     * Stop playing, and reset the play position to the beginning.
     *
     * @see also {@link QMediaPlayer.play | play()} and
     * {@link QMediaPlayer.pause | pause()}.
     */
    stop(): void {
        this.native.stop();
    }
}

/** QMediaPlayer's Signals */
/**
 * NOTE: currently don't have docs rn since jsdocs doesn't have any
 * way of displaying it to a developer, and they're pretty self
 * explanatory. if you really need docs just look at qt's docs.
 *
 * this will be implemented later when web docs exist.
 */
export interface QMediaPlayerSignals extends QObjectSignals {
    activeTracksChanged(): void;
    audioBufferOutputChanged(): void;
    audioOutputChanged(): void;
    bufferProgressChanged(filled: number): void;
    durationChanged(duration: number): void;
    errorChanged(): void;
    errorOccurred(error: Error, errorString: string): void;
    hasAudioChanged(available: boolean): void;
    hasVideoChanged(videoAvailable: boolean): void;
    loopsChanged(): void;
    mediaStatusChanged(status: MediaStatus): void;
    metaDataChanged(): void;
    pitchCompensationChanged(enabled: boolean): void;
    playbackOptionsChanged(): void;
    playbackRateChanged(rate: number): void;
    playbackStateChanged(newState: PlaybackState): void;
    playingChanged(playing: boolean): void;
    positionChanged(position: number): void;
    seekableChanged(seekable: boolean): void;
    sourceChanged(media: string): void;
    tracksChanged(): void;
    videoOutputChanged(): void;
}

/** Defines a media player error condition. */
export enum Error {
    /** No error has occurred. */
    NoError = 0,
    /** A media resource couldn't be resolved. */
    ResourceError = 1,
    /**
     * The format of a media resource isn't (fully) supported.
     * Playback may still be possible, but without an audio or video
     * component.
     */
    FormatError = 2,
    /** A network error occurred. */
    NetworkError = 3,
    /**
     * There are not the appropriate permissions to play a media
     * resource.
     */
    AccessDeniedError = 4,
}

/**
 * Some predefined constants for the
 * {@link QMediaPlayer.loops | loops} property.
 */
export enum Loops {
    /** Loop forever. */
    Infinite = -1,
    /** Play the media once (the default). */
    Once = 1,
}

/** Defines the status of a media player's current media. */
export enum MediaStatus {
    /**
     * There is no current media. The player is in the
     * {@link PlaybackState.StoppedState | StoppedState}.
     */
    NoMedia = 0,
    /**
     * The current media is being loaded. The player may be in any
     * state.
     */
    LoadingMedia = 1,
    /**
     * The current media has been loaded. The player is in the
     * {@link PlaybackState.StoppedState | StoppedState}.
     */
    LoadedMedia = 2,
    /**
     * Playback of the current media has stalled due to insufficient
     * buffering or some other temporary interruption. The player is
     * in the {@link PlaybackState.PlayingState | PlayingState} or
     * {@link PlaybackState.PausedState | PausedState}.
     */
    StalledMedia = 3,
    /**
     * The player is buffering data but has enough data buffered for
     * playback to continue for the immediate future. The player is
     * in the {@link PlaybackState.PlayingState | PlayingState} or
     * {@link PlaybackState.PausedState | PausedState}.
     */
    BufferingMedia = 4,
    /**
     * The player has fully buffered the current media. The player is
     * in the {@link PlaybackState.PlayingState | PlayingState} or
     * {@link PlaybackState.PausedState | PausedState}.
     */
    BufferedMedia = 5,
    /**
     * Playback has reached the end of the current media. The player
     * is in the {@link PlaybackState.StoppedState | StoppedState}.
     */
    EndOfMedia = 6,
    /**
     * The current media cannot be played. The player is in the
     * {@link PlaybackState.StoppedState | StoppedState}.
     */
    InvalidMedia = 7,
}

/**
 * Availablility of pitch compensation.
 *
 * Different backends have different behavior regarding pitch
 * compensation when changing playback rate.
 */
export enum PitchCompensationAvailability {
    /**
     * The media player is always performing pitch compensation.
     */
    AlwaysOn = 0,
    /**
     * The media player can be configured to use pitch compensation.
     * If pitch compensation is available on the current platform, it
     * will be enabled by default, but users can disable if needed.
     */
    Available = 1,
    /**
     * The media player is not able to perform pitch compensation on
     * the current platform.
     */
    Unavailable = 2,
}

/**
 * Defines the current state of a media player.
 */
export enum PlaybackState {
    /**
     * The media player is not playing content, playback will begin
     * from the start of the current track.
     */
    StoppedState = 0,
    /**
     * The media player is currently playing content. This indicates
     * the same as the {@link QMediaPlayer.isPlaying | playing}
     * property.
     */
    PlayingState = 1,
    /**
     * The media player has paused playback, playback of the current
     * track will resume from the position the player was paused at.
     */
    PausedState = 2,
}
