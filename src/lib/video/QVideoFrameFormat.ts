import {
    checkIfNativeElement,
    Component,
    NativeElement,
} from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QSize, QRect, QImageFormat } from "@nodegui/nodegui";
import { Rotation } from "./QtVideo";

/**
 * @summary The QVideoFrameFormat class specifies the stream format of
 * a video presentation surface.
 *
 * @remarks
 * A video sink presents a stream of video frames. QVideoFrameFormat
 * describes the type of the frames and determines how they should be
 * presented.
 *
 * The core properties of a video stream required to set up a video
 * sink are the pixel format given by
 * {@link QVideoFrameFormat.pixelFormat | pixelFormat()}, and the
 * frame dimensions given by
 * {@link QVideoFrameFormat.frameSize | frameSize()}.
 *
 * The region of a frame that is actually displayed on a video surface
 * is given by the {@link QVideoFrameFormat.viewport | viewport()}. A
 * stream may have a viewport less than the entire region of a frame
 * to allow for videos smaller than the nearest optimal size of a
 * video frame. For example the width of a frame may be extended so
 * that the start of each scan line is eight byte aligned.
 *
 * Other common properties are the
 * {@link QVideoFrameFormat.scanLineDirection | scanLineDirection()},
 * {@link QVideoFrameFormat.frameRate | frameRate()} and the
 * yCrCbColorSpace().
 *
 * @see https://doc.qt.io/qt-6/qvideoframeformat.html for Qt's docs
 */
export class QVideoFrameFormat extends Component {
    /** The native C++ QVideoFrameFormat variable. */
    declare native: NativeElement;
    /** Constructs a null video stream format. */
    constructor();
    /**
     * Copy a native QVideoFrameFormat to node bindings.
     * @param nativeElement A native QVideoFrameFormat element.
     */
    constructor(native: NativeElement);
    /**
     * Constructs a video stream with the given frame *{@link size}*
     * and pixel *{@link format}*.
     * @param size The frame size to set the format to.
     * @param format The pixel format to set the format to.
     */
    constructor(size: QSize, format: PixelFormat);
    /**
     * Constructs a copy of *{@link other}*.
     * @param other The other frame format to copy.
     */
    constructor(other: QVideoFrameFormat);
    constructor(
        arg?: NativeElement | QSize | QVideoFrameFormat,
        format?: PixelFormat,
    ) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg;
        } else if (arg instanceof QVideoFrameFormat) {
            native = new addon.QVideoFrameFormat(arg);
        } else if (arg instanceof QSize && format) {
            native = new addon.QVideoFrameFormat(arg, format);
        } else if (arguments.length === 0) {
            native = new addon.QVideoFrameFormat();
        } else {
            throw new TypeError(
                "Wrong number/type of arguments, refer to QVideoFrameFormat()",
            );
        }
        super(native);
    }
    /**
     * Returns the color range that should be used to render the video
     * stream.
     *
     * @see also {@link QVideoFrameFormat.setColorRange | setColorRange()}.
     * @returns The color range for rendering use.
     */
    colorRange(): ColorRange {
        return this.native.colorRange();
    }
    /**
     * Returns the color space of a video stream.
     *
     * @see also {@link QVideoFrameFormat.setColorSpace | setColorSpace()}.
     * @returns The video's color space.
     */
    colorSpace(): ColorSpace {
        return this.native.colorSpace();
    }
    /**
     * Returns the color transfer function that should be used to
     * render the video stream.
     *
     * @see also {@link QVideoFrameFormat.setColorTransfer | setColorTransfer()}.
     * @returns The color transfer function for rendering use.
     */
    colorTransfer(): ColorTransfer {
        return this.native.colorTransfer();
    }
    /**
     * Returns the height of frame in a video stream.
     *
     * @returns The video frame height.
     */
    frameHeight(): number {
        return this.native.frameHeight();
    }
    /**
     * Returns the frame rate of a video stream in frames per second.
     *
     * @see also {@link QVideoFrameFormat.frameRate | frameRate()}.
     * @returns The video's frame rate.
     */
    frameRate(): number {
        return this.native.frameRate();
    }
    /**
     * Returns the dimensions of frames in a video stream.
     *
     * @see also {@link QVideoFrameFormat.setFrameSize | setFrameSize()},
     * {@link QVideoFrameFormat.frameWidth | frameWidth()}, and
     * {@link QVideoFrameFormat.frameHeight | frameHeight()}.
     * @returns The video frame dimensions.
     */
    frameSize(): QSize {
        return this.native.frameSize();
    }
    /**
     * Returns the width of frames in a video stream.
     *
     * @see also {@link QVideoFrameFormat.frameSize | frameSize()} and
     * {@link QVideoFrameFormat.frameHeight | frameHeight()}.
     * @returns The video frame width.
     */
    frameWidth(): number {
        return this.native.frameWidth();
    }
    /**
     * Returns `true` if the surface is mirrored around its vertical
     * axis.
     *
     * Transformations of `QVideoFrameFormat`, specifically, rotation
     * and mirroring, can be determined by the orientation of the
     * camera sensor, camera settings, or the orientation of the video
     * stream.
     *
     * Mirroring is applied after rotation.
     *
     * > **Note:** The mirroring here differs from
     * {@link QImage.mirrored | QImage.mirrored()}, as a vertically
     * mirrored {@link QImage} will be mirrored around its x-axis.
     * @returns Whether or not if the frame should be mirrored.
     */
    isMirrored(): boolean {
        return this.native.isMirrored();
    }
    /**
     * Identifies if a video surface format has a valid pixel format
     * and frame size.
     *
     * Returns true if the format is valid, and false otherwise.
     *
     * @returns If the format is valid or not.
     */
    isValid(): boolean {
        return this.native.isValid();
    }
    /**
     * Returns the pixel format of frames in a video stream.
     *
     * @returns The video frame's pixel format.
     */
    pixelFormat(): PixelFormat {
        return this.native.pixelFormat();
    }
    /**
     * Returns the number of planes used. This number is depending on
     * the pixel format and is 1 for RGB based formats, and a number
     * between 1 and 3 for YUV based formats.
     *
     * @returns The number of planes used.
     */
    planeCount(): number {
        return this.native.planeCount();
    }
    /**
     * Returns the angle by which the surface is rotated clockwise.
     *
     * Transformations of `QVideoFrameFormat`, specifically, rotation
     * and mirroring, can be determined by the orientation of the
     * camera sensor, camera settings, or the orientation of the video
     * stream.
     *
     * Rotation is applied before mirroring.
     *
     * @see also {@link QVideoFrameFormat.setRotation | setRotation()}.
     * @returns The clockwise angle the frame should be rotated.
     */
    rotation(): Rotation {
        return this.native.rotation();
    }
    /**
     * Returns the direction of scan lines.
     *
     * @see also {@link QVideoFrameFormat.setScanLineDirection | setScanLineDirection()}.
     * @returns The scan lines' direction.
     */
    scanLineDirection(): Direction {
        return this.native.scanLineDirection();
    }
    /**
     * Sets the color transfer range that should be used to render the
     * video stream to *{@link range}*.
     *
     * @see also {@link QVideoFrameFormat.colorRange | colorRange()}.
     * @param range The color transfer range to set.
     */
    setColorRange(range: ColorRange): void {
        this.native.setColorRange(range);
    }
    /**
     * Sets the *{@link colorSpace}* of a video stream.
     *
     * @see also {@link QVideoFrameFormat.colorSpace | colorSpace()}.
     * @param colorSpace The color space to set.
     */
    setColorSpace(colorSpace: ColorSpace): void {
        this.native.setColorSpace(colorSpace);
    }
    /**
     * Sets the color transfer function that should be used to render
     * the video stream to *{@link colorTransfer}*.
     *
     * @see also {@link QVideoFrameFormat.colorTransfer | colorTransfer()}.
     * @param colorTransfer The color transfer function to set.
     */
    setColorTransfer(colorTransfer: ColorTransfer): void {
        this.native.setColorTransfer(colorTransfer);
    }
    /**
     * Sets the frame *{@link rate}* of a video stream in frames per
     * second.
     *
     * @see also {@link QVideoFrameFormat.frameRate | frameRate()}.
     * @param rate The frame rate to set.
     */
    setFrameRate(rate: number): void {
        this.native.setFrameRate(rate);
    }
    /**
     * Sets the size of frames in a video stream to size, either a
     * QSize or a width and height.
     *
     * This will reset the
     * {@link QVideoFrameFormat.viewport | viewport()} to fill the
     * entire frame.
     *
     * @see also {@link QVideoFrameFormat.frameSize | frameSize()}.
     * @param widthOrSize Either a QSize or a width to set.
     * @param height The height to set.
     */
    setFrameSize(widthOrSize: QSize | number, height?: number) {
        if (widthOrSize instanceof QSize) {
            this.native.setFrameSize(widthOrSize);
        } else if (height) {
            this.native.setFrameSize(widthOrSize);
        } else {
            throw new TypeError(
                "Wrong type/amount of arguments, see QVideoFrameFormat.setFrameSize()",
            );
        }
    }
    /**
     * Sets the maximum luminance to the given value, *{@link lum}*.
     *
     * @param lum The maximum luminance to set.
     */
    setMaxLuminance(lum: number): void {
        this.native.setMaxLuminance(lum);
    }
    /**
     * Sets if the surface is *{@link mirrored}* around its vertical
     * axis.
     *
     * Transformations of `QVideoFrameFormat`, specifically, rotation
     * and mirroring, can be determined by the orientation of the
     * camera sensor, camera settings, or the orientation of the video
     * stream.
     *
     * Mirroring is applied after rotation.
     *
     * Default value is `false`.
     *
     * > *Note:** The mirroring here differs from
     * {@link QImage.mirrored | QImage.mirrored()}, as a vertically
     * mirrored {@link QImage} will be mirrored around its x-axis.
     *
     * @see also {@link QVideoFrameFormat.isMirrored | isMirrored()}.
     * @param mirrored Set to whether or not the video should be
     * mirrored vertically.
     */
    setMirrored(mirrored: boolean): void {
        this.native.setMirrored(mirrored);
    }
    /**
     * Sets the *{@link angle}* by which the surface is rotated
     * clockwise.
     *
     * Transformations of `QVideoFrameFormat`, specifically, rotation
     * and mirroring, can be determined by the orientation of the
     * camera sensor, camera settings, or the orientation of the video
     * stream.
     *
     * Rotation is applied before mirroring.
     *
     * Default value is {@link Rotation.None}.
     *
     * @see also {QVideoFrameFormat.rotation | rotation()}.
     * @param angle The clockwise angle the video frame should be
     * rotated.
     */
    setRotation(angle: Rotation): void {
        this.native.setRotation(angle);
    }
    /**
     * Sets the *{@link direction}* of scan lines.
     *
     * @see also {@link QVideoFrameFormat.scanLineDirection | scanLineDirection()}.
     * @param direction The scan line direction to set.
     */
    setScanLineDirection(direction: Direction): void {
        this.native.setScanLineDirection(direction);
    }
    /**
     * Sets the frame *{@link rate}* of a video stream in frames per
     * second.
     *
     * @see also {@link QVideoFrameFormat.streamFrameRate | streamFrameRate()}.
     * @param rate The stream frame rate to set.
     */
    setStreamFrameRate(rate: number): void {
        this.native.setStreamFrameRate(rate);
    }
    /**
     * Sets the viewport of a video stream to *{@link viewport}*.
     *
     * @see also {@link QVideoFrameFormat.viewport | viewport()}.
     * @param viewport The viewport to set the video stream to.
     */
    setViewport(viewport: QRect): void {
        this.native.setViewport(viewport);
    }
    /**
     * Returns the frame rate of a video stream in frames per second.
     *
     * @see also {@link QVideoFrameFormat.setStreamFrameRate | setStreamFrameRate()}.
     * @returns The stream frame rate.
     */
    streamFrameRate(): number {
        return this.native.streamFrameRate();
    }
    /**
     * Swaps the current video frame format with the *{@link other}*.
     *
     * @param other The video frame format to swap with.
     */
    swap(other: QVideoFrameFormat): void {
        this.native.swap(other);
    }
    /**
     * Returns the viewport of a video stream.
     *
     * The viewport is the region of a video frame that is actually
     * displayed.
     *
     * By default the viewport covers an entire frame.
     *
     * @see also {@link QVideoFrameFormat.setViewPort | setViewPort()}.
     * @returns The video stream's viewport.
     */
    viewport(): QRect {
        return this.native.viewport();
    }
    /**
     * Returns true if *{@link other}* is the same as this video
     * format, and false if they are different.
     *
     * @returns If the frame format is the same as the other one.
     */
    equals(other: QVideoFrameFormat): boolean {
        return this.native.equals(other);
    }
    /**
     * Returns an image format equivalent to a video frame pixel
     * *{@link format}*. If there is no equivalent format
     * {@link QImageFormat.Format_Invalid} is returned instead.
     *
     * > **Note:** In general {@link QImage} does not handle YUV
     * formats.
     *
     * @param format The pixel format to convert.
     * @returns The equivalent QImage format.
     */
    static imageFormatFromPixelFormat(
        format: PixelFormat,
    ): QImageFormat {
        return addon.QVideoFrameFormat.imageFormatFromPixelFormat(
            format,
        );
    }
    /**
     * Returns a video pixel format equivalent to an image
     * *{@link format}*. Ifthere is no equivalent format
     * {@link PixelFormat.Format_Invalid} is returned instead.
     *
     * > **Note:** In general {@link QImage} does not handle YUV
     * formats.
     *
     * @param format The QImage format to convert.
     * @returns The equivalent pixel format.
     */
    static pixelFormatFromImageFormat(
        format: QImageFormat,
    ): PixelFormat {
        return addon.QVideoFrameFormat.pixelFormatFromImageFormat(
            format,
        );
    }
    /**
     * Returns a string representation of the given
     * *{@link pixelFormat}*.
     *
     * @format format The pixel format to get a string name for.
     * @returns The string name of the format.
     */
    static pixelFormatToString(format: PixelFormat): string {
        return addon.QVideoFrameFormat.pixelFormatToString(format);
    }
}

/**
 * Describes the color range used by the video data. Video data
 * usually comes in either full color range, where all values are
 * being used, or a more limited range traditionally used in YUV video
 * formats, where a subset of all values is being used.
 */
export enum ColorRange {
    /** The color range of the video is unknown. */
    ColorRange_Unknown = 0,
    /**
     * The color range traditionally used by most YUV video formats.
     * For 8 bit formats, the Y component is limited to values between
     * 16 and 235. The U and V components are limited to values
     * between 16 and 240
     *
     * For higher bit depths multiply these values with 2^(depth-8).
     */
    ColorRange_Video = 1,
    /**
     * Full color range. All values from 0 to 2^depth - 1 are valid.
     */
    ColorRange_Full = 2,
}

/** Enumerates the color space of video frames. */
export enum ColorSpace {
    /** No color space is specified. */
    ColorSpace_Undefined = 0,
    /**
     * A color space defined by ITU-R recommendation BT.601 with Y
     * value range from 16 to 235, and Cb/Cr range from 16 to 240.
     * Used mostly by older videos that were targeting CRT displays.
     */
    ColorSpace_BT601 = 1,
    /**
     * A color space defined by ITU-R BT.709 with the same values
     * range as ColorSpace_BT601. The most commonly used color space
     * today.
     */
    ColorSpace_BT709 = 2,
    /** The full range YUV color space used in most JPEG files. */
    ColorSpace_AdobeRgb = 5,
    /**
     * The color space defined by ITU-R BT.2020. Used mainly for HDR
     * videos.
     */
    ColorSpace_BT2020 = 6,
}

export enum ColorTransfer {
    /** The color transfer function is unknown. */
    ColorTransfer_Unknown = 0,
    /**
     * Color values are encoded according to BT709. This is close to,
     * but not identical to a gamma curve of 2.2, and the same
     * transfer curve as is used in sRGB.
     * @see also https://www.itu.int/rec/R-REC-BT.709/en.
     */
    ColorTransfer_BT709 = 1,
    /**
     * Color values are encoded according to BT601.
     * @see also https://www.itu.int/rec/R-REC-BT.601/en.
     */
    ColorTransfer_BT601 = 2,
    /** Color values are linear */
    ColorTransfer_Linear = 3,
    /** Color values are encoded with a gamma of 2.2 */
    ColorTransfer_Gamma22 = 4,
    /** Color values are encoded with a gamma of 2.8 */
    ColorTransfer_Gamma28 = 5,
    /**
     * Color values are encoded using STME ST 2084. This transfer
     * function is the most common HDR transfer function and often
     * called the 'perceptual quantizer'.
     * @see also https://www.itu.int/rec/R-REC-BT.2100 and
     * https://en.wikipedia.org/wiki/Perceptual_quantizer.
     */
    ColorTransfer_ST2084 = 6,
    /**
     * Color values are encoded using ARIB STD B67. This transfer
     * function is also often referred to as 'hybrid log gamma'.
     * @see also https://www.itu.int/rec/R-REC-BT.2100 and
     * https://en.wikipedia.org/wiki/Hybrid_log–gamma.
     */
    ColorTransfer_STD_B67 = 7,
}

/** Enumerates the layout direction of video scan lines. */
export enum Direction {
    /**
     * Scan lines are arranged from the top of the frame to the
     * bottom.
     */
    TopToBottom = 0,
    /**
     * Scan lines are arranged from the bottom of the frame to the
     * top.
     */
    BottomToTop = 1,
}

/** Enumerates video data types. */
export enum PixelFormat {
    /** The frame is invalid. */
    Format_Invalid = 0,
    /**
     * The frame is stored using a ARGB format with 8 bits per
     * component.
     */
    Format_ARGB8888 = 1,
    /**
     * The frame stored using a premultiplied ARGB format with 8 bits
     * per component.
     */
    Format_ARGB8888_Premultiplied = 2,
    /**
     * The frame stored using a 32 bits per pixel RGB format (0xff, R,
     * G, B).
     */
    Format_XRGB8888 = 3,
    /**
     * The frame is stored using a 32-bit BGRA format (0xBBGGRRAA).
     */
    Format_BGRA8888 = 4,
    /**
     * The frame is stored using a premultiplied 32bit BGRA format.
     */
    Format_BGRA8888_Premultiplied = 5,
    /**
     * The frame is stored using a 32-bit ABGR format (0xAABBGGRR).
     */
    Format_ABGR8888 = 7,
    /** The frame is stored using a 32-bit BGR format (0xffBBGGRR). */
    Format_XBGR8888 = 8,
    /**
     * The frame is stored in memory as the bytes R, G, B, A/X, with R
     * at the lowest address and A/X at the highest address.
     */
    Format_RGBA8888 = 9,
    /**
     * The frame is stored in format 32-bit BGRx format, [31:0]
     * B:G:R:x 8:8:8:8 little endian
     */
    Format_BGRX8888 = 6,
    /**
     * The frame is stored in memory as the bytes R, G, B, A/X, with R
     * at the lowest address and A/X at the highest address.
     */
    Format_RGBX8888 = 10,
    /**
     * The frame is stored using a packed 32-bit AYUV format
     * (0xAAYYUUVV).
     */
    Format_AYUV = 11,
    /**
     * The frame is stored using a packed premultiplied 32-bit AYUV
     * format (0xAAYYUUVV).
     */
    Format_AYUV_Premultiplied = 12,
    /**
     * The frame is stored using an 8-bit per component planar YUV
     * format with the U and V planes horizontally and vertically
     * sub-sampled, i.e. the height and width of the U and V planes
     * are half that of the Y plane.
     */
    Format_YUV420P = 13,
    /**
     * The frame is stored using an 8-bit per component planar YUV
     * format with the U and V planes horizontally sub-sampled, i.e.
     * the width of the U and V planes are half that of the Y plane,
     * and height of U and V planes is the same as Y.
     */
    Format_YUV422P = 14,
    /**
     * The frame is stored using an 8-bit per component planar YVU
     * format with the V and U planes horizontally and vertically
     * sub-sampled, i.e. the height and width of the V and U planes
     * are half that of the Y plane.
     */
    Format_YV12 = 15,
    /**
     * The frame is stored using an 8-bit per component packed YUV
     * format with the U and V planes horizontally sub-sampled
     * (U-Y-V-Y), i.e. two horizontally adjacent pixels are stored as
     * a 32-bit macropixel which has a Y value for each pixel and
     * common U and V values.
     */
    Format_UYVY = 16,
    /**
     * The frame is stored using an 8-bit per component packed YUV
     * format with the U and V planes horizontally sub-sampled
     * (Y-U-Y-V), i.e. two horizontally adjacent pixels are stored as
     * a 32-bit macropixel which has a Y value for each pixel and
     * common U and V values.
     */
    Format_YUYV = 17,
    /**
     * The frame is stored using an 8-bit per component semi-planar
     * YUV format with a Y plane (Y) followed by a horizontally and
     * vertically sub-sampled, packed UV plane (U-V).
     */
    Format_NV12 = 18,
    /**
     * The frame is stored using an 8-bit per component semi-planar
     * YUV format with a Y plane (Y) followed by a horizontally and
     * vertically sub-sampled, packed VU plane (V-U).
     */
    Format_NV21 = 19,
    /**
     * The frame is stored using an 8-bit per component planar YUV
     * format with the U and V planes horizontally and vertically
     * sub-sampled. This is similar to the Format_YUV420P type, except
     * that the bytes per line of the U and V planes are padded out to
     * the same stride as the Y plane.
     */
    Format_IMC1 = 20,
    /**
     * The frame is stored using an 8-bit per component planar YUV
     * format with the U and V planes horizontally and vertically
     * sub-sampled. This is similar to the Format_YUV420P type, except
     * that the lines of the U and V planes are interleaved, i.e. each
     * line of U data is followed by a line of V data creating a
     * single line of the same stride as the Y data.
     */
    Format_IMC2 = 21,
    /**
     * The frame is stored using an 8-bit per component planar YVU
     * format with the V and U planes horizontally and vertically
     * sub-sampled. This is similar to the Format_YV12 type, except
     * that the bytes per line of the V and U planes are padded out to
     * the same stride as the Y plane.
     */
    Format_IMC3 = 22,
    /**
     * The frame is stored using an 8-bit per component planar YVU
     * format with the V and U planes horizontally and vertically
     * sub-sampled. This is similar to the Format_YV12 type, except
     * that the lines of the V and U planes are interleaved, i.e. each
     * line of V data is followed by a line of U data creating a
     * single line of the same stride as the Y data.
     */
    Format_IMC4 = 23,
    /**
     * The frame is stored using a 16bit per component semi-planar YUV
     * format with a Y plane (Y) followed by a horizontally and
     * vertically sub-sampled, packed UV plane (U-V). Only the 10 most
     * significant bits of each component are being used.
     */
    Format_P010 = 26,
    /**
     * The frame is stored using a 16bit per component semi-planar YUV
     * format with a Y plane (Y) followed by a horizontally and
     * vertically sub-sampled, packed UV plane (U-V).
     */
    Format_P016 = 27,
    /** The frame is stored using an 8-bit greyscale format. */
    Format_Y8 = 24,
    /**
     * The frame is stored using a 16-bit linear greyscale format.
     * Little endian.
     */
    Format_Y16 = 25,
    /** The frame is stored in compressed Jpeg format. */
    Format_Jpeg = 29,
    /**
     * The frame is stored in external OES texture format. This is
     * currently only being used on Android.
     */
    Format_SamplerExternalOES = 28,
    /**
     * The frame is stored in rectangle texture format
     * (GL_TEXTURE_RECTANGLE). This is only being used on macOS with
     * an OpenGL based Rendering Hardware interface. The underlying
     * pixel format stored in the texture is Format_BRGA8888.
     */
    Format_SamplerRect = 30,
    /**
     * Similar to YUV420, but uses 16bits per component, 10 of those
     * significant.
     */
    Format_YUV420P10 = 31,
}
