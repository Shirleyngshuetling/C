#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

struct contact {
    char name[40];       // Stores the contact's name (up to 39 characters + null terminator).
    char phone[11];      // Stores the contact's phone number (up to 10 digits + null terminator).
    char email[50];      // Stores the contact's email address (up to 49 characters + null terminator).
    int index;           // Indicates the order in which the contact was added.
};

// THE USERNAME AND PASSWORD IS BOTH "user123" FOR TESTING PURPOSES
void login(void) {
    const char username[] = "user123";     // Predefined username for login.
    const char password[] = "user123";     // Predefined password for login.
    char input_username[20] = {0};         // Array to store the entered username, initialized to zeros.
    char input_password[20] = {0};         // Array to store the entered password, initialized to zeros.

    printf("\n************Welcome to Contact Manager**************\n");

    do {
        char hold = 'a';                    // Temporary variable to store individual characters of input.
        char buffer = 'a';                  // Buffer to discard extra characters if input exceeds limit.
        int index = 0;                      // Tracks the current position in the input arrays.

        // Clear the input_username array.
        for (int i = 0; i < 20; i++) {
            input_username[i] = '\0';
        }

        // Clear the input_password array.
        for (int i = 0; i < 20; i++) {
            input_password[i] = '\0';
        }

        // Prompt user for username.
        printf("Please enter your username: ");
        for (scanf("%c", &hold); hold != '\n'; index++, scanf("%c", &hold)) {
            if (index < 20) {
                // Store character in input_username if within bounds.
                input_username[index] = hold;
            } else {
                // If input exceeds 20 characters, discard the rest.
                while (buffer != '\n') {
                    scanf("%c", &buffer);
                }
                break;
            }
        }

        // Reset variables for password input.
        index = 0;
        buffer = 'a';

        // Prompt user for password.
        printf("Please enter your password: ");
        for (scanf("%c", &hold); hold != '\n'; index++, scanf("%c", &hold)) {
            if (index < 20) {
                // Store character in input_password if within bounds.
                input_password[index] = hold;
            } else {
                // If input exceeds 20 characters, discard the rest to clear the buffer
                while (buffer != '\n') {
                    scanf("%c", &buffer);
                }
                break;
            }
        }

        // Compare the entered username and password with predefined values.
        if (strcmp(username, input_username) == 0 && strcmp(password, input_password) == 0) {
            printf("\n\033[33mLogin successful!\033[0m\n"); // Print success message in yellow text.
            return; // Exit the function on successful login.
        }

        // If login fails, notify the user.
        printf("Incorrect username or password, try again\n\n");
    } while (1); // Repeat the process until the user logs in successfully.
}

void print_menu(void) {
    printf("\n*****************Contact Manager********************\n\t\t\033[36m1. Add Contact\n\t\t2. Edit Contact\n\t\t3. Delete Contact\n\t\t4. Display Contacts\n\t\t5. Sort Contacts\n\t\t6. Search Contact\n\t\t7. Save Contacts\033[0m\n*****************************************************\n");
}

void print_contact_list(struct contact *pContact, int count) {
    // Check if there are any contacts to display
    if (count == 0) {
        printf("\nContact list is empty\n"); // Print a message if no contacts
        return; // Exit the function
    }
    // Print header for the contact list
    printf("\n===================================================");
    // Iterate through the list of contacts and display each one
    for(int i = 0; i < count; i++) {
        printf("\n\e[1;94mContact %d\e[0m\n", i + 1); // Highlight the contact number
        printf("\tName: %s\n", pContact[i].name);    // Display contact name
        printf("\tPhone number: %s\n", pContact[i].phone); // Display phone number
        printf("\tEmail: %s\n\n", pContact[i].email);      // Display email
    }
    // Print footer for the contact list
    printf("====================================================\n");
}

void get_valid_input_size(char arr[], char prompt[], int size) {
    while(1) { // Loop until valid input is received
        printf("%s", prompt); // Display the input prompt
        char hold = 'a';      // Temporary character to store input
        char buffer = 'a';    // Buffer to consume excess characters
        int index = 0;        // Keeps track of the current position in the array
        int overflow = 0;     // Flag to indicate if input overflowed the array size
        
        // Initialize the array to empty (set all elements to '\0')
        for(int i = 0; i < size; i++) {
            arr[i] = '\0';
        }
        
        // Read user input character by character until a newline is encountered
        for(scanf("%c", &hold); hold != '\n'; index++, scanf("%c", &hold)) {
            if(index < size) {
                arr[index] = hold; // Store valid characters within array bounds
            } else {
                printf("Invalid input, Too long\n\n"); // Warn user if input is too long
                overflow = 1; // Set overflow flag
                // Consume the rest of the input to avoid incorrect subsequent reads
                while(buffer != '\n') {
                    scanf("%c", &buffer);
                }
                break; // Exit the input reading loop
            }
        }
        // If input was valid (no overflow), exit the loop and return
        if(overflow == 0) {
            return;
        }
    }
}

void get_valid_phone_num(char phone[]) {
    while(1) { // Loop until a valid phone number is provided
        int digit = 0; // Flag to indicate if the input contains non-digit characters
        
        // Prompt the user to enter a phone number and validate its size
        get_valid_input_size(phone, "Enter the phone number (number must be exactly 10 digits): ", 10);
        
        // Check if all characters in the phone number are digits
        for (int i = 0; i < 10; i++) {
            if (!isdigit(phone[i])) { // If a character is not a digit
                printf("Invalid phone number, try again\n\n"); // Inform the user
                digit = 1; // Set the flag indicating invalid input
                break; // Exit the loop to prompt the user again
            }
        }
        
        // If no invalid characters are found, exit the function
        if (digit == 0) {
            return; // Valid phone number is entered
        }
    }
}

int check_valid_index(char prompt[], int count) {
    int size_of_array = 1; // Initial size of the array to hold digits
    
    // Calculate the required size of the array based on the count
    for(double temp_count = count + 0.0; temp_count > 0; temp_count = fmod(temp_count, 1)) {
        size_of_array++; // Increment the size for each digit
    }
    
    char before_check_index[size_of_array]; // Array to store user input
    
    while(1) { // Loop until a valid input is provided
        int valid = 1; // Flag to indicate if the input is valid
        
        // Get user input with a prompt and store it in the array
        get_valid_input_size(before_check_index, prompt, size_of_array);
        
        // Determine the actual length of the input
        int len = sizeof(before_check_index) / sizeof(before_check_index[0]);
        
        // Remove trailing whitespace and null characters
        while (len > 0 && (isspace(before_check_index[len - 1]) || before_check_index[len - 1] == '\0')) {
            len--;
        }
        
        // Check each character to ensure it is a digit
        for (int i = 0; i < len; ++i) {
            if (!isdigit(before_check_index[i])) { // If a non-digit character is found
                printf("Invalid input, only enter a number\n\n");
                valid = 0; // Set the flag to invalid
                break; // Stop checking further characters
            }
        }
        
        // If input is valid, convert it to an integer and return it
        if(valid == 1) {
            char* endptr; // Pointer used by strtol to detect invalid characters
            int checked_index = strtol(before_check_index, &endptr, 10); // Convert input to an integer

            return checked_index; // Return the valid index
        }
    }
}

// Function to save contacts to a file with additional encryption parameters
void save_contacts(struct contact *pContact, int count, int letter_shift, int number_shift) {
    // Open the file "contact_list.txt" in write mode ("w")
    // Change the file path if necessary
    FILE *save_contact_list = fopen("contact_list.txt", "w");
    if (save_contact_list == NULL) { // Check if the file was successfully opened
        printf("File could not be opened\n");
        return; // Exit the function if the file couldn't be opened
    }

    // Save the number of contacts, letter shift, and number shift to the file
    // These values can be used for retrieval or encryption purposes
    fprintf(save_contact_list, "%d\n", count);         // Save the total number of contacts
    fprintf(save_contact_list, "%d\n", letter_shift);  // Save the letter shift value for ceaser cypher
    fprintf(save_contact_list, "%d\n", number_shift);  // Save the number shift value for ceaser cypher

    // Loop through each contact in the array and save its details to the file
    for (int i = 0; i < count; i++) {
        fprintf(save_contact_list, "%s\n", pContact[i].name);  // Save the contact's name
        fprintf(save_contact_list, "%s\n", pContact[i].phone); // Save the contact's phone number
        fprintf(save_contact_list, "%s\n", pContact[i].email); // Save the contact's email
        fprintf(save_contact_list, "%d\n", pContact[i].index); // Save the contact's index
    }

    // Close the file to ensure all data is written and resources are released
    fclose(save_contact_list);
}


// Function to load contacts from a file into memory
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts to populate
//   - int *count: Pointer to store the number of contacts loaded
//   - int *letter_shift: Pointer to store the letter shift value (if used for encryption)
//   - int *number_shift: Pointer to store the number shift value (if used for encryption)
// Returns:
//   - Pointer to the updated array of contacts, or NULL if memory allocation fails
struct contact *load_contact(struct contact *pContact, int *count, int *letter_shift, int *number_shift) {
    char hold;      // Temporary variable to hold characters (not used here but declared)
    char buffer;    // Temporary variable for reading extra characters
    char name[40];  // Temporary buffer for reading names from the file

    // Attempt to open the contact file in read mode ("r")
    FILE *load_contact_list = fopen("contact_list.txt", "r");
    if (load_contact_list == NULL) {  // If the file does not exist
        // Attempt to create a new file in read/write mode ("w+")
        load_contact_list = fopen("contact_list.txt", "w+");
        if (load_contact_list == NULL) {  // If file creation fails
            perror("File could not be opened.\nTerminating program.\n");
            exit(1);  // Terminate the program with an error
        }
    }

    // Read the count, letter shift, and number shift values from the file
    fscanf(load_contact_list, "%d", count);          // Total number of contacts
    fscanf(load_contact_list, "%d", letter_shift);   // Letter shift value
    fscanf(load_contact_list, "%d", number_shift);   // Number shift value

    // Resize the contact array to hold the number of contacts
    struct contact *temp = realloc(pContact, *count * sizeof(struct contact));
    if (temp == NULL) {  // Check if memory allocation was successful
        printf("Memory allocation failed");
        return NULL;  // Return NULL on failure
    }
    pContact = temp;  // Update the pointer to point to the resized array

    // Loop through each contact in the file and populate the array
    for (int i = 0; i < *count; i++) {

        // Read and store each field of the contact structure
        fscanf(load_contact_list, " %39[^\n]", name);               // Read name (max 39 chars, ignore newline)
        strcpy(pContact[i].name, name);                             // Copy name to the contact structure
        fscanf(load_contact_list, " %10[^\n]", pContact[i].phone);  // Read phone number
        fscanf(load_contact_list, " %50[^\n]", pContact[i].email);  // Read email
        fscanf(load_contact_list, "%d", &pContact[i].index);        // Read index (order added)
        
        // Read a single character to flush the buffer (handles newline after each contact)
        fscanf(load_contact_list, "%c", &buffer);
    }

    // Close the file to release resources
    fclose(load_contact_list);

    // Return the pointer to the updated contact array
    return pContact;
}

// Function to add a new contact to the contact list
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts
//   - int *count: Pointer to the current count of contacts
// Returns:
//   - Pointer to the updated array of contacts, or NULL if memory allocation fails
struct contact *add_contact(struct contact *pContact, int *count) {
    while (1) {
        char add[2];  // Buffer to hold the user's choice for adding another contact
        char hold;    // Temporary variable (unused but declared)
        char name[40], phone[11], email[50];  // Buffers for the new contact's details

        // Reallocate memory for one additional contact
        struct contact *temp = realloc(pContact, (*count + 1) * sizeof(struct contact));
        if (temp == NULL) {  // Check if memory allocation was successful
            printf("Memory allocation failed");
            free(pContact); // Free the existing contact array to prevent memory leaks
            return NULL;    // Return NULL on failure
        }
        pContact = temp;    // Update the pointer to the resized array

        // Get the contact's name
        get_valid_input_size(name, "Enter the name: ", 40);
        strcpy(pContact[*count].name, name);  // Copy the name into the contact's structure

        // Get the contact's phone number
        get_valid_phone_num(phone);
        strcpy(pContact[*count].phone, phone);  // Copy the phone number into the contact's structure

        int first_time = 1;  // Flag to track the first attempt at email validation
        // Get the contact's email
        do {
            if (first_time != 1) {  // If not the first attempt, print an error message
                printf("Invalid email, try again\n\n");
            }
            get_valid_input_size(email, "Enter the email: ", 50);  // Get the email input
            first_time = 0;  // Set the flag to indicate the first attempt is done
        } while (strstr(email, "@") == NULL);  // Ensure the email contains an '@'
        strcpy(pContact[*count].email, email);  // Copy the email into the contact's structure
        
        // Assign the index to the contact based on the current count
        pContact[*count].index = *count;

        // Increment the contact count
        (*count)++;
        printf("\n\033[93mContact added successfully\033[0m\n\n");

        // Ask the user if they want to add another contact
        get_valid_input_size(add, "Would you like to continue adding contacts?\033[1;91m(n to stop / any other char to continue)\033[0m: ", 1);
        printf("\n");

        // If the user enters 'n' or 'N', stop adding contacts and return
        if (add[0] == 'n' || add[0] == 'N') {
            return pContact;
        }
    }
}


void clear_input_buffer ()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}

// Function to edit an existing contact's details
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts
//   - int count: The number of contacts in the array
// This function allows the user to select and modify a contact's name, phone number, or email.
void edit_contact(struct contact *pContact, int count) {
    // Check if there are any contacts to edit
    if (count == 0) {
        printf("\nNo contacts found.\n");
        return; // Exit the function if no contacts exist
    }

    // Loop to allow editing multiple contacts
    while (1) {
        char add[2];       // Buffer to hold user response for continuing editing
        int index;         // Index of the contact to edit
        int to_edit;       // User's choice of field to edit

        // Display the list of contacts
        print_contact_list(pContact, count);

        // Get the index of the contact to edit (validate input)
        index = check_valid_index("Enter the contact index to edit: ", count) - 1;

        // Check if the entered index is valid
        if (index < 0 || index >= count) {
            printf("\nInvalid index! Try again.\n");
            continue; // Prompt user again if the index is invalid
        }

        // Display the details of the selected contact
        printf("\nContact %d\n", index + 1);
        printf("\tName: %s\n", pContact[index].name);
        printf("\tPhone number: %s\n", pContact[index].phone);
        printf("\tEmail: %s\n\n", pContact[index].email);

        // Loop to prompt the user for the field to edit
        while (1) {
            printf("What would you like to edit?:\n [1] Name\n [2] Phone Number\n [3] Email\n \nEnter your choice: ");
            
            // Validate input for the field choice
            if (scanf("%d", &to_edit) != 1 || to_edit < 1 || to_edit > 3) {
                printf("Invalid input. Please enter a number from 1 to 3.\n\n");
                clear_input_buffer(); // Clear any remaining input
                printf("\n");
                continue; // Re-prompt user for a valid choice
            }
            break; // Exit the loop once a valid choice is made
        }

        clear_input_buffer(); // Clear input buffer after valid choice

        // Perform the edit based on the user's choice
        switch (to_edit) {
            case 1: // Edit name
                get_valid_input_size(pContact[index].name, "Enter the new name: ", 40);
                printf("\n\033[93mName successfully edited!\033[0m\n\n");
                break;

            case 2: // Edit phone number
                get_valid_phone_num(pContact[index].phone);
                printf("\n\033[93mPhone number successfully edited!\033[0m\n\n");
                break;

            case 3: // Edit email
                do {
                    get_valid_input_size(pContact[index].email, "Enter the new email: ", 50);
                    if (strstr(pContact[index].email, "@") == NULL) { // Basic validation to check for '@'
                        printf("Invalid email format. Please include '@'.\n\n");
                    } else {
                        printf("\n\033[93mEmail successfully edited!\033[0m\n\n");
                    }
                } while (strstr(pContact[index].email, "@") == NULL); // Repeat until valid email is entered
                break;

            default: // Invalid option (should not happen due to prior validation)
                printf("Invalid option. Please try again.\n");
                break;
        }

        // Prompt user to decide if they want to continue editing contacts
        get_valid_input_size(add, "Would you like to continue editing contacts? \033[1;91m(n to stop / any other char to continue)\033[0m: ", 1);
        printf("\n");

        // If user enters 'n' or 'N', stop editing and exit the function
        if (add[0] == 'n' || add[0] == 'N') {
            return;
        }
    }
}

// Function to delete a contact from the list
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts
//   - int *count: Pointer to the number of contacts
// Returns:
//   - Updated pointer to the array of contacts after deletion
struct contact *delete_contact(struct contact *pContact, int *count) {
    while (1) {
        // Check if there are any contacts to delete
        if (*count == 0) {
            printf("There are no contacts to delete, returning to main menu\n");
            return pContact; // Exit if no contacts exist
        }

        char add[2]; // Buffer to hold user response for continuing deletion

        // Display the current list of contacts
        print_contact_list(pContact, *count);

        int index; // Index of the contact to delete
        // Loop to validate the index entered by the user
        while (1) {
            index = check_valid_index("Enter the index for the contact you would like to delete: ", *count);
            if (index > 0 && index <= *count) {
                break; // Valid index entered
            }
            printf("Invalid index, try again\n\n");
        }
        index -= 1; // Convert to zero-based index for array manipulation

        // Shift all contacts after the deleted contact to fill the gap
        for (int i = index; i < *count - 1; i++) {
            pContact[i] = pContact[i + 1]; // Move the next contact into the current position
            pContact[i].index -= 1; // Adjust the index of the shifted contact
        }

        // Reallocate memory for the updated contact list
        if (*count - 1 != 0) { // If contacts remain after deletion
            struct contact *temp = realloc(pContact, (*count - 1) * sizeof(struct contact));
            if (temp == NULL) { // Check for memory allocation failure
                printf("Memory allocation failed");
                return pContact; // Return the current pointer if reallocation fails
            }
            pContact = temp; // Update the contact list pointer
        }

        (*count)--; // Decrement the total contact count
        printf("\n\033[93mContact successfully deleted\033[0m\n\n");

        // Ask if the user wants to delete another contact
        get_valid_input_size(add, "Would you like to continue deleting contacts?\033[1;91m(n to stop / any other char to continue)\033[0m: ", 1);
        printf("\n");

        // Exit if the user chooses 'n' (no)
        if (add[0] == 'n') {
            return pContact; // Return the updated contact list pointer
        }
    }
}


// Function to merge two subarrays of the contact list
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts
//   - int left: The starting index of the left subarray
//   - int mid: The ending index of the left subarray and the midpoint
//   - int right: The ending index of the right subarray
//   - int sort_option: The option determining the sorting criterion (1 = name, 2 = phone, 3 = email, 4 = latest added)
void merge(struct contact *pContact, int left, int mid, int right, int sort_option) {
    int i, j, k;
    // Determine the sizes of the two subarrays
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Temporary arrays to store the subarrays
    struct contact leftArr[n1], rightArr[n2];

    // Copy data into the left and right subarrays
    for (i = 0; i < n1; i++) {
        leftArr[i] = pContact[left + i];
    }
    for (j = 0; j < n2; j++) {
        rightArr[j] = pContact[mid + 1 + j];
    }

    // Initialize pointers for left, right subarrays and the merged array
    i = 0; // Initial index of left subarray
    j = 0; // Initial index of right subarray
    k = left; // Initial index of the merged subarray

    // Switch case to handle different sorting criteria
    switch (sort_option) {
    case 1: // Sort by name
        while (i < n1 && j < n2) {
            // Compare names lexicographically (case-insensitive)
            if (strcasecmp(leftArr[i].name, rightArr[j].name) <= 0) {
                pContact[k] = leftArr[i];
                i++;
            } else {
                pContact[k] = rightArr[j];
                j++;
            }
            k++;
        }
        break;

    case 2: // Sort by phone number
        while (i < n1 && j < n2) {
            // Compare phone numbers lexicographically (case-insensitive)
            if (strcasecmp(leftArr[i].phone, rightArr[j].phone) <= 0) {
                pContact[k] = leftArr[i];
                i++;
            } else {
                pContact[k] = rightArr[j];
                j++;
            }
            k++;
        }
        break;

    case 3: // Sort by email
        while (i < n1 && j < n2) {
            // Compare emails lexicographically (case-insensitive)
            if (strcasecmp(leftArr[i].email, rightArr[j].email) <= 0) {
                pContact[k] = leftArr[i];
                i++;
            } else {
                pContact[k] = rightArr[j];
                j++;
            }
            k++;
        }
        break;

    case 4: // Sort by latest added (index)
        while (i < n1 && j < n2) {
            // Compare indices
            if (leftArr[i].index <= rightArr[j].index) {
                pContact[k] = leftArr[i];
                i++;
            } else {
                pContact[k] = rightArr[j];
                j++;
            }
            k++;
        }
        break;

    default:
        // Handle invalid sort options
        printf("Invalid sort option");
        break;
    }

    // Copy any remaining elements from the left subarray
    while (i < n1) {
        pContact[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy any remaining elements from the right subarray
    while (j < n2) {
        pContact[k] = rightArr[j];
        j++;
        k++;
    }
}


// Function to perform merge sort on an array of contacts
// Parameters:
//   - struct contact *pContact: Pointer to the array of contacts
//   - int left: The starting index of the subarray
//   - int right: The ending index of the subarray
//   - int sort_option: Sorting criterion (1 = name, 2 = phone, 3 = email, 4 = latest added)
void mergeSort(struct contact *pContact, int left, int right, int sort_option) {
    // Base condition for recursion: If the subarray contains at least two elements
    if (left < right) {
        // Calculate the midpoint of the current subarray
        int mid = left + (right - left) / 2;

        // Recursively apply merge sort on the left half of the subarray
        mergeSort(pContact, left, mid, sort_option);

        // Recursively apply merge sort on the right half of the subarray
        mergeSort(pContact, mid + 1, right, sort_option);

        // Merge the two sorted halves into a single sorted array
        merge(pContact, left, mid, right, sort_option);
    }
}


void merge_num_array(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergesort_num_array(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergesort_num_array(arr, left, mid);
        mergesort_num_array(arr, mid + 1, right);

        // Merge the sorted halves
        merge_num_array(arr, left, mid, right);
    }
}



// Function to compare the first N characters of a given word with a target string
// Parameters:
//   - char word[]: The input word to be checked
//   - char target[]: The target string to compare with
// Returns:
//   - 0 if the first N characters of 'word' match the 'target' exactly (case-insensitive).
//   - -1 if the first N characters of 'word' are lexicographically less than 'target'.
//   - 1 if the first N characters of 'word' are lexicographically greater than 'target'.
int letter_in_word(char word[], char target[]) {
    int len_target = 0;

    // Calculate the length of the target string
    for (int i = 0; target[i] != '\0'; i++) {
        len_target++;
    }

    // Create a temporary string `piece` to hold the first `len_target` characters of `word`
    char piece[len_target + 1];
    for (int i = 0; i < len_target; i++) {
        piece[i] = word[i];
    }
    piece[len_target] = '\0'; // Null-terminate the string to make it a valid C-string

    // Compare `piece` with `target` in a case-insensitive manner
    if (strcasecmp(piece, target) == 0) {
        return 0; // Match found
    } else if (strcasecmp(piece, target) < 0) {
        return -1; // `piece` is lexicographically less than `target`
    } else {
        return 1; // `piece` is lexicographically greater than `target`
    }
}


// Function to perform binary search on an array of strings to find all matches for a given prefix
// Parameters:
//   - char tmp[][100]: Array of strings (sorted in lexicographical order) to search through
//   - int left: Leftmost index of the search range
//   - int right: Rightmost index of the search range
//   - char target[100]: The prefix to search for
//   - int *matching_index: Array to store the indices of all matching strings
//   - int *search_count: Pointer to a counter for the number of matches found
void binary_search(char tmp[][100], int left, int right, char target[100], int *matching_index, int *search_count) {

    // Ensure valid bounds (invalid range check)
    if (left < 0 || right < left) {
        return; // Exit if the range is invalid
    }

    // Loop to repeatedly find the midpoint and compare with the target prefix
    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate the midpoint
        int is_letter_in_word = letter_in_word(tmp[mid], target); // Check if the prefix matches

        if (is_letter_in_word == 0) { // Prefix matches at midpoint
            matching_index[*search_count] = mid; // Store the index of the match
            (*search_count)++; // Increment the count of matches

            // Check for additional matches to the left of the midpoint
            int left_mid = mid - 1;
            while (left <= left_mid) {
                if (letter_in_word(tmp[left_mid], target) == 0) {
                    matching_index[*search_count] = left_mid; // Store the index of the match
                    (*search_count)++;
                    --left_mid; // Move further left
                } else {
                    break; // Stop if no further matches are found
                }
            }

            // Check for additional matches to the right of the midpoint
            int right_mid = mid + 1;
            while (right_mid <= right) {
                if (letter_in_word(tmp[right_mid], target) == 0) {
                    matching_index[*search_count] = right_mid; // Store the index of the match
                    (*search_count)++;
                    ++right_mid; // Move further right
                } else {
                    break; // Stop if no further matches are found
                }
            }
            return; // Exit the function as all matches around the midpoint are found
        } else if (is_letter_in_word < 0) { 
            // The target prefix is lexicographically greater; search the right half
            left = mid + 1;
        } else {
            // The target prefix is lexicographically smaller; search the left half
            right = mid - 1;
        }
    }
    return; // Exit if no match is found
}


// Function to search for a contact based on name, phone number, or email
// Parameters:
//   - struct contact *pContact: Array of contact structures
//   - int count: Total number of contacts
// Returns:
//   - int: 0 on successful search and display of matching contacts
int search_contact(struct contact *pContact, int count) {
    // Temporary array to hold strings for binary search
    char tmp[count][100];
    char target[100];   // User-provided search target
    int search_option; // Search option chosen by the user

    // Prompt the user to choose a search option
    while (1) {
        printf("What would you like to search by?:\n[1] Name\n[2] Phone Number\n[3] Email\n\nEnter your search choice: ");
        if (scanf("%d", &search_option) != 1 || search_option < 1 || search_option > 3) {
            // Validate input and handle invalid cases
            printf("Invalid input. Please enter a number from 1 to 3.\n\n");
            clear_input_buffer(); // Clear input buffer in case of invalid input
        } else {
            clear_input_buffer(); // Clear buffer after valid input
            break;
        }
    }

    // Get the search target from the user
    get_valid_input_size(target, "Enter the search target: ", 100);

    // Sort the contact list based on the chosen search option
    mergeSort(pContact, 0, count - 1, search_option);

    // Populate the temporary array `tmp` based on the search option
    switch (search_option) {
        case 1: // Search by name
            for (int i = 0; i < count; i++) {
                strcpy(tmp[i], pContact[i].name); // Copy contact names to the temporary array
                tmp[i][strlen(tmp[i])] = '\0'; // Ensure the string is null-terminated
            }
            break;

        case 2: // Search by phone number
            for (int i = 0; i < count; i++) {
                strcpy(tmp[i], pContact[i].phone); // Copy phone numbers to the temporary array
                tmp[i][strlen(tmp[i])] = '\0'; // Ensure the string is null-terminated
            }
            break;

        case 3: // Search by email
            for (int i = 0; i < count; i++) {
                strcpy(tmp[i], pContact[i].email); // Copy emails to the temporary array
                tmp[i][strlen(tmp[i])] = '\0'; // Ensure the string is null-terminated
            }
            break;

        default:
            break;
    }

    int matching_index[count];  // Array to store indices of matching contacts
    int search_count = 0;       // Counter for the number of matches found

    // Perform a binary search to find all matches
    binary_search(tmp, 0, count - 1, target, matching_index, &search_count);

    // Create an array for post-processing of matching indices
    int post_matching_index[search_count];
    for (int i = 0; i < search_count; i++) {
        post_matching_index[i] = matching_index[i];
    }

    // Sort the matching indices numerically
    mergesort_num_array(post_matching_index, 0, search_count - 1);

    // Display matching contacts
    int found = 0; // Flag to check if any contacts were found
    printf("\nContact(s) found with keyword '%s': \n", target);
    for (int i = 0; i < search_count; i++) {
        printf("\n\e[1;94mContact %d\e[0m\n", i + 1);
        printf("\tName: %s\n", pContact[post_matching_index[i]].name);
        printf("\tPhone number: %s\n", pContact[post_matching_index[i]].phone);
        printf("\tEmail: %s\n\n", pContact[post_matching_index[i]].email);
        found = 1;
    }

    // If no contacts were found, notify the user
    if (!found) {
        printf("\nNo contacts found with the given search term.\n");
    } else {
        return 0; // Successful search
    }

    return 0; // Return 0 regardless of the outcome
}

void ceaser_encrypt(struct contact *pContact, int count, int letter_shift, int number_shift) {
    // Loop through each contact
    for (int outerloop = 0; outerloop < count; outerloop++) {

        // Encrypt phone number using Caesar cipher (numeric only)
        for (int i = 0; pContact[outerloop].phone[i] != '\0'; i++) {
            char letter = pContact[outerloop].phone[i];

            // Shift the digits in the phone number
            // Formula: (current digit - '0' + shift + 10) % 10 + '0' ensures the result wraps around within 0-9
            pContact[outerloop].phone[i] = (letter - '0' + number_shift + 10) % 10 + '0';
        }

        // Encrypt email address using Caesar cipher (letters and digits)
        for (int i = 0; pContact[outerloop].email[i] != '\0'; i++) {
            char letter = pContact[outerloop].email[i];

            // If the character is uppercase, apply the Caesar cipher for uppercase letters
            if (isupper(letter)) {
                pContact[outerloop].email[i] = (letter - 'A' + letter_shift + 26) % 26 + 'A';
            }
            // If the character is lowercase, apply the Caesar cipher for lowercase letters
            else if (islower(letter)) {
                pContact[outerloop].email[i] = (letter - 'a' + letter_shift + 26) % 26 + 'a';
            }
            // If the character is a digit, apply Caesar cipher for digits in the email address
            else if (isdigit(letter)) {
                pContact[outerloop].email[i] = (letter - '0' + number_shift + 10) % 10 + '0';
            }
        }
    }
    return;
}


void ceaser_decrypt(struct contact *pContact, int count, int letter_shift, int number_shift) {
    // Loop through each contact
    for (int outerloop = 0; outerloop < count; outerloop++) {

        // Decrypt phone number using Caesar cipher (numeric only)
        for (int i = 0; pContact[outerloop].phone[i] != '\0'; i++) {
            char letter = pContact[outerloop].phone[i];

            // Shift the digits in the phone number in the opposite direction (decryption)
            // Formula: (current digit - '0' - shift + 10) % 10 + '0' ensures the result wraps around within 0-9
            pContact[outerloop].phone[i] = (letter - '0' - number_shift + 10) % 10 + '0';
        }

        // Decrypt email address using Caesar cipher (letters and digits)
        for (int i = 0; pContact[outerloop].email[i] != '\0'; i++) {
            char letter = pContact[outerloop].email[i];

            // If the character is uppercase, apply the Caesar cipher for uppercase letters (decryption)
            if (isupper(letter)) {
                pContact[outerloop].email[i] = (letter - 'A' - letter_shift + 26) % 26 + 'A';
            }
            // If the character is lowercase, apply the Caesar cipher for lowercase letters (decryption)
            else if (islower(letter)) {
                pContact[outerloop].email[i] = (letter - 'a' - letter_shift + 26) % 26 + 'a';
            }
            // If the character is a digit, apply Caesar cipher for digits in the email address (decryption)
            else if (isdigit(letter)) {
                pContact[outerloop].email[i] = (letter - '0' - number_shift + 10) % 10 + '0';
            }
        }
    }
    return;
}

int main(void) {
    // Call the login function to authenticate the user
    login();
    
    // Initialize random number generator based on current time
    srand(time(NULL));

    // Declare variables for dynamic array of contacts, number of contacts, and user choices
    struct contact *pContact = NULL;  // Dynamic array of contacts (initially NULL)
    int count = 0;  // Number of contacts in the array
    int sort_option = 1;  // Default sort option (by name)
    int letter_shift, number_shift;  // Shifts for Caesar cipher encryption/decryption

    // Load contacts from the saved file, along with Caesar cipher shifts
    pContact = load_contact(pContact, &count, &letter_shift, &number_shift);

    // Decrypt the loaded contacts using the Caesar cipher
    ceaser_decrypt(pContact, count, letter_shift, number_shift);

    // Main loop: display the menu and handle user input
    while(1) {
        int function = 0;  // User's menu choice
        char buffer = 'a';  // To consume the newline character left in the input buffer
        // Print the menu options
        print_menu();
        
        // Prompt the user for their choice of action, and exit if -1 is entered
        printf("Enter the number of what you would like to do, \033[1;91m(-1 to exit)\033[0m: ");
        scanf("%d", &function);
        while(buffer != '\n') {
            scanf("%c", &buffer);
        }

        // Handle the user's choice based on the function input
        switch (function)
        {
        case -1:
            // Save and exit if the user selects -1
            printf("Auto saving contacts...\n");
            
            // Generate random shifts for the Caesar cipher
            letter_shift = rand() % 51 - 25;  // Random letter shift (-25 to +25)
            number_shift = rand() % 19 - 9;   // Random number shift (-9 to +9)

            // Encrypt the contacts, save them, and then decrypt
            ceaser_encrypt(pContact, count, letter_shift, number_shift);
            save_contacts(pContact, count, letter_shift, number_shift);
            ceaser_decrypt(pContact, count, letter_shift, number_shift);
            printf("Exiting Program...\n");
            free(pContact);
            return 0;

        case 1:
            // Add a new contact and update the contact list
            pContact = add_contact(pContact, &count);
            if (pContact == NULL) {
                free(pContact);  // Free memory if adding contact failed
                break;
            }
            // Sort the contact list after adding a new contact
            // so that contact will be auto sorted according to name
            mergeSort(pContact, 0, count - 1, sort_option);
            break;

        case 2:
            // Edit an existing contact
            edit_contact(pContact, count);
            // Sort the contact list after editing
            mergeSort(pContact, 0, count - 1, sort_option);
            break;

        case 3:
            // Delete a contact from the list
            delete_contact(pContact, &count);
            break;

        case 4:
            // Print the list of all contacts
            print_contact_list(pContact, count);
            break;

        case 5:
            // Sort the contacts based on a chosen attribute
            if (count == 0) {
                printf("There are no contacts to delete, returning to main menu\n");
                break;
            }
            while (1) {
                // Prompt the user to choose a sort option
                printf("What would you like to sort by?:\n[1] Name\n[2] Phone Number\n[3] Email\n[4] Latest Added\n\nEnter your sort choice: ");
                if (scanf("%d", &sort_option) != 1 || sort_option < 1 || sort_option > 4) {
                    printf("Invalid input. Please enter a number from 1 to 4.\n\n");
                    clear_input_buffer();  // Clear invalid input
                } else {
                    break;
                }
            }
            // Sort the contacts based on the chosen option
            mergeSort(pContact, 0, count - 1, sort_option);
            print_contact_list(pContact, count);
            printf("\n\033[93mContacts sorted successfully\033[0m\n");
            break;

        case 6:
            // Search for a contact by name, phone, or email
            if (count == 0) {
                printf("There are no contacts to search, returning to main menu\n");
                break;
            }
            search_contact(pContact, count);
            // Sort contacts after searching
            mergeSort(pContact, 0, count - 1, sort_option);
            break;

        case 7:
            // Encrypt the contacts and save them
            letter_shift = rand() % 51 - 25;  // Random letter shift (-25 to +25)
            number_shift = rand() % 19 - 9;   // Random number shift (-9 to +9)
            ceaser_encrypt(pContact, count, letter_shift, number_shift);
            save_contacts(pContact, count, letter_shift, number_shift);
            ceaser_decrypt(pContact, count, letter_shift, number_shift);
            printf("\n\033[93mContacts successfully saved\033[0m\n");
            break;

        case '\n':  //ignore newlines
        case '\t':  //ignore tabs
        case ' ':   //ignore spaces in input
            break;

        default:
            // Handle invalid menu choices
            printf("\nInvalid input, try again\n");
            break;
        }
    }

    // Free dynamically allocated memory before exiting
    free(pContact);
    return 0;
}