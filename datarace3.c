#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

/******************************************/
/* DEFINES */
/******************************************/

/* File containing all the race data */
#define FILE_PATH "cykelloeb-2017.txt"

#define NUMBER_OF_DATA_PER_LINE     7
#define RACE_NAME_SIZE              50
#define NAME_SIZE                   50
#define TEAM_SIZE                   4
#define COUNTRY_SIZE                4
#define RANKING_SIZE                4
#define TIME_SIZE                   8

/*******************************************/
/* DATATYPES */
/*******************************************/

struct race_data {
    char race[RACE_NAME_SIZE];
    char rider_name[NAME_SIZE];
    char first_name[NAME_SIZE];
    char last_name[NAME_SIZE];
    int age;
    char team[TEAM_SIZE];
    char country[COUNTRY_SIZE];
    char ranking[RANKING_SIZE];
    char time[TIME_SIZE];
    int score;
};
typedef struct race_data RACE_DATA;

struct rider_data {
    char name[NAME_SIZE];
    char first_name[NAME_SIZE];
    char last_name[NAME_SIZE];
    int age;
    char team[TEAM_SIZE];
    char country[COUNTRY_SIZE];
    int total_score;
};
typedef struct rider_data RIDER_DATA;

struct team_data {
    char name[TEAM_SIZE];
    int riders_out;
};
typedef struct team_data TEAM_DATA;

struct nation_data {
    char name[COUNTRY_SIZE];
    int total_score;
    int total_age;
};
typedef struct nation_data NATION_DATA;

typedef struct tm TIME_DATA;

/******************************************/
/* PROTOTYPES */
/******************************************/

int string_to_int_helper(const char *first, const char *, int);

int string_to_int(const char *str);

int split_string(char **, const char *, const char *);

int is_upper_case(const char *);

void make_word_proper(char *);

void trim_end(char *);

int get_number_of_lines_file(const char *);

FILE *open_file(int *, const char *);

int get_riders_who_has_completed_the_race(int, RACE_DATA *, RACE_DATA *, char *);

int get_number_of_riders_who_completed_the_race(int, RACE_DATA *, char *);

int get_nations(int, RIDER_DATA *, NATION_DATA *);

int get_races(int, RACE_DATA *, char **);

int get_teams(int, RIDER_DATA *, TEAM_DATA *);

int print_race_data_for_rider(RACE_DATA, int);

int print_rider_data(RIDER_DATA, int format);

int read_race_data_file(const char *, RACE_DATA *, int *, RIDER_DATA *, int *);

int sort_nations(const void *, const void *);

int sort_teams(const void *, const void *);

int sort_rider_scores(const void *, const void *);

int sort_danish_riders(const void *, const void *);

void print_assignment_1(int, RIDER_DATA *);

void print_assignment_2(int, RACE_DATA *);

void print_assignment_3(int, RIDER_DATA *);

void print_assignment_4(int, int, RIDER_DATA *, RACE_DATA *);

void print_assignment_5(int, RIDER_DATA *);

void print_assignment_6(int, RACE_DATA *, int);

/******************************************/
/* MAIN */
/******************************************/
int main(int argc, char *argv[]) {
    int race_data_arr_size, rider_data_arr_size, run_commands = 1, number_of_lines;
    RACE_DATA *race_data_arr;
    RIDER_DATA *rider_data_arr;
    char input[5];

    number_of_lines = get_number_of_lines_file(FILE_PATH);
    race_data_arr = malloc(sizeof(RACE_DATA) * number_of_lines * 2);
    rider_data_arr = malloc(sizeof(RIDER_DATA) * number_of_lines);

    if (!read_race_data_file(FILE_PATH, race_data_arr, &race_data_arr_size, rider_data_arr,
                             &rider_data_arr_size)) {
        exit(0);
    }

    /* Print all statistics if given the command "--print" */
    if (argc > 1 && strcmp(argv[1], "--print") == 0) {
        print_assignment_1(rider_data_arr_size,
                           rider_data_arr);
        printf("\n");
        print_assignment_2(race_data_arr_size,
                           race_data_arr);
        printf("\n");
        print_assignment_3(rider_data_arr_size,
                           rider_data_arr);
        printf("\n");
        print_assignment_4(rider_data_arr_size,
                           race_data_arr_size,
                           rider_data_arr,
                           race_data_arr);
        printf("\n");
        print_assignment_5(rider_data_arr_size,
                           rider_data_arr);
        printf("\n");
        print_assignment_6(race_data_arr_size,
                           race_data_arr,
                           1);
        printf("\n\nPress [ENTER] to Continue...");
        getchar();

    } else {
        printf("////////////////////////////////////////////\n");
        printf("//                                        //\n");
        printf("//                                        //\n");
        printf("//                        #  # #          //\n");
        printf("//                    #####  # #          //\n");
        printf("//            ##########   ##  #          //\n");
        printf("//          ########    ###  ##           //\n");
        printf("//        #######    #####  ###           //\n");
        printf("//        #####    #####   ###            //\n");
        printf("//        ####    #####   ####            //\n");
        printf("//        ####   ######   #####           //\n");
        printf("//         ##    ######   ######          //\n");
        printf("//          #    ######    #######        //\n");
        printf("//               ######     #######       //\n");
        printf("//               #######     ####         //\n");
        printf("//                 ######                 //\n");
        printf("//                                        //\n");
        printf("//                                        //\n");
        printf("//           ###    ###   #   #           //\n");
        printf("//          #   #  #   #  #   #           //\n");
        printf("//          #####  #####  #   #           //\n");
        printf("//          #   #  #   #   ###            //\n");
        printf("//                                        //\n");
        printf("//                                        //\n");
        printf("//     WELCOME TO THE CYCLING MANAGER     //\n");
        printf("//                                        //\n");
        printf("//         Copyright© Jakob Precht        //\n");
        printf("//                                        //\n");
        printf("//                                        //\n");
        printf("////////////////////////////////////////////\n\n");

        printf("Type a number or a command\n\n");
        printf("1     | Belgian riders under 23\n");
        printf("2     | Danish riders who anticipated in one or more of the races\n");
        printf("3     | The 10 riders who got the most points\n");
        printf("4     | Team who has the most riders as OTL or DNF in each race\n");
        printf("5     | The nation with the most points\n");
        printf("6     | The median time for each race\n");
        printf("clear | Clear all content on the screen\n");
        printf("exit  | Exit the program\n");

        while (run_commands) {
            printf("\nCommand: ");
            scanf("%5s", input);

            if (strcmp(input, "exit") == 0) {
                run_commands = 0;
            } else {
                switch (string_to_int(input)) {
                    case 1:
                        printf("\n");
                        print_assignment_1(rider_data_arr_size,
                                           rider_data_arr);
                        break;
                    case 2:
                        printf("\n");
                        print_assignment_2(race_data_arr_size,
                                           race_data_arr);
                        break;
                    case 3:
                        printf("\n");
                        print_assignment_3(rider_data_arr_size,
                                           rider_data_arr);
                        break;
                    case 4:
                        printf("\n");
                        print_assignment_4(rider_data_arr_size,
                                           race_data_arr_size,
                                           rider_data_arr,
                                           race_data_arr);
                        break;
                    case 5:
                        printf("\n");
                        print_assignment_5(rider_data_arr_size,
                                           rider_data_arr);
                        break;
                    case 6:
                        printf("\n");
                        print_assignment_6(race_data_arr_size,
                                           race_data_arr,
                                           1);
                        break;
                    default:
                        printf("\nCommand not found\n");
                        break;
                }
            }
        }
    }

    free(race_data_arr);
    free(rider_data_arr);

    return 1;
}

/*******************************************/
/* FUNCTIONS */
/*******************************************/

/* Read race data file */
int read_race_data_file(const char *file_name,
                        RACE_DATA *race_data_arr,
                        int *race_data_arr_size,
                        RIDER_DATA *rider_data_arr,
                        int *rider_data_arr_size) {
    int i, j, k, res,
            word_counter,
            score,
            already_in_array;
    char **words;
    RACE_DATA race_data;
    FILE *file;

    /* Exit program if can't open the file or the file is empty */
    if ((file = open_file(race_data_arr_size, file_name)) == NULL) {
        fclose(file);
        return 0;
    }

    *race_data_arr_size = 0;

    /* Get data from file */
    while ((res = fscanf(file,
                         "%49s \" %49[^\"] \" %d %3s %3s %3s %7s\r\n",
                         race_data.race,
                         race_data.rider_name,
                         &race_data.age,
                         race_data.team,
                         race_data.country,
                         race_data.ranking,
                         race_data.time)) != EOF) {
        /* Check if line was formatted correctly */
        if (res == NUMBER_OF_DATA_PER_LINE) {
            /* Split full name into single names */
            words = malloc(strlen(race_data.rider_name) + 1);
            word_counter = split_string(words, race_data.rider_name, " ");

            j = 0;
            k = 0;
            for (i = 0; i < word_counter; i++) {
                char *temp_word = words[i];
                if (is_upper_case(temp_word)) {
                    make_word_proper(temp_word);
                    if (j++ == 0) {
                        strcpy(race_data.last_name, temp_word);
                    } else {
                        strcat(race_data.last_name, " ");
                        strcat(race_data.last_name, temp_word);
                    }

                } else {
                    if (k++ == 0) {
                        strcpy(race_data.first_name, temp_word);
                    } else {
                        strcat(race_data.first_name, " ");
                        strcat(race_data.first_name, temp_word);
                    }
                }
            }

            /* Formatted rider name */
            strcpy(race_data.rider_name, race_data.first_name);
            strcat(race_data.rider_name, " ");
            strcat(race_data.rider_name, race_data.last_name);

            /* Add race data to array */
            race_data_arr[(*race_data_arr_size)++] = race_data;
        }
    }

    /* Close file */
    fclose(file);

    *rider_data_arr_size = 0;

    /* Calculate scores */
    for (i = 0; i < *race_data_arr_size; i++) {
        race_data = race_data_arr[i];

        score = 0;
        if (strcmp(race_data.ranking, "DNF") != 0) {

            score += 2;

            if (strcmp(race_data.ranking, "OTL") != 0) {
                int number = get_number_of_riders_who_completed_the_race(*race_data_arr_size,
                                                                         race_data_arr,
                                                                         race_data.race);

                int ranking_value = string_to_int(race_data.ranking);
                score += (number - ranking_value) / 17;

                switch (ranking_value) {
                    case 1:
                        score += 8;
                        break;
                    case 2:
                        score += 5;
                        break;
                    case 3:
                        score += 3;
                        break;
                    default:
                        break;
                }
            }
        }

        race_data_arr[i].score = score;

        already_in_array = 0;

        for (j = 0; j < *rider_data_arr_size; j++) {
            if (strcmp(rider_data_arr[j].name, race_data.rider_name) == 0) {
                already_in_array = 1;
                rider_data_arr[j].total_score += score;
            }
        }

        if (!already_in_array) {
            RIDER_DATA rider_data;
            strcpy(rider_data.name, race_data.rider_name);
            strcpy(rider_data.first_name, race_data.first_name);
            strcpy(rider_data.last_name, race_data.last_name);
            rider_data.age = race_data.age;
            strcpy(rider_data.team, race_data.team);
            strcpy(rider_data.country, race_data.country);
            rider_data.total_score = score;

            rider_data_arr[(*rider_data_arr_size)++] = rider_data;
        }
    }

    return 1;
}

/*******************************************/
/* ASSIGNMENTS */
/*******************************************/

/*
 * Assignment 1
 * All belgian riders under 23
 */
void print_assignment_1(int rider_data_arr_size, RIDER_DATA *rider_data_arr) {
    int i, j, riders_size, already_in_array;
    RIDER_DATA *temp_rider_data_arr, rider_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 1. Belgian riders under 23\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    riders_size = 0;
    temp_rider_data_arr = malloc(sizeof(RIDER_DATA) * rider_data_arr_size);

    for (i = 0; i < rider_data_arr_size; i++) {
        rider_data = rider_data_arr[i];

        if (strcmp(rider_data.country, "BEL") == 0 && rider_data.age < 23) {
            already_in_array = 0;

            for (j = 0; j < riders_size; j++) {
                if (strcmp(temp_rider_data_arr[j].name, rider_data.name) == 0)
                    already_in_array = 1;
            }

            if (!already_in_array) {
                temp_rider_data_arr[riders_size++] = rider_data;
            }
        }
    }

    for (i = 0; i < rider_data_arr_size; i++) {
        rider_data = temp_rider_data_arr[i];

        if (strcmp(rider_data.country, "BEL") == 0 && rider_data.age < 23) {
            print_rider_data(rider_data, 1);
        }
    }
}

/*
 * Assignment 2
 * All danish riders who has participated in one or more of the races
 */
void print_assignment_2(int race_data_arr_size,
                        RACE_DATA *race_data_arr) {
    int i, j, number_of_danish_riders;
    RACE_DATA *danish_riders_race_data_array, race_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 2. Danish riders who participated in one or more of the races\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    number_of_danish_riders = 0;
    danish_riders_race_data_array = malloc(sizeof(RACE_DATA) * race_data_arr_size);

    for (i = 0; i < race_data_arr_size; i++) {
        race_data = race_data_arr[i];

        if (strcmp(race_data.country, "DEN") == 0) {
            int already_in_array = 0;

            for (j = 0; j < number_of_danish_riders; j++) {
                if (strcmp(danish_riders_race_data_array[j].rider_name, race_data.rider_name) == 0)
                    already_in_array = 1;
            }

            if (!already_in_array) {
                danish_riders_race_data_array[number_of_danish_riders++] = race_data;
            }
        }
    }

    qsort(danish_riders_race_data_array, (size_t) number_of_danish_riders, sizeof(race_data), sort_danish_riders);

    for (i = 0; i < number_of_danish_riders; i++) {
        race_data = danish_riders_race_data_array[i];
        print_race_data_for_rider(race_data, 1);
    }

    free(danish_riders_race_data_array);
}

/*
 * Assignment 3
 * The 10 riders who has got the most points
 */
void print_assignment_3(int rider_data_arr_size,
                        RIDER_DATA *rider_data_arr) {
    int i;
    RIDER_DATA rider_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 3. The 10 riders who got the most points\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    qsort(rider_data_arr, (size_t) rider_data_arr_size, sizeof(rider_data), sort_rider_scores);

    for (i = 0; i < 10; i++) {
        rider_data = rider_data_arr[i];
        print_rider_data(rider_data, 0);
    }
}

/*
 * Assignment 4
 * Which team has got the most riders with OTL or DNF for each race
 */
void print_assignment_4(int rider_data_arr_size,
                        int race_data_arr_size,
                        RIDER_DATA *rider_data_arr,
                        RACE_DATA *race_data_arr) {
    int i, j, k, l,
            number_of_teams,
            number_of_races;
    TEAM_DATA *team_data_array;
    char **race_names;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 4. Team who has the most riders as OTL or DNF in each race\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    /* Get teams */
    team_data_array = malloc(sizeof(TEAM_DATA) * rider_data_arr_size);
    number_of_teams = get_teams(rider_data_arr_size, rider_data_arr, team_data_array);

    /* Get race names */
    race_names = malloc(sizeof(RACE_DATA) * race_data_arr_size);
    number_of_races = get_races(race_data_arr_size, race_data_arr, race_names);

    for (i = 0; i < number_of_races; i++) {
        for (j = 0; j < race_data_arr_size; j++) {
            if (j == 0) {
                for (l = 0; l < number_of_teams; l++) {
                    team_data_array[l].riders_out = 0;
                }
            }

            for (k = 0; k < number_of_teams; k++) {
                if (strcmp(race_data_arr[j].race, race_names[i]) == 0 &&
                    strcmp(race_data_arr[j].team, team_data_array[k].name) == 0 &&
                    (strcmp(race_data_arr[j].ranking, "OTL") == 0 || strcmp(race_data_arr[j].ranking, "DNF") == 0)
                        ) {
                    team_data_array[k].riders_out++;
                }
            }
        }

        qsort(team_data_array, (size_t) number_of_teams, sizeof(TEAM_DATA), sort_teams);

        printf("%-49s%-4s%4d\n", race_names[i], team_data_array[0].name, team_data_array[0].riders_out);
    }

    free(team_data_array);
    free(race_names);
}

/*
 * Assignment 5
 * The nation with the most points in total
 */
void print_assignment_5(int rider_data_arr_size, RIDER_DATA *rider_data_arr) {
    int i, j,
            nations_size;
    NATION_DATA *nations;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 5. The nation with the most points\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    nations = malloc(sizeof(NATION_DATA) * rider_data_arr_size);
    nations_size = get_nations(rider_data_arr_size, rider_data_arr, nations);

    for (i = 0; i < rider_data_arr_size; i++) {
        for (j = 0; j < nations_size; j++) {
            if (strcmp(rider_data_arr[i].country, nations[j].name) == 0) {
                nations[j].total_score += rider_data_arr[i].total_score;
                nations[j].total_age += rider_data_arr[i].age;
                break;
            }
        }
    }

    qsort(nations, (size_t) nations_size, sizeof(NATION_DATA), sort_nations);

    printf("%s\n", nations[0].name);

    free(nations);
}

/*
 * Assignment 6
 * Median time for each race
 */
void print_assignment_6(int race_data_arr_size,
                        RACE_DATA *race_data_arr,
                        int only_median) {
    int i, j,
            number_of_races,
            median_index;
    char **race_names;
    RACE_DATA *race_data_array_single_race;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 6. The median time for each race\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    race_names = malloc(sizeof(char) * RACE_NAME_SIZE * race_data_arr_size);
    race_data_array_single_race = malloc(sizeof(RACE_DATA) * race_data_arr_size);

    number_of_races = get_races(race_data_arr_size, race_data_arr, race_names);

    for (i = 0; i < number_of_races; i++) {
        char *race_name = race_names[i];

        int race_data_array_single_race_counter = get_riders_who_has_completed_the_race(race_data_arr_size,
                                                                                        race_data_arr,
                                                                                        race_data_array_single_race,
                                                                                        race_name);

        TIME_DATA *times = malloc(sizeof(TIME_DATA) * race_data_array_single_race_counter);
        int times_size = 0;

        for (j = 0; j < race_data_array_single_race_counter; j++) {
            TIME_DATA time;
            sscanf(race_data_array_single_race[j].time, "%d:%d:%d", &time.tm_hour, &time.tm_min, &time.tm_sec);
            times[times_size++] = time;
        }

        median_index =
                (race_data_array_single_race_counter / 2) +
                (race_data_array_single_race_counter % 2 == 0 ? -1 : 0);

        if (i != 0)
            printf("\n");
        printf("%s\n\n", race_name);

        for (j = 0; j < times_size; j++) {
            TIME_DATA time = times[j];

            if ((only_median && j == median_index) || only_median == 0) {
                if (j == median_index && !only_median) {
                    printf("\n");
                }

                printf("%-3d ", j + 1);

                if (j == median_index) {
                    printf("Median ");
                }

                printf("%d:%02d:%02d\n", time.tm_hour, time.tm_min, time.tm_sec);

                if (j == median_index && !only_median) {
                    printf("\n");
                }
            }
        }

        free(times);
    }

    free(race_names);
    free(race_data_array_single_race);
}

/***********************************/
/* TOOL FUNCTIONS */
/***********************************/

/* Split a string with a given splitter */
int split_string(char **strings, const char *str, const char *splitter) {
    int str_counter = 0;
    char *word;
    word = strtok((char *) str, splitter);
    while (word != NULL) {
        strings[str_counter++] = word;
        word = strtok(NULL, splitter);
    }
    return str_counter;
}

/* Helper for the string_to_int function */
int string_to_int_helper(const char *first, const char *last, const int str_length) {
    return (int) (last >= first && isdigit(*last)
                  ? (*last - '0') * pow(10, (int) (str_length - (last - first + 1))) +
                    string_to_int_helper(first, last - 1, str_length)
                  : 0);
}

/* Convert string to int with no given length */
int string_to_int(const char *str) {
    return string_to_int_helper(str, str + strlen(str) - 1, (const int) strlen(str));
}

/* Check if a string only has upper case letters */
int is_upper_case(const char *str) {
    return *str == '\0' ? 1 :
           (islower(*str) ? 0 : is_upper_case(str + 1));
}

/* Helper for the make_word_proper function */
void make_word_proper_helper(char *str, int str_len) {
    if (*str != '\0') {
        *str = strlen(str) == str_len ? toupper(*str) : tolower(*str);
        make_word_proper_helper(str + 1, str_len);
    }
}

/* Set the letter to upper and the rest to lower */
void make_word_proper(char *str) {
    make_word_proper_helper(str, (int) strlen(str));
}

/* Trim end of string from ' ' and '0' */
void trim_end(char *str) {
    char *last_char = str + strlen(str) - 1;
    if (*last_char == ' ' || *last_char == '0') {
        *last_char = '\0';
        trim_end(str);
    }
}

/* Get number of lines in a file */
int get_number_of_lines_file(const char *file_name) {
    int ch = 0, lines = 1;
    FILE *fp;

    fp = fopen(file_name, "r");

    if (fp == NULL)
        return 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);

    return lines;
}

/* Open a file and count the lines */
FILE *open_file(int *number_of_lines, const char *file_name) {
    FILE *fp;

    *number_of_lines = get_number_of_lines_file(file_name);

    fp = fopen(file_name, "r");

    if (fp == NULL) {
        printf("\nCould not read file: \"%s\"\n", file_name);
        return NULL;
    }

    return fp;
}

/***********************************/
/* HELPER FUNCTIONS */
/***********************************/

/* Get riders who completed a given race */
int get_riders_who_has_completed_the_race(int race_data_array_counter, RACE_DATA *race_data_array,
                                          RACE_DATA *race_data_array_single_race,
                                          char *race) {
    int i, race_data_array_single_race_counter;
    RACE_DATA race_data;

    race_data_array_single_race_counter = 0;

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];
        if (strcmp(race_data.race, race) == 0 && strcmp(race_data.ranking, "OTL") != 0 &&
            strcmp(race_data.ranking, "DNF") != 0) {
            race_data_array_single_race[race_data_array_single_race_counter++] = race_data;
        }
    }

    return race_data_array_single_race_counter;
}

/* Get number of riders who completed a given race */
int get_number_of_riders_who_completed_the_race(int race_data_arr_size,
                                                RACE_DATA *race_data_array,
                                                char *race) {
    int i, number;
    RACE_DATA race_data;

    number = 0;

    for (i = 0; i < race_data_arr_size; i++) {
        race_data = race_data_array[i];
        if (strcmp(race_data.race, race) == 0 && strcmp(race_data.ranking, "OTL") != 0 &&
            strcmp(race_data.ranking, "DNF") != 0)
            number++;
    }

    return number;
}

/* Get all the nations in the races */
int get_nations(int rider_data_arr_size, RIDER_DATA *rider_data_array, NATION_DATA *nations) {
    int i, j, nations_counter;
    NATION_DATA nation;

    nations_counter = 0;

    for (i = 0; i < rider_data_arr_size; i++) {
        int already_contains_nation = 0;
        for (j = 0; j < nations_counter; j++) {
            if (strcmp(nations[j].name, rider_data_array[i].country) == 0)
                already_contains_nation = 1;
        }

        if (!already_contains_nation) {
            strcpy(nation.name, rider_data_array[i].country);
            nations[nations_counter++] = nation;
        }
    }

    return nations_counter;
}

/* Get all the race names */
int get_races(int race_data_arr_size, RACE_DATA *race_data_arr, char **race_names) {
    int i, j,
            race_names_counter,
            already_contains_race_name;
    char *temp_race_name, *race_name;

    race_names_counter = 0;

    for (i = 0; i < race_data_arr_size; i++) {
        race_name = race_data_arr[i].race;
        already_contains_race_name = 0;
        for (j = 0; j < race_names_counter; j++) {
            temp_race_name = race_names[j];

            if (strcmp(race_name, temp_race_name) == 0) {
                already_contains_race_name = 1;
                break;
            }
        }

        if (!already_contains_race_name) {
            if (strcmp(race_name, "") != 0)
                race_names[race_names_counter++] = race_name;
        }
    }

    return race_names_counter;
}

/* Get all the teams */
int get_teams(int rider_data_arr_size, RIDER_DATA *rider_data_array, TEAM_DATA *team_data_array) {
    int i, j, team_data_array_counter;
    TEAM_DATA team_data;

    team_data_array_counter = 0;

    for (i = 0; i < rider_data_arr_size; i++) {
        int already_contains_team = 0;
        for (j = 0; j < team_data_array_counter; j++) {
            if (strcmp(team_data_array[j].name, rider_data_array[i].team) == 0)
                already_contains_team = 1;
        }

        if (!already_contains_team) {
            strcpy(team_data.name, rider_data_array[i].team);
            team_data_array[team_data_array_counter++] = team_data;
        }
    }

    return team_data_array_counter;
}

/* Print race data */
int print_race_data_for_rider(RACE_DATA race_data, int format) {
    switch (format) {
        case 0:
            printf("%-49s%-49s%-4d%-4s%-4s%-4s%-8s%-3d\n", race_data.race, race_data.rider_name, race_data.age,
                   race_data.team,
                   race_data.country, race_data.ranking, race_data.time, race_data.score);
            break;
        case 1:
            printf("%-49s %-4d%-4s\n", race_data.rider_name, race_data.age, race_data.team);
            break;
        default:
            break;
    }

    return 0;
}

/* Print rider data */
int print_rider_data(RIDER_DATA rider_data, int format) {
    switch (format) {
        case 0:
            printf("%-49s%-4d%-4s%-4s%-4d\n", rider_data.name, rider_data.age, rider_data.team, rider_data.country,
                   rider_data.total_score);
            break;
        case 1:
            printf("%-49s %-4d%-4s\n", rider_data.name, rider_data.age, rider_data.team);
            break;
        default:
            break;
    }

    return 0;
}

/***********************************/
/* SORT FUNCTIONS */
/***********************************/

/* Sort nations highest total score first if equal then lowest age first */
int sort_nations(const void *elem1, const void *elem2) {
    const NATION_DATA *first = elem1, *second = elem2;

    if (first->total_score < second->total_score)
        return 1;
    else if (first->total_score > second->total_score)
        return -1;
    else {
        if (first->total_age > second->total_age)
            return 1;
        else if (first->total_age < second->total_age)
            return -1;
        else
            return 0;
    }
}

/* Sort teams highest number of riders out first */
int sort_teams(const void *elem1, const void *elem2) {
    const TEAM_DATA *first = elem1, *second = elem2;

    if (first->riders_out < second->riders_out)
        return 1;
    else if (first->riders_out > second->riders_out)
        return -1;
    else
        return 0;
}

/* Sort rider scores highest total score first if equal the lowest age first */
int sort_rider_scores(const void *elem1, const void *elem2) {
    const RIDER_DATA *first = elem1, *second = elem2;
    int res = 0;

    if (first->total_score < second->total_score)
        res = 1;
    else if (first->total_score > second->total_score)
        res = -1;
    else {
        if (first->age < second->age)
            res = -1;
        else if (first->age > second->age)
            res = 1;
        else {
            return strcmp(first->last_name, second->last_name);
        }
    }

    return res;
}

/* Sort danish riders according to team names */
int sort_danish_riders(const void *elem1, const void *elem2) {
    const RACE_DATA *first = elem1, *second = elem2;
    int res = strcmp(first->team, second->team);

    if (res == 0) {
        res = strcmp(first->first_name, second->first_name);
    }

    return res;
}
