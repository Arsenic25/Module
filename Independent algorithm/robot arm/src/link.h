/*
 * link.h
 *
 *  Created on: 2020/2/26
 *      Author: Arsenic
 */

#ifndef LINK_H_
#define LINK_H_

typedef struct {
    /***parameter***/
    //link ID
    uint8_t myID;           //self link ID
    uint8_t sisterID;       //sister link ID
    uint8_t childID;        //child link ID
    uint8_t motherID;       //mother link ID

    //Kinematics data from world coordinate system
    float p[3];             //[m] position vector of local coordinate system from world coordinate
    float R[3][3];          //[meta] attitude matrix of local coordinate system from world coordinate
    float v[3];             //[m/s] velocity vector of local coordinate system from world coordinate
    float w[3];             //[rad/s] angular velocity vector of local coordinate system from world coordinate

    //joint parameter
    float q;                //[rad] angle of joint
    float dq;               //[rad/s] angular velocity of joint
    float ddq;              //[ras/s^2] angular acceleration
    float a[3];             //[meta] unit vector of joint rolling
    float b[3];             //[m] position vector of local coordinate system from mother coordinate

    //mass parameter
    float m;                //[kg] mass of entire link
    float c[3];             //[m] position vector of contor of mass from self coordinate system
    float I[3];             //[??] matrix of inertia moment 
    /***parameter***/

} link_t;


#endif /* LINK_H_ */