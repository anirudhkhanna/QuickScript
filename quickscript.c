// INCLUDED FILES:
// ---------------
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>
    #include <string.h>

// MACRO DECLARATIONS:
// -------------------
    #define ESC 27
    #define LF 10
    #define CR 13
    #define ONE 49
    #define TWO 50

    #define DELAY(ms) Sleep((ms))
    #define CLEARSCREEN() system("cls||clear")
    #define RANDOM(max) (rand()%(max))

// FUNCTION PROTOTYPES:
// --------------------
    void home_screen( void );
    void about_quickScript( void );
    void syntax_of_quickScript( void );
    void run_quickScript( void );
    void count_files( void );
    void store_files( char (*)[] );
    void validate_files( char (*)[] );
    void append_newline_to_files( char (*)[] );
    void prepare_temp_files( char (*)[] );
    void remove_temp_files( char (*)[] );
    void count_entries_in_file( char * );
    void conversation_engine( char * );
    void reply_to_matched_pattern( FILE * );
    int str_partial_match( char *, char * );
    int check_for_srai( FILE * );
    void put_string( char * );
    void trim_extra_spaces( char * );
    int validate_prefix( char * );
    void remove_space_after_prefix( char * );
    int check_for_comment( char * );
    void left_shift_string( char *, int );
    int find_substring_from_rhs( char *, char * );
    void find_and_replace_substrings( char *, char *, char * );
    void trim_spaces_and_punctuation( char * );

// GLOBAL VARIABLE DECLARATIONS:
// -----------------------------
    char choice, ch, filenames[10000][10000], userquery[10000], pattern[10000], wildcardstar[10000], wildcardunderscore[10000];
    int indF=0, indP=0, indUQ=0, indR=0, i=0, j=0, tempfilesFlag=0, foundFlag=0, sraiFlag=0;
    unsigned long totalFiles=0, totalEntries=0, ctr=1, possibleReplies=0, cnt=1;


// *******************************************************
//                HOME SCREEN FUNCTIONS
// *******************************************************

void home_screen()      /* .......... Home screen with main menu .......... */
{
    char *headers[]={
    "\n\
    \t                  _              _____              _         _    \n\r\
    \t                 (_)       __   / ____|            (_)       | |   \n\r\
    \t   ____ _ __  __ __ _____ / /__| (___    ___  _ __  _  _ __  | |_  \n\r\
    \t  / __ `// / / // // ___// //_/ \\___ \\  / __|| '__|| || '_ \\ | __| \n\r\
    \t / /_/ // /_/ // // /__ / , <   ____) || (__ | |   | || |_) || |_  \n\r\
    \t \\__, / \\__,_//_/ \\___//_/|_|  |_____/  \\___||_|   |_|| .__/  \\__| \n\r\
    \t   / /                                                | |          \n\r\
    \t  /_/                                                 |_|          \n\r\
    \n\
    \t\t    For creating virtual conversational programs\n\r\
    \t\t___________________________________________________\
    \n\n\r\
    \tDEVELOPER: Anirudh Khanna | CONTACT: anirudhkhanna.cse@gmail.com\n\r"
    };

    char *menu={
    "\n\
    \tMENU>>\t ENTER \t:  Run\n\r\
           \t 1 \t:  Syntax \n\r\
           \t 2 \t:  About\n\r\
           \t ESC \t:  Exit \n\r"
    };

    char *heading=headers[0];   //Use one of the headers as the program heading string.

    choice='\0';   //Variable to store user's choice from main menu.

    if(tempfilesFlag==1)
        remove_temp_files(filenames);

    CLEARSCREEN();   //Clear the screen.
    puts(heading);
    DELAY(100);

// INPUT MENU PROMPT:
// ------------------
    while(1)
    {
        puts(menu);
        printf("\tEnter a choice or press RETURN to run quickScript ");
        choice=getch();

        switch(choice)
        {
        case CR:   //Carriage Return
                CLEARSCREEN();
                run_quickScript();
                break;

        case ONE:   //Digit 1
                CLEARSCREEN();
                syntax_of_quickScript();
                break;

        case TWO:   //Digit 2
                CLEARSCREEN();
                about_quickScript();
                break;

        case ESC:    //Escape
                CLEARSCREEN();
                puts(heading);
                DELAY(50);
                printf("\n\tProgram will now exit.\n\n\tThank you for using quickScript!\n\t________________________________\n\t");
                getch();
                exit(0);
                break;

        default:
                CLEARSCREEN();
                puts(heading);
                DELAY(50);
                printf("\n\tInvalid choice!\n\n\tPress any key to go back and try again...\n\t_________________________________________\n\t");
                getch();
                CLEARSCREEN();
                puts(heading);
                break;
        }
    }
}


void syntax_of_quickScript()    /* .......... Show basic information about the syntax used in quickScript .......... */
{
    char *title="\n\n\t____________________________________\n\n\t\tQUICKSCRIPT SYNTAX\n\t____________________________________\n\n\n";

    char *info="\tENTRY TYPE \t- \tPREFIX/SYMBOL\
        \n\n\n\r\
        Pattern \t: \t>> \n\r\
        Reply \t\t: \t## and ++ \n\r\
        SRAI \t\t: \t== \n\r\
        Wildcards \t: \t* and _ \n\r\
        Comment \t: \t// \n\r\
        \n\n\r\
        IT IS HIGHLY RECOMMENDED TO READ THE QUICKSCRIPT DOCUMENTATION.";

    puts(title);
    puts(info);
    printf("\n\tPress any key to go back to the home screen... ");

    getch();
    home_screen();
}


void about_quickScript()    /* .......... Show basic information about the quickScript project .......... */
{
    char *title="\n\n\t____________________________________\n\n\t\tTHE QUICKSCRIPT PROJECT\n\t____________________________________\n\n\n";

    char *info="\tQuickScript is a simple and easy to learn special-purpose language \n\r\
        created by Anirudh Khanna, which can be used to design artificial \n\r\
        conversational agents and other programs that involve textual dialogue \n\r\
        between humans and computers.\
        \n\n\r\
        Find more about the project on it's GitHub repository:\n\r\
        https://github.com/anirudhkhanna/QuickScript\n\n\r\
        Released under the GNU General Public License v3.0 \n\r\
        available here: http://www.gnu.org/licenses/gpl-3.0.html";

    puts(title);
    puts(info);
    printf("\n\tPress any key to go back to the home screen... ");

    getch();
    home_screen();
}


void run_quickScript()      /* .......... Execute quickScript files .......... */
{
// GET AND VALIDATE QUICKSCRIPT FILES FROM "FILES.TXT":
// ----------------------------------------------------
    count_files();
    store_files(filenames);
    validate_files(filenames);  //Check the presence of each file.
    append_newline_to_files(filenames); //Append a newline to each file if it is not already present.
    prepare_temp_files(filenames);     //Removing all blank newlines, validating the syntax, drafting the files into temp files.

    CLEARSCREEN();
    printf("\n\tWELCOME.");
    printf(" TOTAL %lu FILES INCLUDED.", totalFiles);
    printf(" TO GO BACK, TYPE \"EXIT\".");

// TAKE USER QUERY AS INPUT:
// -------------------------
    INPUT:
    if(sraiFlag!=-1)
    {
        printf("\n\n\n\tYOU:\t");
        fgets(userquery, 10000, stdin);
        userquery[(strlen(userquery)-1)]='\0';      //We need to remove the extra newline taken by userquery[] because of using fgets().
        trim_spaces_and_punctuation(userquery);     //Trim extra spaces and remove punctuation marks (except apostrophe and hyphen) in userquery[].
    }
    foundFlag=0;
    sraiFlag=0;

// SEARCH AVAILABLE QS FILES FOR USER QUERY ONE-BY-ONE BY PASSING FILE NAMES TO CONVERSATION ENGINE:
// -------------------------------------------------------------------------------------------------
    for(indF=0; indF<totalFiles; indF++)
    {
        conversation_engine(filenames[indF]);
        if(foundFlag==1 || sraiFlag==-1)    //The sraiFlag status -1 means there was a SRAI and it was not satisfied in its own file. So, we need to search all files for that SRAI pattern now. The SRAI pattern is stored in userquery[], so taking new input has to be skipped too.
            break;
    }

    if(foundFlag==0 && sraiFlag!=-1)
    {
        printf("\n\t");
        printf("BOT:\tNot recognized.\n");
    }

    goto INPUT;
}


// *******************************************************
//               CORE CONVERSATION FUNCTIONS
// *******************************************************

void conversation_engine( char *filename )      /* .......... Match and respond to user query .......... */
{
    count_entries_in_file(filename);

    FILE *fp=fopen(filename, "r");

    MATCHQUERY:
    rewind(fp);
    ctr=1;

    if(strcmpi(userquery, "exit")==0)
        goto BACKTOHOME;

    while(ctr<=totalEntries)
    {
        indP=0;
        while((ch=fgetc(fp))!=LF && ch!=CR)
            pattern[indP++]=ch;
        pattern[indP]='\0';

        if(pattern[0]=='>' && pattern[1]=='>')   //If first 2 characters of a line are ">>", then it is a pattern to be matched.
        {
            left_shift_string(pattern, 2);  //Left shift the pattern string by 2 characters to remove ">>" prefix.

            if(strcmpi(pattern, userquery)==0 || str_partial_match(pattern, userquery)==1)
            {
                if(strcmpi(pattern, userquery)==0)  //Make wild card strings empty if the pattern was not partially matched.
                {
                    strcpy(wildcardstar, "");
                    strcpy(wildcardunderscore, "");
                }

            // CHECKING FOR SRAI:
            // ------------------
                if(check_for_srai(fp)==1)
                {
                    sraiFlag=1;
                    goto MATCHQUERY;
                }

            // NOW REPLY TO MATCHED PATTERN:
            // -----------------------------
                reply_to_matched_pattern(fp);
                foundFlag=1;
                fclose(fp);
                return;
            }
        }

        ctr++;
    }

    if(sraiFlag==1 && foundFlag==0)  //Checking if there was a SRAI pattern and it was satisfied (found) in this very file. (If not, then other files need to be searched).
        sraiFlag=-1;

    fclose(fp);
    return;

    BACKTOHOME:
    fclose(fp);
    printf("\n\tGoing back?\n\tPress <Y> to exit or any other key to cancel. ");
    choice=getch();
    if(choice=='y' || choice=='Y')
    {
        home_screen();
    }
    else
    {
        foundFlag=1;
        return;
    }
}


void reply_to_matched_pattern( FILE *fp )       /* .......... fetch valid replies into reply[][] and display .......... */
{
// COUNT THE POSSIBLE REPLIES:
// ---------------------------
    long initialPos=ftell(fp);  //Store the current position of file pointer for placing it back after counting.
    possibleReplies=0;

    ch=fgetc(fp);
    while(ch!='^')  //Replies are traversed till a new query pattern starts (with ">>") or the database ends (with '^').
    {
        if(ch=='>') //Check if the reply block has ended and a new query pattern has started (i.e. check for ">>" prefix).
        {
            long initPos=ftell(fp);     //Mark the current position of file pointer.
            char ch1=fgetc(fp);         //Store the next character in ch1.

            if(ch1=='>')
                break;

            fseek(fp, initPos, SEEK_SET);
        }

        if(ch==LF || ch==CR)    //When a newline character is encountered, increment the count of replies.
            possibleReplies++;

        ch=fgetc(fp);
    }

    fseek(fp, initialPos, SEEK_SET);    //Place the file pointer back at its position (just after the matched pattern).

// STORE VALID REPLIES IN AN ARRAY OF STRINGS:
// -------------------------------------------
    char reply[possibleReplies][10000];  //Declare an array of strings to store valid reply entries,
    for(i=0; i<possibleReplies; i++)    //and initialize each string with NULL.
        strcpy(reply[i], "");

    cnt=1;
    i=0;
    j=0;

    while(cnt<=possibleReplies)
    {
        j=0;
        while((ch=fgetc(fp))!=LF && ch!=CR)
        {
            reply[i][j]=ch;
            j++;
        }
        reply[i][j]='\0';

        find_and_replace_substrings(reply[i], "[star]", wildcardstar);
        find_and_replace_substrings(reply[i], "[STAR]", wildcardstar);
        find_and_replace_substrings(reply[i], "[underscore]", wildcardunderscore);
        find_and_replace_substrings(reply[i], "[UNDERSCORE]", wildcardunderscore);

        i++;
        cnt++;
    }

// DISPLAY A REPLY:
// ----------------
    indR=RANDOM(possibleReplies);    //Get a random index between 0 to (possibleReplies-1).

    while(reply[indR][0]=='+' && reply[indR][1]=='+')     //Reach the starting line of the random reply segment (Beginning of a reply does not have a "++" prefix while subsequent lines in that very reply do).
        indR--;

    left_shift_string(reply[indR], 2);  //Left shift reply by 2 characters to remove "##" prefix.
    printf("\n\t");
    DELAY(100);
    printf("BOT:\t");
    put_string(reply[indR]);
    indR++;
    while(reply[indR][0]=='+' && reply[indR][1]=='+')
    {
        left_shift_string(reply[indR], 2);     //Left shift reply by 2 character to remove "++" prefix.
        printf("\t\t");
        put_string(reply[indR]);
        indR++;
    }
}


// *******************************************************
//                FILE RELATED FUNCTIONS
// *******************************************************

void count_files()      /* .......... Count the no of quickScript files to be included via "files.txt" .......... */
{
    totalFiles=0;
    FILE* _fnames=fopen("files.txt", "r");

    char _c, _filenm[10000];
    int _i=0;

    while((_c=fgetc(_fnames))!=EOF)
    {
        if(_c=='<')
        {
            strcpy(_filenm, "");
            _i=0;

            while((_c=fgetc(_fnames))==' ')   //Traverse the blank spaces after '<' (if any) till a letter of file name is encountered.
                ;

            while(_c!='>' && _c!=EOF)  //Store file name in _filenm[] string.
            {
                _filenm[_i++]=_c;
                _c=fgetc(_fnames);
            }
            _filenm[_i]='\0';

            int _I=strlen(_filenm)-1;   //Removing spaces (if any) from the end of file name in _filenm[].
            while(_filenm[_I]==' ')
                _filenm[_I--]='\0';

            if(strcmpi(_filenm, "")!=0)
            {
                _I=strlen(_filenm)-1;   //Making sure that the file has ".qs" extension.
                if(_filenm[_I-2]=='.' && _filenm[_I-1]=='q' && _filenm[_I]=='s')
                    totalFiles++;   //Increment the total number of included files if it is a valid quickScript file.
            }
        }
    }

    fclose(_fnames);
}


void  store_files( char filenames[][10000] )     /* .......... Store the names of all the available quickScript files in an array of strings .......... */
{
    FILE* _fnames=fopen("files.txt", "r");

    char _c, _filenm[10000];
    int _i=0, _j=0;

    while((_c=fgetc(_fnames))!=EOF)
    {
        if(_c=='<')
        {
            strcpy(_filenm, "");
            _i=0;

            while((_c=fgetc(_fnames))==' ')   //Traverse the blank spaces after '<' (if any) till a letter of file name is encountered.
                ;

            while(_c!='>' && _c!=EOF)  //Store file name in _filenm[] string.
            {
                _filenm[_i++]=_c;
                _c=fgetc(_fnames);
            }
            _filenm[_i]='\0';

            int _I=strlen(_filenm)-1;   //Removing spaces (if any) from the end of file name in _filenm[].
            while(_filenm[_I]==' ')
                _filenm[_I--]='\0';

            if(strcmpi(_filenm, "")!=0)
            {
                _I=strlen(_filenm)-1;   //Making sure that the file has ".qs" extension.
                if(_filenm[_I-2]=='.' && _filenm[_I-1]=='q' && _filenm[_I]=='s')
                    strcpy(filenames[_j++], _filenm);  //Copy valid file names to filenames[][] array of strings.
            }
        }
    }

    fclose(_fnames);
}


void validate_files( char filenames[][10000] )       /* .......... Validate the presence of all the available quickScript files .......... */
{
    int _i;
    FILE *_fp;

    for(_i=0; _i<totalFiles; _i++)
    {
        _fp=fopen(filenames[_i], "r");

        if(_fp==NULL)
        {
            CLEARSCREEN();
            DELAY(500);
            printf("\n    To be kind and report this error, write to <anirudhkhanna.cse@gmail.com>\
                    \n\n\t____________________________________\n\n\t      ERROR IN ACCESSING FILE\n\t____________________________________\
                    \n\n\n\tApologies from quickScript,\
                    \n\
                    \n\tIt seems that one or more files can\'t be accessed at this moment :(\
                    \n\tPlease make sure that all entries in \"files.txt\" are valid.\n\t(Interrupt was encountered at: \"%s\")\
                    \n\n\n\
                    \n\n\n\tProgram will now go back to home screen.\n\tPress any key to continue... ", filenames[_i]);
            fclose(_fp);
            getch();
            home_screen();
        }

        fclose(_fp);
    }
}


void append_newline_to_files( char filenames[][10000] )     /* .......... Append a newline character to included .qs files if not already present .......... */
{
    int _i;
    char _c='\0', _newlinech='\n';
    FILE *_fp;

    for(_i=0; _i<totalFiles; _i++)
    {
        _fp=fopen(filenames[_i], "a+");

    // CHECK IF A LINE FEED OR CARRIAGE RETURN CHARACTER IS ALREADY PRESENT AT THE END OF FILE:
    // ----------------------------------------------------------------------------------------
        fseek(_fp, -1L, SEEK_END);
        _c=fgetc(_fp);

        if(_c!=LF && _c!=CR)
        {
        // APPEND NEWLINE CHARACTER IF NOT ALREADY PRESENT:
        // ------------------------------------------------
            fseek(_fp, -1L, SEEK_END);
            fputc(_newlinech, _fp);
        }

        fclose(_fp);
    }
}


void prepare_temp_files( char filenames[][10000] )      /* .......... Create *_temp.qs files corresponding to all included .qs files, in proper QS format .......... */
{
    int _i=0, _j=0, _I=1;
    FILE *_fin;
    FILE *_fout;

    char _c='\0';
    unsigned long _lines=0, _ctr=1;
    int _chars=0, _maxchars=0, _progress=0;

// SHOW PROGRESS AS 0% INITIALLY:
// ------------------------------
    CLEARSCREEN();
    printf("\n\n\n\t\t\t\tLoading... (0%%)\n\r\
    \t\t\t   ");

    for(_i=0; _i<totalFiles; _i++)
    {
    // FOR READ OPERATION (ON ACTUAL FILES):
    // -------------------------------------
        _fin=fopen(filenames[_i], "r");

    // FOR WRITE OPERATION (ON TEMP FILES):
    // ------------------------------------
        int _N=strlen(filenames[_i])-3;     //To remove ".qs" part from file name.
        filenames[_i][_N]='\0';
        strcat(filenames[_i], "_temp.qs");  //And then append "_temp.qs" for creating a temp QS file.
        _fout=fopen(filenames[_i], "w");

    // NOW PREPARE TEMP FILES:
    // -----------------------
        _lines=0;
        while((_c=fgetc(_fin))!=EOF)    //Count no of lines in the file.
            if(_c==LF || _c==CR)
                _lines++;

        rewind(_fin);
        _ctr=1;
        _chars=0;
        _maxchars=0;
        while(_ctr<=_lines)     //Get the maximum no of characters any line has in that file, for deciding the size of the string str[].
        {
            _c=fgetc(_fin);
            _chars++;

            if(_c==LF || _c==CR)
            {
                _ctr++;

                if(_chars>_maxchars)
                    _maxchars=_chars;

                _chars=0;
            }
        }

        rewind(_fin);
        _ctr=1;
        char _str[_maxchars];
        int _ind=0;
        while(_ctr<=_lines)     //Read the file line by line and write the non-empty lines into corresponding temp file.
        {
            _ind=0;
            while((_c=fgetc(_fin))!=LF && _c!=CR)
                _str[_ind++]=_c;
            _str[_ind]='\0';

            trim_extra_spaces(_str);    //Trim extra spaces from the string (and also convert all tabs to spaces).

            if(strcmp(_str, "")!=0)
            {
                if(validate_prefix(_str)!=1)   //Validate prefix will return 1 if a valid prefix is detected. Otherwise, it returns 0.
                {
                    char _filenm[10000]="";
                    strcpy(_filenm, filenames[_i]);     //Make a duplicate string of current filename.
                    int _M=strlen(_filenm)-8;   //To remove "_temp.qs" part from copied file name.
                    _filenm[_M]='\0';
                    strcat(_filenm, ".qs");     //And then append ".qs" for displaying original file name below.

                    CLEARSCREEN();
                    printf("\n\n\t____________________________________\n\n\t\t  ERROR IN SYNTAX\n\t____________________________________\n\n\n");
                    printf("\tINVALID PREFIX: ");
                    put_string(_str);
                    printf("\n\tFILE: ");
                    put_string(_filenm);
                    printf("\n\tLINE NO: %d", _ctr);

                    fclose(_fin);
                    fclose(_fout);

                    for(_j=0; _j<=_i; _j++)
                        remove(filenames[_j]);

                    printf("\n\n\n\n\tProgram will now go back to home screen.\n\tPress any key to continue... ");
                    getch();
                    home_screen();
                }

                remove_space_after_prefix(_str);

                if(check_for_comment(_str)!=1)
                {
                    fputs(_str, _fout);
                    fputs("\n", _fout);
                }
            }

            _ctr++;
        }

        fputs("^\n", _fout);    //Also append the '^' character at the end of file.
        fclose(_fin);
        fclose(_fout);

    // SHOW PROGRESS AFTER PREPARING EACH FILE:
    // ----------------------------------------
        CLEARSCREEN();
        _progress=((float)(_i+1)/(totalFiles))*100;
        printf("\n\n\n\t\t\t\tLoading... (%d%%)\n\r\
               \t\t   ", _progress);
        _I=1;
        while(_I<=((float)_progress/100)*26)
        {
            printf("_");
            _I++;
        }
    }

    tempfilesFlag=1;
    DELAY(250);
}


void remove_temp_files( char filenames[][10000] )   /* .......... Delete the files whose names are in in filenames[][]. Intended for *_temp.qs files .......... */
{
    int _i=0;
    for(_i=0; _i<totalFiles; _i++)
    {
        remove(filenames[_i]);
    }

    tempfilesFlag=0;
}


void count_entries_in_file( char *filename )      /* .......... Count the no of entries in a quickScript file .......... */
{
    totalEntries=0;
    FILE *fp = fopen(filename, "r");

    if(fp==NULL)
    {
        CLEARSCREEN();
        DELAY(500);
        printf("\n    To be kind and report this error, write to <anirudhkhanna.cse@gmail.com>\
                \n\n\t____________________________________\n\n\t      ERROR IN ACCESSING FILE\n\t____________________________________\
                \n\n\n\tApologies from quickScript,\
                \n\
                \n\tIt seems that one or more files can\'t be accessed at this moment :(\
                \n\tPlease make sure that all entries in \"files.txt\" are valid.\n\t(Interrupt was encountered at: \"%s\")\
                \n\n\n\
                \n\n\n\tProgram will now go back to home screen.\n\tPress any key to continue... ", filename);
        fclose(fp);
        getch();
        home_screen();
    }

    while((ch=fgetc(fp))!=EOF)
    {
        if(ch==LF || ch==CR)    //When a newline character is encountered, increment the count of entries.
            totalEntries++;
    }

    fclose(fp);
}


// *******************************************************
//                  PERIPHERAL FUNCTIONS
// *******************************************************

int str_partial_match( char *p, char *u )   /* .......... Match strings with '*' and '_' wild cards. Rightmost wild card sequences are also stored in strings wildcardstar[] and wildcardunderscore[] .......... */
{
    char ptrn[10000];
    char usrqry[10000];
    strcpy(ptrn, p);    //Duplicating the strings,
    strcpy(usrqry, u);  //So that original ones are not affected when lowercasing.
    strlwr(ptrn);   //Converting the duplicate strings to lowercase,
    strlwr(usrqry); //This will make case-insignificant matching easier.
    int matchFlag=1;
    int i, j, I, J;
    int wcStart, wcEnd, wcInd, x;

    char nextword[10000];
    strcpy(wildcardstar, "");
    strcpy(wildcardunderscore, "");

    for(i=0, j=0; ptrn[i]!='\0' || usrqry[j]!='\0'; i++, j++)
    {
    // MATCH WILDCARD CHARACTER STAR (*):
    // ----------------------------------
        if(ptrn[i]=='*' && ptrn[i+1]!='\0') //'*' in beginning or middle of the pattern.
        {
            i++;
            wcStart=j;
            I=i;
            J=0;
            nextword[J++]=ptrn[I++];
            while(ptrn[I]!=' ' && ptrn[I]!='*' && ptrn[I]!='_' && ptrn[I]!='\0')
                nextword[J++]=ptrn[I++];
            nextword[J]='\0';

            strrev(nextword);   //Reverse the next word after '*' to match its first occurrence FROM THE RIGHT HAND SIDE in usrqry[].
            if((j=find_substring_from_rhs(usrqry, nextword))!=-1)   //This function returns -1 if the substring is not found, otherwise returns the index just after the substring.
            {
                wcEnd=j;
                x=0;
                for(wcInd=wcStart; wcInd<wcEnd; wcInd++)    //Storing the wildcard pattern in wildcardstar[].
                    wildcardstar[x++]=usrqry[wcInd];
                wildcardstar[x]='\0';
            }
        }
        else
        if(ptrn[i]=='*' && ptrn[i+1]=='\0') //'*' in end of the pattern.
        {
            x=0;
            while(usrqry[j]!='\0')    //Storing the wildcard pattern in wildcardstar[].
                wildcardstar[x++]=usrqry[j++];
            wildcardstar[x]='\0';
            break;
        }

    // MATCH WILDCARD CHARACTER UNDERSCORE (_):
    // ----------------------------------------
        else
        if(ptrn[i]=='_' && ptrn[i+1]!='\0') //'_' in beginning or middle of the pattern.
        {
            i++;
            wcStart=j;
            I=i;
            J=0;
            nextword[J++]=ptrn[I++];
            while(ptrn[I]!=' ' && ptrn[I]!='*' && ptrn[I]!='_' && ptrn[I]!='\0')
                nextword[J++]=ptrn[I++];
            nextword[J]='\0';

            strrev(nextword);   //Reverse the next word after '_' to match its first occurrence FROM THE RIGHT HAND SIDE in usrqry[].
            if((j=find_substring_from_rhs(usrqry, nextword))!=-1)   //This function returns -1 if the substring is not found, otherwise the index just after the substring.
            {
                wcEnd=j;
                x=0;
                for(wcInd=wcStart; wcInd<wcEnd; wcInd++)    //Storing the wildcard pattern in wildcardunderscore[].
                    wildcardunderscore[x++]=usrqry[wcInd];
                wildcardunderscore[x]='\0';
            }
        }
        else
        if(ptrn[i]=='_' && ptrn[i+1]=='\0') //'_' in end of the pattern.
        {
            x=0;
            while(usrqry[j]!='\0')    //Storing the wildcard pattern in wildcardunderscore[].
                wildcardunderscore[x++]=usrqry[j++];
            wildcardunderscore[x]='\0';
            break;
        }

        if(ptrn[i]!=usrqry[j])
        {
            matchFlag=0;
            break;
        }
    }

    if(matchFlag==1)
        return 1;
    else
        return 0;
}


int check_for_srai( FILE *fp )      /* .......... If a "==" entry succeeds a pattern, then it is a SRAI. Store it into userquery[] and return 1, otherwise return 0 .......... */
{
    long initialPos=ftell(fp);
    char ch1=fgetc(fp);
    char ch2=fgetc(fp);

    if(ch1=='=' && ch2=='=')
    {
        indUQ=0;
        while((ch1=fgetc(fp))!=LF && ch1!=CR)    //Replacing user query with SRAI pattern so that now the SRAI pattern is searched.
            userquery[indUQ++]=ch1;
        userquery[indUQ]='\0';

        find_and_replace_substrings(userquery, "[star]", wildcardstar);
        find_and_replace_substrings(userquery, "[STAR]", wildcardstar);
        find_and_replace_substrings(userquery, "[underscore]", wildcardunderscore);
        find_and_replace_substrings(userquery, "[UNDERSCORE]", wildcardunderscore);

        return 1;
    }

    fseek(fp, initialPos, SEEK_SET);
    return 0;
}


void put_string( char *str )    /* .......... Print the string nicely, limit 50-60 characters per line .......... */
{
    int i=0, charactersPrinted=0;

    for(i=0; str[i]!='\0'; i++)
    {
        printf("%c", str[i]);
        charactersPrinted++;

        if(charactersPrinted>=50 && str[i]==' ')
        {
            printf("\n\t\t");
            charactersPrinted=0;
        }

        if(charactersPrinted==60)
        {
            printf("\n\t\t");
            charactersPrinted=0;
        }
    }
    printf("\n");
}


void trim_extra_spaces( char *str )     /* .......... Convert all tabs to spaces. Remove all spaces from beginning & end. Remove extra spaces in the middle of string .......... */
{
    int i, j, I;

// FIRST, CONVERT ALL TABS TO SPACES:
// ----------------------------------
    i=0;
    while(str[i]!='\0')
    {
        if(str[i]=='\t')
            str[i]=' ';
        i++;
    }

// TRIM SPACES & TABS AT THE BEGINNING OF STRING:
// ----------------------------------------------
    i=0;
    while(str[i]==' ')
        i++;
    left_shift_string(str, i);

// TRIM SPACES & TABS AT THE END OF STRING:
// ----------------------------------------
    i=strlen(str)-1;
    while(str[i]==' ')
        str[i--]='\0';

// TRIM EXTRA SPACES & TABS IN THE MIDDLE OF STRING:
// -------------------------------------------------
    i=0;
    j=0;
    while(str[i]!='\0')
    {
        if(str[i]==' ')
        {
            I=i+1;
            while(str[I]==' ')
            {
                i++;
                I++;
            }
        }
        str[j++]=str[i++];
    }
    str[j]='\0';
}


int validate_prefix( char *str )    /* .......... Check for invalid prefixes. Return 0 for an invalid prefix, otherwise 1 .......... */
{
    int i;
    char prefix[3]="";

    for(i=0; i<2 && str[i]!='\0'; i++)
        prefix[i]=str[i];
    prefix[i]='\0';

    if(!(strcmp(prefix, ">>")==0 || strcmp(prefix, "##")==0 || strcmp(prefix, "++")==0 || strcmp(prefix, "==")==0 || strcmp(prefix, "//")==0))
    {
        return 0;
    }

    return 1;
}


void remove_space_after_prefix( char *str )     /* .......... Remove whitespace (if any) after the prefix of an entry .......... */
{
    int i;

    if(str[2]==' ')     //Check the index just after the prefix (a prefix takes 2 characters).
    {
        for(i=2; str[i]!='\0'; i++)
            str[i]=str[i+1];
    }
}


int check_for_comment( char *str )      /* .......... Check for "//" prefix .......... */
{
    if(str[0]=='/' && str[1]=='/')
    {
        return 1;
    }

    return 0;
}


void left_shift_string( char *str, int N )     /* .......... ">>hello" becomes "hello" .......... */
{
    int i;
    while(N--)
    {
        for(i=0; str[i]!='\0'; i++)
            str[i]=str[i+1];
    }
}


int find_substring_from_rhs( char *str, char *sub )     /* .......... Find the first occurrence of a given substring from right hand side. REVERSED SUBSTRING is passed in sub[]. Returns the index just after the substring or -1 if it is not found .......... */
{
	int i, j, I, notfound=1, found=0;

	for(i=strlen(str)-1; i>=0; i--)
	{
		if(sub[0]==str[i])
		{
		    notfound=0;
            I=i;
			for(j=0; sub[j]!='\0'; j++, I--)
			{
				if(str[I]!=sub[j])
                {
                    notfound=1;
                    break;
                }
			}
		}
		if(notfound==0)
		{
			found=1;
			break;
		}
	}

	if(found==1)
        return (I+1);
	else
        return -1;
}


void find_and_replace_substrings( char *str, char *sub, char *rep )     /* .......... Replace all occurrences of a substring with another .......... */
{
    int i, j, I, x, y, substrsize=strlen(sub);
	int notfound=1;

	for(i=0; str[i]!='\0'; i++)
	{
	    notfound=1;
		if(sub[0]==str[i])
		{
		    notfound=0;
			I=i;
			for(j=0; sub[j]!='\0'; j++, I++)
			{
				if(str[I]!=sub[j])
				{
				    notfound=1;
				    break;
				}
			}
		}
		if(notfound==0)
		{
            x=i;
            y=0;
            while(y<substrsize)
            {
                for(x=i; str[x]!='\0'; x++)     //Repeatedly left shift the string str[] from i, to remove the substring.
                    str[x]=str[x+1];
                y++;
            }

            for(y=0; rep[y]!='\0'; y++)
            {
                str[strlen(str)+1]='\0';            //Increasing the size of string str[],
                str[strlen(str)]=str[strlen(str)-1];  //As we write the replacement string character-by-character into it at proper place(s).

                for(x=strlen(str)-1; x>i; x--)      //Making space for the new character coming from replacement string rep[].
                    str[x]=str[x-1];

                str[i]=rep[y];  //Now replace the character at ith position in str[] with required character in rep[],
                i++;            //And increment i.
            }
		}
	}
}


void trim_spaces_and_punctuation( char *str )   /* .......... Remove extra spaces, drop punctuation marks and symbols .......... */
{
    int i, j;

// REMOVE SOME PUNCTUATION (EXCEPT APOSTROPHE AND HYPHEN):
// -------------------------------------------------------
    j=0;
    for(i=0; str[i]!='\0'; i++)
    {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || (str[i]>='0' && str[i]<='9') || (str[i]==' ') || (str[i]=='\'') || (str[i]=='-'))
            str[j++]=str[i];
    }
    str[j]='\0';

// TRIM EXTRA SPACES:
// ------------------
    trim_extra_spaces(str);
}


// *******************************************************
//                      MAIN FUNCTION
// *******************************************************

int main()      /* .......... Driver function of the program .......... */
{
    srand((unsigned)time(NULL));  //Seed the random number generator.
    home_screen();  //Call the home screen.
    return 0;
}
