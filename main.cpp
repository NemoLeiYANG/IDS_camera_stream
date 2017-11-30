#include <iostream>
#include <uEye.h>
#include <ueye_deprecated.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/video.hpp>
#include <bitset>

int stream_IDS_frame_24bpp()
{
    HIDS hCam = 0;
    char* imgMem;
    int memId;
    if(is_InitCamera (&hCam, NULL)!= IS_SUCCESS){
        std::cout << "Camera doesn't open" << std::endl;
        return 0;
    }

    int img_width = 1280, img_height = 1024, img_bpp = 24, img_channel = 3, img_step, img_data_size;
    std::cout << "is set alloc mem - " << is_AllocImageMem(hCam, img_width, img_height, img_bpp, &imgMem, &memId) << std::endl;
    std::cout << "is set image mem - " << is_SetImageMem (hCam, imgMem, memId) << std::endl;
    std::cout << "is set display mode - " << is_SetDisplayMode (hCam, IS_SET_DM_ALLOW_SCALING) << std::endl;
    std::cout << "is set color mode - " << is_SetColorMode (hCam, IS_SET_CM_RGB24) << std::endl;
    is_SetImageSize (hCam, img_width, img_height);


    double enable = 1;
    double disable = 0;
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_WHITEBALANCE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_FRAMERATE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SHUTTER, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_GAIN, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_WHITEBALANCE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_SHUTTER, &disable, 0);
    is_DeviceFeature(hCam, IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_ROLLING, &enable, 0);

    /*
        IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL
        IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL_ALTERNATIVE_TIMING
        IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_ROLLING
        IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_ROLLING_GLOBAL_START
    */

    //Enables/disables the Global Start shutter.
    is_SetGlobalShutter(hCam, enable);


    double FPS, NEWFPS;
    FPS = 30;
    double fps;
    is_SetFrameRate(hCam, FPS, &NEWFPS);

    double parameter = 50;
    int error = is_Exposure(hCam, IS_EXPOSURE_CMD_SET_EXPOSURE, (void*) &parameter, sizeof(parameter));
    if (error != IS_SUCCESS) {
        std::cout << "): failed " << parameter;
    }

    error = is_Exposure(hCam, IS_EXPOSURE_CMD_GET_EXPOSURE, (void*) &parameter, sizeof(parameter));

    UINT uiCaps = 0;
    INT nRet = is_Focus (hCam, FDT_CMD_GET_CAPABILITIES, &uiCaps, sizeof (uiCaps) );

    if (nRet == IS_SUCCESS && (uiCaps & FOC_CAP_AUTOFOCUS_SUPPORTED)){
        std::cout << "If supported, enable auto focus";
        nRet = is_Focus (hCam, FOC_CMD_SET_DISABLE_AUTOFOCUS, NULL, 0);
    }

    nRet = is_SetGamma(hCam, 250);

    void *pMemVoid; //pointer to where the image is stored
    pMemVoid = new unsigned char[img_channel*img_width*img_height];

    while(true){
        // is Freeze - get frame function
        if(is_FreezeVideo(hCam, IS_WAIT) == IS_SUCCESS){
            is_GetImageMem (hCam, &pMemVoid);

            cv::Mat frame(img_height, img_width, CV_8UC3, pMemVoid, img_channel*img_width);
            cv::namedWindow("A");

            cv::imshow("A", frame);
            if (cv::waitKey(10) >= 0){
                break;
            }
        }
        else{
            std::cout << "ERROR FREEZE";
        }
    }

    is_ExitCamera(hCam);
}

void stream_IDS_frame_36bpp()
{
    HIDS hCam = 0;
    char* imgMem;
    int memId;
    if(is_InitCamera (&hCam, NULL)!= IS_SUCCESS){
        std::cout << "Camera doesn't open" << std::endl;
    }

    int img_width = 1280, img_height = 1024, img_bpp = 48, img_channel = 4, img_step, img_data_size;
    std::cout << "is set alloc mem - " << is_AllocImageMem(hCam, img_width, img_height, img_bpp, &imgMem, &memId) << std::endl;
    std::cout << "is set image mem - " << is_SetImageMem (hCam, imgMem, memId) << std::endl;
    std::cout << "is set display mode - " << is_SetDisplayMode (hCam, IS_SET_DM_ALLOW_SCALING) << std::endl;
    std::cout << "is set color mode - " << is_SetColorMode (hCam, IS_CM_BGR12_PACKED) << std::endl;
    is_SetImageSize (hCam, img_width, img_height);

    double enable = 1;
    double disable = 0;
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_GAIN, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_WHITEBALANCE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_FRAMERATE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SHUTTER, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_GAIN, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_WHITEBALANCE, &disable, 0);
    is_SetAutoParameter (hCam, IS_SET_ENABLE_AUTO_SENSOR_SHUTTER, &disable, 0);
/*
    IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL
    IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL_ALTERNATIVE_TIMING
    IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_ROLLING
    IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_ROLLING_GLOBAL_START
*/
    is_DeviceFeature(hCam, IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL, &enable, 0);

    //Enables/disables the Global Start shutter.
    is_SetGlobalShutter(hCam, enable);

    double FPS, NEWFPS;
    FPS = 30;
    double fps;
    is_SetFrameRate(hCam, FPS, &NEWFPS);

    double parameter = 50;
    int error = is_Exposure(hCam, IS_EXPOSURE_CMD_SET_EXPOSURE, (void*) &parameter, sizeof(parameter));
    if (error != IS_SUCCESS) {
        std::cout << "): failed " << parameter;
    }

    error = is_Exposure(hCam, IS_EXPOSURE_CMD_GET_EXPOSURE, (void*) &parameter, sizeof(parameter));

    UINT uiCaps = 0;
    INT nRet = is_Focus (hCam, FDT_CMD_GET_CAPABILITIES, &uiCaps, sizeof (uiCaps) );

    if (nRet == IS_SUCCESS && (uiCaps & FOC_CAP_AUTOFOCUS_SUPPORTED)){
        std::cout << "If supported, enable auto focus";
        nRet = is_Focus (hCam, FOC_CMD_SET_DISABLE_AUTOFOCUS, NULL, 0);
    }

    nRet = is_SetGamma(hCam, 200);

    void *pMemVoid; //pointer to where the image is stored
    pMemVoid = new unsigned char[6*img_width*img_height];
    unsigned char *new_mem_p = new unsigned char[8*img_width*img_height];

    while(true){
        // is Freeze - get frame function
        if(is_FreezeVideo(hCam, IS_WAIT) == IS_SUCCESS){
            is_GetImageMem (hCam, &pMemVoid);

            unsigned char *p_img = static_cast<unsigned char*>(pMemVoid);

            unsigned short int *p_r = new unsigned short int;
            unsigned short int *p_g = new unsigned short int;
            unsigned short int *p_b = new unsigned short int;
            unsigned short int *p_a = new unsigned short int;

            unsigned long long int i = 0, j = 0;
            for(i, j; i < 6*img_width*img_height; i+=6){

                memcpy(p_b, p_img + i, 2);
                memcpy(p_g, p_img + i + 2, 2);
                memcpy(p_r, p_img + i + 4, 2);

                *p_b = *p_b << 4;
                *p_g = *p_g << 4;
                *p_r = *p_r << 4;

                memcpy(new_mem_p + j, p_b, 2);
                memcpy(new_mem_p + j + 2, p_g, 2);
                memcpy(new_mem_p + j + 4, p_r, 2);

                j += 6;
            }

            cv::Mat frame(img_height, img_width, CV_16UC3, new_mem_p, 6*img_width), new_frame;

            frame.convertTo(new_frame, CV_64FC3, 1/65536.0);
//            cv::cvtColor(frame, frame, CV_BGR2BGRA);

            cv::namedWindow("A");

            cv::imshow("A", frame);
            if (cv::waitKey(10) >= 0){
                break;
            }
        }
        else{
            std::cout << "ERROR FREEZE";
        }
    }
    unsigned char *p_img = static_cast<unsigned char*>(pMemVoid);
    delete[] p_img;
    delete[] new_mem_p;
    is_ExitCamera(hCam);
}

int main(int argc, char *argv[])
{
    stream_IDS_frame_36bpp();

    return 0;
}

