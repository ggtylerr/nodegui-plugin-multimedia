import { Component, checkIfNativeElement, NativeElement } from "@nodegui/nodegui";
import addon from "../utils/addon";
import { QVariant } from "@nodegui/nodegui";

/**
 * @summary Provides meta-data for media files.
 * @remarks
 * > **Note:** Not all identifiers are supported by all platforms.
 * 
 * Common Attributes:
 * Value | Description | Type
 * ------|-------------|------
 * Title | The title of the media. | String
 * Author | The authors of the media. | String[]
 * Comment | A user comment about the media. | String
 * Description | A description of the media. | String
 * Genre | The genre of the media. | String[]
 * Date | The recording datetime of the media file, or the encoding datetime of the media stream. | {@link QDateTime}
 * Language | The language of media. | QLocate.Language (note: not implemented in nodegui but it's an enum)
 * Publisher | The publisher of the media. | String
 * Copyright | The media's copyright notice. | String
 * Url | A Url pointing to the origin of the media. | {@link QUrl}
 * 
 * Media Attributes:
 * Value | Description | Type
 * ------|-------------|------
 * MediaType | The type of the media (audio, video, etc). | String
 * FileFormat | The file format of the media. | {@link QMediaFormat.FileFormat}
 * Duration | The duration in milliseconds of the media. | Number
 * 
 * Audio attributes:
 * Value | Description | Type
 * ------|-------------|------
 * AudioBitRate | The bit rate of the media's audio stream in bits per second. | Number
 * AudioCodec | The codec of the media's audio stream. | {@link QMediaFormat.AudioCodec}
 * 
 * Video attributes:
 * Value | Description | Type
 * ------|-------------|------
 * VideoFrameRate | The frame rate of the media's video stream. | Number
 * VideoBitRate | The bit rate of the media's video stream in bits per second. | Number
 * VideoCodec | The codec of the media's video stream. | {@link QMediaFormat.VideoCodec}
 * HasHdrContent | True if video is intended for HDR display (FFmpeg and Darwin media backends only). | Boolean
 * 
 * Music attributes:
 * Value | Description | Type
 * ------|-------------|------
 * AlbumTitle | The title of the album the media belongs to. | String
 * AlbumArtist | The principal artist of the album the media belongs to. | String
 * ContributingArtist | The artists contributing to the media. | String[]
 * TrackNumber | The track number of the media. | Number
 * Composer | The composer of the media. | String[]
 * LeadPerformer | The lead performer in the media. | String[]
 * CoverArtImage | An embedded cover art image. | QImage
 * ThumbnailImage | An embedded thumbnail image. (note: is deprecated in 6.12+ and will be identical to {@link CoverArtImage}) | QImage
 * 
 * Image and video attributes:
 * Value | Description | Type
 * ------|-------------|------
 * Orientation | The rotation angle of an image or video. | Number
 * Resolution | The dimensions of an image or video. | QSize
 * @see https://doc.qt.io/qt-6/qmediametadata.html for Qt's Docs
 */
export class QMediaMetaData extends Component {
    /**
     * The native C++ QMediaMetaData variable.
     */
    declare native: NativeElement;
    /**
     * Create a new, empty, invalid media metadata.
     */
    constructor();
    /**
     * Copy a native QMediaMetaData to node bindings.
     * @param nativeElement A native QMediaMetaData element.
     */
    constructor(nativeElement: NativeElement);
    constructor(arg?: NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arguments.length === 0) {
            native = new addon.QMediaMetaData();
        } else {
            throw new TypeError("Wrong number/type of arguments, refer to QMediaMetaData.QMediaMetaData()");
        }
        super(native);
    }
    /**
     * Returns an object that can allow iteration over this hash.
     * @returns An object version of this QMediaMetaData instance.
     */
    asKeyValueRange(): Record<string, QVariant | null> { return this.native.asKeyValueRange(); }
    /**
     * Removes all data from the meta data object.
     */
    clear(): void { this.native.clear(); }
    /**
     * Inserts a *{@link value}* into a Key: *{@link k}*.
     * @param k A QMediaMetaData key to insert.
     * @param value The value to set the key to.
     */
    insert(k: Key, value: QVariant): void { this.native.insert(k, value); }
    /**
     * Returns true if the meta data contains no items: otherwise 
     * returns false.
     * @returns If the meta data contains no items.
     */
    isEmpty(): boolean { return this.native.isEmpty(); }
    /**
     * Returns an array of keys.
     * @returns A key array.
     */
    keys(): Key[] { return this.native.keys(); }
    /**
     * Removes meta data from a key: *{@link k}*
     * @param k The QMediaMetaData key data to remove. 
     */
    remove(k: Key): void { this.native.remove(k); }
    /**
     * Returns the meta data for key *{@link key}* as a string.
     * 
     * This is mainly meant to simplify presenting the meta data to a
     * user.
     * @param key The QMediaMetaData key to get the value for.
     * @returns The value in a string format.
     */
    stringValue(key: Key): string { return this.native.stringValue(key); }
    /**
     * Returns the meta data value for Key *{@link key}*, or a null
     * {@link QVariant} if no meta data for the key is available.
     * @param key The QMediaMetaData key to get the value for.
     * @returns The value in a QVariant format.
     */
    value(key: Key): QVariant { return this.native.value(key); }
    /**
     * Returns a string representation of {@link key} that can be used
     * when presenting meta data to users.
     * @param key The QMediaMetaData key to get a string name for.
     * @returns A string representation of key.
     */
    static metaDataKeyToString(key: Key): string {
        return addon.QMediaMetaData.metaDataKeyToString(key);
    }
}

/**
 * Various keys for metadata.
 */
export enum Key {
    /** Media title */
    Title = 0,
    /** Media author */
    Author = 1,
    /** Comment */
    Comment = 2,
    /** Brief description */
    Description = 3,
    /** Genre the media belongs to */
    Genre = 4,
    /** Creation date */
    Date = 5,
    /** Media language */
    Language = 6,
    /** Media publisher info */
    Publisher = 7,
    /** Media copyright info */
    Copyright = 8,
    /** Publisher's website URL */
    Url = 9,
    /** Media playback duration */
    Duration = 10,
    /** Type of the media */
    MediaType = 11,
    /** File format */
    FileFormat = 12,
    AudioBitRate = 13,
    AudioCodec = 14,
    VideoBitRate = 15,
    VideoCodec = 16,
    VideoFrameRate = 17,
    /** Album's title */
    AlbumTitle = 18,
    /** Artist's info */
    AlbumArtist = 19,
    ContributingArtist = 20,
    TrackNumber = 21,
    /** Media composer's info */
    Composer = 22,
    LeadPerformer = 23,
    /** Media thumbnail image (deprecated in 6.12+ and will be the same as {@link CoverArtImage}) */
    ThumbnailImage = 24,
    /** Media cover art */
    CoverArtImage = 25, // note: why is this LeadPerformer + 2 in the docs ????????
    Orientation = 26,
    Resolution = 27,
    /** Video may have HDR content (read only, FFmpeg and Darwin media backends only) */
    hasHdrContent = 28,
}