/*  QuickScript - An open-source platform for designing artificial conversational agents.
 *  Website:    http://anirudhkhanna.github.io/QuickScript
 *  GitHub:     http://github.com/anirudhkhanna/QuickScript
 *
 *  Copyright (C) 2016 QuickScript
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact:    Anirudh Khanna
 *              anirudhkhanna.cse@gmail.com
 *              http://anirudhkhanna.github.io/
 */


// *******************************************************
//                REQUIRED HEADER FILES
// *******************************************************

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <time.h>


// *******************************************************
//                CHECKING THE PLATFORM
// *******************************************************

    #if defined (WIN32) || defined (_WIN32)
        #define PLATFORM_WIN
    #elif defined (__linux__) || (__gnu_linux__) || (__GNU__)
        #define PLATFORM_LINUX
    #elif defined (__unix__) || defined (__unix)
        #define PLATFORM_UNIX
    #elif defined (__APPLE__) && defined (__MACH__)
        #define PLATFORM_MAC
    #elif defined (MSDOS) || defined (__MSDOS__) || defined (_MSDOS) || defined(__DOS__)
        #define PLATFORM_DOS
    #endif


    #if defined (PLATFORM_LINUX) || defined (PLATFORM_UNIX) || defined (PLATFORM_MAC)
        #include <unistd.h>
        #if defined _POSIX_VERSION
            #define PLATFORM_POSIX
        #endif
    #endif


// *******************************************************
//                MACRO DEFINITIONS
// *******************************************************

    #define MAX_ARR_SIZE 10000
    #define ESC 27
    #define LF 10
    #define CR 13
    #define ONE 49
    #define TWO 50
    #define UPPERCASE_L 76
    #define LOWERCASE_L 108
    #define EXTERNAL_KNOWLEDGE_FILE "external_knowledge.qs"
    #define EXTERNAL_KNOWLEDGE_INTERMEDIATE_FILE "external_knowledge_intermediate.qs"
    #define EXTERNAL_KNOWLEDGE_TEMP_FILE "external_knowledge_temp.qs"


    #define CLEARSCREEN()   //Under platform-specific code
    #define DELAY(ms)       //Under platform-specific code
    #define RANDOM(max) (rand()%(max))


// *******************************************************
//                PLATFORM-SPECIFIC CODE
// *******************************************************

    #if defined PLATFORM_WIN
        #include <windows.h>
        #undef DELAY
        #define DELAY(ms) Sleep((ms))
    #endif


    #if defined (PLATFORM_WIN) || defined (PLATFORM_DOS)
        #undef CLEARSCREEN
        #define CLEARSCREEN(){if(system(NULL)) system("cls||clear");}
    #elif defined PLATFORM_POSIX
        #undef CLEARSCREEN
        #define CLEARSCREEN(){if(system(NULL)) system("clear");}
    #else
        #undef CLEARSCREEN
        #define CLEARSCREEN() printf("\e[2J\e[H");
    #endif


    #if defined (PLATFORM_POSIX) || defined (PLATFORM_LINUX) || defined (PLATFORM_UNIX) || defined (PLATFORM_MAC)
        #include <unistd.h>
        #include <termios.h>
        int getch(){
            struct termios oldt, newt;
            int ch;
            tcgetattr(STDIN_FILENO, &oldt);
            newt=oldt;
            newt.c_lflag&=~(ICANON|ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            ch=getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return ch;}
    #elif defined PLATFORM_DOS
        #include <conio.h>
    #endif
