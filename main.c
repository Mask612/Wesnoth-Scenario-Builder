#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

int main()
{
    printf("-----Wesnoth Scenario Maker-----\n");
    //variables
    FILE *fileScenario;
    char scenarioName[30];
    char scenarioID[30];
    char scenarioFileName[34];

    char turnsEasy[4];
    char turnsMedium[4];
    char turnsHard[4];
    //get name of scenario
    printf("\nName of scenario: ");
    fgets (scenarioName, 30, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(scenarioName);


    //remove spaces for scenario id and filename
    idString(scenarioName, scenarioID);
    strcpy(scenarioFileName, scenarioID);
    strcat(scenarioFileName, ".cfg");


    //print out name id and file for user
    printf("Scenario name is: %s\n", scenarioName);
    printf("Scenario id is: %s\n", scenarioID);
    printf("Scenario file name is %s\n", scenarioFileName);

    //try to open file with scenarioFileName
    //set to append so easily remove code if file exists
    if ((fileScenario = fopen(scenarioFileName, "w")) == NULL)
    {
        printf("\nCould not create scenario %s", scenarioFileName);
        exit(1);
    }

    //get turn limits
    printf("\nEnter a turn limit for easy: ");
    fgets (turnsEasy, 4, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(turnsEasy);

    printf("\nEnter a turn limit for medium: ");
    fgets (turnsMedium, 4, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(turnsMedium);

    printf("\nEnter a turn limit for hard: ");
    fgets (turnsHard, 4, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(turnsHard);


    //print what info we have so far to file
    fprintf(fileScenario, "[scenario]\n");
    fprintf(fileScenario, "\tid=%s\n", scenarioID);
    fprintf(fileScenario, "\tname= _ \"%s\"\n", scenarioName);
    fprintf(fileScenario, "\tnext_scenario=id of next scenario\n", scenarioName);
    fprintf(fileScenario, "\tvictory_when_enemies_defeated=yes\n");
    fprintf(fileScenario, "\tmap_data=\"{YOUR MAP FILE PATH HERE}\"\n");
    fprintf(fileScenario, "\t{TURNS %s %s %s}\n", turnsEasy, turnsMedium, turnsHard);
    fprintf(fileScenario, "\t{DEFAULT_SCHEDULE}\n");
    fprintf(fileScenario, "\t{DEFAULT_SCHEDULE}\n");

    //basic music from httt
    fprintf(fileScenario, "\t{SCENARIO_MUSIC \"battle.ogg\"}\n"
    "\t{EXTRA_SCENARIO_MUSIC \"casualties_of_war.ogg\"}\n"
    "\t{EXTRA_SCENARIO_MUSIC \"knolls.ogg\"}\n"
    "\t{EXTRA_SCENARIO_MUSIC \"siege_of_laurelmor.ogg\"}"
    "\t{EXTRA_SCENARIO_MUSIC \"suspense.ogg\"}"
    "\t{EXTRA_SCENARIO_MUSIC \"the_city_falls.ogg\"}\n");

    //make objectives
    objectives(fileScenario);
    //set factions
    side(fileScenario);
    ai(fileScenario);


    //add events
    int done = 0;
    char command[15];
    while(done != 1)
    {
        //get command from user
        printf("\n\nType done to finish\n"); //this will be used to add events but for now only allows you to finish the scene
        fgets (command, 15, stdin);
        addNull(command);


        if (strcmp(command, "done") == 0)
        {
            done = 1;
            fprintf(fileScenario, "[/scenario]");
        }
        else
        {
            printf("\nINVALID COMMAND\nFor help type help\n");
        }

    }

    fclose(fileScenario);
    return 0;
}
