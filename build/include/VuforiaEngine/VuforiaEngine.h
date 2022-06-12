/*===============================================================================
Copyright (c) 2022 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.
===============================================================================*/

#ifndef _VU_VUFORIAENGINE_H_
#define _VU_VUFORIAENGINE_H_

/**
 * \file VuforiaEngine.h
 * \brief Umbrella header for the Vuforia Engine
 */

// ======== VUFORIA ENGINE API HEADER FILES ========

// Core data types and defines
#include <VuforiaEngine/Core/Core.h>

// Database content information
#include <VuforiaEngine/Core/Database.h>

// Linear algebra functions
#include <VuforiaEngine/Core/MathUtils.h>

// Core Engine lifecycle management and configuration
#include <VuforiaEngine/Engine/Engine.h>

// Engine configuration
#include <VuforiaEngine/Engine/DriverConfig.h>
#include <VuforiaEngine/Engine/FusionProviderConfig.h>
#include <VuforiaEngine/Engine/LicenseConfig.h>
#include <VuforiaEngine/Engine/RenderConfig.h>

#if defined(VU_PLATFORM_ANDROID)
#   include <VuforiaEngine/Engine/Android/PlatformConfig_Android.h>
#elif defined(VU_PLATFORM_LUMIN)
#   include <VuforiaEngine/Engine/Lumin/PlatformConfig_Lumin.h>
#elif defined(VU_PLATFORM_LUMIN_GEN1)
#   include <VuforiaEngine/Engine/LuminGen1/PlatformConfig_LuminGen1.h>
#endif

// Observers
#include <VuforiaEngine/Observer/AnchorObserver.h>
#include <VuforiaEngine/Observer/AreaTargetObserver.h>
#include <VuforiaEngine/Observer/CloudImageTargetObserver.h>
#include <VuforiaEngine/Observer/CylinderTargetObserver.h>
#include <VuforiaEngine/Observer/DevicePoseObserver.h>
#include <VuforiaEngine/Observer/IlluminationObserver.h>
#include <VuforiaEngine/Observer/ImageTargetObserver.h>
#include <VuforiaEngine/Observer/ModelTargetObserver.h>
#include <VuforiaEngine/Observer/MultiTargetObserver.h>
#include <VuforiaEngine/Observer/VirtualButtonObserver.h>
#include <VuforiaEngine/Observer/VuMarkObserver.h>
#include <VuforiaEngine/Observer/MeshObserver.h>

// Controllers
#include <VuforiaEngine/Controller/CameraController.h>
#include <VuforiaEngine/Controller/PlatformController.h>
#include <VuforiaEngine/Controller/RenderController.h>
#include <VuforiaEngine/Controller/SessionRecorderController.h>
#include <VuforiaEngine/Controller/AreaTargetCaptureController.h>

// Platform-specific controllers
#if defined(VU_PLATFORM_ANDROID)
#   include <VuforiaEngine/Controller/Android/PlatformController_Android.h>
#elif defined(VU_PLATFORM_IOS)
#   include <VuforiaEngine/Controller/iOS/PlatformController_iOS.h>
#elif defined(VU_PLATFORM_UWP)
#   include <VuforiaEngine/Controller/UWP/PlatformController_UWP.h>
#endif

#endif // _VU_VUFORIAENGINE_H_
