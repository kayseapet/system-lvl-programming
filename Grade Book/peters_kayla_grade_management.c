/*
    Grade Management Program
    Kayla Peters, July 17 2025
    -program to manage student grades in a class, where user can create a class roster, input grades for each student, and calculate & display student grades.
        *Course structure: structure to store the course name, number, and an array of students
        *Student structure: object containing a student's name, ID number, exactly five assignment grades, their average grade, and letter grade.
    1. User inputs class size, and each student's data (name, ID, 5 grades)
    2. Program calculates the average grade & correlating letter grade
    3. Program displays table with the data given.
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct Student
{
    char name[50];
    int studentID;
    float grades[5];
    float avgGrade;
    char letterGrade;
};

struct Course
{
    //similar to a 'class' in java for OOP
    int courseNum; 
    char courseName[50];
    struct Student *roster; //ptr to list of students[0]

};

// calcAvg: given a pointer to a student's array of grades, the function will calculate the average and return a float
float calcAvg (float *ptr)
{
    // we know for a fact there are only 5 grades, so we can do a loop adds each grade together and then divde by five at the end
    float sum;
    int i;
    for(i = 0; i< 5 ; i++)
    {
        float grade = *(ptr + i) ;
        sum += grade;
    }

    return (sum/5);
    
}

// returns the letter grade of the grade percentage given
char letGrade (float avg) 
{
    if (avg >= 90.00)
    {
        return 'A';
    }
    else if (avg <= 89.99 && avg >= 80.00)
    {
        return 'B';
    }
   else if (avg <= 79.99 && avg >= 70.00)
    {
        return 'C';
    }
    else if (avg <= 69.99 && avg >= 60.00)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

// displays the whole course, given the ptr to the Course & the length of the roster.
void displayClass(struct Course *class, int length)
{
    
    //print course name, num, and the amount of students
    printf ("Course #: %d\n", (*class).courseNum);
    printf("Course Name: %s\n",(*class).courseName);
    printf("# of Students: %d\n",length);

    //print the table header & divider
    printf("%-25s %14s %14s %14s %14s %14s %14s %7s %10s \n", 
     "Name", "Student ID", "Assignment 1", "Assignment 2" ,"Assignment 3", "Assignment 4", "Assignment 5", "Avg", "Letter");
    printf("---------------------------\n");

    //print each student based on the roster
    struct Student *rster = (*class).roster;
    struct Student stu; // will represent the student we are printing the info of
    int i;
    for(i = 0; i < length; i++)
    {
        stu = *(rster + i);
        // print each of column using the same spacing so it'll form a table
        printf("%-30s %10d %12.2f %12.2f %12.2f %12.2f %12.2f %7.1f %c\n",
            stu.name, stu.studentID, stu.grades[0], stu.grades[1], stu.grades[2], stu.grades[3], stu.grades[4], stu.avgGrade, stu.letterGrade);
    }

   printf("---------------------------\n");
}

int main()
{

    // 1. prompt user to enter the Course Name, nnumber, and total number of students in the class
        struct Course class;
        printf("Enter the course number:\n :> ");
        scanf("%d", &class.courseNum);
        getchar();

        char str[50];
        printf("Enter the course name:\n :> ");
        fgets(str, sizeof(str), stdin);
        str[50] = '\0'; // to ensure the string will end when it's supposed to.
        strcpy(class.courseName, str);
       

        int class_len;
        printf("Enter the number of students in the course:\n :> ");
        scanf("%d", &class_len);
        // use that num to dynamically allocate an array of students, then change class roster ptr.
        struct Student * arr;
        arr = (struct Student *) malloc(sizeof(struct Student)* class_len);
        class.roster = arr;

    // 2. create a loop that accepts the required data for each student
        int s;
        for(s =0; s < class_len; s++)
        {
            struct Student *stu = (class.roster + s); // ptr that represents where this student's info will go in the roster.

            printf("Student %d Details\n", s+1);

            printf("Enter Student ID:\n :> ");
            scanf("%d", &((*stu).studentID));
            getchar();


            printf("Enter Student Name:\n :> ");
            fgets((*stu).name, sizeof((*stu).name), stdin);
            (*stu).name[50] = '\0';

            //enter all five grades
            printf(" Enter Grades \n");

            float grade;
            int i;
            for (i = 0; i < 5 ; i++)
            {   
                printf("\nAssignment %d:\n :>  ",i + 1);
                scanf("%f", &grade);
                (*stu).grades[i] = grade;
            }

    // 3. calculate the average grade for the student, and the letter grade
         // i want to do this here so we dont have to go back and compute them all at the end.
            printf("Now calculating average...\n");
            (*stu).avgGrade = calcAvg(&((*stu).grades[0]));
            printf("Complete!\n");

            printf("Now Computing Letter Grade...\n");
            (*stu).letterGrade = letGrade((*stu).avgGrade);
            printf("Complete!\n");
            

            // now we do the same thing for the rest of the students needed to complete the roster.
        }

    // 4. Display a formatted table showing the information of all the students.
        displayClass(&class,class_len);
        return 0;
    /*
    //testing the calcavg works as expected.
    struct Student stu;
    float grade;
    int len = sizeof(stu.grades) / sizeof(stu.grades[0]);
    int i;
    for (i = 0; i < 5 ; i++)
    {   
        printf("\nGrade %d: ",i + 1);
        scanf("%f", &grade);
        stu.grades[i] = grade;
        printf("Grade successfully accepted!\n");
    }

    printf("Now calculating average...\n");
    stu.avgGrade = calcAvg(&stu.grades[0]);
    printf("average grade: %.2f", stu.avgGrade);
    */
}



