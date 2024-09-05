#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//Dimensions
int N;    //1D  Rows (Vertical)
int M;    //2D  Columns (Horizonal)
   
//Moves
void right(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt);
void left(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt);
void up(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt);
void down(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt);     

int main(void)
{

   char DigDoug = '$';    //protagonist of the Game

                          //Different Dificulty Levels
   char easy[] = "easy\n";
   char medium[] = "medium\n";                       
   char hard[] = "hard\n";
   char difficulty[10];

   /*
                          //Dimensions
   int N;    //1D  Rows (Vertical)
   int M;    //2D  Columns (Horizonal)
   */

             //2D array that we are gonna allocate dynamically
   char **arr;    //N*M
            //Things that are behind the closed squares of arr   
   char **arr2;
             //number of diamonds in the table
   int diamonds;
   int value;
   int diamondscnt = 0;
             //number of obstacles in the table
   int obstacles;                                
             //Differency of the table after the user move to the next level
   int leveldif; 

             //Random variables that we find useful
   int a,b;
             //When the ground is cracked, it is equal to ' ' (space)
   char dug = ' ';
             //Diamond value
   int LDvalue = 0;
   int GDvalue = 0;

             //Orders (Moves DigDoug makes during the Game)
   char terminate = 'X';
   char caseterminate = 'x';

   char Up   = 'U';
   char caseUp = 'u';

   char Down = 'D';
   char caseDown = 'd';

   char Left = 'L';
   char caseLeft = 'l';

   char Right= 'R'; 
   char caseRight = 'r';
              //Full order that it consists of two parts         
   char order[10];
        char part1;
        int part2int;  //We got to convert it from char to integer
        char *v;
        v = (char *)malloc(sizeof(char)*10);
              
   //User entering the Dimensions of the Table

      
  for(int i = 0;i<1;i++)
  { 
   printf("The SUM of Rows and Columns should be atleast equal to 10\n\n");
   /*Αυτο γιατί η δυσκολία "easy" απαιτεί τα εμπόδια να αποτελούν το
     10% των τετραγώνων. Που σημαίνει πως το εμπόδιο για να είναι τουλάχιστον 1,
     πρέπει τα τατράγωνα NxM >= 10
   */

    printf("Enter the Number of Rows: ");
    scanf("%d",&N);

    printf("Enter the Number of Columns: ");
    scanf("%d",&M);

    /*
    Το Μ(columns) θα πρέπει να είναι M<=128 επειδή είναι ο maximum αριθμός που μπορεί
    να δείξει η κονσόλα δίχως οι στήλες να αλλάξουν σειρά.
   */

     if((N+M) < 10 || M > 128 )
     {
       i--;
       continue;  
     }  
  }

char arrstatic[N][M];//We need a static array in order to transfer the data to another function
char arr2static[N][M];
    //arr1
       //Dynamically allocating the table  
         //Dynamic allocation of the 1D (rows)
        arr = (char**)malloc(N*sizeof(char *));

           if(arr == NULL)
           {
              printf("An error during the allocation (1D)");
              exit(1); 
           }

         //Dynamic allocation of the 2D (columns)
        for(int i = 0;i<N;i++)
        {
           arr[i] = (char*)malloc(M*sizeof(char));

             if(arr[i] == NULL)
             {
                printf("An error during the allocation (2D)");
                exit(1);  
             } 
        } 

    //arr2
         arr2 = (char**)malloc(N*sizeof(char *));

           if(arr2 == NULL)
           {
              printf("An error during the allocation");
              exit(1); 
           }

         //Dynamic allocation of the 2D (columns)
        for(int i = 0;i<N;i++)
        {
           arr2[i] = (char*)malloc(M*sizeof(char));

             if(arr2[i] == NULL)
             {
                printf("An error during the allocation");
                exit(1);  
             } 
        }      


getchar();//in order to eat the \n from previous scanf
   //Letting User to choose difficulty
   printf("\nChoose one of the following difficulties:\n1)easy\n2)medium\n3)hard\n");

  for(int i = 0;i<1;i++)
  {
    fgets(difficulty,sizeof(difficulty),stdin);
    
      if( strcmp(easy,difficulty)!=0 && strcmp(medium,difficulty)!=0 && strcmp(hard,difficulty)!=0 )
      {
          printf("Error\n");
          i--;
          continue;
      }    
  }

           
        // i)  Number of diamonds in the table according to the difficulty the user choosed
        //&
        // ii) Number of obstacles \\ - \\ - \\ -
        // iii)Differency of the table after the user move to the next level
           if(strcmp(easy,difficulty)==0)
           {
             diamonds = 3;
             obstacles = (M*N*1)/10;
             leveldif = 3;
           }

           else if(strcmp(medium,difficulty)==0)
           {
             diamonds = 6;
             obstacles = (M*N*15)/100;
             leveldif = 2;
           }

           else
           {
             diamonds = 9;
             obstacles = (M*N*2)/10;
             leveldif = 1;
           }


  //initializing two tables with '.' as we haven't dig to the ground yet  
  for(int i = 0;i<N;i++)
  {
     for(int j = 0;j<M;j++)
     {
       arr[i][j] = '.';
       arr2[i][j] = '.';
     } 

  }

        
        srand(time(NULL)); //In order to get different random positions after running the program
                           //more than once
                           //(rand()%(upper-lower+gap))+lower;
        //Dig Doug
           b = (rand()%(M-0))+0; //Column
           arr[0][b] = DigDoug;
           arr2[0][b] = DigDoug;                               


        //Adding diamonds randomly in the table                   
        for(int i = 0;i<obstacles;i++)
        {
            a = (rand()%(N-0))+0; //row
            b = (rand()%(M-0))+0; //column

            if(arr[a][b] != '.')
            {
              i--;
              continue;
            }

            else
            {
              arr[a][b] = '#';               
            }
        }

        for(int i = 0;i<diamonds;i++)
        {
            a = (rand()%(N-0))+0; //row
            b = (rand()%(M-0))+0; //column

            if(arr[a][b] != '.')
            {
              i--;
              continue;
            }

            else
            {
              value = (rand()%(N-0))+0;
              arr[a][b] = 48+value;               
            }
        }


       //**SOLUTION**
      //PRINTING THE TABLE
        //This is the solution of the game of how to find all the diamonds
            printf("   ");
            for(int i = 0;i<M;i++)
            {
              printf("%d ",(i+1));
            }
                printf("\n");
              for(int i = 0;i<M+2;i++)
              {
                printf("- ");
              } 
                printf("\n");  

              for(int i = 0;i<N;i++)
              {
                 printf("%d |",(i+1));
                for(int j = 0;j<M;j++)
                {
                  printf("%c ",arr[i][j]);
                }
              printf("\n"); 
              }  


 //Transfering data from dynamic array to static
//arr1
    for(int d = 0;d<N;d++)
    {
      for(int g = 0;g<M;g++)
      { 
        arrstatic[d][g] = arr[d][g];
      }
    }  
 //Transfering data from dynamic array to static
//arr2
    for(int d = 0;d<N;d++)
    {
       for(int g = 0;g<M;g++)
       { 
        arr2static[d][g] = arr2[d][g];
       }
    }  


 //**********           
//Creating a for loop to keep the Repitition among and after the completation of a Level            
for(int i = 0;i<1;i++)
{
   //UI 
  //Printing the actual Table
  printf("   ");
            for(int i = 0;i<M;i++)
            {
              printf("%d ",(i+1));
            }
                printf("\n");
              for(int i = 0;i<M+2;i++)
              {
                printf("- ");
              } 
                printf("\n");  

              for(int i = 0;i<N;i++)
              {
                 printf("%d |",(i+1));
                for(int j = 0;j<M;j++)
                {
                  printf("%c ",arr2[i][j]);
                }
              printf("\n"); 
              }  

    //Waiting from the User to make a move each round
    printf("Diamonds Collected: %d\nLevel diamond value: %d \nGame diamond value: %d \nExample: ""U1"" \nMake your move(s): ",diamondscnt,LDvalue,GDvalue);

 //4)
   //**Character by Character method**
   for(int j = 0;j<1;j++)
  {  
    fgets(order,sizeof(order),stdin);

    part1 = order[0]; //U/u/D/d/L/l/R/r

    int counter1 = (sizeof(order)/sizeof(char))-1; //size of order array without the U/D/L/R part
      
         for(int k = 0;k<counter1;k++)//transfering all the numbers to the left of the array
         {
           order[k] = order[k+1];
         }
      part2int = atoi(order); //Turning char to integer with the use of atoi
       

        //Checking which option user choosed
        if(terminate == part1 || caseterminate == part1)
        {
          printf("\nThe program has been terminated\n");
          exit(1);
        } 

        else if(Down == part1 || caseDown == part1)
        {
          //Movement
          down(arrstatic,arr2static,part2int,&LDvalue,&GDvalue,&diamondscnt); 

             //Transfering data from dynamic array to static
             for(int d = 0;d<N;d++)
            {
                for(int g = 0;g<M;g++)
              { 
                arr2[d][g] = arr2static[d][g];
              }
            }
           
        } 

        else if(Up == part1 || caseUp == part1)
        {
          //Movement
          up(arrstatic,arr2static,part2int,&LDvalue,&GDvalue,&diamondscnt); 

             //Transfering data from dynamic array to static
             for(int d = 0;d<N;d++)
            {
                for(int g = 0;g<M;g++)
              { 
                arr2[d][g] = arr2static[d][g];
              }
            }
        } 

         else if(Right == part1 || caseRight == part1)
        {
          //Movement
          right(arrstatic,arr2static,part2int,&LDvalue,&GDvalue,&diamondscnt); 

             //Transfering data from dynamic array to static
             for(int d = 0;d<N;d++)
            {
                for(int g = 0;g<M;g++)
              { 
                arr2[d][g] = arr2static[d][g];
              }
            }
        } 

         else if(Left == part1 || caseLeft == part1)
        {
          //Movement
          left(arrstatic,arr2static,part2int,&LDvalue,&GDvalue,&diamondscnt); 

             //Transfering data from dynamic array to static
             for(int d = 0;d<N;d++)
            {
                for(int g = 0;g<M;g++)
              { 
                arr2[d][g] = arr2static[d][g];
              }
            }
        } 

        else
        {
          printf("No order with such name found. Try again.");
          j--;
          continue;
        }
  }//End of for we use for the reputation for the orders user can use
  

  //**6)**
  //Checking if the User has collected all the Diamonds in the Table
  //If he has, then he will go to the next level
   if(diamondscnt == diamonds)
   {
     //Printing old Array for the last time before we go to the next level
     printf("   ");
            for(int i = 0;i<M;i++)
            {
              printf("%d ",(i+1));
            }
                printf("\n");
              for(int i = 0;i<M+2;i++)
              {
                printf("- ");
              } 
                printf("\n");  

              for(int i = 0;i<N;i++)
              {
                 printf("%d |",(i+1));
                for(int j = 0;j<M;j++)
                {
                  printf("%c ",arr2[i][j]);
                }
              printf("\n"); 
              }  

    //Waiting from the User to make a move each round
    printf("Diamonds Collected: %d\nLevel diamond value: %d \nGame diamond value: %d \nExample: ""U1"" \nMake your move(s): ",diamondscnt,LDvalue,GDvalue);
 
     printf("\nYou found all of the available Diamonds !\nYou are going to the next Level\n");
     
     //When the User passes the First level
     //Dimensions are being extented according to the difficulty the user choosed
      N = N + leveldif; //rows N+
      M = M + leveldif; //columns M+
     
      LDvalue = 0;      //Reseting Level Diamond value
      diamondscnt = 0;  //Reseting diamonds counter as we go to a brand new level

                        //New Number Obstacles of the Extended Table
      if(strcmp(easy,difficulty)==0)
      obstacles = (M*N*1)/10;
             
      else if(strcmp(medium,difficulty)==0)
      obstacles = (M*N*15)/100;
             
      else
      obstacles = (M*N*2)/10;
             
           
               
        //arr1
        arr = (char**)realloc(arr,leveldif*sizeof(char *));

        if(arr == NULL)
        {
         printf("An error during the allocation (1D)");
         exit(1); 
        }

     //Dynamic allocation of the 2D (columns)
        for(int s = 0;s<leveldif;s++)
        {
           arr[s] = (char*)realloc(arr,leveldif*sizeof(char));

             if(arr[s] == NULL)
             {
                printf("An error during the allocation (2D)");
                exit(1);  
             } 
        } 

    //arr2
      arr2 = (char**)realloc(arr2,leveldif*sizeof(char *));

        if(arr2 == NULL)
       {
        printf("An error during the allocation");
        exit(1); 
       }

     //Dynamic allocation of the 2D (columns)
        for(int s = 0;s<leveldif;s++)
        {
           arr2[s] = (char*)realloc(arr2,leveldif*sizeof(char));

             if(arr2[s] == NULL)
             {
                printf("An error during the allocation");
                exit(1);  
             }
 
        }      

        //Initializing arr and arr2 with new random Obstacles and going on
        //initializing two tables with '.' as we haven't dig to the ground yet  
       for(int i = 0;i<N;i++)
      {
         for(int j = 0;j<M;j++)
        {
         arr[i][j] = '.';
         arr2[i][j] = '.';
         } 

       }
     
        //srand(time(NULL)); //In order to get different random positions after running the program
                           //more than once
                           //(rand()%(upper-lower+gap))+lower;
        //Dig Doug
         int a,b;
           b = (rand()%(M-0))+0; //Column
           arr[0][b] = DigDoug;
           arr2[0][b] = DigDoug;                               


        //Adding diamonds randomly in the table 
                          
        for(int p = 0;p<obstacles;p++)
        {
            a = (rand()%(N-0))+0; //row
            b = (rand()%(M-0))+0; //column

            if(arr[a][b] != '.')
            {
              p--;
              continue;
            }

            else
            {
              arr[a][b] = '#';               
            }
        }

        for(int p = 0;p<diamonds;p++)
        {
            a = (rand()%(N-0))+0; //row
            b = (rand()%(M-0))+0; //column

            if(arr[a][b] != '.')
            {
              p--;
              continue;
            }

            else
            {
              value = (rand()%(N-0))+0;
              arr[a][b] = 48+value;               
            }
        }

      printf("I reached the end of if");
      
   } //End of if. We Created the **NEXT LEVEL**
  


  i--; //Refreshing the Table and Asking the user for a new move
  continue;

}//End of for we use for the General reputation


    return 0;
}



void right(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt)
{
  int i = 0;
  int j = 0;
  char diamondvalue[1];
  
   if(part2int == 0) //End of recursion
   {
     return;
   }
    
  //Finding the position of our Protagonist "$" in the table
   for(i = 0;i<N;i++)
  {
     for(j = 0;j<M;j++)
    {
       if(arr2[i][j] == '$')
       goto end;               
    }
  }
 end:   


   //Moving Dig Doug
   //Exceptions:
      
      if(j+1 < M )            //Making sure that the Dig Doug will not go out of bonds
    {
         if(arr[i][j+1] == '#')//In case we meet an obstacle
         {
           arr2[i][j+1] = arr[i][j+1];
           return;
         }

         else if(arr[i][j+1] == '.')
         {
            arr2[i][j] = ' ';
            arr2[i][j+1] = '$';
         }

         else if(arr[i][j+1] == ' ')
         {
            arr2[i][j] = ' ';
            arr2[i][j+1] = '$';
         }

         else if(arr[i][j+1] == '$')
         {
            arr2[i][j] = ' ';
            arr2[i][j+1] = '$';
         }
         else
         {
             printf("\narr = %c\n",arr[i][j+1]);
            *diamondscnt = *diamondscnt + 1;
            diamondvalue[0] = arr[i][j+1];
            arr[i][j+1] = ' '; //We claimed the diamonds so we deleted it from the table
           *LDvalue = *LDvalue + atoi(diamondvalue);
           *GDvalue = *GDvalue + atoi(diamondvalue);
            arr2[i][j] = ' ';
            arr2[i][j+1] = '$';  
         }
   
      }  

      else //If Dig Doug is about to go Out Of Bonds then we stop
      {
        printf("You are Out of Bonds !\n");
        return;
      }
   return right(arr,arr2,part2int-1,LDvalue,GDvalue,diamondscnt);
}

void left(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt)
{
  int i = 0;
  int j = 0;
  char diamondvalue[1];
  
   if(part2int == 0) //End of recursion
   {
     return;
   }


  //Finding the position of our Protagonist "$" in the table
   for(i = 0;i<N;i++)
  {
     for(j = 0;j<M;j++)
    {
       if(arr2[i][j] == '$')
       goto end;                     
    }
  }
end:
    
   //Moving Dig Doug
   //Exceptions:
      
      if(j-1 >=0 )            //Making sure that the Dig Doug will not go out of bonds
      {
         if(arr[i][j-1] == '#')//In case we meet an obstacle
         {
           arr2[i][j-1] = arr[i][j-1];
           return;
         }

         else if(arr[i][j-1] == '.')
         {
            arr2[i][j] = ' ';
            arr2[i][j-1] = '$';
         }

         else if(arr[i][j-1] == ' ')
         {
            arr2[i][j] = ' ';
            arr2[i][j-1] = '$';
         }

         else if(arr[i][j-1] == '$')
         {
            arr2[i][j] = ' ';
            arr2[i][j-1] = '$';
         }

         else
         {
             printf("\narr = %c\n",arr[i][j-1]);
            *diamondscnt = *diamondscnt + 1;
            diamondvalue[0] = arr[i][j-1];
            arr[i][j-1] = ' '; //We claimed the diamonds so we deleted it from the table
           *LDvalue = *LDvalue + atoi(diamondvalue);
           *GDvalue = *GDvalue + atoi(diamondvalue);
            arr2[i][j] = ' ';
            arr2[i][j-1] = '$';  
         }
   
      }  

      else //If Dig Doug is about to go Out Of Bonds then we stop
      {
        printf("You are Out of Bonds !\n");
        return;
      }
   return left(arr,arr2,part2int-1,LDvalue,GDvalue,diamondscnt);
}


void up(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt)
{
  int i = 0;
  int j = 0;
  char diamondvalue[1];
  
   if(part2int == 0) //End of recursion
   {
     return;
   }
    
  //Finding the position of our Protagonist "$" in the table
   for(i = 0;i<N;i++)
  {
     for(j = 0;j<M;j++)
    {
       if(arr2[i][j] == '$')
       goto end;             
    }
  }
 end:   
   //Moving Dig Doug
   //Exceptions:

      if(i-1 >=0 )            //Making sure that the Dig Doug will not go out of bonds
      {
         if(arr[i-1][j] == '#')//In case we meet an obstacle
         {
           arr2[i-1][j] = arr[i-1][j];
           return;
         }

         else if(arr[i-1][j] == '.')
         {
            arr2[i][j] = ' ';
            arr2[i-1][j] = '$';
         }

         else if(arr[i-1][j] == ' ')
         {
           arr2[i][j] = ' ';
           arr2[i-1][j] = '$';
         }

         else if(arr[i-1][j] == '$')
         {
           arr2[i][j] = ' ';
           arr2[i-1][j] = '$';
         }

         else
         {
             printf("\narr = %c\n",arr[i-1][j]);
            *diamondscnt = *diamondscnt + 1;
            diamondvalue[0] = arr[i-1][j];
            arr[i-1][j] = ' '; //We claimed the diamonds so we deleted it from the table
           *LDvalue = *LDvalue + atoi(diamondvalue);
           *GDvalue = *GDvalue + atoi(diamondvalue);
            arr2[i][j] = ' ';
            arr2[i-1][j] = '$';  
         }
   
      }  

      else //If Dig Doug is about to go Out Of Bonds then we stop
      {
        printf("You are Out of Bonds !\n");
        return;
      }
   return up(arr,arr2,part2int-1,LDvalue,GDvalue,diamondscnt);
}

void down(char arr[N][M],char arr2[N][M],int part2int,int* LDvalue,int* GDvalue,int* diamondscnt)
{
  int i = 0;
  int j = 0;
  char diamondvalue[1];
  
   if(part2int == 0) //End of recursion
   {
     return;
   }
    
  //Finding the position of our Protagonist "$" in the table
   for(i = 0;i<N;i++)
  {
     for(j = 0;j<M;j++)
    {
       if(arr2[i][j] == '$')
       goto end;           
    }  
  }
  end:
    
   //Moving Dig Doug
   //Exceptions:

      if(i+1 < N)            //Making sure that the Dig Doug will not go out of bonds
      {
         if(arr[i+1][j] == '#')//In case we meet an obstacle
         {
           arr2[i+1][j] = arr[i+1][j];
           return;
         }

         else if(arr[i+1][j] == '.')
         {
            arr2[i][j] = ' ';
            arr2[i+1][j] = '$';
         }

         else if(arr[i+1][j] == ' ')
         {
            arr2[i][j] = ' ';
            arr2[i+1][j] = '$';
         }

         else if(arr[i+1][j] == '$')
         {
            arr2[i][j] = ' ';
            arr2[i+1][j] = '$';
         }

         else
         {
             printf("\narr = %c\n",arr[i+1][j]);
            *diamondscnt = *diamondscnt + 1;
            diamondvalue[0] = arr[i+1][j];
            arr[i+1][j] = ' '; //We claimed the diamonds so we deleted it from the table
           *LDvalue = *LDvalue + atoi(diamondvalue);
           *GDvalue = *GDvalue + atoi(diamondvalue);
            arr2[i][j] = ' ';
            arr2[i+1][j] = '$';  
         }
   
      }  

      else //If Dig Doug is about to go Out Of Bonds then we stop
      {
        printf("You are Out of Bonds !\n");
        return;
      }
   return down(arr,arr2,part2int-1,LDvalue,GDvalue,diamondscnt);
   
}
