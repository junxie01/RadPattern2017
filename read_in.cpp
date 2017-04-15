/**
 * @short   read in parameters
 * @file    read_in.cpp
 * @author  Yixin Zhang
 *
 * This file contains the prototypes for reading parameters from the input file and write into memory and login file.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

#include "read_in.h"
#include "error_check.h"

using namespace std;

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function read all parameters in from parameter.in, check the reasonability, and then store them into login file, out to the screen as well as to the program memory.
 *
 * Return             0 on sucess
 *
 * Return             EXIT_FAILURE when parameter.in is wrong.
 */

int process_parameter(int argc, char* argv[], string *model_name, string *force_type,
                      float *alpha, float *beta, float *time_step, float *total_time,
                      string *waveform, float *area_x, float *area_y, int *n_x, int *n_y,
                      float *moment, float *rho)
{
    string str[100], variable_name;
    
    // Check the number of input files, exit program if check failed
    check_file_num(argc);
    
    // Read parameters as strings from input file
    read_infile(argc, argv, str);
    
    // Store parameters into memory as their declared types
    store_parameters(str, model_name, force_type, alpha, beta, time_step, total_time, waveform,
                     area_x, area_y, n_x, n_y, moment, rho);
    
    // Check the reasonability of variables
    check_variables(alpha, beta, time_step, total_time, area_x, area_y, n_x, n_y, moment, rho);
    
    // Write parameters into login file
    out_logfile(model_name, force_type, alpha, beta, time_step, total_time,
                waveform, area_x, area_y, n_x, n_y, moment, rho);
    
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function read information from infile and store them as strings.
 *
 * Return             0 on sucess
 *
 * Return             EXIT_FAILURE when parameter.in is wrong.
 */

int read_infile(int argc, char* argv[], string str[])
{
    int i = 0;
    string s;
    ifstream infile;
    
    infile.open(argv[1]);
    
    check_file_open(infile);
    
    // Read variables as strings from infile
    while( infile >> s )
    {
        str[i] = s;
        i++;
    }

    infile.close();
    
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function read parameters in memory as their declared types.
 *
 * Return             0 on sucess
 *
 * Return             EXIT_FAILURE when parameter.in is wrong.
 */

int store_parameters(string str[], string *model_name, string *force_type, float *alpha, float *beta,
                     float *time_step, float *total_time, string *waveform, float *area_x, float *area_y,
                     int *n_x, int *n_y, float *moment, float *rho)
{
    cout << "Start reading variables to memory\n" << endl;

    int i = 0;
    string variable_name;
    
    while(str[i] != "")
    {
        if(str[i] == "model_name")
        {
            read_string(str, i, variable_name, *model_name);
        }
        
        if(str[i] == "force_type")
        {
            read_string(str, i, variable_name, *force_type);
        }
        
        if(str[i] == "alpha")
        {
            read_float(str, i, variable_name, *alpha);
        }
        
        if(str[i] == "waveform")
        {
            read_string(str, i, variable_name, *waveform);
        }
        
        if(str[i] == "beta")
        {
            read_float(str, i, variable_name, *beta);
        }

        if(str[i] == "time_step")
        {
            read_float(str, i, variable_name, *time_step);
        }
        
        if(str[i] == "total_time")
        {
            read_float(str, i, variable_name, *total_time);
        }
        
        if(str[i] == "area_x")
        {
            read_float(str, i, variable_name, *area_x);
        }
        
        if(str[i] == "area_y")
        {
            read_float(str, i, variable_name, *area_y);
        }
        
        if(str[i] == "n_x")
        {
            read_int(str, i, variable_name, *n_x);
        }
        
        if(str[i] == "n_y")
        {
            read_int(str, i, variable_name, *n_y);
        }
        
        if(str[i] == "moment")
        {
            read_float(str, i, variable_name, *moment);
        }
        
        if(str[i] == "density")
        {
            read_float(str, i, variable_name, *rho);
        }
        
        i++;
    }
    
    cout << "Finish reading parameters.\n" << endl;
    
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function used for reading string variables in memory, print to screen
 *
 * Return             0 on sucess
 *
 */

int read_string(string str[], int i, string variable_name, string &string_value)
{
    variable_name = str[i];
    cout << variable_name << "=\t" << endl;

    string_value = str[i+1];
    cout << string_value << endl << "\n";
    
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function used for reading float variables in memory, print to screen
 *
 * Return             0 on sucess
 *
 */

int read_float(string str[], int i, string variable_name, float &float_value)
{

    char* c;
    variable_name = str[i];
    cout << variable_name << "=\t" << endl;

    c = const_cast<char*>(str[i+1].c_str());
    sscanf(c, "%e", &float_value);
    cout << float_value << endl << "\n";
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function used for reading int variables in memory, print to screen
 *
 * Return             0 on sucess
 *
 */

int read_int(string str[], int i, string variable_name, int &int_value)

{
    char* c;
    variable_name = str[i];
    cout << variable_name << "=\t" << endl;
    
    c = const_cast<char*>(str[i+1].c_str());
    sscanf(c,"%d", &int_value);
    cout << int_value << endl << "\n";
    
    return 0;
}

/**
 * Author:            Yixin Zhang
 *
 * Short description: This function used for writing values into login file
 *
 * Return             0 on sucess
 *
 */

int out_logfile(string *model_name, string *force_type, float *alpha, float *beta, float *time_step,
              float *total_time, string *waveform, float *area_x, float *area_y, int *n_x,
              int *n_y, float *moment, float *rho)
{
    ofstream logfile;
    
    logfile.open("login.txt");
    
    logfile << "model_name =\t" << model_name << endl;
    logfile << "force_type =\t" << force_type << endl;
    logfile << "alpha =\t" << alpha << endl;
    logfile << "beta =\t" << beta << endl;
    logfile << "time_step =\t" << time_step << endl;
    logfile << "total_time =\t" << total_time << endl;
    logfile << "waveform =\t" << waveform << endl;
    logfile << "area_x =\t" << area_x << endl;
    logfile << "area_y =\t" << area_y << endl;
    logfile << "n_x =\t" << n_x << endl;
    logfile << "n_y =\t" << n_y << endl;
    logfile << "moment =\t" << moment << endl;
    logfile << "density =\t" << rho << endl;

    logfile.close();
    
    cout << "login file has been written.\n" <<endl;

    return 0;
}
