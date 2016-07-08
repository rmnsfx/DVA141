/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 8.5 and the Signal Processing Toolbox 7.0.
 * Generated on: 08-Jul-2016 16:48:15
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 2
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\MATLAB Production Server\R2015a\extern\include\tmwtypes.h 
 */
#define MWSPT_NSEC 5
const int NL[MWSPT_NSEC] = { 1,3,1,3,1 };
const real64_T NUM[MWSPT_NSEC][3] = {
  {
     0.9984956150039,                 0,                 0 
  },
  {
                   1,                -2,                 1 
  },
  {
     0.9963812167278,                 0,                 0 
  },
  {
                   1,                -2,                 1 
  },
  {
                   1,                 0,                 0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1 };
const real64_T DEN[MWSPT_NSEC][3] = {
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.996983530959,   0.9969989290564 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.992754750711,   0.9927701162008 
  },
  {
                   1,                 0,                 0 
  }
};