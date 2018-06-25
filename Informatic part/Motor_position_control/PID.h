/**
  * @author   David
  * @date     14-june-2018
  * @version  v1.1
  * @brief
  * @remark   for arduino
**/

#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* Typedef -----------------------------------------------------------*/
/**
	*	@brief default max and min output limit
**/
#define LIMIT_MAX   50
#define	LIMIT_MIN   -50

/**
	*	@brief	default sample time (ms)
**/
#define	SAMPLE_TIME 10
/**
	*	@brief
**/
enum pid_control_directions{
	E_PID_DIRECT,
	E_PID_REVERSE,
};

/**
	*	@brief
**/
struct pid_controller{
	//Input, output, setpoint
	float *input;
	float *output;
	float *setpoint;
	//Tuning parameters
	float Kp;
	float Ki;
	float Kd;
	//Output minimum and maximum values
	float omin;
	float omax;
	//Variables for PID algorithm
	float iterm;
	float lasterror;
	//Time related
	uint32_t lasttime;
	uint32_t sampletime;
	//Operation mode
	enum pid_control_directions direction;
};

typedef struct pid_controller *pid_t;

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/**
	*	@brief 	Creates a new PID controller
	*	@param	pid A pointer to a pid_controller structure
	*	@param	out Pointer to put the controller output value
	*	@param	in Pointer to put the controller output value
	*	@param	set Pointer float with the process setpoint value
	*	@param	kp Proportionnal gain
	*	@param	ki	Integral gain
	*	@param	kd Differential gain
	*	@retval returns a pid_t controller handle
	**/
pid_t pid_create(pid_t pid, float* in, float* out, float*set, float kp, float ki, float kd);

/**
	*	@brief 	Check if PID loop needs to run
	*	@param	pid A pointer to a pid controller structure to check
	*	@retval returns True if PID control algorithm is required to run
	**/
bool pid_need_compute(pid_t pid);

/**
	*	@brief 	Computes the output of the PID control
	*	@param	pid The PID controller instance which will be used for computation
	**/
void pid_compute(pid_t pid);

/**
	*	@brief Set the sampling time
	*	@param sample time
**/
void pid_sample_time(pid_t pid, uint32_t sampletime);

/**
	*	@brief 	Sets new PID tuning parameters
	*	@param 	pid The PID controller instance to modify
	*	@param	kp Proportionnal gain
	* @param	ki Integral gain
	*	@param	kd Derivative gain
	**/
bool pid_tune(pid_t pid, float kp, float ki, float kd);

/**
	*	@brief	Sets the limits for the PID controller output
	*	@param	pid The PID controller instance to modify
	*	@param	min The minimum output value for PID controller
	*	@param	max The maximum output value for the PID controller
	**/
bool pid_limits(pid_t pid, float min, float max);

#ifdef __cplusplus
}
#endif

#endif /** PID_H **/
