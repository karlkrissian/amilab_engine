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

#ifdef AMI_USE_ITK

#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageLinearIteratorWithIndex.h"

#include "itkImageFileReader.h"
#include "itkImage.h"
#include "inrimage.hpp"

#endif // AMI_USE_ITK


template <class TPixel, unsigned int Dimension> 
InrImage* ITKToInr(typename itk::Image<TPixel,Dimension>::Pointer image,
                  typename itk::Image<TPixel,Dimension>::RegionType region)
{
  typedef TPixel               PixelType;
  typedef itk::Image< PixelType, Dimension >    ImageType;
  typedef itk::ImageLinearConstIteratorWithIndex< ImageType >  ConstIteratorType;
  InrImage* res = NULL;

  ConstIteratorType inputIt( image, region);
  std::cout << "1 " << std::endl;
  // size 
  int dimx = region.GetSize(0);
  int dimy = region.GetSize(1);
  int dimz = 1;
  if (Dimension==3) dimz = region.GetSize(2);
  res = new InrImage(dimx,dimy,dimz,1,WT_FLOAT,"Image_itk.ami.gz");

  //std::cout << "2 " << std::endl;
  res->SetTranslation(image->GetOrigin()[0],
            image->GetOrigin()[1],
            image->GetOrigin()[2]);
  res->SetVoxelSize(image->GetSpacing()[0],
            image->GetSpacing()[1],
            image->GetSpacing()[2]);


  //cout << "3 " << std::endl;
  int i=0;
  res->InitBuffer();
  inputIt.SetDirection(0);
  for ( inputIt.GoToBegin(); ! inputIt.IsAtEnd();  inputIt.NextLine())
  {
    inputIt.GoToBeginOfLine();
    while ( ! inputIt.IsAtEndOfLine() )
    {
      res->FixeValeur( inputIt.Get() );
      ++inputIt;
      if (!res->IncBuffer()) 
        std::cout << "! res->IncBuffer()" << std::endl;
    }
    i++;
  }
  return res;
}


//------------------------------------------------------------------
template <class TPixel, unsigned int Dimension> 
typename itk::Image<TPixel,Dimension>::Pointer 
    InrToITK_Vect(InrImage* input,
//  ------------- 
                typename itk::Image<TPixel,Dimension>::RegionType &region)
{
  typedef  TPixel              PixelType;
  typedef typename itk::Image< TPixel,Dimension>    ImageType;
  
  typename ImageType::ConstPointer inputImage;
  typedef itk::ImageLinearConstIteratorWithIndex< ImageType >  ConstIteratorType;
  typedef itk::ImageLinearIteratorWithIndex< ImageType >       IteratorType;
  
  typename ImageType::Pointer image = ImageType::New();
  typename ImageType::SizeType size;

  size[0] = input->DimX();
  size[1] = input->DimY();
  if (Dimension==3) size[2] = input->DimZ();
  region.SetSize(size);
  image->SetRegions(region);
  image->Allocate();

  float origin[Dimension];
  origin[0] = input->TrX();
  origin[1] = input->TrY();
  if (Dimension==3) origin[2] = input->TrZ();
  image->SetOrigin(origin);
  float voxsize[Dimension];
  voxsize[0] = input->VoxSizeX();
  voxsize[1] = input->VoxSizeY();
  if (Dimension==3) voxsize[2] = input->VoxSizeZ();
  image->SetSpacing(voxsize);

  IteratorType iter( image, region );
  iter.GoToBegin();
  input->InitBuffer();
  iter.SetDirection(0);
  for ( iter.GoToBegin(); ! iter.IsAtEnd();  iter.NextLine())
  {
    iter.GoToBeginOfLine();
    while ( ! iter.IsAtEndOfLine() )
    {
      TPixel v;
      for(int i=0;i<input->GetVDim();i++)
        v.SetNthComponent(i,input->VectValeurBuffer(i));
      iter.Set(v);
      ++iter;
      input->IncBuffer();
    }
  }
  return image;
}


//------------------------------------------------------------------
template <class TPixel, unsigned int Dimension> 
typename itk::Image<TPixel,Dimension>::Pointer 
  InrToITK(InrImage* input, 
//--------
                typename itk::Image<TPixel,Dimension>::RegionType &region)
{
  typedef  TPixel              PixelType;
  typedef typename itk::Image< TPixel,Dimension>    ImageType;
  
  typename ImageType::ConstPointer inputImage;
  typedef itk::ImageLinearConstIteratorWithIndex< ImageType >  ConstIteratorType;
  typedef itk::ImageLinearIteratorWithIndex< ImageType >       IteratorType;
  
  typename ImageType::Pointer image = ImageType::New();
  typename ImageType::SizeType size;

  size[0] = input->DimX();
  size[1] = input->DimY();
  if (Dimension==3) size[2] = input->DimZ();
  region.SetSize(size);
  image->SetRegions(region);
  image->Allocate();

  float origin[Dimension];
  origin[0] = input->TrX();
  origin[1] = input->TrY();
  if (Dimension==3) origin[2] = input->TrZ();
  image->SetOrigin(origin);
  float voxsize[Dimension];
  voxsize[0] = input->VoxSizeX();
  voxsize[1] = input->VoxSizeY();
  if (Dimension==3) voxsize[2] = input->VoxSizeZ();
  image->SetSpacing(voxsize);

  IteratorType iter( image, region );
  iter.GoToBegin();
  input->InitBuffer();
  iter.SetDirection(0);
  for ( iter.GoToBegin(); ! iter.IsAtEnd();  iter.NextLine())
  {
    iter.GoToBeginOfLine();
    while ( ! iter.IsAtEndOfLine() )
    {
      iter.Set(input->ValeurBuffer());
      ++iter;
      input->IncBuffer();
    }
  }
  return image;
}
