/**
	*	@author   David
	*	@date 	  14-june-2018
	*	@version  v1.1
	*	@brief
  * @remark   for arduino
  *           not sure for derivative calculation
**/

/* Includes ------------------------------------------------------------------*/
#include "PID.h"
#include <Arduino.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define GET_TIME micros()
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
	*	@brief
	*	@param
	*	@retval
**/
pid_t pid_create(pid_t pid, float* in, float* out, float* set, float kp, float ki, float kd){
	pid->input = in;
	pid->output = out;
	pid->setpoint = set;

	pid_limits(pid,LIMIT_MIN, LIMIT_MAX);

	pid->sampletime = SAMPLE_TIME;

	pid_tune(pid, kp, ki, kd);

	pid->lasttime = GET_TIME;

	return pid;
}

/**
	*	@brief
	*	@param
	*	@retval
**/
bool pid_need_compute(pid_t pid){
	return ((GET_TIME - pid->lasttime) >= pid->sampletime) ? true : false;
}

/**
	*	@brief
	*	@param
	*	@retval
**/
void pid_compute(pid_t pid){
	float in = *pid->input;

	//Compute error
	float error = (*(pid->setpoint))-in;

	//Compute integral of error with windup
	pid->iterm += (pid->Ki * error);
	if(pid->iterm > pid->omax){
		pid->iterm = pid->omax;
	}
	else if(pid->iterm < pid->omin){
		pid->iterm = pid->omin;
	}

	//Compute differential on input
	float dterm = (error - pid->lasterror);

	//Compute PID output
	float out = pid->Kp * error + pid->iterm + pid->Kd*dterm;

	//Apply limit to output value
	if(out > pid->omax){
		out = pid->omax;
	}
	else if(out < pid->omin){
		out = pid->omin;
	}

	//Output to pointed variable
	(*pid->output) = out;
	//Keep track of some variables for next execution
	pid->lasterror = error;
	pid->lasttime = GET_TIME;

}

/**
	*	@brief
	*	@param
	*	@retval
**/
bool pid_tune(pid_t pid,float kp, float ki, float kd){
	//Check for validity
	if(kp < 0 || ki < 0 || kd < 0){
        return false;
	}
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
	return true;
}

/**
	*	@brief
	*	@param
	*	@retval
**/
void pid_sample_time(pid_t pid, uint32_t sampletime){
	pid->sampletime = sampletime;
}


/**
	*	@brief
	*	@param
	*	@retval
**/
bool pid_limits(pid_t pid, float min, float max){
	//Check for validity
	if(min >= max){
        return false;
    }
	pid->omax = max;
	pid->omin = min;
	return true;
}

