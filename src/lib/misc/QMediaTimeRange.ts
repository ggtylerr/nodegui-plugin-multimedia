import { checkIfNativeElement, Component, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";

/**
 * @summary The QMediaTimeRange class represents a set of zero or more
 * disjoint time intervals.
 * @remarks
 * The {@link QMediaTimeRange.earliestTime | earliestTime()}, 
 * {@link QMediaTimeRange.latestTime | latestTime()}, 
 * {@link QMediaTimeRange.intervals | intervals()} and 
 * {@link QMediaTimeRange.isEmpty | isEmpty()} methods are used to get
 * information about the current time range.
 * 
 * The {@link QMediaTimeRange.addInterval | addInterval()},
 * {@link QMediaTimeRange.removeInterval | removeInterval()} and
 * {@link QMediaTimeRange.clear | clear()} methods are used to modify
 * the current time range.
 * 
 * When adding or removing intervals from the time range, existing
 * intervals within the range may be expanded, trimmed, deleted,
 * merged or split to ensure that all intervals within the time range
 * remain distinct and disjoint. As a consequence, all intervals added
 * or removed from a time range must be normal.
 * 
 * @see also {@link Interval}.
 * @see https://doc.qt.io/qt-6/qmediatimerange.html for Qt's docs
 */
export class QMediaTimeRange extends Component {
    /**
     * The native C++ QMediaTimeRange variable.
     */
    declare native: NativeElement;
    /**
     * Constructs an empty time range.
     */
    constructor();
    /**
     * Copy a native QMediaTimeRange to node bindings.
     * @param nativeElement A native QMediaTimeRange element.
     */
    constructor(nativeElement: NativeElement);
    /**
     * Constructs a time range by copying another time range.
     * @param other The QMediaTimeRange to copy/move from.
     */
    constructor(other: QMediaTimeRange);
    /**
     * Constructs a time range that contains an initial interval,
     * *{@link interval}*.
     * 
     * If *{@link interval}* is not normal, the resulting time range
     * will be empty.
     * 
     * @see also {@link QMediaTimeRange.addInterval | addInterval()}.
     * @param interval The initial interval to start the time range
     * with.
     */
    constructor(interval: Interval);
    /**
     * Constructs a time range that contains an initial interval from
     * *{@link start}* to *{@link end}* inclusive.
     * 
     * If the interval is not normal, the resulting time range will be
     * empty.
     * 
     * @see also {@link QMediaTimeRange.addInterval | addInterval()}.
     * @param start The starting position.
     * @param end The ending position.
     */
    constructor(start: number, end: number);
    constructor(
        arg?: NativeElement | QMediaTimeRange | Interval | number,
        end?: number
    ) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg instanceof QMediaTimeRange) {
            native = new addon.QMediaTimeRange(arg.native);
        } else if (arguments.length === 0) {
            native = new addon.QMediaTimeRange();
        } else if (typeof arg === "object" &&
            typeof arg.start === "number" &&
            typeof arg.end === "number") {
            native = new addon.QMediaTimeRange(arg);
        } else if (typeof arg === "number" && end) {
            native = new addon.QMediaTimeRange(arg, end);
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QMediaTimeRange.QMediaTimeRange()");
        }
        super(native);
    }
    /**
     * Adds the specified interval to the time range. Also can add a
     * new interval specified by start and end.
     * 
     * Adding intervals which are not normal is invalid, and will be
     * ignored.
     * 
     * If the specified interval is adjacent to, or overlaps existing
     * intervals within the time range, these intervals will be
     * merged.
     * 
     * This operation takes linear time.
     * @see also {@link QMediaTimeRange.removeInterval | removeInterval()}.
     * @param intervalOrStart Either an interval to add or a starting
     * position.
     * @param end The ending position.
     */
    addInterval(intervalOrStart: Interval | number, end?: number): void {
        if (!end) this.native.addInterval(intervalOrStart);
        else this.native.addInterval(intervalOrStart, end);
    }
    /**
     * Adds each of the intervals in *{@link range}* to this time
     * range.
     * 
     * Equivalent to calling
     * {@link QMediaTimeRange.addInterval | addInterval()} for each
     * interval in *{@link range}*.
     * @param range The time range to add intervals from.
     */
    addTimeRange(range: QMediaTimeRange): void {
        this.native.addTimeRange(range);
    }
    /**
     * Removes all intervals from the time range.
     * 
     * @see also {@link QMediaTimeRange.removeInterval | removeInterval()}.
     */
    clear(): void { this.native.clear(); }
    /**
     * Returns true if the specified *{@link time}* lies within the
     * time range.
     * @param time The time to check
     * @return Whether or not if the time is in range.
     */
    contains(time: number): boolean { 
        return this.native.contains(time); 
    }
    /**
     * Returns the earliest time within the time range.
     * 
     * For empty time ranges, this value is equal to zero.
     * 
     * @see also {@link QMediaTimeRange.latestTime | latestTime()}.
     * @returns The earliest time in the range.
     */
    earliestTime(): number { return this.native.earliestTime(); }
    /**
     * Returns an array of intervals covered by this time range.
     * @returns All the intervals covered by this range.
     */
    intervals(): Interval[] { return this.native.intervals(); }
    /**
     * Returns true if the time range consists of a continuous
     * interval. That is, there is one or fewer disjoint intervals
     * within the time range.
     * @returns If the time range consists of a continuous interval.
     */
    isContinuous(): boolean { return this.native.isContinuous(); }
    /**
     * Returns true if there are no intervals within the time range.
     * 
     * @see also {@link QMediaTimeRange.intervals | intervals()}.
     * @returns Whether or not if the time range has no intervals.
     */
    isEmpty(): boolean { return this.native.isEmpty(); }
    /**
     * Returns the latest time within the time range.
     * 
     * For empty time ranges, this value is equal to zero.
     * @see also {@link QMediaTimeRange.earliestTime | earliestTime()}.
     * @returns The latest time in the range.
     */
    latestTime(): number { return this.native.latestTime(); }
    /**
     * Removes the specified interval to the time range. Also can 
     * removes an interval specified by start and end.
     * 
     * Removing intervals which are not normal is invalid, and will be
     * ignored.
     * 
     * Intervals within the time range will be trimmed, split or
     * deleted such that no intervals within the time range include
     * any part of the target interval.
     * 
     * This operation takes linear time.
     * @see also {@link QMediaTimeRange.addInterval | addInterval()}.
     * @param intervalOrStart Either an interval to add or a starting
     * position.
     * @param end The ending position.
     */
    removeInterval(intervalOrStart: Interval | number, end?: number): void {
        if (!end) this.native.removeInterval(intervalOrStart);
        else this.native.removeInterval(intervalOrStart, end);
    }
    /**
     * Removes each of the intervals in range from this time range.
     * 
     * Equivalent to calling 
     * {@link QMediaTimeRange.removeInterval | removeInterval()} for
     * each interval in range.
     * @param range The time range to get intervals from and remove
     * from the base range.
     */
    removeTimeRange(range: QMediaTimeRange): void {
        this.native.removeTimeRange(range);
    }
    /**
     * Swaps the current instance with the *{@link other}*.
     * @param other The other time range to swap with.
     */
    swap(other: QMediaTimeRange): void { this.native.swap(other); }
    /**
     * Adds an interval, or all intervals in a range, to the time
     * range.
     * @param intervalOrRange A single interval to add, or a time
     * range to add all of its intervals.
     */
    add(intervalOrRange: QMediaTimeRange | Interval): void {
        this.native.add(intervalOrRange);
    }
    /**
     * Removes an interval, or all intervals in a range, to the time
     * range.
     * @param intervalOrRange A single interval to remove, or a time
     * range to remove all of its intervals.
     * @returns The result of removing the interval / range.
     */
    sub(intervalOrRange: QMediaTimeRange | Interval): void {
        this.native.sub(intervalOrRange);
    }
    /**
     * Returns true if all intervals in *{@link other}* are present
     * in this range.
     * @param other The range to test against.
     * @returns Whether or not if all intervals are present in both
     * ranges.
     */
    equals(other: QMediaTimeRange): boolean {
        return this.native.equals(other);
    }
}

/**
 * @summary The Interval class represents a time interval with integer
 * precision.
 * 
 * @remarks
 * **NOTE:** As of right now, Interval is only a simple interface, as 
 * most of its functions can be used within JS's own Object functions
 * (i.e. contains). In the future, we may provide a binding class for
 * porting sake, under "IntervalClass", which will contain these
 * functions.
 * 
 * The following remarks are from Qt's documentation and may not
 * reflect this interface.
 * 
 * @remarks
 * An interval is specified by an inclusive {@link start} and 
 * {@link end} time. These must be set in the constructor, as this is
 * an immutable class. The specific units of time represented by the 
 * class have not been defined - it is suitable for any times which
 * can be represented by a signed 64 bit integer.
 * 
 * The isNormal() method determines if a time interval is normal (a
 * normal time interval has start <= end). A normal interval can be
 * received from an abnormal interval by calling the normalized()
 * method.
 * 
 * The contains() method determines if a specified time lies within
 * the time interval.
 * 
 * The translated() method returns a time interval which has been
 * translated forwards or backwards through time by a specified
 * offset.
 */
export interface Interval {
    /** The start time of the interval. */
    start: number;
    /** The end time of the interval. */
    end: number;
}