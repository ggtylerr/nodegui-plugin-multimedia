import { checkIfNativeElement, NativeElement, QObject, QObjectSignals } from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QAudioDevice } from "./QAudioDevice";

/**
 * @summary Represents an output channel for audio.
 * @remarks 
 * This class represents an output channel that can be used together
 * with {@link QMediaPlayer} or {@link QMediaCaptureSession}. It
 * enables the selection of the physical output device to be used,
 * muting the channel, and changing the channel's volume.
 * 
 * > **Note:** On WebAssembly platform, due to its asynchronous
 * nature, 
 * {@link QMediaDevices.audioOutputsChanged | QMediaDevices.audioOutputsChanged()} 
 * signal is emitted when the list of audio outputs is ready. User
 * permissions are required. Works only on secure https contexts.
 * 
 * @see also {@link QAudioInput}.
 */
export class QAudioOutput extends QObject<QAudioOutputSignals> {
    /**
     * The native C++ QAudioFormat variable.
     */
    declare native: NativeElement;
    /**
     * Create a new, empty, invalid audio output.
     */
    constructor();
    /**
     * Copy a native QAudioOutput to node bindings.
     * @param nativeElement A native QAudioOutput element.
     */
    constructor(nativeElement: NativeElement);
    constructor(arg?: NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arguments.length === 0) {
            native = new addon.QAudioOutput();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QAudioOutput::QAudioOutput()");
        }
        super(native);
    }
    /**
     * This property holds the audio device connected to this output.
     * @returns The audio device connected to this output.
     */
    device(): QAudioDevice { return new QAudioDevice(this.native.device()); }
    /**
     * This property holds the muted state of the current media.
     * 
     * The value will be true if output is muted; otherwise false.
     * @returns Whether the media is muted or not.
     */
    isMuted(): boolean { return this.native.isMuted(); }
    /**
     * This property holds the current volume.
     * 
     * The volume is scaled linearly, ranging from 0 (silence) to 1
     * (full volume).
     * 
     * > **Note:** values outside this range will be clamped.
     * 
     * By default the volume is 1.
     * 
     * UI volume controls should usually be scaled non-linearly. For
     * example, using a logarithmic scale will produce linear changes
     * in perceived loudness, which is what a user would normally
     * expect from a volume control.
     * @see also {@link QtAudio.convertVolume | QtAudio.convertVolume()}.
     * @returns The volume level, between 0 and 1.
     */
    volume(): number { return this.native.volume(); }
    /**
     * This property holds the audio device connected to this output.
     * 
     * The device property represents the audio device this output is
     * connected to. This property can be used to select an output
     * device from the {@link QMediaDevices.audioOutputs} list. You
     * can select the system default audio output by setting this
     * property to a default constructed {@link QAudioDevice} object.
     * @param device The audio device to set the output to.
     */
    setDevice(device: QAudioDevice) { this.native.setDevice(device); }
    /**
     * This property holds the muted state of the current media.
     * 
     * The value will be true if output is muted; otherwise false.
     * @param muted Whether the media is muted or not.
     */
    setMuted(muted: boolean) { this.native.setMuted(muted); }
    /**
     * This property holds the current volume.
     * 
     * The volume is scaled linearly, ranging from 0 (silence) to 1
     * (full volume).
     * 
     * > **Note:** values outside this range will be clamped.
     * 
     * By default the volume is 1.
     * 
     * UI volume controls should usually be scaled non-linearly. For
     * example, using a logarithmic scale will produce linear changes
     * in perceived loudness, which is what a user would normally
     * expect from a volume control.
     * @see also {@link QtAudio.convertVolume | QtAudio.convertVolume()}.
     * @param volume The volume level, between 0 and 1.
     */
    setVolume(volume: number) { this.native.setVolume(volume); }
}

/**
 * QAudioOutputSignals's Signals
 */
export interface QAudioOutputSignals extends QObjectSignals {
    /**
     * Signals that the audio device has been changed.
     */
    deviceChanged: () => void;
    /**
     * Signals that the muted status has been changed.
     * @param muted Whether it's muted.
     */
    mutedChanged: (muted: boolean) => void;
    /**
     * Signals that the volume has been changed.
     * @param volume The volume level, between 0 and 1.
     */
    volumeChanged: (volume: number) => void;
}