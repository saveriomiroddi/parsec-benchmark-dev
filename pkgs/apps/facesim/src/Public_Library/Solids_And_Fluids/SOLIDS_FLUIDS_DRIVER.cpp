//#####################################################################
// Copyright 2004-2006, Ron Fedkiw, Andrew Selle, Eftychios Sifakis.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class SOLIDS_FLUIDS_DRIVER
//#####################################################################
#include "SOLIDS_FLUIDS_DRIVER.h"
#include "../Utilities/LOG.h"

#include <sys/time.h>
#include <stdio.h>
#include <stddef.h>

static double _roi_time_begin;
static double _roi_time_end;

using namespace PhysBAM;
//#####################################################################
// Function Execute_Main_Program
//#####################################################################
template<class T> void SOLIDS_FLUIDS_DRIVER<T>::
Execute_Main_Program()
{
	Initialize();

	if (!example.restart && example.write_output_files && !example.write_substeps) Write_Output_Files (example.first_frame);


fflush(NULL);
struct timeval _t_start;
gettimeofday(&_t_start, NULL);
_roi_time_begin = (double)_t_start.tv_sec + (double)_t_start.tv_usec * 1e-6;

	Simulate_To_Frame (example.last_frame);

struct timeval _t_end;
gettimeofday(&_t_end, NULL);
_roi_time_end = (double)_t_end.tv_sec + (double)_t_end.tv_usec * 1e-6;
printf("ROI time measured: %.3fs\n", _roi_time_end - _roi_time_begin);
fflush(NULL);


	//Always write last frame for verification purposes
	if (!example.write_output_files && !example.write_substeps) Write_Output_Files (example.last_frame);

	LOG::Dump_Log();
}
//#####################################################################
// Function Initialize
//#####################################################################
template<class T> void SOLIDS_FLUIDS_DRIVER<T>::
Initialize()
{
	if (example.restart)
	{
		current_frame = example.restart_frame;
		Read_Time (current_frame);
	}
	else current_frame = example.first_frame;

	output_number = current_frame;
	time = Time_At_Frame (current_frame);
}
//#####################################################################
// Function Simulate_To_Frame
//#####################################################################
template<class T> void SOLIDS_FLUIDS_DRIVER<T>::
Simulate_To_Frame (const int frame_input)
{
	while (current_frame < frame_input)
	{
		LOG::Push_Scope ("FRAME", "Frame %d", current_frame + 1);
		Preprocess_Frame (current_frame + 1);
		Advance_To_Target_Time (Time_At_Frame (current_frame + 1));
		Postprocess_Frame (++current_frame);

		if (example.write_output_files && !example.write_substeps) Write_Output_Files (current_frame);

		if (example.verbose) std::cout << "TIME = " << time << std::endl;

		LOG::Pop_Scope();
		/*
		        std::cout<<"Printing log..."<<std::endl;
		        FILE_UTILITIES::Create_Directory(example.output_directory+"/xml");
		        std::ostream* output=FILE_UTILITIES::Safe_Open_Output(STRING_UTILITIES::string_sprintf("%s/xml/timing_xml.%d",example.output_directory.c_str(),current_frame));
		        LOG::Dump_Log_XML(*output);
		        delete output;
		*/
	}
}
//#####################################################################

template class SOLIDS_FLUIDS_DRIVER<float>;
template class SOLIDS_FLUIDS_DRIVER<double>;
