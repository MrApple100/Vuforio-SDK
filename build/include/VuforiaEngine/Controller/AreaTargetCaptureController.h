/*===============================================================================
Copyright (c) 2021 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.
===============================================================================*/

#ifndef _VU_AREATARGETCAPTURECONTROLLER_H_
#define _VU_AREATARGETCAPTURECONTROLLER_H_

/**
 * \file AreaTargetCaptureController.h
 * \brief Controller to access the Area Target Capture functionality in the Vuforia Engine
 */

#include <VuforiaEngine/Engine/Engine.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** \addtogroup AreaTargetCaptureGroup Area Target Capture Controller
 * \{
 * This controller provides functionality to generate Area Targets by capturing all required data with Vuforia Engine. 
 * \note This feature is supported only on iOS devices with a LiDAR sensor.
 */

/// \brief Area Target Capture creation error
VU_ENUM(VuAreaTargetCaptureCreationError)
{
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_NONE                             = 0x0, ///< No error
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_INTERNAL                         = 0x1, ///< An internal error occurred while creating the capture
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_AUTOSTART_FAILED                 = 0x2, ///< Auto-start of the capture failed
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_FEATURE_NOT_SUPPORTED            = 0x3, ///< Feature is not supported on the current device
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_MULTIPLE_INSTANCES_NOT_SUPPORTED = 0x4, ///< Multiple captures are not allowed to exist at the same time
    VU_AREA_TARGET_CAPTURE_CREATION_ERROR_INVALID_DEVICE_POSE_OBSERVER     = 0x5, ///< Device pose observer is NULL or invalid
};

/// \brief Area Target Capture status
VU_ENUM(VuAreaTargetCaptureStatus)
{
    VU_AREA_TARGET_CAPTURE_STATUS_INITIALIZED = 0x1, ///< The capture was created and can be started
    VU_AREA_TARGET_CAPTURE_STATUS_PREPARING   = 0x2, ///< The capture has not collected sufficient data to create the initial reconstruction of the environment. A target cannot be generated yet
    VU_AREA_TARGET_CAPTURE_STATUS_CAPTURING   = 0x3, ///< The capture created an initial reconstruction of the environment. A target can now be generated, or continue to capture more data
    VU_AREA_TARGET_CAPTURE_STATUS_PAUSED      = 0x4, ///< The capture was paused
    VU_AREA_TARGET_CAPTURE_STATUS_STOPPED     = 0x5, ///< The capture was stopped
    VU_AREA_TARGET_CAPTURE_STATUS_GENERATING  = 0x6, ///< The capture is generating a target from the captured data
};

/// \brief Area Target Capture status info
VU_ENUM(VuAreaTargetCaptureStatusInfo)
{
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_NORMAL                                 = 0x01, ///< The capture is running normally
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_RELOCALIZING                           = 0x02, ///< The capture is relocalizing, the user should move around or return towards a previously mapped area in order to resume normal capturing
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_EXCESSIVE_MOTION                       = 0x03, ///< The user is moving too quickly
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_CAPACITY_WARNING                       = 0x04, ///< The capture is removing old data to make room for new data and should be stopped soon
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_INTERRUPTED                            = 0x05, ///< The capture is unable to add new data, the user should stop the capture
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_SUSPENDED                              = 0x06, ///< The capture is suspended until Engine is started
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_TRACKING_DATA_GENERATION               = 0x07, ///< The capture is processing the captured data
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_AUTHORING_DATA_GENERATION              = 0x08, ///< The capture is generating the authoring artifacts (3dt, glb)
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_DEVICE_DATABASE_GENERATION             = 0x09, ///< The capture is generating the Vuforia device database (dat, xml)
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_PACKAGE_GENERATION                     = 0x0A, ///< The capture is generating the package(s)
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_SUCCESS                     = 0x0B, ///< Generation successful
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_CANCELED                    = 0x0C, ///< Generation was canceled
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_ERROR_INTERNAL              = 0x0D, ///< Generation failed because an internal error occurred
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_ERROR_NO_NETWORK_CONNECTION = 0x0E, ///< Generation failed because the device has no network connection
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_ERROR_SERVICE_NOT_AVAILABLE = 0x0F, ///< Generation failed because the server was not found, is unreachable, or overloaded
    VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_ERROR_AUTHORIZATION_FAILED  = 0x10, ///< Generation failed because the credentials are wrong or outdated
};

/// \brief Area Target Capture generation error
/**
 * \note These errors report the cause for Area Target generation failing to **start**.
 * Errors that arise **during** Area Target generation are reported in \ref VuAreaTargetCaptureStatusInfo.
 */
VU_ENUM(VuAreaTargetCaptureGenerationError)
{
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_NONE                        = 0x0, ///< No error
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_INTERNAL                    = 0x1, ///< An internal error occurred
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_ENGINE_NOT_RUNNING          = 0x2, ///< Generation failed because Engine is not running
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_INVALID_STATUS              = 0x3, ///< Generation failed because the capture is in the wrong status
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_INSUFFICIENT_DATA           = 0x4, ///< Generation failed because the capture has not yet created an initial reconstruction of the environment
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_MISSING_AUTHENTICATION      = 0x5, ///< Generation failed because authentication details are missing (user authentication or authentication secret)
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_INVALID_OUTPUT_DIRECTORY    = 0x6, ///< Generation failed because the output directory does not exist or can not be written to
    VU_AREA_TARGET_CAPTURE_GENERATION_ERROR_INVALID_TARGET_NAME         = 0x7, ///< Generation failed because the target name does not satisfy requirements
};

/// \brief Area Target Capture instance
typedef struct VuAreaTargetCapture_ VuAreaTargetCapture;

/// \brief Configuration options for Area Target Capture instance creation
typedef struct VuAreaTargetCaptureConfig
{
    /// \brief Device pose observer
    /**
     * \note The Area Target Capture instance can only capture data while the device pose observer is active.
     */
    VuObserver* devicePoseObserver;

    /// \brief Set to VU_TRUE to immediately start the capture after creation
    /**
     * \note Default value is VU_FALSE
     */
    VuBool start;
} VuAreaTargetCaptureConfig;

/// \brief Default capture configuration
/**
 * \note Use this function to initialize the VuAreaTargetCaptureConfig data structure with default values.
 */
VU_API VuAreaTargetCaptureConfig VU_API_CALL vuAreaTargetCaptureConfigDefault();

/// \brief Configuration options for Area Target generation
typedef struct VuAreaTargetCaptureGenerationConfig
{
    /// \brief User name for authentication with the Vuforia server
    /**
     * \note The provided string is copied, and can be freed, after the Area Target Capture instance is created.
     */
    const char* userAuth;
    
    /// \brief Secret key for authentication with the Vuforia server
    /**
     * \note The provided string is copied, and can be freed, after the Area Target Capture instance is created.
     */
    const char* secretAuth;
    
    /// \brief Output directory path
    /**
     * The output directory path can be absolute or relative. The capture will store the files it was configured to
     * generate to this path. The directory must exist and be writable throughout the lifetime of the capture.
     * \note The provided string is copied, and can be freed, after the Area Target Capture instance is created.
     */
    const char* outputDirectory;

    /// \brief Target name
    /**
     * The name of the generated Area Target is required to respect the following restrictions:
     * - Length: 1 - 64 characters
     * - Encoding: ASCII
     * - Allowed characters: numerals (0-9), literals (a-zA-Z), dash (-), underscore (_)
     *
     * \note The provided string is copied, and can be freed, after the Area Target Capture instance is created.
     */
    const char* targetName;

    /// \brief Generate authoring artifacts
    /**
     * \note Default value is VU_TRUE
     */
    VuBool generateAuthoringFiles;

    /// \brief Generate packages
    /**
     * \note Default value is VU_FALSE. If set to VU_TRUE, \ref generateAuthoringFiles should be set to VU_TRUE, too,
     * otherwise the Area Target generation will fail.
     */
    VuBool generatePackages;
} VuAreaTargetCaptureGenerationConfig;

/// \brief Default generation configuration
/**
 * \note Use this function to initialize the VuAreaTargetCaptureGenerationConfig data structure with default values.
 */
VU_API VuAreaTargetCaptureGenerationConfig VU_API_CALL vuAreaTargetCaptureGenerationConfigDefault();

/// \brief Retrieve Area Target Capture Controller to get access to Area Target Capture functionality in Engine
VU_API VuResult VU_API_CALL vuEngineGetAreaTargetCaptureController(const VuEngine* engine, VuController** controller);

/// \brief Create a new capture with the specified configuration
/**
 * Any previously created capture has to be destroyed before creating a new capture.
 *
 * This function creates an Area Target capture based on the specified configuration.
 * On successful creation the capture has status \ref VU_AREA_TARGET_CAPTURE_STATUS_INITIALIZED,
 * unless the configuration's start flag is VU_TRUE, then the capture has status
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_PREPARING. If creation of the capture fails,
 * then VU_FAILED is returned and the optional error parameter will hold an error code
 * that reflects the cause of the error.
 *
 * \note If Engine is not running and the configuration's start flag is VU_TRUE,
 * then on successful creation the capture has status
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_PAUSED and status info
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_SUSPENDED. The capture
 * will then be started automatically during the next call to \ref vuEngineStart().
 *
 * \param controller Area Target Capture Controller
 * \param config The configuration for the new capture
 * \param capture Output variable storing the newly created capture
 * \param error Optional output variable providing additional error information. Can be NULL.
 * \returns VU_SUCCESS on successful creation of the capture, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureControllerCreateAreaTargetCapture(VuController* controller, const VuAreaTargetCaptureConfig* config, VuAreaTargetCapture** capture, VuAreaTargetCaptureCreationError* error);

/// \brief Start a capture
/**
 * The capture starts data acquisition and switches to status \ref VU_AREA_TARGET_CAPTURE_STATUS_PREPARING.
 *
 * \note If Engine is not running, then the capture switches to status
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_PAUSED and status info
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_SUSPENDED. The capture
 * will then be started automatically during the next call to \ref vuEngineStart().
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_INITIALIZED
 * and start is successful, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureStart(VuAreaTargetCapture* capture);

/// \brief Stop a running or paused capture
/**
 * The capture stops data acquisition, and switches to status \ref VU_AREA_TARGET_CAPTURE_STATUS_STOPPED.
 *
 * \note An Area Target can be generated only when the capture is stopped.
 * \note This function fails if Engine is not running.
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_PREPARING,
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_CAPTURING, or \ref VU_AREA_TARGET_CAPTURE_STATUS_PAUSED
 * and stop is successful, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureStop(VuAreaTargetCapture* capture);

/// \brief Pause a running capture
/**
 * Data acquisition of the capture can be paused and resumed. \ref vuAreaTargetCapturePause()
 * pauses data acquisition and switches the capture to status \ref VU_AREA_TARGET_CAPTURE_STATUS_PAUSED.
 * \ref vuAreaTargetCaptureResume() resumes data acquisition and switches the capture to the status it
 * was in before the pause.

 * \note If Engine is stopped while a capture is running, then the capture will be automatically
 * paused during \ref vuEngineStop(), and it will be automatically resumed during the next call
 * to \ref vuEngineStart(). A capture that is automatically paused by Engine has status info
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_SUSPENDED.
 * \note This function fails if Engine is not running.
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_PREPARING or
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_CAPTURING and pause is successful, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCapturePause(VuAreaTargetCapture* capture);

/// \brief Resume a paused capture
/**
 * The capture resumes data acquisition, and switches to the status it was in before the pause.
 *
 * \note This function fails if Engine is not running.
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_PAUSED and resume is successful, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureResume(VuAreaTargetCapture* capture);

/// \brief Start Area Target generation from a stopped capture
/**
 * This function starts Area Target generation based on the specified configuration. Once successfully started,
 * Area Target generation runs in the background. For Area Target generation to successfully start, the following
 * requirements have to be met:
 * - Engine is required to be running.
 * - The capture is required to have status \ref VU_AREA_TARGET_CAPTURE_STATUS_STOPPED.
 * - The capture is required to have accumulated sufficient data to switch from the
 *  \ref VU_AREA_TARGET_CAPTURE_STATUS_PREPARING status to the
 *  \ref VU_AREA_TARGET_CAPTURE_STATUS_CAPTURING status.
 * - The generation configuration is required to be valid. It has to hold valid credentials for communication with the
 *  Vuforia server, it has to provide the path to an existing output directory that can be written to, and it has to
 *  provide a valid target name.
 *
 * If all the requirements are met, this function starts Area Target generation in the background, switches the capture to status
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_GENERATING, and returns VU_SUCCESS. If any of the requirements
 * are not met, VU_FAILED is returned and the optional error parameter will hold an error code that reflects the cause of the error.
 *
 * Area Target generation runs in the background. When it completes, the capture switches back
 * to status \ref VU_AREA_TARGET_CAPTURE_STATUS_STOPPED. On successful Area Target
 * generation, status info reports \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_SUCCESS.
 * If Area Target generation failed, then status info holds one of
 * the values prefixed with VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_ERROR
 * to report on the failure cause. If Area Target generation was canceled, status info holds the value
 * \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_CANCELED.
 *
 * \note If Engine is stopped while Area Target generation is running, then Area Target generation
 * is automatically canceled.
 *
 * \param capture The Area Target Capture instance
 * \param config The configuration for the Area Target generation
 * \param error Optional output variable providing additional error information. Can be NULL.
 *
 * \returns VU_SUCCESS if the Area Target generation has successfully started, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureGenerate(VuAreaTargetCapture* capture, const VuAreaTargetCaptureGenerationConfig* config, VuAreaTargetCaptureGenerationError* error);

/// \brief Get status of the capture
VU_API VuResult VU_API_CALL vuAreaTargetCaptureGetStatus(const VuAreaTargetCapture* capture, VuAreaTargetCaptureStatus* status);

/// \brief Get status info for the capture
VU_API VuResult VU_API_CALL vuAreaTargetCaptureGetStatusInfo(const VuAreaTargetCapture* capture, VuAreaTargetCaptureStatusInfo* statusInfo);

/// \brief Cancel Area Target generation
/**
 * A helper function to abort a running target generation.
 * If the target generation has been canceled successfully, then status info will hold the
 * value \ref VU_AREA_TARGET_CAPTURE_STATUS_INFO_GENERATION_CANCELED.
 *
 * \note This function blocks until target generation has aborted
 * \note This is a potentially long running operation
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_GENERATING and cancelation is successful, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureCancelGeneration(VuAreaTargetCapture* capture);

/// \brief Get progress information of the current Area Target generation in the range [0.0f, 1.0f]
/**
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_GENERATING, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureGetGenerationProgress(const VuAreaTargetCapture* capture, float* progress);

/// \brief Get estimated time remaining to complete the current Area Target generation in seconds
/**
 * It may take few seconds after the Area Target generation started for the time estimate to become available.
 *
 * \returns VU_SUCCESS if the capture is in status \ref VU_AREA_TARGET_CAPTURE_STATUS_GENERATING and the time estimate is available, VU_FAILED otherwise
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureGetGenerationTimeEstimate(const VuAreaTargetCapture* capture, int32_t* remainingTimeSeconds);

/// \brief Destroy the given capture instance
/**
 * If the capture is running data acquisition, it is automatically stopped. If the capture is running target generation,
 * it is automatically canceled.
 *
 * \note This is a potentially long running operation
 */
VU_API VuResult VU_API_CALL vuAreaTargetCaptureDestroy(VuAreaTargetCapture* capture);

/** \} */

#ifdef __cplusplus
}
#endif

#endif // _VU_AREATARGETCAPTURECONTROLLER_H_
