//
//  Dynamsoft Camera Enhancer SDK
//
//  Copyright © 2021 Dynamsoft. All rights reserved.
//

//#import <DynamsoftBarcodeReader/DynamsoftBarcodeReader.h>

NS_ASSUME_NONNULL_BEGIN
static NSString* _Nonnull const DCEErrorDomain = @"com.dynamsoft.cameraEnhancer.error";

/**
 * Describes the error codes.
 * @enum EnumDCEErrorCode
 */
typedef NS_ENUM(NSInteger, EnumDCEErrorCode)
{
    /** OK*/
    EnumDCEErrorCode_OK                             = 0,
    
    /** Unknown error. */
    EnumDCEErrorCode_UNKNOWN                        = -10000,
    
    /** The license is invalid. */
    EnumDCEErrorCode_LICENSE_INVALID                = -10001,
    
    /** The license has expired.*/
    EnumDCEErrorCode_LICENSE_EXPIRED                = -10002,
    
    /** The camera module is not exist. */
    EnumDCEErrorCode_CAMERA_MODULE_NOT_EXIST        = -10003,
    
    /** The file is not found.*/
    EnumDCEErrorCode_FILE_NOT_FOUND                 = -10004,
    
    /** The file format error. */
    EnumDCEErrorCode_FILE_FORMAT_ERROR              = -10005,
    
    /** Failed to request the license file. */
    EnumDCEErrorCode_REQUEST_FAILED                 = -10044,
    
    /** No license.*/
    EnumDCEErrorCode_NO_LICENSE                     = -20000,
    
    /** The handshake code is invalid. */
    EnumDCEErrorCode_HANDSHAKE_CODE_INVALID         = -20001,
    
    /** Failed to read or write license cache. */
    EnumDCEErrorCode_LICENSE_BUFFER_FAILED          = -20002,

    /** Falied to synchronize license info wirh license tracking server. */
    EnumDCEErrorCode_LICENSE_SYNC_FAILED            = -20003,
    
    /** Device does not match with license buffer. */
    EnumDCEErrorCode_DEVICE_NOT_MATCH               = -20004,

    /** Falied to bind device. */
    EnumDCEErrorCode_BIND_DEVICE_FAILED             = -20005,
    
    /** Interface InitLicenseFromLTS can not be used together with other license initiation interfaces. */
    EnumDCEErrorCode_LICENSE_INTERFACE_CONFLICT     = -20006,
    
    /** License Client dll is missing.*/
    EnumDCEErrorCode_LICENSE_CLIENT_DLL_MISSING     = -20007,
    
    /**Instance count is over limited.*/
    EnumDCEErrorCode_INSTANCE_COUNT_OVER_LIMITED    = -20008,

    /** Interface InitLicenseFromLTS has to be called before creating any SDK objects. */
    EnumDCEErrorCode_LICENSE_INIT_SEQUENCE_FAILED   = -20009,
    
    /** Trial License*/
    EnumDCEErrorCode_TRIAL_LICENSE                  = -20010,

    /** Failed to reach License Tracking Server.*/
    EnumDCEErrorCode_FAILED_TO_REACH_LTS            = -20200
};

typedef NS_ENUM(NSInteger, Resolution)
{
    RESOLUTION_AUTO NS_SWIFT_NAME(RESOLUTION_AUTO)   = 0,
    RESOLUTION_480P NS_SWIFT_NAME(RESOLUTION_480P)   = 1,
    RESOLUTION_720P NS_SWIFT_NAME(RESOLUTION_720P)   = 2,
    RESOLUTION_1080P NS_SWIFT_NAME(RESOLUTION_1080P) = 3,
    RESOLUTION_4K NS_SWIFT_NAME(RESOLUTION_4K)       = 5
} NS_SWIFT_NAME(Resolution);

typedef NS_ENUM(NSInteger, TorchState) {
    TORCH_STATE_OFF NS_SWIFT_NAME(TORCH_STATE_OFF)    = 0,
    TORCH_STATE_ON  NS_SWIFT_NAME(TORCH_STATE_ON)     = 1,
    TORCH_STATE_AUTO NS_SWIFT_NAME(TORCH_STATE_AUTO)  = 2
} NS_SWIFT_NAME(TorchState);

typedef NS_ENUM(NSInteger, CameraState) {
    CAMERA_STATE_OFF NS_SWIFT_NAME(CAMERA_STATE_OFF)  = 0,
    CAMERA_STATE_ON  NS_SWIFT_NAME(CAMERA_STATE_ON)   = 1
} NS_SWIFT_NAME(CameraState);

typedef NS_ENUM(NSInteger, CameraPosition) {
    CAMERA_POSITION_USER NS_SWIFT_NAME(CAMERA_POSITION_USER)   = 0,
    CAMERA_POSITION_WORLD NS_SWIFT_NAME(CAMERA_POSITION_WORLD) = 1
} NS_SWIFT_NAME(CameraPosition);

/// Return the  decode results and additional information.
@interface FramePackage : NSObject

@property (strong, nonatomic) NSData* buffer;
@property (strong, nonatomic) NSNumber* width;
@property (strong, nonatomic) NSNumber* height;
@property (strong, nonatomic) NSNumber* stride;
@property (copy, nonatomic) NSString* pixelFormat;
@property (strong, nonatomic) NSNumber* frameID;
@property (strong, nonatomic) NSNumber* fastFrameID;
@property (assign, nonatomic) CVImageBufferRef imageBuffer;

- (instancetype)initWithBuffer:(NSData*)buffer width:(NSNumber*)width height:(NSNumber*)height stride:(NSNumber*)stride pixelFormat:(NSString*)pixelFormat frameID:(NSNumber*)frameID fastFrameID:(NSNumber*)fastFrameID imageBuffer:(CVImageBufferRef)imageBuffer;
@end

@protocol CameraEnhancerListener <NSObject>

@required
- (void)onPreviewOriginalFrame:(FramePackage*)frame;

@optional
- (void)onPreviewFilterFrame:(FramePackage*)frame;

@optional
- (void)onPreviewFastFrame:(FramePackage*)frame;

@end

@protocol CameraTorchListener <NSObject>

@required
- (void)didChangeTorchState:(TorchState)torchState NS_SWIFT_NAME(didChangeTorchState(torchState:));

@end

/**
 * Protocol for a delegate to handle callback when license verification message returned.
 */
@protocol CameraLTSLicenseVerificationDelegate <NSObject>

@required
/**
 * The callback of license server.
 *
 * @param [in,out] isSuccess Whether the license verification was successful.
 * @param [in,out] error The error message from license server.
 *
 * @par Code Snippet:
 * @code
     DynamsoftCameraEnhancer *barcodeCamera;
     iCameraLTSConnectionParameters* lts = [[iCameraLTSConnectionParameters alloc] init];
     lts.handshakeCode = @"*****-hs-****";
     lts.sessionPassword = @"******";
     barcodeCamera = [[DynamsoftCameraEnhancer alloc] initLicenseFromLTS:lts verificationDelegate:self];
     - (void)CameraLTSLicenseVerificationCallback:(bool)isSuccess error:(NSError * _Nullable)error
     {
         //TODO add your code for license verification
     }
 * @endcode
 */
- (void)CameraLTSLicenseVerificationCallback:(bool)isSuccess error:(NSError * _Nullable)error;

@end

NS_ASSUME_NONNULL_END
