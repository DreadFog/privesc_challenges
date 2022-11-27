#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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

void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

void build_decoding_table() {
 
    decoding_table = malloc(256);
 
    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}
unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length) {
 
    if (decoding_table == NULL) build_decoding_table();
 
    if (input_length % 4 != 0) return NULL;
 
    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
 
    unsigned char *decoded_data = malloc(*output_length);
    if (decoded_data == NULL) return NULL;
 
    for (int i = 0, j = 0; i < input_length;) {
 
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
 
        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);
 
        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
 
    return decoded_data;
}
void main(int argc, char* argv[]) {
    // Check if the user provided the correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <password>", argv[0]);
        exit(1);
    }
    // Check if the user is root
    if (getuid() != 0) {
        printf("You need to be root to run this script. Exiting...");
        exit(1);
    }

    // try to decode the password the same way
    // get the length of the password
    printf("%s\n", argv[1]);
    int input_size = strlen(argv[1]);
    printf("salut\n %d", input_size);

    // alloc the size of the password
    char *password = malloc(input_size*sizeof(char));
    // copy the password twice
    printf("salut\n");

    strcpy(password, argv[1]);
    for (int j = 0; j < input_size; j++) {
        password[j] = password[j] - 1;
        if (password[j] == '*') {
            password[j] = '=';
        }
    }
    printf("salut\n");
    password = base64_decode(password, input_size, &input_size);

    for (int j = 0; j < input_size; j++) {
        password[j] = password[j] ^ 0x42;
    }
    input_size = strlen(password);
    printf("salut\n");
    // get the length of the password and divide it by 2
    int decoded_password_length = strlen(password)/2;
    char* decoded_password;
    slice(password, decoded_password, 0, decoded_password_length);
    // print the first half of the password
    printf("here is the decoded password: %s\n", decoded_password);
}