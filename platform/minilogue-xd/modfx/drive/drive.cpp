#include "usermodfx.h"

#define WINDOW 4000
#define DRIVE_LIMIT 8
#define SOFT_CLIP_C 0.3

float threshold;
float drive;
//float max;
//float temp_max;
//uint32_t count;


// reduce output volume based on drive to keep similar loudness
// low pass filtering 

                   
void MODFX_INIT(uint32_t platform, uint32_t api)
{
  threshold = 1.0;
  drive = 1.0;
  //max = 1.0;
  //temp_max = 0.0;
  //count = 0;
}


void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn,  float *sub_yn,
                   uint32_t frames)
{
  uint32_t i;
  float sample;
  
  for (i = 0; i < frames * 2; i++) {
    sample = *(main_xn++);
    
    //temp_max = (sample > temp_max) ? sample : temp_max;
    //if (++count == WINDOW) {
    //  max = temp_max;
    //  temp_max = 0.0;
    //  count = 0;
    //}
    
    sample *= drive;
    sample = fx_softclipf_thres(SOFT_CLIP_C, threshold, sample);
    
    *(main_yn++) = sample;
  }
}


void MODFX_PARAM(uint8_t index, int32_t value)
{
   switch (index) {
      case k_user_modfx_param_time:
        threshold = q31_to_f32(value);
        break;
      case k_user_modfx_param_depth:
        drive = 1 + (DRIVE_LIMIT - 1) * q31_to_f32(value);
   }
}

