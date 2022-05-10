#include <stdio.h>
#include <string.h>
#include "mpi.h"
int size=100;
int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int coresNum;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	char message[100];	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/



	/* Start up MPI */
	MPI_Init( &argc , &argv );



	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &coresNum);



	if( my_rank == 0)
	{

	    FILE* fileptr;
		int numOfStudents=0;
        char filearray[size][size];

		fileptr = fopen("/shared/ss.txt", "r");
		if (NULL == fileptr) {
        printf("can't be found!! \n");
        }

         while(fgets(filearray[numOfStudents], 100, fileptr))
  {
     numOfStudents++;
    }
    fclose(fileptr);

		int numPerProcess=(int) numOfStudents/(coresNum-1);
int remain = numOfStudents%(coresNum-1);
      printf(" There exist  Students %d\n ", remain);
 //printf(" There exist  Students %d\n ", numPerProcess);
        int process=1;
		for(;process<coresNum;process++){
            //if (process==coresNum-1 && remain !=0){numPerProcess=numPerProcess+remain;}
            MPI_Send( &numPerProcess, 1, MPI_INT, process, tag, MPI_COMM_WORLD);
		}
 int myStudents[numOfStudents][2];
 int grade=0;
 int i;

 char  temp[100];
char  temp2[100];

  for( i = 0 ; i<numOfStudents ; i++ )
  {


  char *split = strtok(filearray[i], " ");
    if(split)
    {
         strcpy(temp,split);
       sscanf(temp, "%d", & myStudents[i][0]);

        }
    split = strtok(NULL, " ");

    if(split){
        strcpy(temp2,split);
       sscanf(temp2, "%d", &myStudents[i][1]);

    }


  }

int proessData;
int j;
int Pass;
int All=0;
int t=0;



      for (j = 1; j< coresNum; j++)
      {
      for(proessData= 0 ; proessData < numPerProcess ; proessData++)
      {
        MPI_Send(&myStudents[proessData+t][0],1,MPI_INT, j, 0,MPI_COMM_WORLD);
        MPI_Send(&myStudents[proessData+t][1],1,MPI_INT, j, 0,MPI_COMM_WORLD);

      }
    if (j==coresNum-1 && remain !=0){numPerProcess=numPerProcess+remain;}
      t+=numPerProcess;
      MPI_Recv(&Pass, 1, MPI_INT, j, tag, MPI_COMM_WORLD, &status );
      All+=Pass;

            }

      printf(" total number of passed students is %d  out of %d \n",All,numOfStudents);



	}else
	{
    int numPerProcess=0;
    int Pass=0;
	MPI_Recv(&numPerProcess, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
		 int i ;
		 int grade;
         int id;
 printf(" There exist  Students %d\n ", numPerProcess);

    for (i =0 ; i<numPerProcess;i++)
    {
    // if (i==coresNum-1 && remain !=0){numPerProcess=numPerProcess+remain;}
    MPI_Recv(&id, 1,MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
    MPI_Recv(&grade, 1,MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
    if(grade>=60)
    {
      printf("%d Passed The Exam \n", id);
      Pass++;
    }
   else printf("%d Failed. Please Repeat The Exam \n",id);




    }
MPI_Send(&Pass,1, MPI_INT, 0, 0,MPI_COMM_WORLD);

    }



	/* shutdown MPI */
	MPI_Finalize();
	return 0;

}
