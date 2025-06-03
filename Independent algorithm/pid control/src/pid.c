/*
 * pid.c
 *
 *  Created on: 2019/11/7
 *      Author: Arsenic
 */
#include "pid.h"

float pidExecute(pid_control_t* pid) {
    if (!pid->enable) {
        pid->out = 0.0f;
        clearPid(pid);
        return 0.0f;
    }
    pid->error = *(pid->target_p) - *(pid->follow_p);
    pid->integralOut += pid->i * pid->error * (pid->t / 1000.0f);
    if (pid->integralOutLimit < pid->integralOut) pid->integralOut = pid->integralOutLimit;
    else if (pid->integralOut < -pid->integralOutLimit) pid->integralOut = -pid->integralOutLimit;
    pid->differentialFilter = pid->differentialFilter * pid->differentialFilterRate
        + (pid->d * (pid->error - pid->lastError) * (1000.0f / pid->t)) * (1 - pid->differentialFilterRate);
    float u = pid->p * pid->error + pid->integralOut + pid->differentialFilter;
    if (pid->outLimit < u) u = pid->outLimit;
    else if (u < -pid->outLimit)u = -pid->outLimit;
    pid->lastError = pid->error;
    pid->out = u;
    return u;
}

void clearPid(pid_control_t* pid) {
    pid->integralOut = 0.0f;
    pid->lastError = 0.0f;
    pid->differentialFilter = 0.0f;
}