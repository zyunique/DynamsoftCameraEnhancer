
Pod::Spec.new do |spec|
  spec.name         = "DynamsoftCameraEnhancer"
  spec.version      = "1.0.0"
  spec.summary      = "DynamsoftCameraEnhancer SDK 1.0.0."
  spec.description  = <<-DESC
  Dynamsoft Camera Enhancer is best !
                   DESC
  spec.homepage    = "https://github.com/Dynamsoft/DynamsoftCameraEnhancer"
  spec.license      	= { :type => 'MIT', :file => 'LICENSE' }
  spec.author       	= { "Dynamsoft" => "sales@dynamsoft.com" }
  spec.source       	= { :git => "https://github.com/Dynamsoft/DynamsoftCameraEnhancer.git", :tag => spec.version.to_s }
  spec.platform     	= :ios, "9.0"
  spec.source_files  = "DynamsoftCameraEnhancer.framework/**/*", "DynamsoftCameraEnhancer.framework/*"
  spec.public_header_files = "DynamsoftCameraEnhancer.framework/Headers/*.h"

end
