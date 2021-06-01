//
//  Dynamsoft Camera Enhancer SDK
//
//  Copyright © 2021 Dynamsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN
@class DCECaptureView;

@protocol DCECaptureViewListener <NSObject>

@required
- (void)barcodeCaptureView:(DCECaptureView *)view
             didChangeSize:(CGSize)size
               orientation:(UIInterfaceOrientation)orientation;

@end

@interface DCECaptureView: UIView<CALayerDelegate>

+ (instancetype)captureWithFrame:(CGRect)frame NS_SWIFT_NAME(init(frame:));

- (instancetype)initWithView:(CGRect)frame;

- (void)addTorch;

- (void)addTorchWith:(UIImage*)torchOnImage TorchOffImg:(UIImage*)torchOffImage frame:(CGRect)frame;

- (void)addOverlay;

- (void)addOverlay:(UIColor *)stroke fill:(UIColor*)fill;

- (void)addListener:(id<DCECaptureViewListener>)listener NS_SWIFT_NAME(addListener(_:));

- (void)removeListener;

- (void)setInterestRegion:(CGRect)region;

@end
NS_ASSUME_NONNULL_END
