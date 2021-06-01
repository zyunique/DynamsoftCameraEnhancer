//
//  Dynamsoft Camera Enhancer SDK
//
//  Copyright © 2021 Dynamsoft. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "DCECaptureView.h"
#import "DCEBase.h"

NS_ASSUME_NONNULL_BEGIN

/**
* Describes the charge way.
* @enum CameraChargeWay
*/
typedef NS_ENUM(NSInteger,EnumDMChargeWay)
{
    /**The charge way automatically determined by the license server.*/
    EnumDMChargeWayAuto = 0,
    
    /**Charges by the count of devices.*/
    EnumDMChargeWayDeviceCount = 1,
    
    /**Charges by the count of concurrent devices.*/
    EnumDMChargeWayConcurrentDeviceCount = 3,
    
    /**Charges by the count of app domains.*/
    EnumDMChargeWayAppDomainCount = 6,
    
    /**Charges by the count of active devices.*/
    EnumDMChargeWayActiveDeviceCount = 8
};

/**
 * Describes UUID generation method.
 * @enum EnumDMUUIDGenerationMethod
*/
typedef NS_ENUM(NSInteger, EnumDMUUIDGenerationMethod)
{
    /**Generates UUID with random values.*/
    EnumDMUUIDGenerationMethodRandom = 1,
    
    /**Generates UUID based on hardware info.*/
    EnumDMUUIDGenerationMethodHardware = 2
};

/**
* @enum EnumProduct
*
* Describes the Product.
*/
typedef NS_ENUM(NSInteger,EnumProduct)
{
    /**Dynamsoft Barcode Reader.*/
    EnumProductDBR = 0x01,

    /**Dynamsoft Label Recognition.*/
    EnumProductDLR = 0x02,
    
    /**Dynamic Web Twain.*/
    EnumProductDWT = 0x04,

    /**Dynamsoft Camera Enhancer.*/
    EnumProductDCE = 0x08,
    
    /**Dynamsoft Content Structurizator. Not supported yet.*/
    EnumProductDCS = 0x10,

    /**Dynamsoft Panorama.*/
    EnumProductDPS = 0x20,
    
    /**All Product.*/
    EnumProductALL = 0xffff
};

/**
* iDMLTSConnectionParameters
*
*/
@interface iDCELTSConnectionParameters : NSObject

/** The URL of the  license tracking server. */
@property (nonatomic, nullable) NSString* mainServerURL;

/** The URL of the  standby license tracking server. */
@property (nonatomic, nullable) NSString* standbyServerURL;

/** Set the organization ID. */
@property (nonatomic, nullable) NSString* organizationID;

/** The handshake code. */
@property (nonatomic, nullable) NSString* handshakeCode;

/** The session password of the handshake code set in license tracking server. */
@property (nonatomic, nullable) NSString* sessionPassword;

/** Set the charge way. */
@property (nonatomic, assign) EnumDMChargeWay chargeWay;

/** Set the method to generate UUID. */
@property (nonatomic, assign) EnumDMUUIDGenerationMethod UUIDGenerationMethod;

/** Set the max days to buffer the license info. */
@property (nonatomic, assign) NSInteger maxBufferDays;

/** Set the count of license modules to use. */
@property (nonatomic, nullable) NSArray* limitedLicenseModules;

/** Set the products. A combined value of Product Enumration items. */
@property (nonatomic, assign) NSInteger products;

@end

@interface DynamsoftCameraEnhancer:NSObject

/**
 * Stores the license used in DynamsoftCameraEnhancer.
 */
@property (nonatomic, copy, readonly) NSString* license;

/// Whether to open camera video stream
@property (nonatomic, assign) BOOL isEnable;

@property (nonatomic, assign) BOOL enableBeepSound;

@property (nonatomic, assign) BOOL enableAutoZoom;

@property (nonatomic, assign) BOOL enableDefaultAutoFocus;

@property (nonatomic, assign) BOOL enableRegularAutoFocus;

@property (nonatomic, assign) BOOL enableFastMode;

@property (nonatomic, assign) BOOL enableSensorControl;

@property (nonatomic, assign) BOOL enableFrameFilter;

@property (nonatomic, assign) BOOL enableAutoFocusOnSharpnessChange;

- (instancetype)initWithView:(DCECaptureView *)view NS_SWIFT_NAME(init(view:));

- (instancetype)initLicenseFromLTS:(iDCELTSConnectionParameters*)parameters
                              view:(DCECaptureView *)view
              verificationDelegate:(id)connectionDelegate;

- (NSString*)getVersion;

- (FramePackage*)AcquireListFrame;

- (void)setFrameListLength:(int)length;

/// To start streaming frames. The camera is started asynchronously and will take some time to completely turn on.
/// @param state camera state
- (void)setCameraDesiredState:(CameraState)state;

/// getCameraDesiredState
- (CameraState)getCameraDesiredState NS_SWIFT_NAME(getCameraDesiredState());

/// getCameraCurrentState
- (CameraState)getCameraCurrentState NS_SWIFT_NAME(getCameraCurrentState());

/// resumeCamera
- (void)resumeCamera NS_SWIFT_NAME(resumeCamera());

/// pauseCamera
- (void)pauseCamera NS_SWIFT_NAME(pauseCamera());

/// addCameraListener
/// @param listener Camera Listener
- (void)addCameraListener:(id)listener NS_SWIFT_NAME(addCameraListener(_:));

/// setTorch
/// @param state torch state
- (void)setTorchDesiredState:(TorchState)state NS_SWIFT_NAME(setTorchDesiredState(_:));
- (TorchState)getTorchDesiredState;
- (TorchState)getTorchCurrentState;
- (void)addTorchListener:(id)listener NS_SWIFT_NAME(addTorchListener(_:));

/// setZoomFactor
/// @param zoomeFactor set zoom factor
- (void)setZoomFactor:(CGFloat)zoomeFactor;
- (void)setMaxFrameRate:(int)maxFrameRate NS_SWIFT_NAME(setMaxFrameRate(_:));

/// The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5).Focus mode will be AVCaptureFocusModeContinuousAutoFocus.
- (void)setDefaultAutoFocusPosition:(CGPoint)point NS_SWIFT_NAME(setDefaultAutoFocusPosition(_:));

/// The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5).Focus mode will be AVCaptureFocusModeAutoFocus.
- (void)setManualFocusPosition:(CGPoint)point NS_SWIFT_NAME(setManualFocusPosition(_:));

/// Whether to enable sensor filtering. If enable, the captured blurry frames are filtered.
/// @param sensor [0, 10] The shaking sensitivity threshold, the smaller the easier to be discard.
- (void)setSensorControlThreshold:(double)sensor NS_SWIFT_NAME(setSensorControlThreshold(_:));

- (void)setRegularAutoFocusParam:(int)focusTimems terminateFocusByTime:(int)terminateFocusByTime NS_SWIFT_NAME(setRegularAutoFocusParam(_:terminateFocusByTime:));

/// The range of possible positions is 0.0 to 1.0, with 0.0 being the shortest distance at which the lens can focus and 1.0 the furthest. Note that 1.0 does not represent focus at infinity. The default value is 1.0. Note that a given lens position value does not correspond to an exact physical distance, nor does it represent a consistent focus distance from device to device.
/// @param len len position
- (void)setFocalLength:(float)len NS_SWIFT_NAME(setFocalLength(_:));

/// @param time Use CMTimeMake(1, 1000) means seconds = 1 / 1000 = 0.001
- (void)setExposureTime:(CMTime)time NS_SWIFT_NAME(setExposureTime(_:));

///@param iso A float between the minimum and maximum supported exposure ISO value.
- (void)setISO:(float)iso NS_SWIFT_NAME(setISO(_:));

/// switchCameraPosition
- (void)switchCameraPosition;

/// Get Camera Position
- (CameraPosition)getCameraPosition;

- (void)setResolution:(Resolution)resolution;
- (NSString*)getResolution;

- (void)updateCameraSettingFromFile:(NSString*)filePath;

- (void)updateCameraSettingFromJson:(NSString*)params;

- (void)startScanning;
- (void)stopScanning;

- (BOOL)clearCache:(iDCELTSConnectionParameters*)parameters;
@end

NS_ASSUME_NONNULL_END
