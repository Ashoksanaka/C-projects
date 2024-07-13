#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h> //import time header file to compute random value for computer
//function to return result
int
game (char you, char computer)
{
  if (you == computer)
	{
	  return 0; //return 0 for DRAW
	}
  else if ((you == 'r' && computer == 's') || (you == 'p' && computer == 'r')
		   || (you == 's' && computer == 'p'))
	{
	  return 1; //return 1 if USER won
	}
  else
	{
	  return -1; //return -1 if COMPUTER won
	}
}

int
main ()
{
  int n, result;
  char you, computer;
  srand (time (NULL)); //generate a random number 
  n = rand () % 100; //make the random number less than 100
  if (n < 33)
	{
	  computer = 'r';
	}
  else if (n < 66 && n > 33)
	{
	  computer = 'p';
	}
  else
	{
	  computer = 's';
	}
  printf ("\n\n\t\tEnter your choice (r-rock/p-paper/s-scissor): ");
  scanf (" %c", &you); //input from the user
  result = game (you, computer);
  if (result == 0)
	{
	  printf ("\n\n\t\tDRAW!\nYou choose:%c \n Computer choose:%c\n\n\t\t",
			  you, computer);
	}
  else if (result == 1)
	{
	  printf
		("\n\n\t\t\tYAY! YOU WIN\n\t\t\tYou choose:%c\n\t\t\tcomputer choose:%c\n\n\n\t\t",
		 you, computer);
	}
  else
	{
	  printf
		("\n\n\t\t\tCOMPUTER WIN\n\t\t\tYou choose:%c\n\t\t\tComputer choose:%c\n\n\nt\t",
		 you, computer);
	}
  return 0;
}
