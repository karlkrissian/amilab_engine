/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
               Sara Arencibia
    Email    : karl@bwh.harvard.edu
               darkmind@gmail.com

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

#ifndef _WRAPCONVERSION_H_
#define _WRAPCONVERSION_H_

#include "itkImage.h"
#include "itkImageIOBase.h"

// InrToITK
template <class TPixel, unsigned int Dimension> 
typename itk::Image<TPixel,Dimension>::Pointer InrToITK(InrImage* input, 
                typename itk::Image<TPixel,Dimension>::RegionType &region);

// InrToITK_Vect
template <class TPixel, unsigned int Dimension> 
typename itk::Image<TPixel,Dimension>::Pointer InrToITK_Vect(InrImage* input, 
                typename itk::Image<TPixel,Dimension>::RegionType &region);

// ITKToInr
template <class TPixel, unsigned int Dimension> 
InrImage* ITKToInr(typename itk::Image<TPixel,Dimension>::Pointer image,
								typename itk::Image<TPixel,Dimension>::RegionType region);

#include "wrapConversion.tpp"

#endif // _WRAPCONVERSION_H_