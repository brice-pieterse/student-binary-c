## Create/Manage Records In a Binary File (C)

This project serves as an introduction to several elementary concepts in C, inluding pointers, input/output, and file struction for a non trivial program.

The goal is to create a menu driven program to create and update student records in a binary file. The program includes the ability to:

- Create an initial binary file with student records
- Open and read from a binary file
- Seek a student record from a binary file
- Update or delete a student record from a binary file

#### Running the program

Compile the project:
```C
gcc src/*.c -o binmaker
```

Run the program:
```C
./binmaker
```

Make your selections from the menu:
```console
Welcome - Main Menu 
1. Create the Binary File
2. Display the contents of the file
3. Seek a specific record
4. Update the contents of a record
5. Delete a record for the specific name
6. Exit
Enter Menu Option (1-6):
```
