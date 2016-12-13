#include "info.h"

//its sloppy for now but I will fix it up when I add more features

void idString(char name[], char id[])
{
        int i;
        int endString = 0;

    for(i=0; i<30; i++)
    {

        if(name[i] != ' ')
        {
            id[i] = name[i];
            //nameFile[i] = name[i];

        }
        else
        {
            id[i] = '_';
            //nameFile[i] = '_';
        }
        endString++;
    }


    //strcpy(nameFile, id);
    //id[endString] = '\0';
    //strcat(nameFile, ".cfg");


}

void objectives(FILE *fileScenario)
{
    int done = 0;
    char objective[200];
    //print out basic prestart event with objectives
    fprintf(fileScenario, "\t[event]\n");
    fprintf(fileScenario, "\t\tname=prestart\n");
    fprintf(fileScenario, "\t\t[objectives]\n");
    fprintf(fileScenario, "\t\t\tside=1\n");
    //get winning conditions
    while (done != 1)
    {
        printf("Enter winning condition (200 characters max) type done when done\n");
        fgets (objective, 200, stdin);
        //remove newline character since fgets adds it when you press enter
        addNull(objective);
        if (strcmp(objective, "done") == 0)
        {
            done = 1;
        }
        else
        {
            fprintf(fileScenario, "\t\t\t[objective]\n");
            fprintf(fileScenario, "\t\t\t\tdescription= _ \"%s\"\n", objective);
            fprintf(fileScenario, "\t\t\t\tcondition=win\n", objective);
            fprintf(fileScenario, "\t\t\t[/objective]\n");

        }

    }// end winning while loop
    done = 0;
    //now for lose conditions
        while (done != 1)
    {
        printf("Enter losing condition (200 characters max) type done when done\n");
        printf("Turns running out will be done automatically\n");
        fgets (objective, 200, stdin);
        //remove newline character since fgets adds it when you press enter
        addNull(objective);

        if (strcmp(objective, "done") == 0)
        {
            done = 1;
        }
        else
        {
            fprintf(fileScenario, "\t\t\t[objective]\n");
            fprintf(fileScenario, "\t\t\t\tdescription= _ \"%s\"\n", objective);
            fprintf(fileScenario, "\t\t\t\tcondition=lose\n", objective);
            fprintf(fileScenario, "\t\t\t[/objective]\n");

        }

    }// end losing while loop
    fprintf(fileScenario, "\t\t\t{TURNS_RUN_OUT}\n");

    //gold carry over
    fprintf(fileScenario, "\t\t\t[gold_carryover]\n");
    fprintf(fileScenario, "\t\t\t\tbonus=yes\n"
                "\t\t\t\tcarryover_percentage=40\n");
    fprintf(fileScenario, "\t\t\t[/gold_carryover]\n");

    fprintf(fileScenario, "\t\t[/objectives]\n");+
    fprintf(fileScenario, "\t[/event]\n");
}

void side(FILE *fileScenario)
{
    int done = 0;
    char gold[8];
    char team[20];
    char teamID[20];
    char type[20];
    char name[20];
    char nameID[20];
    char recruit[20];
    char anotherUnit[8] = "meh";
    printf("\nInformation on your faction\n");
    fprintf(fileScenario, "\t[side]\n");
    printf("Unit type for your leader: ");
    //fgets because unit types have spaces
    fgets (type, 30, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(type);

    printf("Type a name for your leader: ");
    fgets (name, 20, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(name);

    idString(name, nameID);
    fprintf(fileScenario, "\t\ttype=%s\n", type);
    fprintf(fileScenario, "\t\tid=%s\n", nameID);
    fprintf(fileScenario, "\t\tname=_ \"%s\"\n", name);
    fprintf(fileScenario, "\t\tside=1\n");
    fprintf(fileScenario, "\t\tcanrecruit=yes\n");
    fprintf(fileScenario, "\t\tcontroller=human\n");
    //see if user needs to add recruits
    while (strcmp(anotherUnit, "yes") != 0 && strcmp(anotherUnit, "no") != 0)
    {
            printf("\nDo you need to add recruits? (yes/no)\nRecruits carry over from previous scenarios\n");
            fgets (anotherUnit, 8, stdin);
            //remove newline character since fgets adds it when you press enter
            addNull(anotherUnit);

    }
    if(strcmp(anotherUnit, "yes") == 0)
    {

    fprintf(fileScenario, "\t\trecruit=");
    printf("Type units you can recruit for this scenario one at a time\n");

    while (done != 1)
    {
        anotherUnit[0] = 'l';
        printf("Unit: ");
        fgets (recruit, 20, stdin);

        //remove newline character since fgets adds it when you press enter
        addNull(recruit);

        if (strcmp(recruit, "done") == 0)
        {
            done = 1;
        }
        else
        {
            fprintf(fileScenario, "%s", recruit);
        }
        //check if user wants to add another unit
        while (strcmp(anotherUnit, "yes") != 0 && strcmp(anotherUnit, "no") != 0)
        {
            printf("Add another unit? yes/no\n");
            fgets (anotherUnit, 8, stdin);
            //remove newline character since fgets adds it when you press enter
            addNull(anotherUnit);

        }
        if (strcmp(anotherUnit, "yes") == 0)
        {
            fprintf(fileScenario, ", ");
        }
        else if (strcmp(anotherUnit, "no") == 0)
        {
            fprintf(fileScenario, "\n");
            break;

        }

    }// end while
    }//end if statement to add units
    //get gold
    printf("\nEnter your starting gold: ");
    fgets (gold, 8, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(gold);

    fprintf(fileScenario, "\t\tgold=%s\n", gold);

    //team
    printf("Enter your team name\n");
    fgets (team, 20, stdin);
    //remove newline character since fgets adds it when you press enter
    addNull(team);
    idString(team, teamID);
    fprintf(fileScenario, "\t\tteam_name=%s\n", teamID);
    fprintf(fileScenario, "\t\tuser_team_name=_\"%s\"\n", team);
    fprintf(fileScenario, "\t[/side]\n");


}
void ai(FILE *fileScenario)
{
    char aiFactions[8];
    char gold[8];
    char team[20];
    char teamID[20];
    char type[20];
    char name[20];
    char nameID[20];
    char recruit[20];
    char anotherUnit[5] = "meh";
    int aiFactionsNum;
    int i;
    int done = 0;
    printf("\nHow many ai factions: ");
    //get number of ai and parse into int
    fgets(aiFactions, 8, stdin);
    addNull(aiFactions);
    //char to int
    aiFactionsNum =atoi(aiFactions);
    printf("\nAi factions information\n");
    for (i = 0; i<aiFactionsNum; i++)
    {
        printf("\nEnemy leader name: ");
        fgets(name, 20, stdin);
        addNull(name);
        idString(name, nameID);

        fprintf(fileScenario, "\t[side]\n");
        fprintf(fileScenario, "\t\tside=%d\n", (i+2));
        printf("\nAi leader type: ");
        fprintf(fileScenario, "\t\tname= _ \"%s\"\n", name);
        fprintf(fileScenario, "\t\tid=%s\n",nameID);
        fprintf(fileScenario, "\t\tcanrecruit=yes\n");
        fgets(type, 20, stdin);
        addNull(type);
        fprintf(fileScenario, "\t\ttype=%s\n", type);
        fprintf(fileScenario, "\t\trecruit=");
        //loop to add recruits
        while (done != 1)
        {
            printf("\nAi recruitable unit\n");
            anotherUnit[0] = 'l';
            printf("Unit: ");
            fgets (recruit, 20, stdin);

            //remove newline character since fgets adds it when you press enter
            addNull(recruit);


            fprintf(fileScenario, "%s", recruit);

            //check if user wants to add another unit
            while (strcmp(anotherUnit, "yes") != 0 && strcmp(anotherUnit, "no") != 0)
            {
                printf("Add another unit? yes/no\n");
                fgets (anotherUnit, 8, stdin);
                //remove newline character since fgets adds it when you press enter
                addNull(anotherUnit);

            }
            if (strcmp(anotherUnit, "yes") == 0)
            {
                fprintf(fileScenario, ", ");
            }
            else if (strcmp(anotherUnit, "no") == 0)
            {
                fprintf(fileScenario, "\n");
                break;

            }

    }// end recruit while

    printf("\nAi starting gold: ");
    fgets(gold, 8, stdin);
    fprintf(fileScenario, "\t\tgold=%s\n", gold);
    printf("\n%s's team name: ", name);
    fgets(team, 20, stdin);
    addNull(team);
    idString(team, teamID);
    fprintf(fileScenario, "\t\tteam_name=%s\n", teamID);
    fprintf(fileScenario, "\t\tuser_team_name=_\"%s\"\n", team);
    fprintf(fileScenario, "\t[/side]\n");
    }// end for loop to generate factions


}

void addNull(char inArray[])
{
    if ((strlen(inArray)>0) && (inArray[strlen (inArray) - 1] == '\n'))
    {
        inArray[strlen (inArray) - 1] = '\0';
    }
}

void commandMessage()
{
//will be used to add messages to events
}

