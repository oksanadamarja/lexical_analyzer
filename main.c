#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    FILE *filePsi ;
    FILE *fileLex;
    filePsi = fopen("code.psi.txt" ,"r"); //read the file code.psi
    fileLex = fopen("code.lex.txt" , "w"); //write on the file code.lex


    int k = 0;  //used for the strings array.
    int int_len = 0; //counts the number of integers.
    char strings[1000];  //array that keeps the strings read from the file.
    int m = 0;  //used to print the characters in fileLex.
    char words[20]; //keeps the identifiers.


    int a;
    int b;
    int identifier_length;
    int control_var;


    char keywords[18][20];  //the keywords are kept in an array.

    strcpy(keywords[0],"break");
    strcpy(keywords[1],"case");
    strcpy(keywords[2],"char");
    strcpy(keywords[3],"const");
    strcpy(keywords[4],"continue");
    strcpy(keywords[5],"do");
    strcpy(keywords[6],"else");
    strcpy(keywords[7],"enum");
    strcpy(keywords[8],"float");
    strcpy(keywords[9],"for");
    strcpy(keywords[10],"goto");
    strcpy(keywords[11],"if");
    strcpy(keywords[12],"int");
    strcpy(keywords[13],"long");
    strcpy(keywords[14],"record");
    strcpy(keywords[15],"return");
    strcpy(keywords[16],"static");
    strcpy(keywords[17],"while");

    char ch ;

    if(filePsi == NULL){  // if file is not found a message is printed.
        printf("File not found!");

    }
    else
    {
        ch = fgetc(filePsi);
        while(!feof(filePsi)) //reading the file.
            {
                if(isspace(ch))  //spaces not considered.
                {
                    ch = fgetc(filePsi);

                }
               //identifiers and keywords control.
               if(islower(ch)|| isupper(ch))
               {
                   a = 0;
                   b = 0;
                   identifier_length = 0;
                   control_var = 0;
                   while(isdigit(ch)|| islower(ch)|| isupper(ch)|| (ch == '_'))
                   {
                       if(a > 20 )
                       {
                        fputs("Lexical Error.The identifier cannot exceed 20 characters.\n",fileLex);
                        break;
                       }
                       if(islower(ch))
                       {
                        toupper(ch);  //if the character is lower case,convert it to upper case.
                       }
                       if(isdigit(ch)|| (ch == '_'))
                       {
                           control_var = 1; //this variable , when 1 means the word is an identifier.

                       }
                       words[a] = ch;
                       ch = getc(filePsi);
                       a++;
                   }
                   words[a] = '\0';
                   identifier_length = a;
                   if(control_var == 0)  //if the identifier is all letters, compared to keywords.
                   {
                       while(b < 18)
                       {
                         if(strcmp(words,keywords[b])== 0)
                         {
                             fputs("Keyword (",fileLex);
                             control_var = 0;
                             break;

                         }
                         else
                         {
                            control_var = 1;
                         }
                         b++;

                       }

                   }
                   if(control_var == 1)
                   {
                       fputs("Identifier (",fileLex);

                   }
                   b = 0; //b is zeroes so as to be used again.
                   while(b < identifier_length)
                   {
                       fputc(words[b],fileLex); //the identifier character by character is put in the fileLex.
                       b++;
                   }
                   fputs(")\n",fileLex);
               }
                //operators control.
                if(ch == '+') // checking for the + operator.
                {
                    ch = getc(filePsi);
                    if(ch =='+')     // if after the first + operator comes another +.
                    {
                        fputs("Operator (++)\n",fileLex);  // Operator ++ found.

                    }
                    else
                        {
                            fputs("Operator(+)\n",fileLex);  //else operator + found.
                            continue;
                        }

                }

                if(ch == '-')  // checking for the - operator.
                {
                    ch = getc(filePsi);
                    if(ch == '-')  // if after the first + operator comes another -.
                    {
                        fputs("Operator(--)\n",fileLex);   // Operator -- found.

                    }
                    else
                    {
                       fputs("Operator(-)\n",fileLex);   //else operator - found.
                       continue;

                    }

                }
                if(ch == ':')  // checking for := operator.
                {
                    ch = getc(filePsi);
                    if(ch == '=')
                    {
                        fputs("Operator(:=)\n",fileLex);
                    }
                    else
                    {
                        fputs("Undefined input :\n",fileLex);
                        continue;
                    }
                }

                if(ch == '*')
                {
                    fputs("Operator(*)\n",fileLex);

                }
                if(ch == '/')
                {
                    fputs("Operator(/)\n",fileLex);

                }
                //comments ,LeftPar and RightPar control.
                if(ch == '(')
                {
                    ch = getc(filePsi);

                    if(ch == '*')
                    {
                        while(ch = getc(filePsi)!= EOF)
                        {
                            ch = getc(filePsi);
                            if(ch == '*')
                            {
                                ch = getc(filePsi);
                                if(ch == ')')
                                {
                                   ch = getc(filePsi);
                                   break;
                                }
                                if(ch == EOF)
                                {
                                fputs("Lexical Error.The comment didn't end before EOF.\n",fileLex);
                                }
                            }

                        }
                    }
                    else
                    {
                        fputs("LeftPar\n ",fileLex);
                        continue;
                    }
                    continue;
                }
                if(ch == ')')
                {
                    fputs("RightPar\n",fileLex);
                }


                //strings control.
                if(ch == '"')
                {
                    ch = getc(filePsi);
                    strings[k] = ch;  // every character read after the " is added to the strings array.
                    k++;

                    while(ch != '"' && ch != EOF)
                    {
                        ch = getc(filePsi);
                        if(ch == '"')  // when the character is equal to " the string is terminated.
                        {
                            break;
                        }
                        strings[k] = ch;
                        k++;
                    }

                    if(ch == '"')  //if second " is reached than the string is terminated.
                    {
                        fputs("String (",fileLex);

                    while(m < strlen(strings))
                    {
                        fputc(strings[m],fileLex);
                        m++;
                    }
                    fputs(")\n",fileLex);
                    }
                    else if (ch == EOF)
                    {
                        fputs("Lexical Error occurred. String didn't finish before EOF.",fileLex);

                    }

                }


                //integer control.
                if(isdigit(ch))
                {
                    fputs("IntConst(", fileLex);
                    while (isdigit(ch))
                    {
                        if(int_len > 10)
                        {
                            fputs("Integers can't be longer than 10 characters!",fileLex);
                            return 1;
                        }
                    fputc(ch , fileLex);
                    ch = getc(filePsi);
                    int_len++; //counts the total number of digits.
                    }
                    fputs(")\n", fileLex);
                    int_len = 0;
                    continue;

                }


                //brackets and end of line control.

                if(ch == ';')
                {
                    fputs("End Of Line\n",fileLex);

                }
                if(ch == '[')
                {
                    fputs("LeftSquareBracket.\n",fileLex);

                }
                if(ch == ']')
                {
                    fputs("RightSquareBracket.\n",fileLex);

                }
                if(ch == '{')
                {
                    fputs("LeftCurlyBracket.\n",fileLex);

                }
                if(ch == '}')
                {
                    fputs("RightCurlyBracket.",fileLex);

                }



        ch = fgetc(filePsi);
        }
    }
    fclose(filePsi);  //filePsi closed.
    fclose(fileLex);  //fileLex closed.

    return 0;
}
