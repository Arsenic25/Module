/*
 * pid.h
 *
 *  Created on: 2019/11/7
 *      Author: Arsenic
 */

#ifndef PID_H_
#define PID_H_

#include <stdbool.h>

typedef struct {
    bool enable;

    /***parameter***/
    float t;	//time cycle[ms]	pid calculate period

    float p;	//gain p[META] proportional
    float i;	//gain i[META] integral
    float d;	//gain d[META] differential

    float outLimit;	//[META]	control output max value
    float integralOutLimit;	//[META]	integral effect max output value
    float differentialFilterRate;	//[%](0~1)	differemtial effect smoothing
    /***parameter***/

    /***internal variables***/
    float integralOut;	//[META]
    float lastError;	//[META]
    float differentialFilter;	//[META]

    float error;	//[META]
    /***internal variables***/

    /***input***/
    float* target_p;
    float* follow_p;
    /***input***/

    /***output***/
    float out;
    /***output***/

} pid_control_t;

//calculate output value from error
float pidExecute(pid_control_t* pid);

void clearPid(pid_control_t* pid);

#endif /* PID_H_ */
