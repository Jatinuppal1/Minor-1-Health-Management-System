#include <stdio.h>

#include <stdlib.h>

#include <mysql.h>

#include <conio.h>

#include <string.h>

#include <windows.h>

#include <stdbool.h>

// MYSQL Connection Variables
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

// MySQL Credentials
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "hms";


void pass_entry(char *passwrd)      //Password Entry
{

    int i =0;

    do{

        passwrd[i] = getch();
        printf("*");

    } while(passwrd[i++] != 13 && i < 10);

    printf("\b ");
    passwrd[i-1] = '\0';

}

bool hospital_register()        //It will return true if registered successfully and false if not.
{

    char query[150];
    unsigned int h_id;
    char h_name[50];
    char address[50];
    char city[50];
    char district[50];
    char state[50];
    unsigned long int contact;
    unsigned int bed_avail;
    char passwrd[10];

    conn = mysql_init(NULL);        //Initialization of connection object.

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))    // Establishing a connection with Database.
   {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    if (mysql_query(conn, "SELECT Hospital_ID FROM hospital_details ORDER BY Hospital_ID DESC LIMIT 1"))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);

    if( mysql_num_rows(result))
    {

        row = mysql_fetch_row(result);
        h_id = atoi(row[0]) + 1;

    } else h_id = 30001;

    mysql_free_result(result);

    system("cls");
    printf("\n ____________________ Hospital Registration ____________________\n\n");
    printf("\n Hospital ID :\t%d\n", h_id);

    printf("\n Hospital Name :\t");
    scanf("%[^\n]s",h_name);
    fflush(stdin);

    printf(" Address (Street No.) :\t");
    scanf("%[^\n]s", &address);
    fflush(stdin);

    printf(" City :\t");
    scanf("%[^\n]s", &city);
    fflush(stdin);

    printf(" District :\t");
    scanf("%[^\n]s", &district);
    fflush(stdin);

    printf(" State :\t");
    scanf("%[^\n]s", &state);
    fflush(stdin);

    printf(" Contact :\t");
    scanf("%ld", &contact);

    printf(" Available Bed :\t");
    scanf("%d", &bed_avail);
    fflush(stdin);

    do {

            char temp[10];

            printf("\n\n Password (Max 10) :\t");
            pass_entry(passwrd);
            fflush(stdin);

            printf("\n Re-Type Password (Max 10) :\t");
            pass_entry(temp);
            fflush(stdin);

            if(!strcmp( passwrd, temp))
                break;

    } while( true );

    sprintf(query,"INSERT INTO hospital_details VALUES(%d,'%s','%s','%s','%s','%s',%ld,%d,'%s')", h_id, h_name, address, city, district, state, contact, bed_avail, passwrd);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    mysql_close(conn);
    return true;

}

bool doctor_register()
{

    int num_fields;
    char query[150];
    unsigned int d_id;
    char d_name[50];
    char specltn[50];
    char address[50];
    char city[50];
    char district[50];
    char state[50];
    char gender[15];
    unsigned int age;
    unsigned long int contact;
    int h_id;
    char passwrd[10];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    if (mysql_query(conn, "SELECT Doctor_ID FROM doctor_details ORDER BY Doctor_ID DESC LIMIT 1"))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);

    if( mysql_num_rows(result))
    {

        row = mysql_fetch_row(result);
        d_id = atoi(row[0]) + 1;

    } else d_id = 20001;

    mysql_free_result(result);

    system("cls");
    printf("\n ____________________ Doctor Registration ____________________\n\n");
    printf("\n Doctor ID :\t%d\n", d_id);

    printf("\n Doctor Name :\t");
    scanf("%[^\n]s",d_name);
    fflush(stdin);

    printf(" Specialization :\t");
    scanf("%[^\n]s",specltn);
    fflush(stdin);

    printf(" Address (Street No.) :\t");
    scanf("%[^\n]s", &address);
    fflush(stdin);

    printf(" City :\t");
    scanf("%[^\n]s", &city);
    fflush(stdin);

    printf(" District :\t");
    scanf("%[^\n]s", &district);
    fflush(stdin);

    printf(" State :\t");
    scanf("%[^\n]s", &state);
    fflush(stdin);

    printf(" Contact :\t");
    scanf("%ld", &contact);

    printf(" Age :\t");
    scanf("%d", &age);
    fflush(stdin);

    printf(" Gender :\t");
    scanf("%[^\n]s",gender);
    fflush(stdin);

    sprintf(query,"SELECT Hospital_ID, Hospital_Name FROM hospital_details WHERE upper(City) = '%s'", strupr(city));

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    printf("\n List Of Hospitals :\n");
    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
            printf("%s\t", row[i] ? row[i] : "NULL");

        printf("\n");

    }

    mysql_free_result(result);

    printf(" Enter Hospital_ID You are Associated with :\t");
    scanf("%d", &h_id);
    fflush(stdin);

    do {

            char temp[10];

            printf("\n\n Password (Max 10) :\t");
            pass_entry(passwrd);
            fflush(stdin);

            printf("\n Re-Type Password (Max 10) :\t");
            pass_entry(temp);
            fflush(stdin);

            if(!strcmp( passwrd, temp))
                break;

    } while( true );

    sprintf(query,"INSERT INTO doctor_details VALUES(%d,'%s','%s','%s','%s','%s','%s',%ld,%d,'%s',%d,'%s')", d_id, d_name, specltn, address, city, district, state, contact, age, gender, h_id, passwrd);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    mysql_close(conn);
    return true;

}

bool patient_register()
{

    char query[150];
    unsigned int p_id;
    char p_name[50];
    char address[50];
    char city[50];
    char district[50];
    char state[50];
    char gender[15];
    unsigned int age;
    unsigned long int contact;
    char passwrd[10];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    if (mysql_query(conn, "SELECT Patient_ID FROM patient_details ORDER BY Patient_ID DESC LIMIT 1"))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);

    if( mysql_num_rows(result))
    {

        row = mysql_fetch_row(result);
        p_id = atoi(row[0]) + 1;

    }  else p_id = 10001;

    mysql_free_result(result);

    system("cls");
    printf("\n ____________________ Patient Registration ____________________\n\n");
    printf("\n Patient ID :\t%d\n", p_id);

    printf("\n Patient Name :\t");
    scanf("%[^\n]s",&p_name);
    fflush(stdin);

    printf(" Address (Street No.) :\t");
    scanf("%[^\n]s", &address);
    fflush(stdin);

    printf(" City :\t");
    scanf("%[^\n]s", &city);
    fflush(stdin);

    printf(" District :\t");
    scanf("%[^\n]s", &district);
    fflush(stdin);

    printf(" State :\t");
    scanf("%[^\n]s", &state);
    fflush(stdin);

    printf(" Contact :\t");
    scanf("%ld", &contact);

    printf(" Age :\t");
    scanf("%d", &age);
    fflush(stdin);

    printf("Gender :\t");
    scanf("%[^\n]s",gender);
    fflush(stdin);

    do {

            char temp[10];

            printf("\n\n Password (Max 10) :\t");
            pass_entry(passwrd);
            fflush(stdin);

            printf("\n Re-Type Password (Max 10) :\t");
            pass_entry(temp);
            fflush(stdin);

            if(!strcmp( passwrd, temp))
                break;

    } while( true );

    sprintf(query,"INSERT INTO patient_details VALUES(%d,'%s','%s','%s','%s','%s',%ld,%d,'%s','%s')", p_id, p_name, address, city, district, state, contact, age, gender, passwrd);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"CREATE VIEW %d_Records AS SELECT Diagnosis_Date, Doctor_ID, Disease, Prescription, Medicines FROM medical_records WHERE Patient_ID = %d", p_id, p_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      sprintf(query,"DELETE FROM patient_details WHERE Patient_ID = %d", p_id);
      if (mysql_query(conn, query))
        {

          printf("\n Failed to execute query. Error: %s", mysql_error(conn));
          Sleep(1500);
          return false;

        }
      Sleep(1500);
      return false;

    }

    mysql_close(conn);
    return true;

}

bool pharmacy_register()        //It will return true if registered successfully and false if not.
{

    int num_fields;
    char query[150];
    unsigned int ph_id;
    char ph_name[50];
    char address[50];
    char city[50];
    char district[50];
    char state[50];
    unsigned int h_id;
    unsigned long int contact;
    char passwrd[10];

    conn = mysql_init(NULL);        //Initialization of connection object.

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))    // Establishing a connection with Database.
   {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    if (mysql_query(conn, "SELECT Pharmacy_ID FROM pharmacy_details ORDER BY Pharmacy_ID DESC LIMIT 1"))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);

    if( mysql_num_rows(result))
    {

        row = mysql_fetch_row(result);
        ph_id = atoi(row[0]) + 1;

    } else ph_id = 40001;

    mysql_free_result(result);

    system("cls");
    printf("\n ____________________ Pharmacy Registration ____________________\n\n");
    printf("\n Pharmacy ID :\t%d\n", ph_id);

    printf("\n Pharmacy Name :\t");
    scanf("%[^\n]s",ph_name);
    fflush(stdin);

    printf(" Address (Street No.) :\t");
    scanf("%[^\n]s", address);
    fflush(stdin);

    printf(" City :\t");
    scanf("%[^\n]s", city);
    fflush(stdin);

    printf(" District :\t");
    scanf("%[^\n]s", district);
    fflush(stdin);

    printf(" State :\t");
    scanf("%[^\n]s", state);
    fflush(stdin);

    printf(" Contact :\t");
    scanf("%ld", &contact);

    sprintf(query,"SELECT Hospital_ID, Hospital_Name FROM hospital_details WHERE upper(City) = '%s'", strupr(city));

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    printf("\n List Of Hospitals :\n");
    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
            printf("%s\t", row[i] ? row[i] : "NULL");

        printf("\n");

    }

    mysql_free_result(result);

    printf(" Enter Hospital_ID You are Associated with :\t");
    scanf("%d", &h_id);
    fflush(stdin);

    do {

            char temp[10];

            printf("\n\n Password (Max 10) :\t");
            pass_entry(passwrd);
            fflush(stdin);

            printf("\n Re-Type Password (Max 10) :\t");
            pass_entry(temp);
            fflush(stdin);

            if(!strcmp( passwrd, temp))
                break;

    } while( true );

    sprintf(query,"INSERT INTO pharmacy_details VALUES(%d,'%s','%s','%s','%s','%s',%ld,%d,'%s')", ph_id, ph_name, address, city, district, state, contact, h_id, passwrd);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    mysql_close(conn);
    return true;

}

bool hospital_login( int h_id, char passwrd[10] )
{

    char query[150];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Password from hospital_details WHERE Hospital_ID = %d",h_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    if( strcmp(passwrd, row[0]))
        return false;

    mysql_free_result(result);
    mysql_close(conn);
    return true;

}

bool doctor_login(int d_id, char passwrd[10])
{

    char query[150];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Password from doctor_details WHERE Doctor_ID = %d",d_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    if( strcmp(passwrd, row[0]))
        return false;

    mysql_free_result(result);
    mysql_close(conn);
    return true;

}

bool patient_login( int p_id, char passwrd[10] )
{

    char query[150];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Password from patient_details WHERE Patient_ID = %d",p_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    if( strcmp(passwrd, row[0]))
        return false;

    mysql_free_result(result);
    mysql_close(conn);
    return true;

}

bool pharmacy_login( int ph_id, char passwrd[10] )
{

    char query[150];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Password from pharmacy_details WHERE Pharmacy_ID = %d",ph_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    if( strcmp(passwrd, row[0]))
        return false;

    mysql_free_result(result);
    mysql_close(conn);
    return true;

}

void hospital()
{

    char query[150];
    int h_id;
    int num_fields;
    char passwrd[10];
    bool condition = true;

    while( condition )
    {

        system("cls");
        printf("\n ____________________ HOSPITALS ____________________\n\n"
               " 1. Hospital Registration\n 2. Hospital Login\n");
        printf("Enter Choice [1 or 2] :\t");
        fflush(stdin);

        switch(getche())
        {
            case '1':

                fflush(stdin);

                while(!hospital_register())
                {

                    system("cls");
                    printf("\n\n *!!!! Registration Unsuccessful !!!!*"
                           "\n Press ENTER to re-try and any other key to main menu.");

                    if(getch() != 13)
                        return;

                    fflush(stdin);

                }

                fflush(stdin);
                system("cls");
                printf("\n ************ Registration Successful ************\n");
                Sleep(1500);


            case '2':

                while(condition)
                {

                    system("cls");
                    printf("\n ____________________ Hospital Login ____________________\n\n");

                    printf("\n Hospital ID :\t");
                    scanf("%d", &h_id);
                    fflush(stdin);

                    printf(" Password (Max 10) :\t");
                    pass_entry(passwrd);
                    fflush(stdin);

                    if(!hospital_login(h_id,passwrd))
                    {

                        system("cls");
                        printf("\n\n *!!!! Login Unsuccessful !!!!*"
                               "\n Press ENTER to re-try and any other key to main menu.");

                        if(getch() != 13)
                            return;
                        else {
                                fflush(stdin);
                                continue;
                        }

                    }

                    condition = false;

                }

                system("cls");
                printf("\n ************* Login Successful *************\n");
                Sleep(1500);
                break;


            default:

                printf("\n !!Wrong Choice!!");
                condition = true;
                Sleep(1000);

        }

    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Hospital_ID, Hospital_Name, Address, City, District, State, Contact, Bed_Availability FROM hospital_details WHERE Hospital_ID = %d", h_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    system("cls");

    printf("\n ____________________ Hospital Details ____________________\n\n");

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {
            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");
        }

    }

    mysql_free_result(result);

    int beds, no_patients;
    char disease[50], city[50];
    char f_date[12], t_date[11];

    printf("\n\n 1. Update Bed Available Tally\n 2. Generate Report\n"
           " Press Enter to go to main menu."
           "\nEnter [ 1 , 2 ] :\t");
    switch(getche())
    {
        case '1':

            printf("\n Beds Available :\t");
            scanf("%d",&beds);
            sprintf(query,"UPDATE hospital_details SET Bed_Availability = %d WHERE Hospital_ID = %d", h_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return false;

            }

            break;

        case '2':

            printf("\n\n Disease Name :\t");
            scanf("%[^\n]s",disease);
            fflush(stdin);
            printf("\n City Name :\t");
            scanf("%[^\n]s",city);
            fflush(stdin);
            printf("\n DATE\n  From :\t");
            scanf("%s",f_date);
            fflush(stdin);
            printf("  To :\t");
            scanf("%s",t_date);
            fflush(stdin);

            sprintf(query,"SELECT COUNT(disease) FROM medical_records WHERE disease = '%s' AND Diagnosis_Date >= '%s' AND Diagnosis_Date <= '%s' AND Patient_ID IN (SELECT Patient_ID from patient_details where City = '%s')", disease, f_date, t_date, city);

            if (mysql_query(conn, query))
            {

                printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                Sleep(1500);
                return false;

            }

            result = mysql_store_result(conn);
            row = mysql_fetch_row(result);
            no_patients = atoi(row[0]);
            mysql_free_result(result);

            printf("\n\n\n\n____________________ Report ____________________\n");
            printf("\n\nDisease :\t%s",disease);
            printf("\n\n DATE :\t%s  To  %s", f_date, t_date);
            printf("\n\n No. Of Patients Affected :\t%d", no_patients);
            printf("\n\n City :\t%s",city);

        case 13:

            break;


        default:

            printf("\n !!Wrong Choice!!");
            Sleep(1000);

    }

    mysql_close(conn);

    printf("\n\nPress any key to continue.");
    getch();

}

void doctor()
{

    char query[150];
    int d_id;
    char passwrd[10];
    int num_fields;
    bool condition = true;

    while( condition )
    {

        system("cls");
        printf("\n ____________________ Doctors ____________________\n\n"
               " 1. Doctor Registration\n 2. Doctor Login\n");
        printf(" Enter Choice [1 or 2] :\t");
        fflush(stdin);

        switch(getche())
        {

            case '1':

                fflush(stdin);

                while(!doctor_register())
                {

                    system("cls");
                    printf("\n\n *!!!! Registration Unsuccessful !!!!*"
                           "\n Press ENTER to re-try and any other key to main menu.");

                    if(getch() != 13)
                        return;

                    fflush(stdin);

                }

                fflush(stdin);
                system("cls");
                printf("\n ************ Registration Successful ************\n");
                Sleep(1500);


            case '2':

                while(condition)
                {
                    system("cls");
                    printf("\n ____________________ Doctor Login ____________________\n\n");

                    printf("\n Doctor ID :\t");
                    scanf("%d", &d_id);
                    fflush(stdin);

                    printf(" Password (Max 10) :\t");
                    pass_entry(passwrd);
                    fflush(stdin);

                    if(!doctor_login(d_id,passwrd))
                    {

                        system("cls");
                        printf("\n\n *!!!! Login Unsuccessful !!!!*"
                               "\n Press ENTER to re-try and any other key to main menu.");

                        if(getch() != 13)
                            return;
                        else {
                                fflush(stdin);
                                continue;
                        }

                    }

                    condition = false;

                }

                system("cls");
                printf("\n ************* Login Successful *************\n");
                Sleep(1500);
                break;


            default:

                printf("\n !!Wrong Choice!!");
                condition = true;
                Sleep(1000);

        }

    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Doctor_ID, Doctor_Name, Specialization, Address, City, District, State, Contact, Age, Gender FROM doctor_details WHERE Doctor_ID = %d", d_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    system("cls");

    printf("\n ____________________Doctor Details____________________\n\n");

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {
            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");
        }

    }

    mysql_free_result(result);

    sprintf(query,"SELECT Hospital_Name FROM hospital_details WHERE Hospital_ID IN (SELECT Hospital_ID FROM doctor_details WHERE Doctor_ID = %d)", d_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {
            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");
        }

    }

    mysql_free_result(result);

    int p_id;
    char a_date[10];

    printf("\n\n 1. Show Appointments\n 2. Medical Prescription\n"
           " Press Enter to go to main menu."
           "\nEnter [ 1 , 2 ] :\t");
    switch(getche())
    {

        case '1':

            fflush(stdin);

            sprintf(query,"SELECT Appointment_Date, Patient_ID, STATUS FROM appointment_details WHERE Doctor_ID = %d AND DATEDIFF(Appointment_Date,CURDATE()) >= 0", d_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);
            fields = mysql_fetch_fields(result);
            num_fields = mysql_num_fields(result);

            printf("\n ____________________ Appointment Details ____________________\n\n");

             if( mysql_num_rows(result))
             {

                while ((row = mysql_fetch_row(result)))
                {

                    for(int i = 0; i < num_fields; i++)
                    {

                        printf("%s :\t",fields[i].name);
                        printf("%s\t", row[i] ? row[i] : "NULL");
                        printf("\n");

                    }

                }

                mysql_free_result(result);

                condition = true;
                while(condition)
                {
                    printf("\n Press '1' to continue changing Status and Enter to save Changes or Proceed.");
                    switch(getch())
                    {
                        case '1':

                            printf("\n\nEnter Appointment Date :\t");
                            scanf("%s",a_date);
                            fflush(stdin);
                            printf("\nEnter Patient ID :\t");
                            scanf("%d",&p_id);
                            fflush(stdin);
                            sprintf(query,"UPDATE appointment_details SET Status ='APPROVED' WHERE Doctor_ID = %d AND Patient_ID = %d AND Appointment_Date = '%s'", d_id, p_id, a_date);

                            if (mysql_query(conn, query))
                            {

                              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                              Sleep(1500);
                              getch();
                              return;

                            }
                            printf("\n\n UPDATED!\n\n");
                            break;

                        case 13:
                            condition = false;
                            break;
                    }
                }


             }  else printf("\n\n NO APPOINTMENTS!\n\n");

            Sleep(1000);
            break;


        case '2':

            fflush(stdin);

            char disease[50];
            char prescrptn[200];
            char medicine[200];

            system("cls");

            printf("\n ____________________ Medical Prescription ____________________\n\n");
            printf("\n Patient ID :\t");
            scanf("%d",&p_id);
            fflush(stdin);

            printf(" Disease :\t");
            scanf("%[^\n]s", &disease);
            fflush(stdin);

            printf(" Prescription :\t");
            scanf("%[^\n]s", &prescrptn);
            fflush(stdin);

            printf(" Medicines :\t");
            scanf("%[^\n]s", &medicine);
            fflush(stdin);

            sprintf(query,"INSERT INTO medical_records VALUES(CURDATE(),%d,%d,'%s','%s','%s')", p_id, d_id, disease, prescrptn, medicine);

            if (mysql_query(conn, query))
            {

                printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                Sleep(1500);
                return false;

            }

            printf("\n Record Added...");
            Sleep(1000);

            sprintf(query,"UPDATE appointment_details SET Status ='COMPLETED' WHERE Doctor_ID = %d AND Patient_ID = %d AND Appointment_Date = CURDATE()", d_id, p_id);

            if (mysql_query(conn, query))
            {

                printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                Sleep(1500);
                return;

            }

            break;


        case 13:

            break;


        default:

            printf("\n Wrong Choice!!\n");
            Sleep(1000);

    }

    mysql_close(conn);

}

void patient()
{

    char query[150];
    int num_fields;
    int p_id;
    char passwrd[10];
    bool condition = true;

    while( condition )
    {

        system("cls");
        printf("\n ____________________ Patient ____________________\n\n"
               " 1. Patient Registration\n 2. Patient Login\n");
        printf(" Enter Choice [1 or 2] :\t");
        fflush(stdin);

        switch(getche())
        {

            case '1':

                fflush(stdin);

                while(!patient_register())
                {

                    system("cls");
                    printf("\n\n *!!!! Registration Unsuccessful !!!!*"
                           "\n Press ENTER to re-try and any other key to main menu.");

                    if(getch() != 13)
                        return;

                    fflush(stdin);

                }

                fflush(stdin);
                system("cls");
                printf("\n ************ Registration Successful ************\n");
                Sleep(1500);


            case '2':

                while(condition)
                {
                    system("cls");
                    printf("\n ____________________ Patient Login ____________________\n\n");

                    printf("\n Patient ID :\t");
                    scanf("%d", &p_id);
                    fflush(stdin);

                    printf(" Password (Max 10) :\t");
                    pass_entry(passwrd);
                    fflush(stdin);

                    if(!patient_login(p_id,passwrd))
                    {

                        system("cls");
                        printf("\n\n *!!!! Login Unsuccessful !!!!*"
                               "\n Press ENTER to re-try and any other key to main menu.");

                        if(getch() != 13)
                            return;
                        else {
                                fflush(stdin);
                                continue;
                        }

                    }

                    condition = false;

                }

                system("cls");
                printf("\n ************* Login Successful *************\n");
                Sleep(1500);
                break;


            default:

                printf("\n !!Wrong Choice!!");
                condition = true;
                Sleep(1000);

        }

    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return;

    }

    sprintf(query,"SELECT Patient_ID, Patient_Name, Address, City, District, State, Contact, Age, Gender FROM patient_details WHERE Patient_ID = %d", p_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    system("cls");

    printf("\n ____________________ Patient Details ____________________\n\n");

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {

            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");

        }

    }

    mysql_free_result(result);
    int d_id;
    char c_date[10], a_date[11];
    //char p_date[10];
    char prescrptn[200];
    char medicine[200];
    char disease[50];

    if (mysql_query(conn, "SELECT CURDATE()"))
    {
        printf("\n Failed to execute query. Error: %s", mysql_error(conn));
        Sleep(1500);
        return;
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    strcpy(c_date,row[0]);

    mysql_free_result(result);

    printf("\n\n 1. Make an Appointment\n 2. Status of Appointment\n 3. View Records\n 4. Add Previous Records\n"
           " Press Enter to go to main menu."
           "\n Enter [ 1, 2, 3, 4 ] :\t");
    switch(getche())
    {
        case '1':

            fflush(stdin);
            sprintf(query,"SELECT a.Doctor_ID, a.Doctor_Name, b.Hospital_Name FROM doctor_details a, hospital_details b WHERE a.City IN (SELECT City FROM patient_details WHERE Patient_ID = %d) AND b.Hospital_ID = a.Hospital_ID", p_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);
            fields = mysql_fetch_fields(result);
            num_fields = mysql_num_fields(result);

            system("cls");

            printf("\n ____________________ Create Appointment ____________________\n\n"
                   " DATE - %s\n\n Available Doctors in your city :\n\n",c_date);

            while ((row = mysql_fetch_row(result)))
            {

                for(int i = 0; i < num_fields; i++)
                {

                    printf(" %s :\t",fields[i].name);
                    printf("%s\n", row[i] ? row[i] : "NULL");

                }

                printf("\n\n");

            }

            mysql_free_result(result);

            printf("\n Enter Appointment Date[yyyy-mm-dd] :\t");
            scanf("%s",a_date);
            printf("\n Enter Doctor ID :\t");
            scanf("%d",&d_id);
            fflush(stdin);

            sprintf(query, "SELECT DATEDIFF('%s','%s') days", a_date, c_date);

            if (mysql_query(conn, query))
            {
                printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                Sleep(1500);
                return;
            }

            result = mysql_store_result(conn);
            row = mysql_fetch_row(result);

            if(atoi(row[0]) < 0)
            {
                printf("\n Appointment Can't be Generated!");
                mysql_free_result(result);
                Sleep(1000);
                return;
            }

            mysql_free_result(result);

            sprintf(query,"SELECT Status FROM appointment_details WHERE Appointment_Date = '%s' AND Doctor_ID = %d AND Patient_ID = %d",a_date,d_id,p_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);

            if( !mysql_num_rows(result))
            {

                sprintf(query,"INSERT INTO appointment_details(Appointment_Date, Doctor_ID, Patient_ID) VALUES('%s',%d,%d)",a_date,d_id,p_id);
                if (mysql_query(conn, query))
                {
                    printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                    Sleep(1500);
                    return;
                }
                printf("\n\t******Appointment Successful*******\n");

            } else printf("\nAppointment Already Exists.");

            mysql_free_result(result);

            printf("\n\n Press any key to continue.");
            getch();
            break;


        case '2':

            fflush(stdin);

            sprintf(query,"SELECT Appointment_Date, Doctor_ID, Status FROM appointment_details WHERE Patient_ID = %d", p_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);
            fields = mysql_fetch_fields(result);
            num_fields = mysql_num_fields(result);

            printf("\n ____________________ Appointment Details ____________________\n\n"
                   " DATE - %s\n",c_date);

             if( mysql_num_rows(result))
             {

                while ((row = mysql_fetch_row(result)))
                {

                    for(int i = 0; i < num_fields; i++)
                    {

                        printf("%s :\t",fields[i].name);
                        printf("%s\t", row[i] ? row[i] : "NULL");
                        printf("\n");

                    }

                }

             }  else printf("\nNO APPOINTMENTS!\n");

            mysql_free_result(result);

            printf("\n\n Press any key to continue.");
            getch();
            break;


        case '3':

            fflush(stdin);
            sprintf(query,"SELECT * FROM %d_Records", p_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);
            fields = mysql_fetch_fields(result);
            num_fields = mysql_num_fields(result);

            system("cls");

            printf("\n ____________________ Medical Records ____________________\n\n"
                   " DATE - %s\n\n",c_date);

            while ((row = mysql_fetch_row(result)))
            {

                for(int i = 0; i < num_fields; i++)
                {

                    printf(" %s :\t",fields[i].name);
                    printf("%s\n", row[i] ? row[i] : "NULL");

                }

                printf("\n\n");

            }

            mysql_free_result(result);

            printf("\n\n Press any key to continue.");
            getch();
            break;


        case '4':

            fflush(stdin);

            sprintf(query,"SELECT a.Doctor_ID, a.Doctor_Name, b.Hospital_Name FROM doctor_details a, hospital_details b WHERE a.City IN (SELECT City FROM patient_details WHERE Patient_ID = %d) AND b.Hospital_ID = a.Hospital_ID", p_id);

            if (mysql_query(conn, query))
            {

              printf("\n Failed to execute query. Error: %s", mysql_error(conn));
              Sleep(1500);
              return;

            }

            result = mysql_store_result(conn);
            fields = mysql_fetch_fields(result);
            num_fields = mysql_num_fields(result);
            condition = true;

            while(condition)
            {
                system("cls");

                printf("\n ____________________ Old Medical Records ____________________\n\n"
                       " DATE - %s\n\n Available Doctors in your city :\n\n",c_date);

                while ((row = mysql_fetch_row(result)))
                {

                    for(int i = 0; i < num_fields; i++)
                    {

                        printf(" %s :\t",fields[i].name);
                        printf("%s\n", row[i] ? row[i] : "NULL");

                    }

                    printf("\n\n");

                }

                printf("\n Patient ID :\t%d\n", p_id);

                printf("\n Issued Date :\t");
                scanf("%s",a_date);
                fflush(stdin);

                printf(" Doctor_ID :\t");
                scanf("%d", &d_id);
                fflush(stdin);

                printf(" Disease :\t");
                scanf("%[^\n]s", disease);
                fflush(stdin);

                printf(" Prescription :\t");
                scanf("%[^\n]s", prescrptn);
                fflush(stdin);

                printf(" Medicines :\t");
                scanf("%[^\n]s", medicine);
                fflush(stdin);

                sprintf(query,"INSERT INTO medical_records VALUES('%s',%d,%d,'%s','%s','%s')", a_date, p_id, d_id, disease, prescrptn, medicine);

                if (mysql_query(conn, query))
                {

                  printf("\n Failed to execute query. Error: %s", mysql_error(conn));
                  Sleep(1500);
                  return false;

                }

                printf("\n Record Added...");

                printf("\n\n Press any key to continue or Enter to stop adding records.");

                if(getch() == 13)
                    condition = false;
            }

            mysql_free_result(result);
            break;


        case 13:

            break;


        default:

            printf("\n Wrong Choice!!\n");
            Sleep(1000);
            break;

    }

    mysql_close(conn);

    return;

}

void pharmacy()
{

    char query[150];
    int ph_id;
    int num_fields;
    char passwrd[10];
    bool condition = true;

    while( condition )
    {

        system("cls");
        printf("\n ____________________ Pharmacy ____________________\n\n"
               " 1. Pharmacy Registration\n 2. Pharmacy Login\n");
        printf("Enter Choice [1 or 2] :\t");
        fflush(stdin);

        switch(getche())
        {
            case '1':

                fflush(stdin);

                while(!pharmacy_register())
                {

                    system("cls");
                    printf("\n\n *!!!! Registration Unsuccessful !!!!*"
                           "\n Press ENTER to re-try and any other key to main menu.");

                    if(getch() != 13)
                        return;

                    fflush(stdin);

                }

                fflush(stdin);
                system("cls");
                printf("\n ************ Registration Successful ************\n");
                Sleep(1500);


            case '2':

                while(condition)
                {

                    system("cls");
                    printf("\n ____________________ Pharmacy Login ____________________\n\n");

                    printf("\n Pharmacy ID :\t");
                    scanf("%d", &ph_id);
                    fflush(stdin);

                    printf(" Password (Max 10) :\t");
                    pass_entry(passwrd);
                    fflush(stdin);

                    if(!pharmacy_login(ph_id,passwrd))
                    {

                        system("cls");
                        printf("\n\n *!!!! Login Unsuccessful !!!!*"
                               "\n Press ENTER to re-try and any other key to main menu.");

                        if(getch() != 13)
                            return;
                        else {
                                fflush(stdin);
                                continue;
                        }

                    }

                    condition = false;

                }

                system("cls");
                printf("\n ************* Login Successful *************\n");
                Sleep(1500);
                break;


            default:

                printf("\n !!Wrong Choice!!");
                condition = true;
                Sleep(1000);

        }

    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {

      printf("\n Failed to connect MySQL Server %s. Error: %s", server, mysql_error(conn));
      Sleep(1500);
      return false;

    }

    sprintf(query,"SELECT Pharmacy_ID, Pharmacy_Name, Address, City, District, State, Contact FROM pharmacy_details WHERE Pharmacy_ID = %d", ph_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    system("cls");

    printf("\n ____________________ Pharmacy Details ____________________\n\n");

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {
            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");
        }

    }

    mysql_free_result(result);

    sprintf(query,"SELECT Hospital_Name FROM hospital_details WHERE Hospital_ID IN (SELECT Hospital_ID FROM pharmacy_details WHERE Pharmacy_ID = %d)", ph_id);

    if (mysql_query(conn, query))
    {

      printf("\n Failed to execute query. Error: %s", mysql_error(conn));
      Sleep(1500);
      return false;

    }

    result = mysql_store_result(conn);
    fields = mysql_fetch_fields(result);
    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {

        for(int i = 0; i < num_fields; i++)
        {
            printf("%s :\t",fields[i].name);
            printf("%s\t", row[i] ? row[i] : "NULL");
            printf("\n");
        }

    }

    mysql_free_result(result);

    mysql_close(conn);

    printf("\n\nPress any key to continue.");
    getch();

}

int main()           /*Part of Menu*/
{

    bool condition = true;

    while( condition )
    {

        system("cls");
        printf("\n ____________________ WELCOME TO HOSPITAL MANAGEMENT SYSTEM ____________________");
        printf("\n Press 1 For Hospital\n Press 2 For Doctor\n Press 3 For Patient\n Press 4 For Pharmacy\n\n Press Enter for Exit.");
        printf("\n\n Enter Your Choice : ");
        fflush(stdin);

        switch( getche())
        {

            case '1':

                hospital();
                break;


            case '2':

                doctor();
                break;


            case '3' :

                patient();
                break;


            case '4' :

                pharmacy();
                break;


            case 13:            //13 for Enter.

                condition = false;
                break;


            default:

                printf("\n !!Wrong Choice!!");
                Sleep(1000);

        }

    }

    return 0;

}
