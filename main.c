/*void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
int main()
{
 setupUART(); // enable UART
 unsigned char output;
 while(1)
 {

 output = UART_read(); // get UART input
 UART_write(output); // output the received input through UART
 }
return 0;
}*/

/*
void setupUART(); // Function prototypes, in assembly)
unsigned char UART_read();
void UART_write(unsigned char a);

int main(void) {
 unsigned char input_char;
 int n;

 // Initialize UART
 setupUART();

 // Prompt the user to enter a digit (1-9) by writing each character individually
 UART_write('n');
 UART_write('=');

 // Read a single character from UART (expected to be a digit)
 input_char = UART_read();
 // Echo the input character back
 UART_write(input_char);
 // Move to a new line
 UART_write('\r');
 UART_write('\n');
 // Convert the ASCII digit to an integer
 n = input_char - '0';

 // Keep the program running (typical for embedded systems)
 while (1) {

    if (n == 0){
        break;
    }

    for(int i = 0; i < n; i++){
        for (int j = 0; j <= i; j++){
            UART_write('*');
        }
        UART_write('\r');
        UART_write('\n');
    }

    break;

}

 return 0;
}*/


void setupUART();
unsigned char UART_read();
void UART_write(unsigned char a);
#define MAX_BUFFER_SIZE 100
int indexx = 0;
int index_num1 =0;
int index_num2 =0;
void uart_write_string(const char *str){
    while(*str){
        UART_write(*str);
        str++;
    }
}// 2 dig + 3 dig adds first 2 not last 3rd
// with 3 first it just prints the first 3 digits, doesnt add, just spit out same 3 digits as first entered

int getNum(char num[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (num[i] >= 0x30 && num[i] <= 0x39) {
            result = (result * 10) + (num[i] - 0x30);
        } else {
            return result; // Stop parsing on non-digit
        }
    }
    return result;
}


void getChar(int result){
    char answer[MAX_BUFFER_SIZE];
    int temp1 = result;
    int temp2 = result;
    int size = 0;

    while(1){
        if ((temp2 / 10) != 0){
            temp2 = temp2 / 10;
            size ++;
        }
        else{
            break;
        }
    }

    for (int i = size; i >= 0 ; i--){
        answer[i] = (temp1 % 10) + 0x30;
        temp1 = temp1 /10;
    }
    answer[size + 1] = '\0';

    uart_write_string(answer);
    
}

int main(void){   
    

    setupUART();
    //uart_write_string("Solve: ");
while(1){
    char num1[MAX_BUFFER_SIZE];
    char num2[MAX_BUFFER_SIZE];
    unsigned char ch; 
    int x =0 ;
    int y =0;
    int z =0;
    indexx = 0;
    uart_write_string("\n");
    uart_write_string("Solve: ");
    while (indexx < MAX_BUFFER_SIZE - 1){
        ch = UART_read();
        if(ch == '+'){
            UART_write('+');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x + y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        
        else if(ch == '-'){
            UART_write('-');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x - y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        
        else if(ch == '/'){
            UART_write('/');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x / y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }

        else if(ch == '*'){
            UART_write('*');
            int indexx = 0;
            while (indexx < MAX_BUFFER_SIZE - 1){
                ch = UART_read();
                UART_write(ch);
                index_num2 ++;
                num2[indexx++] = ch;
                num2[indexx] = '\0';
                if (ch == '\n' || ch == '\r'){
                    break;
                }
            }
            x = getNum(num1, index_num1);
            y = getNum(num2, index_num2);
            z = x * y;
            uart_write_string("\r\n");
            (getChar(z));
            break;
        }
        else{
            UART_write(ch);
            index_num1++;
            num1[indexx++] = ch;
            num1[indexx] = '\0';
        }
    }
}
    


 // Keep the program running (typical for embedded systems)
    while (1){
 // Additional functionality could be added here
    }

    return 0;
}
// detect if character entered is number or letter
// do calculation
// convert answer from number to character