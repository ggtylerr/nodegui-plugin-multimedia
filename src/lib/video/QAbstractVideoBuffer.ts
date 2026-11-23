import {
    checkIfNativeElement,
    Component,
    NativeElement,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { MapMode } from "./QVideoFrame";
import { QVideoFrameFormat } from "./QVideoFrameFormat";

/**
 * @summary The QAbstractVideoBuffer class is an abstraction for video
 * data.
 * @remarks
 * The {@link QVideoFrame} class makes use of a QAbstractVideoBuffer
 * internally to reference a buffer of video data. Creating a subclass
 * of QAbstractVideoBuffer allows you to construct video frames from
 * preallocated or static buffers. The subclass can contain a hardware
 * buffer, and implement access to the data by mapping the buffer to
 * CPU memory.
 *
 * The contents of a buffer can be accessed by mapping the buffer to
 * memory using the {@link QAbstractVideoBuffer.map | map()} function,
 * which returns a structure containing information about plane layout
 * of the current video data.
 *
 * @see also {@link QVideoFrame}, {@link QVideoFrameFormat}, and
 * {@link MapMode | QVideoFrame.MapMode}
 * @see https://doc.qt.io/qt-6/qabstractvideobuffer.html for Qt's docs
 */
export class QAbstractVideoBuffer extends Component {
    /**
     * The native C++ QAbstractVideoBuffer variable.
     */
    declare native: NativeElement;
    /**
     * Copy a native QAbstractVideoBuffer to node bindings.
     *
     * QAbstractVideoBuffer is an abstract class with no default
     * constructor, so instances must come from another class or from
     * native code.
     * @param nativeElement A native QAbstractVideoBuffer element.
     */
    constructor(nativeElement: NativeElement);
    constructor(arg?: NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QAbstractVideoBuffer()",
            );
        }
        super(native);
    }
    /**
     * Gets {@link QVideoFrameFormat} of the underlying video buffer.
     *
     * The format must be available upon construction of
     * {@link QVideoFrame}. {@link QVideoFrame} will contain one
     * instance of the given format, that can be detached and
     * modified.
     * @returns  The Video Frame Format of the underlying video
     * buffer.
     */
    format(): QVideoFrameFormat {
        return new QVideoFrameFormat(this.native.format());
    }
    /**
     * Maps the planes of a video buffer to memory.
     *
     * Returns a {@link MapData} structure that contains information
     * about the plane layout of the mapped current video data. If the
     * mapping fails, the method returns the default structure. For
     * CPU memory buffers, the data is considered as already mapped,
     * so the function just returns the plane layout of the
     * preallocated underlying data.
     *
     * The map *{@link mode}* indicates whether the contents of the
     * mapped memory should be read from and/or written to the buffer.
     * If the map mode includes the `QVideoFrame.ReadOnly` flag the
     * mapped memory will be populated with the content of the buffer
     * when initially mapped. If the map mode includes the
     * `QVideoFrame.WriteOnly` flag the content of the possibly
     * modified mapped memory will be written back to the buffer when
     * unmapped.
     *
     * When access to the data is no longer needed, the
     * {@link QAbstractVideoBuffer.unmap | unmap()} function is called
     * to release the mapped memory and possibly update the buffer
     * contents.
     *
     * If the format of the video data is multiplanar, the method may
     * map the whole pixel data as a single plane. In this case,
     * mapping a buffer with {@link QVideoFrame} will calculate
     * additional planes from the specified line stride of the first
     * plane, the frame height, and the data size.
     * @param mode The mode to map to.
     * @returns A MapData structure.
     */
    map(mode: MapMode): MapData {
        return this.native.map(mode);
    }
    /**
     * Releases the memory mapped by the
     * {@link QAbstractVideoBuffer.map | map()} function.
     *
     * If the {@link MapMode} included the `QVideoFrame.WriteOnly`
     * flag this will write the current content of the mapped memory
     * back to the video frame.
     *
     * For CPU video buffers, the function may be not overridden. The
     * default implementation of `unmap` does nothing.
     *
     * @see also {@link QAbstractVideoBuffer.map | map()}.
     */
    unmap(): void {
        this.native.unmap();
    }
}

/**
 * @summary The MapData structure describes the mapped plane layout.
 * @remarks
 * The structure contains a number of mapped planes, and plane data
 * for each plane, specificly, a number of bytes per line, a data
 * pointer, and a data size. The structure doesn't hold any ownership
 * of the data it refers to.
 *
 * A defaultly created structure means that no data has been mapped.
 *
 * All the values in the structure default to zeros.
 *
 * @see also {@link QAbstractVideoBuffer.map}.
 */
export interface MapData {
    /**
     * The array of numbers of bytes per line for each plane from `0`
     * to `planeCount - 1`.
     *
     * The values of the array default to 0.
     */
    bytesPerLine: number[];
    /**
     * The array of pointers to the mapped video pixel data for each
     * plane from `0` to `planeCount - 1`. The implementation of
     * {@link QAbstractVideoBuffer} must hold ownership of the data at
     * least until {@link QAbstractVideoBuffer.unmap} is called.
     *
     * The values of the array default to `null`.
     */
    data: (Buffer | null)[];
    /**
     * The array of sizes in bytes of the mapped video pixel data for
     * each plane from `0` to `planeCount - 1`.
     *
     * The values of the array default to 0.
     */
    dataSize: number[];
    /**
     * The number of planes of the mapped video data. If the format of
     * the data is multiplanar, and the value is `1`, the actual plane
     * layout will be calculated upon invoking of
     * {@link QVideoFrame.map} from the frame height,
     * `bytesPerLine[0]`, and `dataSize[0]`.
     *
     * Defaults to 0.
     */
    planeCount: number;
}
