#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

void build_decoding_table() {
 
    decoding_table = malloc(256);
 
    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}
 
 
void base64_cleanup() {
    free(decoding_table);
} 
 
char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {
 
    *output_length = 4 * ((input_length + 2) / 3);
 
    char *encoded_data = malloc(*output_length);
    if (encoded_data == NULL) return NULL;
 
    for (int i = 0, j = 0; i < input_length;) {
 
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
 
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
 
        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }
 
    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';
 
    return encoded_data;
}
 
void main(int argc, char *argv[]) {
    char* expected_password = "eTl4CSdKI4[{MHO2LUdGGxlgeoNtZx++";
    // check if the user is root
    if (getuid() != 0) {
        printf("You need to be root to run this script. Exiting...\n");
        exit(1);
    }
    // check if the user provided the right number of arguments
    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        exit(1);
    }
    // get the length of the password
    int password_length = strlen(argv[1]);
    int input_size = 2*password_length;
    // alloc twice the size of the password
    char *password = malloc(2*password_length*sizeof(char));
    // copy the password twice
    strcpy(password, argv[1]);
    strcpy(password+password_length, argv[1]);
    // XOR the password with 0x42 
    // then base64 it 
    // then replace '=' with '*'
    // then change every character to next one in the ASCII table
    
    for (int j = 0; j < input_size; j++) {
        password[j] = password[j] ^ 0x42;
    }
    password = base64_encode(password, input_size, &input_size);
    for (int j = 0; j < input_size; j++) {
        if (password[j] == '=') {
            password[j] = '*';
        }
        password[j] = password[j] + 1;
    }


    // print the password
    printf("here is the encoded password: %s\n", password);
    // check if the password is correct
    if (strcmp(password, expected_password) == 0) {
        printf("Admin password is correct.\n");
        printf("--------- Passwords ---------\n");
        printf("root machine account: the same you entered\n");
        printf("banking account: 0x42!?;555\n");
        printf("Github account: 0m3g4_d3v3l0p3r\n");
        printf("----------------------------\n");
    } else {
        printf("Password is incorrect. Exiting...\n");
    }   
    

}