import {
    checkIfNativeElement,
    Component,
    NativeElement,
} from "@nodegui/nodegui";

import addon from "../utils/addon";

import {
    QImage,
    QColor,
    AspectRatioMode,
    QPainter,
    QRectF,
    QSize,
} from "@nodegui/nodegui";
import { QVideoFrameFormat, PixelFormat } from "./QVideoFrameFormat";
import { QAbstractVideoBuffer } from "./QAbstractVideoBuffer";
import { Rotation } from "./QtVideo";

/**
 * @summary The QVideoFrame class represents a frame of video data.
 * @remarks
 * A QVideoFrame encapsulates the pixel data of a video frame, and
 * information about the frame.
 *
 * Video frames can come from several places - decoded
 * {@link QMediaPlayer media}, a {@link QCamera camera}, or generated
 * programmatically. The way pixels are described in these frames can
 * vary greatly, and some pixel formats offer greater compression
 * opportunities at the expense of ease of use.
 *
 * The pixel contents of a video frame can be mapped to memory using
 * the {@link QVideoFrame.map | map()} function. After a successful
 * call to {@link QVideoFrame.map | map()}, the video data can be
 * accessed through various functions. Some of the YUV pixel formats
 * provide the data in several planes. The
 * {@link QVideoFrame.planeCount | planeCount()} method will return
 * the amount of planes that are being used.
 *
 * While mapped, the video data of each plane can be accessed using
 * the {@link QVideoFrame.bits | bits()} function, which returns a
 * buffer. The size of this buffer is given by the
 * {@link QVideoFrame.mappedBytes | mappedBytes()} function, and the
 * size of each line is given by
 * {@link QVideoFrame.bytesPerLine | bytesPerLine()}. The return value
 * of the {@link QVideoFrame.handleType | handleType()} function may
 * also be used to access frame data using the internal buffer's
 * native APIs (for example - an OpenGL texture handle).
 *
 * A video frame can also have timestamp information associated with
 * it. These timestamps can be used to determine when to start and
 * stop displaying the frame.
 *
 * QVideoFrame objects can consume a significant amount of memory or
 * system resources and should not be held for longer than required by
 * the application.
 *
 * > **Note:** Since video frames can be expensive to copy,
 * QVideoFrame is explicitly shared, so any change made to a video
 * frame will also apply to any copies.
 *
 * @see also {@link QAbstractVideoBuffer}, {@link QVideoFrameFormat},
 * and {@link QVideoFrame.MapMode}.
 * @see https://doc.qt.io/qt-6/qvideoframe.html for Qt's docs.
 */
export class QVideoFrame extends Component {
    /**
     * The native C++ QVideoFrame variable.
     */
    declare native: NativeElement;
    /**
     * Constructs a null video frame.
     */
    constructor();
    /**
     * Copy a native QVideoFrame to node bindings.
     * @param nativeElement A native QVideoFrame element.
     */
    constructor(native: NativeElement);
    /**
     * Constructs a QVideoFrame from a {@link QImage}.
     *
     * If the {@link QImage.Format} matches one of the formats in
     * {@link QVideoFrameFormat.PixelFormat}, the QVideoFrame will
     * hold an instance of the *{@link image}* and use that format
     * without any pixel format conversion. In this case, pixel data
     * will be copied only if you call
     * {@link QVideoFrame.map | QVideoFrame.map()} with the
     * `WriteOnly` flag while keeping the original image.
     *
     * Otherwise, if the {@link QImage.Format} matches none of the
     * video formats, the image is first converted to a supported
     * (A)RGB format using
     * {@link QImage.convertedTo | QImage.convertedTo()} with the
     * {@link ImageConversionFlag.AutoColor} flag. This may incur a
     * performance penalty.
     *
     * If {@link QImage.isNull | QImage.isNull()} evaluates to true
     * for the input {@link QImage}, the QVideoFrame will be invalid
     * and
     * {@link QVideoFrameFormat.isValid | QVideoFrameFormat.isValid()}
     * will return false.
     *
     * @see also
     * {@link QVideoFrameFormat.pixelFormatFromImageFormat | QVideoFrameFormat.pixelFormatFromImageFormat()},
     * {@link QImage.convertedTo | QImage.convertedTo()}, and
     * {@link QImage.isNull | QImage.isNull()}.
     * @param image The image to construct a video frame from.
     */
    constructor(image: QImage);
    /**
     * Constructs a video frame of the given pixel *{@link format}*.
     * @param format The pixel format to construct a frame from.
     */
    constructor(format: QVideoFrameFormat);
    /**
     * Constructs a QVideoFrame from a {@link QAbstractVideoBuffer}.
     *
     * The specified *{@link videoBuffer}* refers to an instance a
     * reimplemented {@link QAbstractVideoBuffer}. The instance is
     * expected to contains a preallocated custom video buffer and
     * must implement
     * {@link QAbstractVideoBuffer.format | QAbstractVideoBuffer.format()},
     * {@link QAbstractVideoBuffer.map | QAbstractVideoBuffer.map()},
     * and
     * {@link QAbstractVideoBuffer.unmap | QAbstractVideoBuffer.unmap()}
     * for GPU content.
     *
     * If *{@link videoBuffer}* is null or gets an invalid
     * {@link QVideoFrameFormat}, the constructors creates an invalid
     * video frame.
     *
     * The created frame will hold ownership of the specified video
     * buffer for its lifetime. Considering that QVideoFrame is
     * implemented via a shared private object, the specified video
     * buffer will be destroyed upon destruction of the last copy of
     * the created video frame.
     *
     * Note, if a video frame has been passed to
     * {@link QMediaRecorder} or a rendering pipeline, the lifetime of
     * the frame is undefined, and the media recorder can destroy it
     * in a different thread.
     *
     * QVideoFrame will contain own instance of
     * {@link QVideoFrameFormat}. Upon invoking
     * {@link QVideoFrameFormat.setStreamFrameRate | setStreamFrameRate()},
     * {@link QVideoFrameFormat.setMirrored | setMirrored()}, or
     * {@link QVideoFrameFormat.setRotation | setRotation()}, the
     * inner format can be modified, and
     * {@link QVideoFrameFormat.surfaceFormat | surfaceFormat()} will
     * return a detached instance.
     *
     * @see also {@link QAbstractVideoBuffer} and
     * {@link QVideoFrameFormat}.
     * @param videoBuffer The video buffer to construct a video frame
     * from. Will be **moved** to the frame, **not copied.**
     */
    constructor(videoBuffer: QAbstractVideoBuffer);
    /**
     * Constructs a shallow copy of *{@link other}*. Since QVideoFrame
     * is explicitly shared, these two instances will reflect the same
     * frame.
     * @param other The video frame to copy from.
     */
    constructor(other: QVideoFrame);
    constructor(
        arg?:
            | NativeElement
            | QImage
            | QVideoFrameFormat
            | QAbstractVideoBuffer
            | QVideoFrame,
    ) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (
            arg instanceof QImage ||
            arg instanceof QVideoFrameFormat ||
            arg instanceof QAbstractVideoBuffer ||
            arg instanceof QVideoFrame
        ) {
            native = new addon.QVideoFrame(arg.native);
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QVideoFrame()",
            );
        }
        super(native);
    }
    /**
     * Returns a buffer pointer to the start of the frame data buffer
     * for a *{@link plane}*.
     *
     * This value is only valid while the frame data is
     * {@link QVideoFrame.map | mapped}.
     *
     * Changes made to data accessed via this pointer (when mapped
     * with write access) are only guaranteed to have been persisted
     * when {@link QVideoFrame.unmap | unmap()} is called and when the
     * buffer has been mapped for writing.
     *
     * @see also {@link QVideoFrame.map | map()},
     * {@link QVideoFrame.mappedBytes | mappedBytes()},
     * {@link QVideoFrame.bytesPerLine | bytesPerLine()}, and
     * {@link QVideoFrame.planeCount | planeCount())}.
     * @param plane The plane to get a buffer from.
     * @returns a pointer buffer to the start of a frame data buffer.
     */
    bits(plane: number): Buffer {
        return this.native.bits(plane);
    }
    /**
     * Returns the number of bytes in a scan line of a
     *{@link plane}*.
     *
     * This value is only valid while the frame data is
     * {@link QVideoFrame.map | mapped}.
     *
     * @see also {@link QVideoFrame.bits | bits()},
     * {@link QVideoFrame.map | map()},
     * {@link QVideoFrame.mappedBytes | mappedBytes()}, and
     * {@link QVideoFrame.planeCount | planeCount()}.
     * @param plane The plane to get the number of bytes for.
     * @returns the number of bytes in a scan line of the plane.
     */
    bytesPerLine(plane: number): number {
        return this.native.bytesPerLine(plane);
    }
    /**
     * Returns the presentation time (in microseconds) when a frame
     * should stop being displayed.
     *
     * An invalid time is represented as `-1`.
     *
     * @see also {@link QVideoFrame.setEndTime | setEndTime()}.
     * @returns the end time in microseconds.
     */
    endTime(): number {
        return this.native.endTime();
    }
    /**
     * Returns the type of a video frame's handle.
     *
     * The handle type could either be a
     * {@link HandleType.NoHandle | NoHandle}, meaning that the frame
     * is memory based, or a RHI texture.
     * @returns the type of a video frame's handle.
     */
    handleType(): HandleType {
        return this.native.handleType();
    }
    /**
     * Returns the height of a video frame.
     * @return the height of a video frame.
     */
    height(): number {
        return this.native.height();
    }
    /**
     * Identifies if a video frame's contents are currently mapped to
     * system memory.
     *
     * This is a convenience function which checks that the
     * {@link MapMode} of the frame is not equal to
     * {@link MapMode.NotMapped | NotMapped}.
     *
     * Returns true if the contents of the video frames are mapped to
     * system memory, and false otherwise.
     *
     * @see also {@link QVideoFrame.mapMode | mapMode()} and
     * {@link MapMode}.
     * @returns If the frame contents are mapped to memory.
     */
    isMapped(): boolean {
        return this.native.isMapped();
    }
    /**
     * Identifies if the mapped contents of a video frame were read
     * from the frame when it was mapped.
     *
     * This is a convenience function which checks if the
     * {@link MapMode} contains the
     * {@link MapMode.ReadOnly | ReadOnly} flag.
     *
     * Returns true if the contents of the mapped memory were read
     * from the video frame, and false otherwise.
     *
     * @see also {@link QVideoFrame.mapMode | mapMode()} and
     * {@link MapMode}.
     * @returns If the mapped frame contents were read when it was
     * mapped.
     */
    isReadable(): boolean {
        return this.native.isReadable();
    }
    /**
     * Identifies whether a video frame is valid.
     *
     * An invalid frame has no video buffer associated with it.
     *
     * Returns true if the frame is valid, and false if it is not.
     *
     * @returns If the frame is valid or not.
     */
    isValid(): boolean {
        return this.native.isValid();
    }
    /**
     * Identifies if the mapped contents of a video frame will be
     * persisted when the frame is unmapped.
     *
     * This is a convenience function which checks if the
     * {@link MapMode} contains the
     * {@link MapMode.WriteOnly | WriteOnly} flag.
     *
     * Returns true if the video frame will be updated when unmapped,
     * and false otherwise.
     *
     * > **Note:** The result of altering the data of a frame that is
     * mapped in read-only mode is undefined. Depending on the buffer
     * implementation the changes may be persisted, or worse alter a
     * shared buffer.
     *
     * @see also {@link QVideoFrame.mapMode | mapMode()} and
     * {@link MapMode}.
     * @returns If the mapped frame contents will be persisted when
     * the frame is unmapped.
     */
    isWritable(): boolean {
        return this.native.isWritable();
    }
    /**
     * Maps the contents of a video frame to system (CPU addressable)
     * memory.
     *
     * In some cases the video frame data might be stored in video
     * memory or otherwise inaccessible memory, so it is necessary to
     * map a frame before accessing the pixel data. This may involve
     * copying the contents around, so avoid mapping and unmapping
     * unless required.
     *
     * The map *{@link mode}* indicates whether the contents of the
     * mapped memory should be read from and/or written to the frame.
     * If the map mode includes the {@link MapMode.ReadOnly} flag the
     * mapped memory will be populated with the content of the video
     * frame when initially mapped. If the map mode includes the
     * {@link MapMode.WriteOnly} flag the content of the possibly
     * modified mapped memory will be written back to the frame when
     * unmapped.
     *
     * While mapped the contents of a video frame can be accessed
     * directly through the pointer returned by the
     * {@link QVideoFrame.bits | bits()} function.
     *
     * When access to the data is no longer needed, be sure to call
     * the {@link QVideoFrame.unmap | unmap()} function to release the
     * mapped memory and possibly update the video frame contents.
     *
     * If the video frame has been mapped in read only mode, it is
     * permissible to map it multiple times in read only mode (and
     * unmap it a corresponding number of times). In all other cases
     * it is necessary to unmap the frame first before mapping a
     * second time.
     *
     * > **Note:** Writing to memory that is mapped as read-only is
     * undefined, and may result in changes to shared data or crashes.
     *
     * Returns true if the frame was mapped to memory in the given
     * *{@link mode}* and false otherwise.
     *
     * @see also {@link QVideoFrame.unmap | unmap()},
     * {@link QVideoFrame.mapMode | mapMode()}, and
     * {@link QVideoFrame.bits | bits()}.
     * @param The map mode to use.
     */
    map(mode: MapMode): void {
        this.native.map(mode);
    }
    /**
     * Returns the mode a video frame was mapped to system memory in.
     *
     * @see also {@link QVideoFrame.map | map()} and {@link MapMode}.
     * @returns The current map mode.
     */
    mapMode(): MapMode {
        return this.native.mapMode();
    }
    /**
     * Returns the number of bytes occupied by plane *{@link plane}*
     * of the mapped frame data.
     *
     * This value is only valid while the frame data is
     * {@link QVideoFrame.map | mapped}.
     *
     * @see also {@link QVideoFrame.map | map()}.
     * @param plane The plane to get mapped bytes from.
     * @returns The number of bytes of mapped frame data.
     */
    mappedBytes(plane: number): number {
        return this.native.mappedBytes(plane);
    }
    /**
     * Returns whether the frame should be mirrored around its
     * vertical axis before displaying.
     *
     * Transformations of `QVideoFrame`, specifically rotation and
     * mirroring, are used only for displaying the video frame and are
     * applied on top of the surface transformation, which is
     * determined by {@link QVideoFrameFormat}. Mirroring is applied
     * after rotation.
     *
     * Mirroring is typically needed for video frames coming from a
     * front camera of a mobile device.
     *
     * @see also {@link QVideoFrame.setMirrored | setMirrored()}.
     * @returns If the frame should be vertically mirrored.
     */
    mirrored(): boolean {
        return this.native.mirrored();
    }
    /**
     * Uses a {@link QPainter}, *{@link painter}*, to render this
     * QVideoFrame to *{@link rect}*. The PaintOptions
     *{@link options}* can be used to specify a background color and
     * how *{@link rect}* should be filled with the video.
     *
     * > **Note:** that rendering will usually happen without hardware
     * acceleration when using this method.
     *
     * @param painter The QPainter to use.
     * @param rect The rect to render to.
     * @param options Any options to use.
     */
    paint(
        painter: QPainter,
        rect: QRectF,
        options: PaintOptions,
    ): void {
        return this.native.paint();
    }
    /**
     * Returns the pixel format of this video frame.
     *
     * @returns the pixel format of this frame.
     */
    pixelFormat(): PixelFormat {
        return this.native.pixelFormat();
    }
    /**
     * Returns the number of planes in the video frame.
     *
     * @see also {@link QVideoFrame.map | map()}.
     * @returns The plane count in the frame.
     */
    planeCount(): number {
        return this.native.planeCount();
    }
    /**
     * Returns the angle the frame should be rotated clockwise before
     * displaying.
     *
     * Transformations of `QVideoFrame`, specifically rotation and
     * mirroring, are used only for displaying the video frame and are
     * applied on top of the surface transformation, which is
     * determined by {@link QVideoFrameFormat}. Rotation is applied
     * before mirroring.
     *
     * @see also {@link QVideoFrame.setRotation | setRotation()}.
     * @returns The clockwise angle that the frame should rotated.
     */
    rotation(): Rotation {
        return this.native.rotation();
    }
    /**
     * Sets the presentation *{@link time}* (in microseconds) when a
     * frame should stop being displayed.
     *
     * An invalid time is represented as `-1`.
     *
     * @see also {@link QVideoFrame.endTime | endTime()}.
     * @param time The end time (in microseconds) to set.
     */
    setEndTime(time: number): void {
        this.native.setEndTime(time);
    }
    /**
     * Sets whether the frame should be *{@link mirrored}* around its
     * vertical axis before displaying.
     *
     * Transformations of `QVideoFrame`, specifically rotation and
     * mirroring, are used only for displaying the video frame and are
     * applied on top of the surface transformation, which is
     * determined by {@link QVideoFrameFormat}. Mirroring is applied
     * after rotation.
     *
     * Mirroring is typically needed for video frames coming from a
     * front camera of a mobile device.
     *
     * Default value is `false`.
     *
     * @see also {@link QVideoFrame.mirrored | mirrored()}.
     * @param mirrored Whether the frame should be mirrored.
     */
    setMirrored(mirrored: boolean): void {
        this.native.setMirrored(mirrored);
    }
    /**
     * Sets the *{@link angle}* the frame should be rotated clockwise
     * before displaying.
     *
     * Transformations of `QVideoFrame`, specifically rotation and
     * mirroring, are used only for displaying the video frame and are
     * applied on top of the surface transformation, which is
     * determined by {@link QVideoFrameFormat}. Rotation is applied
     * before mirroring.
     *
     * Default value is {@link Rotation.None}.
     *
     * @see also {@link QVideoFrame.rotation | rotation()}.
     * @param angle The clockwise angle to set.
     */
    setRotation(angle: Rotation): void {
        this.native.setRotation(angle);
    }
    /**
     * Sets the presentation *{@link time}* (in microseconds) when the
     * frame should initially be displayed.
     *
     * An invalid time is represented as -1.
     *
     * @see also {@link QVideoFrame.startTime | startTime()}.
     * @param time The start time to set.
     */
    setStartTime(time: number): void {
        this.native.setStartTime(time);
    }
    /**
     * Sets the frame *{@link rate}* of a video stream in frames per
     * second.
     *
     * @see also
     * {@link QVideoFrame.streamFrameRate | streamFrameRate()}.
     * @param rate The frame rate to set.
     */
    setStreamFrameRate(rate: number): void {
        this.native.setStreamFrameRate(rate);
    }
    /**
     * Sets the subtitle text that should be rendered together with
     * this video frame to *{@link text}*.
     *
     * @see also {@link QVideoFrame.subtitleText | subtitleText()}.
     * @param text The subtitle text to set.
     */
    setSubtitleText(text: string): void {
        this.native.setSubtitleText(text);
    }
    /**
     * Returns the dimensions of a video frame.
     *
     * @returns The frame dimensions.
     */
    size(): QSize {
        return this.native.size();
    }
    /**
     * Returns the presentation time (in microseconds) when the frame
     * should be displayed.
     *
     * An invalid time is represented as `-1`.
     *
     * @see also {@link QVideoFrame.setStartTime | setStartTime()}.
     * @returns The start time in microseconds.
     */
    startTime(): number {
        return this.native.startTime();
    }
    /**
     * Returns the frame rate of a video stream in frames per second.
     *
     * @see also
     * {@link QVideoFrame.setStreamFrameRate | setStreamFrameRate()}.
     * @returns The stream frame rate.
     */
    streamFrameRate(): number {
        return this.native.streamFrameRate();
    }
    /**
     * Returns the subtitle text that should be rendered together with
     * this video frame.
     *
     * @see also
     * {@link QVideoFrame.setSubtitleText | setSubtitleText()}.
     * @returns The subtitle text.
     */
    subtitleText(): string {
        return this.native.subtitleText();
    }
    /**
     * Returns the surface format of this video frame.
     *
     * @returns The frame's surface format.
     */
    surfaceFormat(): QVideoFrameFormat {
        return this.native.surfaceFormat();
    }
    /**
     * Swaps the current video frame with *{@link other}*.
     *
     * @param other The frame to swap with.
     */
    swap(other: QVideoFrame): void {
        this.native.swap(other);
    }
    /**
     * Converts current video frame to image.
     *
     * The conversion is based on the current pixel data and the
     * {@link QVideoFrameFormat | surface format}. Transformations of
     * the frame don't impact the result since they are applied for
     * presentation only.
     *
     * @returns The frame as an image.
     */
    toImage(): QImage {
        return this.native.toImage();
    }
    /**
     * Releases the memory mapped by the
     * {@link QVideoFrame.map | map()} function.
     *
     * If the {@link MapMode} included the {@link MapMode.WriteOnly}
     * flag this will persist the current content of the mapped memory
     * to the video frame.
     *
     * unmap() should not be called if {@link QVideoFrame.map | map()}
     * function failed.
     *
     * @see also {@link QVideoFrame.map | map()}.
     */
    unmap(): void {
        this.native.unmap();
    }
    /**
     * Returns the width of a video frame.
     * @returns The frame's width.
     */
    width(): number {
        return this.native.width();
    }
    /**
     * Returns `true` if this QVideoFrame and *{@link other}* reflect
     * the same frame.
     *
     * @param other The other frame to test against.
     * @returns If this frame is the same as other.
     */
    equals(other: QVideoFrame): boolean {
        return this.native.equals(other);
    }
}

/**
 * Identifies the type of a video buffers handle.
 *
 * @see also {@link QVideoFrame.handleType | QVideoFrame.handleType()}
 */
export enum HandleType {
    /**
     * The buffer has no handle, its data can only be accessed by
     * mapping the buffer.
     */
    NoHandle = 0,
    /**
     * The handle of the buffer is defined by The Qt Rendering
     * Hardware Interface (RHI). RHI is Qt's internal graphics
     * abstraction for 3D APIs, such as OpenGL, Vulkan, Metal, and
     * Direct 3D.
     */
    RhiTextureHandle = 1,
}

/**
 * Enumerates how a video buffer's data is mapped to system memory.
 *
 * @see also {@link QVideoFrame.mapMode | QVideoFrame.mapMode()} and
 * {@link QVideoFrame.map | QVideoFrame.map()}.
 */
export enum MapMode {
    /**
     * The video buffer is not mapped to memory.
     */
    NotMapped = 0x0,
    /**
     * The mapped memory is populated with data from the video buffer
     * when mapped, but the content of the mapped memory may be
     * discarded when unmapped.
     */
    ReadOnly = 0x1,
    /**
     * The mapped memory is uninitialized when mapped, but the
     * possibly modified content will be used to populate the video
     * buffer when unmapped.
     */
    WriteOnly = 0x2,
    /**
     * The mapped memory is populated with data from the video buffer,
     * and the video buffer is repopulated with the content of the
     * mapped memory when it is unmapped.
     */
    ReadWrite = ReadOnly | WriteOnly,
}

export interface PaintOptions {
    backgroundColor: QColor;
    aspectRatioMode: AspectRatioMode;
    paintFlags: PaintFlag;
}

export enum PaintFlag {
    DontDrawSubtitles = 0x1,
}
