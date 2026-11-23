/**
 * The angle of the clockwise rotation that should be applied to a
 * video frame before displaying. The rotation is performed in video
 * coordinates, where the Y-axis points downwards on the display. It
 * means that the rotation direction complies with
 * {@link QTransform.rotate | QTransform.rotate()}.
 */
export enum Rotation {
    /**
     * No rotation required, the frame has correct orientation
     */
    None = 0,
    /**
     * The frame should be rotated clockwise by 90 degrees
     */
    Clockwise90 = 90,
    /**
     * The frame should be rotated clockwise by 180 degrees
     */
    Clockwise180 = 180,
    /**
     * The frame should be rotated clockwise by 270 degrees
     */
    Clockwise270 = 270,
}
