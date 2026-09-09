/*

                          PROBLEM
                          =======


There are five bastions in Cape Town Castle.

Catzenellenbogen, Buren, Leerdam, Oranje, and Nassau.

On the first week of January 18--, starting on a Sunday, fifteen privates of B. Company,
East Lancashire regiment were stationed as guards, three to each bastion.
During the week no two privates were posted together twice.
(If Edwards and Harris were together on Monday they were not together at any bastion during the rest of the week.)

 - Anderson was at the same bastion every day of the week.
 - Price was at Buren every weekday and Ingles was at Leerdam six times.
 - Ford was at Oranje the first four days of the week and Carter was at Nassau four times but not on Tuesday.
 - Ross was never posted to Oranje.
 - On Sunday Ross, Green and Dawson were at Leerdam and Edwards was at Oranje.
 - On Monday Ingles, Wilson and Ross were together and so also were Thompson, Edwards and Harris.
 - On Friday Ford and Morris were together in one section (and so also were Dawson and Harris).
 - On Saturday Thompson was at Nassau.
 - Thompson and Carter were together at Buren and so also were Harris and Ross.
 - Jones was not at Buren on Monday.

(Saturday is included as a weekday)

Where was Smith posted each day and with whom?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE   1
#define FALSE -1

#define UNASSIGNED -1

#define ANDERSON  0
#define CARTER    1
#define DAWSON    2
#define EDWARDS   3
#define FORD      4
#define GREEN     5
#define HARRIS    6
#define INGLES    7
#define JONES     8
#define MORRIS    9
#define PRICE    10
#define ROSS     11
#define SMITH    12
#define THOMPSON 13
#define WILSON   14

#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

#define CATZENELLENBOGEN   0
#define BUREN              1
#define LEERDAM            2
#define ORANJE             3
#define NASSAU             4

typedef enum guards {Anderson, Carter, Dawson, Edwards, Ford, Green, Harris,
                     Ingles, Jones, Morris, Price, Ross, Smith, Thompson, Wilson} guards;

typedef enum days {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday} days;

typedef enum bastions {Catzenellenbogen, Buren, Leerdam, Oranje, Nassau} bastions;

char const* guardlist[] =   {"Anderson  ", "Carter    ", "Dawson    ", "Edwards   ", "Ford      ",
                             "Green     ", "Harris    ", "Ingles    ", "Jones     ", "Morris    ",
                             "Price     ", "Ross      ", "Smith     ", "Thompson  ", "Wilson    "};

char const* daylist[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char const* bastionlist[] = {"Catzen", "Buren", "Leerdam", "Oranje", "Nassau"};

// Function Protoptypes

int sort_function (const void *a, const void *b);
int sort_int (const void *a, const void *b);

// Class Definitions

class Postings
{
private:
   int postingarray[7][5][3];									// 7 days, 5 bastions, 3 guards per bastion.
   int fixedarray[7][5][3];                           // This determines which slots are fixed and which not. (For example, no point in changing the guards we *know* are fixed.
   int doublearray[15][15];                           // Who is posted with whom how many times.
   int totalerror;

   int addGuardOnDayAndBastion(int, int, int, int);        // Guards are allocated in a set of three.

public:
    Postings();																// Public constructor function

    // *** Evaluation Rulebase.
    int  EvalRule01_AndersonWasAtSameBastionEveryWeekday();					// Rule  1
    int  PriceWasAtBurenEveryWeekday();								// Rule  2
    int  InglesWasAtLeerdamSixTimes();								// Rule  3
    int  FordWasAtOranjeFirstFourDaysOfWeek();					    // Rule  4
    int  CarterAtNassauFourTimesNotTuesday();						// Rule  5
    int  RossNeverPostedToOranje();									// Rule  6
    int  SundayRossGreenDawsonLeerdam();							// Rule  7
    int  SundayEdwardsOranje();										// Rule  8
    int  MondayInglesWilsonRossTogether();							// Rule  9
    int  MondayThompsonEdwardsHarrisTogether();					    // Rule 10
    int  FridayFordMorrisTogether();								// Rule 11
    int  FridayDawsonHarrisTogether();								// Rule 12
    int  SaturdayThompsonNassau();									// Rule 13
    int  ThompsonAndCarterTogetherAtBuren();						// Rule 14
    int  HarrisAndRossTogetherAtBuren();							// Rule 15
    int  JonesNotAtBurenOnMonday();									// Rule 16

    // *** Setter Rulebase
    void SetRule01_AndersonWasAtSameBastionEveryWeekday();				    // Rule  1
    void SetPriceWasAtBurenEveryWeekday();							// Rule  2
    void SetInglesWasAtLeerdamSixTimes();							// Rule  3
    void SetFordWasAtOranjeFirstFourDaysOfWeek();				    // Rule  4
    void SetCarterAtNassauFourTimesNotTuesday();					// Rule  5
    void SetSundayRossGreenDawsonLeerdam();					    	// Rule  7
    void SetSundayEdwardsOranje();									// Rule  8
    void SetMondayInglesWilsonRossTogether();						// Rule  9
    void SetMondayThompsonEdwardsHarrisTogether();			    	// Rule 10
    void SetSaturdayThompsonNassau();								// Rule 13

    // *** End of Rulebase.

    int  DerivedRule01();

    int  Experiment(); // Experimenting with Genetic Edge Recombination

    /*
    1) Anderson was at the same bastion every day of the week.
    2) Price was at Buren every weekday.
    3) Ingles was at Leerdam six times.
    4) Ford was at Oranje the first four days of the week.
    5) Carter was at Nassau four times but not on Tuesday.
    6) Ross was never posted to Oranje.
    7) On Sunday Ross, Green and Dawson were at Leerdam.
    8) On Sunday Edwards was at Oranje.
    9) On Monday Ingles, Wilson and Ross were together.
    10) On Monday Thompson, Edwards and Harris were together.
    11) On Friday Ford and Morris were together in one section.
    12) On Friday Dawson and Harris were together in one section.
    13) On Saturday Thompson was at Nassau.
    14) Thompson and Carter were together at Buren.
    15) Harris and Ross were together at Buren.
    16) Jones was not at Buren on Monday.
    */

    void EvaluateFitness(const int);
    void Initialize();
    void Print();                               // Prints the entire solution.
    void PrintFixed();
    void RandomlyAssignRemainingGuards();
    void SortRemainingGuards();
    void EvaluateDoubles();
    void PrintDoubles();
    int  EvaluatePostingError();
    int  GetTotalError();
    int* GetArrayStart();
    void Reset();
    void SetArray(int*);
    void CrossoverByDay(Postings, Postings);
    void CrossoverByUnFixed(Postings, Postings);
    void Mutate();
    void RandomSearch();
};

// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

int globalFixed[105];

//==============================================================================
//
// Start of program.
//
//==============================================================================

int main(int argc, char **argv)
{
	#define SAMPLE_SIZE 3500  	  	// Was 40000 at last edit. 23/9/2007
	#define MUTATION_RATE 5			     // Expressed as a percentage. Was 25 at last edit. 23/9/2007/ Was 15 as at 24 April 2020
	#define TOTAL_ITERATIONS 5 // 1000
	#define FITNESS_FACTOR 15 			// Was 50 before Dec 2009. Now 200. Now 5 [NJW] Oct 2015
  #define PRINT_EVERY 50
  #define CROSSOVER_BY_DAY 1
  #define CROSSOVER_BY_UNFIXED 2
  #define CROSSOVER_METHOD CROSSOVER_BY_DAY

   Postings myposting[SAMPLE_SIZE];
	//Postings tempposting[SAMPLE_SIZE];
   time_t seed;
   char str[5];

     int deletethis=0;
     deletethis = sizeof(globalFixed);

   // Clear Global Variables

   memset(globalFixed, 0, sizeof(globalFixed));

	/*
	myposting = (Postings*)malloc(sizeof(Postings) * SAMPLE_SIZE);
	if (myposting == NULL)
	{
		printf("Unable to allocate posting memory.\n");
		exit(0);
	}
	else
	{
		printf("Memory allocation: malloc %p\n", myposting);
	}
	*/

	printf("Size of sample %lu.\n", sizeof(myposting));
	printf("Size of class  %lu.\n", sizeof(myposting[0]));
	printf("Size of integer %lu.\n", sizeof(int));

	// Set the random seed
   srand((unsigned int)time(&seed));

	// Create an initial population of SAMPLE_SIZE
   for (register int xx = 0; xx < SAMPLE_SIZE; xx++)
   {
      myposting[xx].Initialize();
      myposting[xx].EvaluateFitness(FITNESS_FACTOR);
   }

   // #IFDEF DEBUG getchar();

   // Sort the sample
   printf("Sorting ... ");
   qsort((void*)(myposting), SAMPLE_SIZE, sizeof(myposting[0]), sort_function);
   printf("sorted.\n\n");

   // Main loop of iterations
   printf("\nIteration\tTotal Error[0]\tAverage\n");

   for (unsigned long yy = 0; yy <= TOTAL_ITERATIONS; yy++)
   {
	    if ((yy % PRINT_EVERY) == 0)		// Print every PRINT_EVERY
		  {
			     int average = 0;
			     for (int zzz = 0; zzz < SAMPLE_SIZE; zzz++)
				   average += myposting[zzz].GetTotalError();
			    printf("%lu\t\t%i\t\t%i\n", yy, myposting[0].GetTotalError(), average / SAMPLE_SIZE);
      }

		// Run through the entire population and decide if we are going to mutate.

      for (int mutation = 1; mutation < SAMPLE_SIZE; mutation++)  // Exclude the top ranked. (Used to be 10 before Apr 2020)
      {
      	if ( ((rand() % 100) + 1) <= MUTATION_RATE)
            myposting[mutation].Mutate();
      }

      // Sort the sample

      qsort( (void*)(myposting), SAMPLE_SIZE, sizeof(myposting[0]), sort_function);

		// STOCHASTIC UNIVERSAL SAMPLING
		// Described as an algorithm, pseudocode for SUS looks like:
		//
		//	SUS(Population, N)
		//		F := total fitness of Population
		//		N := number of offspring to keep
		//		P := distance between the pointers (F/N)
		//		Start := random number between 0 and P
		//		Pointers := [Start + i*P | i in [0..(N-1)]]
		//		return RWS(Population,Pointers)
		//
		//	RWS(Population, Points)
		//		Keep = []
		//		i := 0
		//		for P in Points
		//			while fitness sum of Population[0..i] < P
		//				i++
		//			add Population[i] to Keep
		// 	return Keep
		//
		//	Where Population[0..i] is the set of individuals with array-index 0 to (and including) i.
		//
		// Here RWS() describes the bulk of fitness proportionate selection (also known as "roulette wheel selection") - in true
		// fitness proportional selection the parameter Points is always a (sorted) list of random numbers from 0 to F.
		// The algorithm above is intended to be illustrative rather than canonical.



		// Perform the crossover
      for (int breeding = SAMPLE_SIZE - 1; breeding >= 10; breeding--)
      {
			int rand01 = 0;
			int rand02 = 0;

			rand01 = rand() % SAMPLE_SIZE;
			rand02 = rand() % SAMPLE_SIZE;

        switch (CROSSOVER_METHOD)
        {
          case CROSSOVER_BY_DAY:
        	    myposting[breeding].CrossoverByDay(myposting[rand01], myposting[rand02]);
              break;
          case CROSSOVER_BY_UNFIXED:
        	    myposting[breeding].CrossoverByUnFixed(myposting[rand01], myposting[rand02]);
              break;
        }

      }

      if (myposting[0].GetTotalError() == 0)
      {
      	yy = 99999999;
      }

	}

	// Resort the sample
   qsort( (void*)(myposting), SAMPLE_SIZE, sizeof(myposting[0]), sort_function);

    //myposting[0].Print();
    printf("\nFXIED 01 ====================================================\n\n\n");
    myposting[0].PrintFixed();
    printf("\nFIXED 02=====================================================\n\n\n");
    myposting[SAMPLE_SIZE - 1].PrintFixed();
    myposting[0].PrintDoubles();
    printf("\nTotal Error : %i.\n",  myposting[0].GetTotalError());
    printf("\n");
    printf("Total Posting Error :                  %i.\n", myposting[0].EvaluatePostingError());
    printf("\n");
    printf("EvalRule01_AndersonWasAtSameBastionEveryWeekday : %i.\n", myposting[0].EvalRule01_AndersonWasAtSameBastionEveryWeekday());	// R01
    printf("PriceWasAtBurenEveryWeekday :          %i.\n", myposting[0].PriceWasAtBurenEveryWeekday());				   // R02
    printf("InglesWasAtLeerdamSixTimes :           %i.\n", myposting[0].InglesWasAtLeerdamSixTimes());					 // R03
    printf("FordWasAtOranjeFirstFourDaysOfWeek :   %i.\n", myposting[0].FordWasAtOranjeFirstFourDaysOfWeek());	 // R04
    printf("CarterAtNassauFourTimesNotTuesday :    %i.\n", myposting[0].CarterAtNassauFourTimesNotTuesday());		 // R05
    printf("RossNeverPostedToOranje :              %i.\n", myposting[0].RossNeverPostedToOranje());						   // R06
    printf("SundayRossGreenDawsonLeerdam :         %i.\n", myposting[0].SundayRossGreenDawsonLeerdam());				 // R07
    printf("SundayEdwardsOranje :                  %i.\n", myposting[0].SundayEdwardsOranje());							     // R08
    printf("MondayInglesWilsonRossTogether :       %i.\n", myposting[0].MondayInglesWilsonRossTogether());			 // R09
    printf("MondayThompsonEdwardsHarrisTogether :  %i.\n", myposting[0].MondayThompsonEdwardsHarrisTogether());  // R10
    printf("FridayFordMorrisTogether :             %i.\n", myposting[0].FridayFordMorrisTogether());					   // R11
    printf("FridayDawsonHarrisTogether :           %i.\n", myposting[0].FridayDawsonHarrisTogether());					 // R12
    printf("SaturdayThompsonNassau :               %i.\n", myposting[0].SaturdayThompsonNassau());						   // R13
    printf("ThompsonAndCarterTogetherAtBuren :     %i.\n", myposting[0].ThompsonAndCarterTogetherAtBuren());		 // R14
    printf("HarrisAndRossTogetherAtBuren :         %i.\n", myposting[0].HarrisAndRossTogetherAtBuren());				 // R15
    printf("JonesNotAtBurenOnMonday :              %i.\n", myposting[0].JonesNotAtBurenOnMonday());						   // R16

    printf("\n=============================================================\n\n\n");

    return 0; // Added on 23/9/2007

	// Based on the above, this code below WILL NOT RUN!
	// myposting[0].Experiment();
   // Turned off 2020

	// Work on the top chromosome in a random way to get the remaining slots.
	// myposting[0].RandomSearch();
   // Turned off 2020

   getchar();

/*   myposting[1].Print();
   myposting[1].PrintDoubles();
   printf("\nTotal Error : %i.\n",  myposting[1].GetTotalError());
   gets(str);*/

	free(myposting);

}


//==============================================================================

int Postings::Experiment()
{
	int temp_postingarray[7][5][3];

	int lineararray[105];

	memcpy(lineararray, postingarray, sizeof(temp_postingarray));

	printf("Array: ");
	for (register int xx=0; xx <= 104; xx++)
	{
		printf("%i\t", lineararray[xx]);
		if (!((xx+1) % 3)) printf("\n");
		if (!((xx+1) % 15)) printf("\n");
	}
	printf("\n");
	return(0);
}


//==============================================================================

void Postings::RandomSearch(void)
{
	int PostingError;

		if ( (EvalRule01_AndersonWasAtSameBastionEveryWeekday() > 0)		||			// Rule 1
			  (PriceWasAtBurenEveryWeekday() > 0)					||			// Rule 2
			  (InglesWasAtLeerdamSixTimes() > 0)					||			// Rule 3
			  (FordWasAtOranjeFirstFourDaysOfWeek() > 0)			||			// Rule 4
			  (CarterAtNassauFourTimesNotTuesday() > 0)			||			// Rule 5
			  (RossNeverPostedToOranje() > 0)						||			// Rule 6
			  (SundayEdwardsOranje() > 0)								||			// Rule 7
			  (SundayRossGreenDawsonLeerdam() > 0)					||			// Rule 8
			  (MondayThompsonEdwardsHarrisTogether() > 0)		||			// Rule 9
			  (MondayInglesWilsonRossTogether() > 0)				||			// Rule 10
			  (FridayFordMorrisTogether() > 0)						||			// Rule 11
			  (FridayDawsonHarrisTogether() > 0)					||			// Rule 12
			  (SaturdayThompsonNassau() > 0)							||			// Rule 13
			  (ThompsonAndCarterTogetherAtBuren() > 0)			||			// Rule 14
			  (HarrisAndRossTogetherAtBuren() > 0)					||			// Rule 15
			  (JonesNotAtBurenOnMonday() > 0))									// Rule 16
		{
			printf("Very MAJOR error in function RandomSearch()");
			exit(0);
		}

	while (EvaluatePostingError() > 0)
	{
		PostingError = EvaluatePostingError();
		// We are going to swap a single bit (guard) around on a certain day
		int bastion1 = 0, section1 = 0;
		int bastion2 = 0, section2 = 0;
		int day;
		int guard1, guard2;
		int counter = 0;

	RESTARTRANDOMSEARCH:

		bastion1 = 0;
		section1 = 0;
		bastion2 = 0;
		section2 = 0;
		day = rand() % 7;

		while ((bastion1 == bastion2))
		{
			bastion1 = rand() % 5;
			bastion2 = rand() % 5;
		}

		while ((section1 == section2))
		{
			section1 = rand() % 3;
			section2 = rand() % 3;
		}

		guard1 = postingarray[day][bastion1][section1];
		guard2 = postingarray[day][bastion2][section2];

		// Swap

		postingarray[day][bastion1][section1] = guard2;
		postingarray[day][bastion2][section2] = guard1;

		// If there is a fundamental rules error then we have to undo and restart
		// The crossover is on a day level, so that if we rules that are dependent
		// on the number of days that a guard was a bastion, for example, then
		// we cannot necessarily assume that it was even correct coming in, since the
		//	crossover will have destroyed it.

		if ( (EvalRule01_AndersonWasAtSameBastionEveryWeekday() > 0)		||			// Rule 1
			  (PriceWasAtBurenEveryWeekday() > 0)					||			// Rule 2
			  (InglesWasAtLeerdamSixTimes() > 0)					||			// Rule 3
			  (FordWasAtOranjeFirstFourDaysOfWeek() > 0)			||			// Rule 4
			  (CarterAtNassauFourTimesNotTuesday() > 0)			||			// Rule 5
			  (RossNeverPostedToOranje() > 0)						||			// Rule 6
			  (SundayEdwardsOranje() > 0)								||			// Rule 7
			  (SundayRossGreenDawsonLeerdam() > 0)					||			// Rule 8
			  (MondayThompsonEdwardsHarrisTogether() > 0)		||			// Rule 9
			  (MondayInglesWilsonRossTogether() > 0)				||			// Rule 10
			  (FridayFordMorrisTogether() > 0)						||			// Rule 11
			  (FridayDawsonHarrisTogether() > 0)					||			// Rule 12
			  (SaturdayThompsonNassau() > 0)							||			// Rule 13
			  (ThompsonAndCarterTogetherAtBuren() > 0)			||			// Rule 14
			  (HarrisAndRossTogetherAtBuren() > 0)					||			// Rule 15
			  (JonesNotAtBurenOnMonday() > 0))									// Rule 16
		{
			// Undo the initial work
			postingarray[day][bastion1][section1] = guard1;
			postingarray[day][bastion2][section2] = guard2;

			counter++;
			if (counter == 100)
			{
				Print();
				printf("Overflow Retry Error in RandomSearch()\n");
				exit(0);
			}

			goto RESTARTRANDOMSEARCH;
		}

		//printf("Swapped for Day: %s: Guard %s @ %s with Guard %s @ %s.\n",
		//		daylist[day], trim(guardlist[guard1]), bastionlist[bastion1],
		//						  guardlist[guard2], bastionlist[bastion2]);


		counter = 0;
		EvaluateDoubles();
		//printf("Posting Error %i, %i\n", EvaluatePostingError(), PostingError);
		if	(EvaluatePostingError() >= PostingError)
		{
			// Swap back
			postingarray[day][bastion1][section1] = guard1;
			postingarray[day][bastion2][section2] = guard2;
			goto RESTARTRANDOMSEARCH;
		}
		else
			PostingError = EvaluatePostingError();

		printf("Posting Error : %i.\n", PostingError);
		EvaluateFitness(FITNESS_FACTOR);
		SortRemainingGuards();
		GetTotalError();
		Print();
		printf("\n");
	}
	Print();
	PrintDoubles();
}


//==============================================================================

int sort_int (const void *a, const void *b)
{
	return ( *(int*)a - *(int*)b );
};

//==============================================================================

int sort_function (const void *a, const void *b)
{

   if ( ( ((Postings *)a) -> GetTotalError() )  <  ( ((Postings *)b) -> GetTotalError() ) )
      return -1;
   else
      if ( ( ((Postings *)a) -> GetTotalError() )  ==  ( ((Postings *)b) -> GetTotalError() ) )
         return 0;
      else
         return 1;
}

//==============================================================================

int Postings::addGuardOnDayAndBastion(int day, int bastion, int guard, int fixed)
{
   int returncode;

   if (postingarray[day][bastion][0] != UNASSIGNED)
   {
      if (postingarray[day][bastion][1] != UNASSIGNED)
      {
         if (postingarray[day][bastion][2] != UNASSIGNED)
         {
            returncode = FALSE;
         }
         else
         {
            postingarray[day][bastion][2] = guard;
            fixedarray[day][bastion][2]   = fixed;
            returncode = TRUE;
         }
      }
      else
      {
         postingarray[day][bastion][1] = guard;
         fixedarray[day][bastion][1]   = fixed;
         returncode = TRUE;
      }
   }
   else
   {
      postingarray[day][bastion][0] = guard;
      fixedarray[day][bastion][0]   = fixed;
      returncode = TRUE;
   }

   // Check that we have not assigned the same guard to each of the slots.
   // At a minimum, postingarray[day][bastion][0] should be populated.

   if (returncode)	// We have assigned somebody at this stage
   {
   	if ( (postingarray[day][bastion][0] == postingarray[day][bastion][1]) ||
   	     (postingarray[day][bastion][0] == postingarray[day][bastion][2]) )
   		returncode = FALSE;

   	if (postingarray[day][bastion][1] != UNASSIGNED)
   	{
	   	if ( postingarray[day][bastion][1] == postingarray[day][bastion][2] )
   			returncode = FALSE;
   	}
	}

   return returncode;
};

//==============================================================================

void Postings::EvaluateFitness(const int factor)
{
	totalerror = 0;
   // Work out who was posted with whom how many times [15][15].
	EvaluateDoubles();
   // Determine the posting error associated with the above posting matrix.
   totalerror += (EvaluatePostingError() * 3); // WAS * 2 Changed on 27/04/05 // WAS * 3 Changed December 2009

   totalerror += (factor * EvalRule01_AndersonWasAtSameBastionEveryWeekday());		//R1
	totalerror += (factor * PriceWasAtBurenEveryWeekday());					//R2
	totalerror += (factor * InglesWasAtLeerdamSixTimes());					//R3
	totalerror += (factor * FordWasAtOranjeFirstFourDaysOfWeek());			//R4
	totalerror += (factor * CarterAtNassauFourTimesNotTuesday());			//R5
	totalerror += (factor * RossNeverPostedToOranje());						//R6
	totalerror += (factor * SundayRossGreenDawsonLeerdam());					//R7
	totalerror += (factor * MondayInglesWilsonRossTogether());				//R9
	totalerror += (factor * MondayThompsonEdwardsHarrisTogether());		//R10
	totalerror += (factor * FridayFordMorrisTogether());						//R11
   totalerror += (factor * FridayDawsonHarrisTogether());					//R12
	totalerror += (factor * SaturdayThompsonNassau());							//R13
	totalerror += (factor * ThompsonAndCarterTogetherAtBuren());			//R14
	totalerror += (factor * HarrisAndRossTogetherAtBuren());					//R15
	totalerror += (factor * JonesNotAtBurenOnMonday());						//R16

}


//==============================================================================

void Postings::Initialize(void)
{
	// Complete knowns
   SetRule01_AndersonWasAtSameBastionEveryWeekday();	// R01  Although this seems unknown, please read the method comments
   SetPriceWasAtBurenEveryWeekday();				// R02
   SetFordWasAtOranjeFirstFourDaysOfWeek();		// R04
   SetSundayRossGreenDawsonLeerdam();				// R07
   SetSundayEdwardsOranje();							// R08
   SetMondayInglesWilsonRossTogether();			// R09  Although this seems unknown, please read the method comments
   SetMondayThompsonEdwardsHarrisTogether();		// R10 Although this seems unknown, please read the method comments
   SetSaturdayThompsonNassau();						// R13

	// Relative unknowns, but have to get slots for the bastions
	// SetFridayFordMorrisTogetherOneSection();
	// SetFridayDawsonHarrisTogetherOneSection();

	// Set the rest.
   SetInglesWasAtLeerdamSixTimes();					// R03
   SetCarterAtNassauFourTimesNotTuesday();		// R05


	// Assign the rest of the guards
	RandomlyAssignRemainingGuards();
	SortRemainingGuards();

   EvaluateFitness(FITNESS_FACTOR);
}

//==============================================================================

void Postings::Print(void)
{
   int guard, bastion, day;

   for (day = SUNDAY; day <= SATURDAY; day++)
   {
      printf("Day : %s\n", daylist[day]);
      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
      {
         printf("%s\t:   ", bastionlist[bastion]);
         for (guard = 0; guard <= 2; guard++)
         {
            if (postingarray[day][bastion][guard] == -1)
               printf("Unassigned");
            else
               printf("%s", guardlist[postingarray[day][bastion][guard]]);
            if (guard < 2) printf("   ");
         }
         printf("\n");
      }
      printf("\n");
   }
};

//==============================================================================

void Postings::PrintFixed(void)
{
   int guard, bastion, day;

   for (day = SUNDAY; day <= SATURDAY; day++)
   {
      printf("Day : %s\n", daylist[day]);
      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
      {
         printf("%s\t:   ", bastionlist[bastion]);
         for (guard = 0; guard <= 2; guard++)
         {
            if (fixedarray[day][bastion][guard] == TRUE)
               printf("FIXED     ");
            else
               printf("%s", guardlist[postingarray[day][bastion][guard]]);
            if (guard < 2)
                printf("   ");
         }
         printf("\n");
      }
      printf("\n");
   }
};

//==============================================================================

Postings::Postings()
{
	Reset();
};

//==============================================================================

void Postings::RandomlyAssignRemainingGuards(void)
{
   int guard, bastion, day;
   int placeholder, counter;

	// Anderson and Price must have been together on Sunday (R1, R2)
	// Anderson could not have been at Leerdam (R7)
	// This must include Ingles since he was at Leerdam for the remainder (see R8 derived),
	// and Anderson and Ingles need to be together.
	// It could not have been Oranje since Edwards was posted there (R8)
	// This leaves Buren, Catz or Nassau
	// This becomes Derived Rule 1

	bastion = rand() % 3;   // Random number from 0 to 2
	//bastion = 0; // NB!!!!!! This line MUST be deleted. It was put here to test. Uncomment the line above!!!!!!! (29 Dec 09) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
	if (bastion == 0)
		bastion = BUREN;
	else
		if (bastion == 1)
			bastion = CATZENELLENBOGEN;
		else
			bastion = NASSAU;

	addGuardOnDayAndBastion(SUNDAY, bastion, ANDERSON, FALSE);
	addGuardOnDayAndBastion(SUNDAY, bastion, INGLES, FALSE);
	addGuardOnDayAndBastion(SUNDAY, bastion, PRICE, FALSE);

	// Random from 0 - 99 ==> rand() % 100
   for (day = SUNDAY; day <= SATURDAY; day++)
   {
      // Establish who is already assigned.

      int alreadyallocated[15] = {UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED,
                                  UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED,
                                  UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED, UNASSIGNED};

      counter = 0;

      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
         for (guard = 0; guard <= 2; guard++)
            if (postingarray[day][bastion][guard] != UNASSIGNED)
            {
               alreadyallocated[postingarray[day][bastion][guard]] = 1;
               counter++;
            }

     // Now allocate the remainder.
      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
      {
         for (guard = 0; guard <=2; guard++)
         {
         	// Sort out the negative rules below.

            while(alreadyallocated[placeholder = (rand() % 15)] == 1);			// Get a free placholder

            while ( (placeholder == ROSS) && (bastion == ORANJE) )				// Ross cannot be at Oranje, ever (R6)
            {
            	while(alreadyallocated[placeholder = (rand() % 15)] == 1);		// Find another free placeholder
            }

            while ( (placeholder == JONES) && (bastion == BUREN) && (day == MONDAY) )	// Jones cannot be @ Buren on Monday
            {
            	while(alreadyallocated[placeholder = (rand() % 15)] == 1);					// Find another free placeholder
            }

/*				// For the next two negative rules.
				// Thompson Edwards and Harris were together on Monday (R10)
				// Thompson was placed at Nassau on Saturday (R9)
				// Hence Edwards and Harris cannot be there.

				while ( (placeholder == EDWARDS) && (bastion == NASSAU) && (day == SATURDAY) )	// From Set R9 + R13
            {
            	while(alreadyallocated[placeholder = (rand() % 15)] == 1);							// Find another free placeholder
            }

				while ( (placeholder == HARRIS) && (bastion == NASSAU) && (day == SATURDAY) )	// From Set R9 + R13
            {
					Print(); exit(0);

            	while(alreadyallocated[placeholder = (rand() % 15)] == 1);							// Find another free placeholder
            }
            There is a problem here since the guards get left out.*/

           if (addGuardOnDayAndBastion(day, bastion, placeholder, FALSE) != FALSE)
            {
               alreadyallocated[placeholder] = 1;
               counter++;
               if (counter == 15)
               {
                  bastion = NASSAU + 1;      // Break out of outer loop.
                  guard   = 4;               // Break out in inner loop.
               }
            }
         }
      }
   }
};

//==============================================================================

void Postings::SortRemainingGuards(void)
{

    // Sort the remaining guards and the corresponding fixarray()

	for (register int day = SUNDAY; day <= SATURDAY; day++)
    {
        for (register int bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
        {

            if (postingarray[day][bastion][0] > postingarray[day][bastion][2])
            {
                int temp = postingarray[day][bastion][0];
                int tfix = fixedarray[day][bastion][0];

                postingarray[day][bastion][0] = postingarray[day][bastion][2];
                postingarray[day][bastion][2] = temp;

                fixedarray[day][bastion][0]   = fixedarray[day][bastion][2];
                fixedarray[day][bastion][2]   = tfix;
            }

            if (postingarray[day][bastion][0] > postingarray[day][bastion][1])
            {
                int temp = postingarray[day][bastion][0];
                int tfix = fixedarray[day][bastion][0];

                postingarray[day][bastion][0] = postingarray[day][bastion][1];
                postingarray[day][bastion][1] = temp;

                fixedarray[day][bastion][0]   = fixedarray[day][bastion][1];
                fixedarray[day][bastion][1]   = tfix;

            }

            if (postingarray[day][bastion][1] > postingarray[day][bastion][2])
            {
                int temp = postingarray[day][bastion][1];
                int tfix = fixedarray[day][bastion][1];

                postingarray[day][bastion][1] = postingarray[day][bastion][2];
                postingarray[day][bastion][2] = temp;

                fixedarray[day][bastion][1]   = fixedarray[day][bastion][2];
                fixedarray[day][bastion][2]   = tfix;
            }
        }
    }
}

//==============================================================================

void Postings::Reset(void)
{
   register int guard, bastion, day;

   for (day = SUNDAY; day <= SATURDAY; day++)
      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
         for (guard = 0; guard <= 2; guard++)
         {
            postingarray[day][bastion][guard] = UNASSIGNED;
            fixedarray[day][bastion][guard] = FALSE;               // At initialization, there are no fixed positions.
         }

   totalerror = 0;
};

//==============================================================================

void Postings::EvaluateDoubles(void)
{

   register int bastion, day;
   const int A = 0;
   const int B = 1;
   const int C = 2;

   // Initialise the array
   for (register int x = ANDERSON; x <= WILSON; x++)
      for (register int y = ANDERSON; y <= WILSON; y++)
      	// No guard on the x-axis has been assigned to the one on the y-axis.
         doublearray[x][y] = 0;

   // The doublearray is symmetrical. There will be six assignments.
   // Out of a, b, c:
   // {a,b}, {b,a}, {a,c}, {c,a}, {b,c}, {c,b}
   for (day = SUNDAY; day <= SATURDAY; day++)
   {
      for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
      {
         doublearray[postingarray[day][bastion][A]][postingarray[day][bastion][B]]++;
         doublearray[postingarray[day][bastion][B]][postingarray[day][bastion][A]]++;
         doublearray[postingarray[day][bastion][A]][postingarray[day][bastion][C]]++;
         doublearray[postingarray[day][bastion][C]][postingarray[day][bastion][A]]++;
         doublearray[postingarray[day][bastion][B]][postingarray[day][bastion][C]]++;
         doublearray[postingarray[day][bastion][C]][postingarray[day][bastion][B]]++;
      }
   }
};

//==============================================================================

void Postings::PrintDoubles(void)
{
	const char legend[] = "A C D E F G H I J M P R S T W\n";
   printf("\n\n  ");
   printf (legend);

   for (int x = ANDERSON; x <= WILSON; x++)
   {
      printf("%c ", legend[x * 2]);
      for (int y = ANDERSON; y <= WILSON; y++)
      {
         if (x != y)
            printf("%i ", doublearray[x][y]);
         else
            printf ("* ");
      }
      printf("\n");
   }
};

//==============================================================================

int Postings::EvaluatePostingError(void)
{
   int SQUARES_CONSTANT = 0;  // Has been 3 in the past until April 2020

	int total = 0;
   for (register int x = ANDERSON; x <= WILSON; x++)
   {
      for (register int y = ANDERSON; y <= WILSON; y++)
      {
         if (doublearray[x][y] > 1)
            total += ( (doublearray[x][y] + SQUARES_CONSTANT) * (doublearray[x][y] + SQUARES_CONSTANT)); // Sum of squares. (x + 1)^2
      }
   }
   return total;
};

//==============================================================================

int Postings::GetTotalError()
{
   return totalerror;
};

//==============================================================================

int* Postings::GetArrayStart()
{
   return &postingarray[0][0][0];
};

//==============================================================================

void Postings::SetArray(int* intptr)
{
	// Not the most elegant solution. Breaks all OO rules.
	memcpy(postingarray, intptr, sizeof(postingarray));
	EvaluateFitness(FITNESS_FACTOR);
};

//==============================================================================

void Postings::CrossoverByDay(Postings X, Postings Y)
{
   int splitter;
   int arrayX[7][5][3];
   int arrayY[7][5][3];
   int swap[7][5][3];
   int *ptrX;
   int *ptrY;

   // Decide how the chromosome is going to be split.
   splitter = (rand() % 6) + 1;					// Random number from [1 .. 6] [inclusive]. This will make sure that there is at least a split.

   ptrX = X.GetArrayStart();					// Get the position of the first chromosome.
   ptrY = Y.GetArrayStart();					// Get the position of the second chromosome.

   memcpy(arrayX, ptrX, sizeof(arrayX));	// Copy in to temporary variables.
   memcpy(arrayY, ptrY, sizeof(arrayY));

   // Crossover on days.
   memcpy(swap, ptrX, sizeof(int) * 5 * 3 * splitter);
   memcpy(swap + splitter,	arrayY + splitter, sizeof(int) * 5 * 3 * (7 - splitter));			// This used to be 8 [NJW] 4 Oct 2015 which gave segmentation faults.

  	// Recalculate the 'Who is posted with whom matrix'
   SetArray(&swap[0][0][0]);

   // Re-evaluate the total finess.
   EvaluateFitness(FITNESS_FACTOR);

   GetTotalError();

};

//==============================================================================
// Do array crossover by positions that are unfixed
void Postings::CrossoverByUnFixed(Postings X, Postings Y)
{
   int splitter;
   int arrayX[7][5][3];
   int arrayY[7][5][3];
   int swap[7][5][3];
   int *ptrX;
   int *ptrY;

   int temparrayX[105];        // There are 105 slots in a week.
   int temparrayY[105];
   int templengthX = 0;        // The length of the temporary array
   int templengthY = 0;


   // Decide how the chromosome is going to be split.
   splitter = (rand() % 6) + 1;					// Random number from [1 .. 6] [inclusive]. This will make sure that there is at least a split.

   ptrX = X.GetArrayStart();					// Get the position of the first chromosome.
   ptrY = Y.GetArrayStart();					// Get the position of the second chromosome.

   memcpy(arrayX, ptrX, sizeof(arrayX));	// Copy in to temporary variables.
   memcpy(arrayY, ptrY, sizeof(arrayY));

   // Algorithm
   // 1. Take all the entries where the fixedarray is FALSE
   // 2. String them all together
   // 3. Crossover as per a normal string
   // 4. Put them back in the correct slots (those that are not fixed)

   for (register int counter = 0; counter <= 104;counter++)
   {
       temparrayX[counter] = 0;
       temparrayY[counter] = 0;
   }

   for (register int counter = 0; counter <= 104;counter++)
   {
/*       if (X.fixedarray[counter] == TRUE)
       {
            //#pragma -f permissive
            //temparrayX[templengthX] = *(arrayX + counter);
            //templengthX++;
       }

       if (Y.fixedarray[counter] == TRUE)
       {
            //temparrayY[templengthX] = arrayY[counter];
            //templengthY++;

       }
*/   }


  // Crossover on days.
   memcpy(swap, ptrX, sizeof(int) * 5 * 3 * splitter);
   memcpy(swap + splitter,	arrayY + splitter, sizeof(int) * 5 * 3 * (7 - splitter));			// This used to be 8 [NJW] 4 Oct 2015 which gave segmentation faults.

  	// Recalculate the 'Who is posted with whom matrix'
   SetArray(&swap[0][0][0]);

   // Re-evaluate the total finess.
   EvaluateFitness(FITNESS_FACTOR);

   GetTotalError();

};//==============================================================================

void Postings::Mutate (void)
{
	// We are going to swap a single bit (guard) around on a certain day
	int bastion1 = 0, section1 = 0;
	int bastion2 = 0, section2 = 0;
	int day1     = 0, day2     = 0;
	int guard1, guard2;
	int counter = 0;

	if (EvalRule01_AndersonWasAtSameBastionEveryWeekday() > 0)
		printf("Anderson");
	else
	if (PriceWasAtBurenEveryWeekday() > 0)
		printf("Price");
	else
	if (InglesWasAtLeerdamSixTimes() > 0)
		printf("Ingles");
	else
	if (FordWasAtOranjeFirstFourDaysOfWeek() > 0)
		printf("Ford");
	else
	if (RossNeverPostedToOranje() > 0)
		printf("Ross");
	else
	if (SundayRossGreenDawsonLeerdam() > 0)
		printf("SundayRossGreeDawsonLeerdam");
	else
	if (MondayThompsonEdwardsHarrisTogether() > 0)
		printf("MondayThompsaonEdwardsHarrisTogether");
	else
	if (MondayInglesWilsonRossTogether() > 0)
		printf("MondayInglesRossWilsonTogether");
	else
	if	(SaturdayThompsonNassau() > 0)
		printf("SaturdayThompsonNassau");
	else
	if (JonesNotAtBurenOnMonday() > 0)
		printf("JonesNotAtBurenOnMonday");

RESTART:

	bastion1 = 0;
	section1 = 0;
	bastion2 = 0;
	section2 = 0;
	day1 = rand() % 7;
   day2 = rand() & 7;

	while ((bastion1 == bastion2))
	{
		bastion1 = rand() % 5;
		bastion2 = rand() % 5;
		section1 = rand() % 3;
		section2 = rand() % 3;
	}

	guard1 = postingarray[day1][bastion1][section1];
	guard2 = postingarray[day2][bastion2][section2];

	// Swap

	postingarray[day1][bastion1][section1] = guard2;
	postingarray[day2][bastion2][section2] = guard1;

	// If there is a fundamental rules error then we have to undo and restart
	// The crossover is on a day level, so that if we rules that are dependent
	// on the number of days that a guard was a bastion, for example, then
	// we cannot necessarily assume that it was even correct coming in, since the
	//	crossover will have destroyed it.

	if ( (EvalRule01_AndersonWasAtSameBastionEveryWeekday() > 0)		||			// Rule 1
		  (PriceWasAtBurenEveryWeekday() > 0)					||			// Rule 2
		  (InglesWasAtLeerdamSixTimes() > 0)					||			// Rule 3
		  (FordWasAtOranjeFirstFourDaysOfWeek() > 0)			||			// Rule 4
		  (CarterAtNassauFourTimesNotTuesday() > 0)			||			// Rule 5
		  (RossNeverPostedToOranje() > 0)						||
		  (SundayEdwardsOranje() > 0)								||			//
		  (SundayRossGreenDawsonLeerdam() > 0)					||
		  (MondayThompsonEdwardsHarrisTogether() > 0)		||
		  (MondayInglesWilsonRossTogether() > 0)				||
		  (SaturdayThompsonNassau() > 0)							||
		  (JonesNotAtBurenOnMonday() > 0)						||
		  (DerivedRule01() > 0))
	{
		// Undo the initial work
		postingarray[day1][bastion1][section1] = guard1;
		postingarray[day2][bastion2][section2] = guard2;

		counter++;
		if (counter == 1000)
		{
			return;
			Print();
			printf("Guard allocation Error in Mutation() function.\n");
			exit(0);
		}

		goto RESTART;
	}

	// TAKE THIS OUT .... Nick put it in to mess around. 22 Mar 06

	EvaluateFitness(FITNESS_FACTOR);
	SortRemainingGuards();
	GetTotalError();

}


//==============================================================================
// EVALUATION RULEBASE
//==============================================================================

//==============================================================================
// Evaluation Rule 01

int  Postings::EvalRule01_AndersonWasAtSameBastionEveryWeekday(void)
{
   int bastionarray[5] = {0, 0, 0, 0, 0};		// How many times each bastion was visited.
   int totalnumberofbastions = 0;

   for (register int day = MONDAY; day <= SATURDAY; day++)
   {
   	for (int bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
      {
      	if ( (postingarray[day][bastion][0] == ANDERSON) ||
              (postingarray[day][bastion][1] == ANDERSON) ||
              (postingarray[day][bastion][2] == ANDERSON) )
         {
         	bastionarray[bastion]++;
         }
		}
   }

   // Work out how many times Anderson was a bastion the most.

   // Sort the array. From MONDAY = 1, hence dayarray + 1
   //qsort (bastionarray, 5, sizeof(int), sort_int);

   for (int bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
   {
   	if (bastionarray[bastion] > 0)
      	totalnumberofbastions++;
   }

	// Return the square of the total number of bastions less one

   return ((totalnumberofbastions - 1) * (totalnumberofbastions - 1));
};


//==============================================================================
// Rule 02

int Postings::PriceWasAtBurenEveryWeekday(void)
{
	// Will return the square of the number that Price
   // was at Buren that deviated from 6.
   // Sequence 36, 25, 16, 9, 4, 1 , 0, 1.
   // Measured as an error.

   int counter = 0;

   for (int day = MONDAY; day <= SATURDAY; day++)
   {
	  	if ( (postingarray[day][BUREN][0] == PRICE) ||
   	     (postingarray[day][BUREN][1] == PRICE) ||
      	  (postingarray[day][BUREN][2] == PRICE) )
   		counter++;
   }

	// Return the square of the total number of bastions less one

   return ((6 - counter) * (6 - counter));
}


//==============================================================================
// Rule 3

int Postings::InglesWasAtLeerdamSixTimes(void)
{
	// Will return the square of the number that Ingles
   // was at Leerdam that deviated from 6.
   // Sequence 36, 25, 16, 9, 4, 1 , 0, 1.
   // Measured as an error.

	int counter = 0;

	for (int day = SUNDAY; day <= SATURDAY; day++)
   {
   	if ( (postingarray[day][LEERDAM][0] == INGLES) ||
      	  (postingarray[day][LEERDAM][1] == INGLES) ||
           (postingarray[day][LEERDAM][2] == INGLES) )
			counter++;
   }
   return ( (6 - counter) * (6 - counter) );
}


//==============================================================================
// Rule 4

int Postings::FordWasAtOranjeFirstFourDaysOfWeek(void)
{
	// Will return the square of the number that Ford
   // was at Oranje that deviated from 4.
	// Sequence

   int counter = 0;

   for (int day = MONDAY; day <= THURSDAY; day++)
   {
   	if ( (postingarray[day][ORANJE][0] == FORD) ||
      	  (postingarray[day][ORANJE][1] == FORD) ||
           (postingarray[day][ORANJE][2] == FORD) )
      	counter++;
   }

   return ( (4 - counter) * (4 - counter) );

}

//==============================================================================
// Rule 5

int Postings::CarterAtNassauFourTimesNotTuesday(void)
{
	// Will return the square of the number that Carter
   // was at Nassau that deviated from 4. (excl. Tuesday)
   // If Carter was at Nassau on Tuesday, then return a
   // constant.

   int counter = 0;

   for (int day = SUNDAY; day <= SATURDAY; day++)
   {
		if (day != TUESDAY)
      {
	   	if ( (postingarray[day][NASSAU][0] == CARTER) ||
   	   	  (postingarray[day][NASSAU][1] == CARTER) ||
      	     (postingarray[day][NASSAU][2] == CARTER) )
      		counter++;
      }
   }

	// Ensure that Carter was not at Nassau on Tuesday
  	if ( (postingarray[TUESDAY][NASSAU][0] == CARTER) ||
   	  (postingarray[TUESDAY][NASSAU][1] == CARTER) ||
  	     (postingarray[TUESDAY][NASSAU][2] == CARTER) )
 		return 20;
	else
   	return ( (4 - counter) * (4 - counter) );


};

//==============================================================================
// Rule 6

int Postings::RossNeverPostedToOranje()
{
	int totalerror = 0;

	for (int day = SUNDAY; day <= SATURDAY; day++)
   {
   	for (int guard = 0; guard <= 2; guard++)
      {
	   	if (postingarray[day][ORANJE][guard] == ROSS)
         	totalerror++;
      }
   }

   // Return the square of the number of times that Ross was
   // posted to Oranje.

   return (totalerror * totalerror);
};


//==============================================================================
// Rule 7

int Postings::SundayRossGreenDawsonLeerdam(void)
{
	// For every guard (of the set) not at Leerdam, add PENALTY points.

	const int PENALTY = 5;

   int total_penalty = 0;

  	if ( (postingarray[SUNDAY][LEERDAM][0] == ROSS) ||
        (postingarray[SUNDAY][LEERDAM][1] == ROSS) ||
        (postingarray[SUNDAY][LEERDAM][2] == ROSS) )
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[SUNDAY][LEERDAM][0] == GREEN) ||
        (postingarray[SUNDAY][LEERDAM][1] == GREEN) ||
        (postingarray[SUNDAY][LEERDAM][2] == GREEN) )
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[SUNDAY][LEERDAM][0] == DAWSON) ||
        (postingarray[SUNDAY][LEERDAM][1] == DAWSON) ||
        (postingarray[SUNDAY][LEERDAM][2] == DAWSON) )
	{}
   else
   	total_penalty += PENALTY;

   return (total_penalty);
};

//==============================================================================
// Rule 8

int Postings::SundayEdwardsOranje(void)
{
   if ( (postingarray[SUNDAY][EDWARDS][0] == ORANJE) ||
     	  (postingarray[SUNDAY][EDWARDS][1] == ORANJE) ||
        (postingarray[SUNDAY][EDWARDS][2] == ORANJE) )
		return 0;
   else
   	return 10;
}


//==============================================================================
// Rule 9

int  Postings::MondayInglesWilsonRossTogether(void)
{
	// We know that on Sunday, Ross Green and Dawson were at Leerdam (R7)
	// We know that Ingles was at Leerdam six times. (R3)
	// ==> Ingles must be at Leerdam Mon, Tue, Wed, Thur, Fri, Sat
	// (==> Wilson and Ross were together at Leerdam with Ingles (R9))

	const int PENALTY = 5;

	int total_penalty = 0;

	if ( (postingarray[MONDAY][LEERDAM][0] == INGLES) ||
		  (postingarray[MONDAY][LEERDAM][1] == INGLES) ||
		  (postingarray[MONDAY][LEERDAM][2] == INGLES))
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[MONDAY][LEERDAM][0] == WILSON) ||
        (postingarray[MONDAY][LEERDAM][1] == WILSON) ||
        (postingarray[MONDAY][LEERDAM][2] == WILSON) )
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[MONDAY][LEERDAM][0] == ROSS) ||
        (postingarray[MONDAY][LEERDAM][1] == ROSS) ||
        (postingarray[MONDAY][LEERDAM][2] == ROSS) )
	{}
   else
   	total_penalty += PENALTY;

   return (total_penalty);
}


//==============================================================================
// Rule 10

int  Postings::MondayThompsonEdwardsHarrisTogether(void)
{
	// From R9, eliminiate Leerdam
	// From R1 (deduced) eliminate Catz
	// From R4 eliminate Oranje
	// From R2 eliminate Buren

	const int PENALTY = 5;

	int total_penalty = 0;

	if ( (postingarray[MONDAY][NASSAU][0] == THOMPSON) ||
		  (postingarray[MONDAY][NASSAU][1] == THOMPSON) ||
		  (postingarray[MONDAY][NASSAU][2] == THOMPSON))
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[MONDAY][NASSAU][0] == EDWARDS) ||
        (postingarray[MONDAY][NASSAU][1] == EDWARDS) ||
        (postingarray[MONDAY][NASSAU][2] == EDWARDS) )
	{}
   else
   	total_penalty += PENALTY;

  	if ( (postingarray[MONDAY][NASSAU][0] == HARRIS) ||
        (postingarray[MONDAY][NASSAU][1] == HARRIS) ||
        (postingarray[MONDAY][NASSAU][2] == HARRIS) )
	{}
   else
   	total_penalty += PENALTY;

   return (total_penalty);
}


//==============================================================================
// Rule 11

int  Postings::FridayFordMorrisTogether(void)
{
	register int bastion = 0;					// This used to be part of the for loop, resulting in a possible scope loss in the 'if' statement. [NJW] 30 June 2015

	for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
	{
		if ( (postingarray[FRIDAY][bastion][0] == FORD) ||
			  (postingarray[FRIDAY][bastion][1] == FORD) ||
			  (postingarray[FRIDAY][bastion][2] == FORD))
			break;
	}

	if ( (postingarray[FRIDAY][bastion][0] == MORRIS) ||
		  (postingarray[FRIDAY][bastion][1] == MORRIS) ||
		  (postingarray[FRIDAY][bastion][2] == MORRIS))
		return(0);
	else
		return(10);
}


//==============================================================================
// Rule 1	2

int Postings::FridayDawsonHarrisTogether(void)
{
	register int bastion = 0;					// This used to be part of the for loop, resulting in a possible scope loss in the 'if' statement. [NJW] 30 June 2015

	for (bastion = CATZENELLENBOGEN; bastion <= NASSAU; bastion++)
	{
		if ( (postingarray[FRIDAY][bastion][0] == DAWSON) ||
			  (postingarray[FRIDAY][bastion][1] == DAWSON) ||
			  (postingarray[FRIDAY][bastion][2] == DAWSON))
			break;
	}

	if ( (postingarray[FRIDAY][bastion][0] == HARRIS) ||
		  (postingarray[FRIDAY][bastion][1] == HARRIS) ||
		  (postingarray[FRIDAY][bastion][2] == HARRIS))
		return(0);
	else
		return(10);}


//==============================================================================
// Rule 13

int Postings::SaturdayThompsonNassau(void)
{
   if ( (postingarray[SATURDAY][NASSAU][0] == THOMPSON) ||
     	  (postingarray[SATURDAY][NASSAU][1] == THOMPSON) ||
        (postingarray[SATURDAY][NASSAU][2] == THOMPSON) )
   	return 0;
   else
   	return 10;
};


//==============================================================================
// Rule 14

int Postings::ThompsonAndCarterTogetherAtBuren(void)
{
	// During the search there is the possibility that Thompson
   // and Carter will not be posted together.
   // Also, there is the possibility that neither of them are
   // posted to Buren.

   // Logic:
   // Find out when Thompson is posted to Buren.
   // If he is never posted to Buren, return NOT_AT_BASTION
   // If he is posted to Buren and Carter is not with him, return NOT_TOGETHER

   // Naturally, this rule will not double up the scores if the two are posted
   // together twice. This will be handled by the rule that works out the
   // doubling of postings.

   const int NOT_AT_BASTION = 50;
   const int NOT_TOGETHER   = 30;

	int ThompsonAtBuren = FALSE;
	int CarterAtBuren   = FALSE;

	for (int day = SUNDAY; day <= SATURDAY; day++)
   {
   	if ( (postingarray[day][BUREN][0] == THOMPSON) ||
      	  (postingarray[day][BUREN][1] == THOMPSON) ||
           (postingarray[day][BUREN][2] == THOMPSON) )
      {
      	// We have a day that Thompson is at Buren
         ThompsonAtBuren = TRUE;
         // Find out whether Carter is with him
	   	if ( (postingarray[day][BUREN][0] == CARTER) ||
   	   	  (postingarray[day][BUREN][1] == CARTER) ||
      	     (postingarray[day][BUREN][2] == CARTER) )
	         CarterAtBuren = TRUE;
      }
   }

	if (!ThompsonAtBuren)
   	return NOT_AT_BASTION;
   else
   	if (!CarterAtBuren)
      	return NOT_TOGETHER;
      else
      	return 0;
};

//==============================================================================
// Rule 15

int Postings::HarrisAndRossTogetherAtBuren(void)
{
	// During the search there is the possibility that Harris
   // and Ross will not be posted together.
   // Also, there is the possibility that neither of them are
   // posted to Buren.

   // Logic:
   // Find out when Harris is posted to Buren.
   // If he is never posted to Buren, return NOT_AT_BASTION
   // If he is posted to Buren and Ross is not with him, return NOT_TOGETHER

   // Naturally, this rule will not double up the scores if the two are posted
   // together twice. This will be handled by the rule that works out the
   // doubling of postings.

   const int NOT_AT_BASTION = 50;
   const int NOT_TOGETHER   = 30;

	int HarrisAtBuren = FALSE;
   int RossAtBuren   = FALSE;

	for (int day = SUNDAY; day <= SATURDAY; day++)
   {
   	if ( (postingarray[day][BUREN][0] == HARRIS) ||
      	  (postingarray[day][BUREN][1] == HARRIS) ||
           (postingarray[day][BUREN][2] == HARRIS) )
      {
      	// We have a day that Thompson is at Buren
         HarrisAtBuren = TRUE;
         // Find out whether Ross is with him
	   	if ( (postingarray[day][BUREN][0] == ROSS) ||
   	   	  (postingarray[day][BUREN][1] == ROSS) ||
      	     (postingarray[day][BUREN][2] == ROSS) )
	         RossAtBuren = TRUE;
      }
   }

	if (!HarrisAtBuren)
   	return NOT_AT_BASTION;
   else
   	if (!RossAtBuren)
      	return NOT_TOGETHER;
      else
      	return 0;
};

//==============================================================================
// Rule 16

int Postings::JonesNotAtBurenOnMonday(void)
{
   if ( (postingarray[MONDAY][BUREN][0] == JONES) ||
     	  (postingarray[MONDAY][BUREN][1] == JONES) ||
        (postingarray[MONDAY][BUREN][2] == JONES) )
		return 10;
   else
   	return 0;
};


//==============================================================================
// SETTING RULEBASE
//==============================================================================

//==============================================================================
// Set Rule 01

void Postings::SetRule01_AndersonWasAtSameBastionEveryWeekday(void)
{
	// We know that on Sunday, Ross Green and Dawson were at Leerdam (R07)
	// We know that Ingles was at Leerdam six times. (R03)
	// ==> Ingles must be at Leerdam Mon, Tue, Wed, Thur, Fri, Sat
	// ==> Rule out Leerdam
	// (==> Wilson and Ross were together at Leerdam with Ingles on Monday (R09))
	// We know that Price was at Buren every weekday (R02)
	// ==> Rule out Buren
	// We know that Ford was at Oranje M, T, W, T (R04)
	// Rule out Oranje
	// Leaves us with Catz or Nassau
	// However,
	// Carter was at Nassau four times, not Tuesday. (R05)
	// Even if Carter was at Nassau on Sunday it means he has to have at least
	// three other weekdays at Nassau
	// This clashes with Anderson.
	// So Anderson MUST have been at Catz.

	int bastion;

	bastion = CATZENELLENBOGEN;

	for (int day = MONDAY; day <= SATURDAY; day++)
	{
		if (!addGuardOnDayAndBastion(day, bastion, ANDERSON, TRUE))
			printf("Error allocating SetRule01_AndersonWasAtSameBastionEveryWeekday\n");
	}
};



//==============================================================================
// Set Rule 07

void Postings::SetSundayRossGreenDawsonLeerdam(void)
{
   addGuardOnDayAndBastion(SUNDAY, LEERDAM, ROSS, TRUE);
   addGuardOnDayAndBastion(SUNDAY, LEERDAM, GREEN, TRUE);
   addGuardOnDayAndBastion(SUNDAY, LEERDAM, DAWSON, TRUE);
};


//==============================================================================
// Set Rule 08

void Postings::SetSundayEdwardsOranje(void)
{
	addGuardOnDayAndBastion(SUNDAY, ORANJE, EDWARDS, TRUE);
}


//==============================================================================
// Rule 4

void Postings::SetFordWasAtOranjeFirstFourDaysOfWeek(void)
{
   for (int day = MONDAY; day <= THURSDAY; day++)
   {
      if (addGuardOnDayAndBastion(day, ORANJE, FORD, TRUE))
      {}
      else
         printf("Error allocating SetFordWasAtOranjeFirstFourDaysOfWeek.\n");
   }
}


//==============================================================================
// Rule 2
void Postings::SetPriceWasAtBurenEveryWeekday(void)
{
   for (register int day = MONDAY; day <= SATURDAY; day++)
   {
      if (addGuardOnDayAndBastion(day, BUREN, PRICE, TRUE))
      {}
      else
         printf("Error allocating SetPriceWasAtBurenEveryWeekday\n");
   }
};


//==============================================================================
// Rule 3
void Postings::SetInglesWasAtLeerdamSixTimes(void)
{
	// We know that Ross, Green and Dawson were at Leerdam on Sunday
	// This is rule 7
	// Therefore Ingles must have been at Leerdam MONDAY ... SATURDAY

	for (register int day = MONDAY; day <= SATURDAY; day++)
	{
		if (!addGuardOnDayAndBastion(day, LEERDAM, INGLES, TRUE))
			printf("Error allocating SetInglesWasAtLeerdamSixTimes\n");
	}
}


//==============================================================================
// Rule 5

void Postings::SetCarterAtNassauFourTimesNotTuesday(void)
{
	int weekarray[7] = {0, 0, 1, 0, 0, 0, 0};			// Tuesday is blocked out
	int day;

	for (register int counter = 1; counter <= 4; counter++)
	{
		while (weekarray[day = (rand() % 7)] != 0);
		weekarray[day] = 1;
		if (!addGuardOnDayAndBastion(day, NASSAU, CARTER, FALSE))
			printf("Error allocating SetCarterAtNassauFourTimesNotTuesday\n");
	}
}

//==============================================================================
// Rule 9

void Postings::SetMondayInglesWilsonRossTogether(void)
{
	// We know that on Sunday, Ross Green and Dawson were at Leerdam (R7)
	// We know that Ingles was at Leerdam six times. (R3)
	// ==> Ingles must be at Leerdam Mon, Tue, Wed, Thur, Fri, Sat
	// (==> Wilson and Ross were together at Leerdam with Ingles (R9))

	// addGuardOnDayAndBastion(MONDAY, LEERDAM, INGLES);		Don't add this since it is done already (R3)

	addGuardOnDayAndBastion(MONDAY, LEERDAM, ROSS, TRUE);
	addGuardOnDayAndBastion(MONDAY, LEERDAM, WILSON, TRUE);

}

//==============================================================================
// Rule 10

void Postings::SetMondayThompsonEdwardsHarrisTogether(void)
{
	// From R9, eliminiate Leerdam
	// From R1 (deduced) eliminate Catz
	// From R4 eliminate Oranje
	// From R2 eliminate Buren

	addGuardOnDayAndBastion(MONDAY, NASSAU, THOMPSON, TRUE);
	addGuardOnDayAndBastion(MONDAY, NASSAU, EDWARDS, TRUE);
	addGuardOnDayAndBastion(MONDAY, NASSAU, HARRIS, TRUE);
}

//==============================================================================
// Rule 13

void Postings::SetSaturdayThompsonNassau(void)
{
   addGuardOnDayAndBastion(SATURDAY, NASSAU, THOMPSON, TRUE);
};

//==============================================================================
// DERIVED RULEBASE
//==============================================================================

//==============================================================================
// Derived Rule 1

int Postings::DerivedRule01(void)
{
	int bastion;
	int factor = 0;
	int total =  0;

	// Anderson and Price must have been together on Sunday (R1, R2)
	// Anderson could not have been at Leerdam (R7)
	// This must include Ingles since he was at Leerdam for the remainder (see R8 derived),
	// and Anderson and Ingles need to be together.
	// It could not have been Oranje since Edwards was posted there (R8)
	// This leaves Buren, Catz or Nassau for
	// Anderson, Ingles, Price (in that sort order).

	for (register int counter = 0; counter <= 2; counter++)
	{
		if (counter == 0)
			{bastion = BUREN; factor = 1;}
		else
			if (counter == 1)
				{bastion = CATZENELLENBOGEN; factor = 10;}
			else
				{bastion = NASSAU; factor = 100;}

		if (postingarray[SUNDAY][bastion][0] == ANDERSON)
			total += factor;
		if (postingarray[SUNDAY][bastion][1] == INGLES)
			total += factor;
		if (postingarray[SUNDAY][bastion][2] == PRICE)
			total += factor;
	}

	if ( (factor == 3) || (factor == 30) || (factor == 300) )
		return 0;
	else
		return 5;

}
