/* 
    This file is part of WARG's computer-vision

    Copyright (c) 2015, Waterloo Aerial Robotics Group (WARG)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Usage of this code MUST be explicitly referenced to WARG and this code
       cannot be used in any competition against WARG.
    4. Neither the name of the WARG nor the names of its contributors may be used
       to endorse or promote products derived from this software without specific
       prior written permission.

    THIS SOFTWARE IS PROVIDED BY WARG ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL WARG BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "../../core/include/frame.h"
#include "../../core/src/frame.cpp"
#include "../include/imgimport.h"
#include <vector>
#include <string>
#include "csvreading.cpp"
#include <dirent.h>

using namespace cv;
using namespace std;

ImageImport::ImageImport(std::string telemetry_path, std::string filePath, std::vector<int> videoDeviceNums) {
	string filename;
	Mat img;
	DIR* dr=opendir(filePath.c_str());
	struct dirent* drnt;
	count=0;
	Metadatalinkedlist* mdls=readcsv(telemetry_path.c_str());
	while(mdls!=0)
	{
		drnt=readdir(dr);
		while(strcmp(drnt->d_name,"..")==0||strcmp(drnt->d_name,".")==0)
		{
			drnt=readdir(dr);
		}
		if(drnt==NULL)
			break;
		filename=drnt->d_name;
		img=imread(filename,-1);
		Frame* newframe=new Frame(&img,filename,mdls->a);
		vec.push_back(*newframe);
		mdls=mdls->next;
		count++;
	}
	processed=0;
}

ImageImport::~ImageImport(){
	cout<<"image import ends."<<endl;
}

Frame * ImageImport::next_frame(){
	if(processed==count)
	{
		cout<<"no more input images"<<endl;
		return NULL;
	}
	else
	{
		processed++;
		return &vec.at(processed-1);
	}
}
