/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
    Email    : karl@bwh.harvard.edu

    AMILab is a language for image processing
    ==================================================
    Copyright (C) 1996-2005  Karl Krissian

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    ================================================== 
   The full GNU Lesser General Public License file is in Devel/Sources/Prog/LesserGPL_license.txt
*/
/***************************************************************************
 * $Author: karl $
 * $Revision: 1.2 $
 * $Log: Timing.cpp,v $
 * Revision 1.2  2005/11/16 14:03:07  karl
 * added LGPL license
 *
 * Revision 1.1.1.1  2004/02/02 20:47:07  karl
 * source code in C++
 *
 * Revision 1.1.1.1  2003/08/14 07:16:03  karl
 * Source code
 *
 * Revision 1.2  2000/10/25 23:52:07  karl
 *
 * Calcul en prenant en compte les millisecondes
 *
 * Revision 1.2  2000/10/06 22:52:06  karl
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2000/04/07 16:12:33  karl
 * Sources code
 *
 * Revision 1.1  1998/12/03 16:18:05  kkrissia
 * *** empty log message ***
 *
 *
 ***************************************************************************/

#include "Timing.hpp"
#include <iostream>
#include <iomanip>

#include "AMILabEngineConfig.h"
#ifdef AMI_USE_OPENMP
  #include <omp.h>
#endif

double am_timer(void)
{
#ifdef _OPENMP
  /*
   * The omp_get_wtime() function was added to the OpenMP API
   * in version 2.0 (March 2002).  For older versions, default
   * to clock().
   */
  #if (_OPENMP >= 200203)
    //std::cout << "om_get_wtime()" << std::endl;
    return omp_get_wtime();
  #else
    return (double)clock() / (double)CLOCKS_PER_SEC;
  #endif
#endif
  return (double)clock() / (double)CLOCKS_PER_SEC;
} /* am_timer() */


#if defined(_MSC_VER) || defined(__MINGW32__)

#include <mmsystem.h>

int gettimeofday(struct timeval* tp, void* tzp)
{
    DWORD t;
    t = timeGetTime();
    tp->tv_sec = t / 1000;
    tp->tv_usec = t % 1000;
    /* 0 indicates that the call succeeded. */
    return 0;
}
#endif

//---------------------------------------------------------------------
//
std::ostream& operator<<(std::ostream& o, const Timing& d)
{
  if (d.debut_OK && d.fin_OK)
    return o  << d.name << " Timing du traitement: " 
              << std::setw(12) << std::setprecision(6) 
              << d.diff_sec*1.0+d.diff_microsec*1E-6 << " sec. ";
  else
    return o << " Timing inconnue ";
}

//--------------------------------------
void Timing::AfficheCumul(std::ostream& o)
{
  
    long minutes;
    long heures;
    long secondes;

  heures = minutes = secondes = 0;

  secondes = cumul_diff_sec;
  if (secondes > 60) {
      minutes  = secondes / 60;
      secondes = secondes % 60;
  }

  if (minutes        > 60) {
      heures   = minutes / 60;
      minutes  = minutes % 60;
  }
  

  o << " Cumul of time for " 
    << name << " is: \t ";
  /*      << heures << "h" 
  << minutes << "min" 
  << secondes << "s. " << std::endl

  << cumul_diff_microsec/1000.0 << " msec." << std::endl

  << "OMP: " */
  if (cumul_timer>1)
    o << cumul_timer << " sec." << std::endl;
  else
    o << cumul_timer*1000.0 << " msec." << std::endl;

}
