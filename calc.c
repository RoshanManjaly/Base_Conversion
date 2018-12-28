#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


unsigned short get_binary_op (char *bin);
void convert_to_binary (short acc, char *bin);
short get_operand (char mode);
void add (short *acc, char mode);
void subtract (short *acc, char mode);
void print_acc (short acc);
char print_menu ();



void add (short *acc, char mode)
{
short x_input = get_operand((char)mode);
short y_input = *acc;

short op_output = 0;
int input_sign = 0;
int existing_sign = 0;
int output_sign = 0;
short carry = 0;


input_sign = (short)x_input>>(15);
existing_sign = (short)y_input>>(15);


while ((short)y_input != 0) // addition
{
    carry = (short)x_input & (short)y_input;
    x_input = (short)x_input ^ (short)y_input; 
    y_input = (short)(carry << 1);
}

op_output = x_input;
output_sign = (short)op_output>>(15);

if ((input_sign == existing_sign) && (input_sign !=output_sign))
{
    if (input_sign == 0)
        printf("Overflow Error\n");
    else 
        printf("Negative Overflow Error\n");
}  
print_acc(op_output);

}



void subtract (short *acc, char mode)
{
short x_input = get_operand((char)mode);
short y_input = *acc;

short op_output = 0;
int input_sign = 0;
int existing_sign = 0;
int output_sign = 0;
short carry = 0;


input_sign = (short)x_input>>(15);
existing_sign = (short)y_input>>(15);


      while (x_input != 0)
      {
            int borrow = (~y_input) & x_input;
            y_input = y_input ^ x_input;
            x_input = borrow << 1;
      }

op_output = y_input;
output_sign = (short)op_output>>(15);

if ((input_sign == existing_sign) && (input_sign !=output_sign))
{
    if (input_sign == 0)
        printf("Overflow Error\n");
    else 
        printf("Negative Overflow Error\n");
}  


print_acc(op_output);
}



void convert_to_binary (short acc, char *bin)
{
    int i = 0;
    short one = 0000000000000001;

    for (i = 0; i < 16; i++)
    {
        if ( (i%4) ==0)
           printf(" ");
        printf("%d", ((acc>>(16-1-i)) & one));    
    }
}


unsigned short get_binary_op (char *bin) // return binary as short
{
    signed long binary;
    long bin_input;
    long out = 0;
    long base = 1;
    long temp;


    binary = atol(bin);

    bin_input = binary;
    while (bin_input > 0)
    {
        temp = bin_input % 10;
        out = out + temp * base;
        bin_input = bin_input / 10 ;
        base = base * 2;
    }

    return out;
}

short get_operand (char mode)
{
    signed int input;
    signed short output;
	unsigned short num;
	unsigned short octal;
    unsigned long binary;
    signed short binary_output;
    char temp[64];


    switch(mode) {
        case 'B' :
            printf("Enter binary value: ");
            scanf("%s" , temp);
            printf("%s\n",temp);
            binary_output = get_binary_op(temp);
            output = binary_output; 
            break;
        case 'H' :
            printf("Enter hex value: ");
            scanf("%hx" , &num);
            printf("%hx\n",num);
            output = num;
            break;
        case 'O' :
            printf("Enter octal value: ");
            scanf("%ho" , &octal);
            printf("%ho\n",octal);
			output = octal;
            break;
        case 'D' :
            printf("Enter decimal value: ");
            scanf("%d" , &input);
            printf("%d\n",input);
            output = input;
            break;
        }
    return output;
}

void print_acc (short acc)
{
    char buffer[20];

    printf("**************************************\n"); // prints out accumulator
    printf("* Accumulator:                       *\n");
    printf("*   Binary  : "); 
    convert_to_binary(acc, buffer);
    printf("   *\n");
    printf("*   Hex     :  %04X                  *\n", (unsigned short)acc); // 20 spaces after hex
    printf("*   Octal   :  %06o                *\n", (unsigned short)acc); // 16 spaces after octal
    printf("*   Decimal :  %-22d* \n", acc);
    printf("**************************************\n\n");
}

char print_menu () // Power house of this
{
    int status = 1;
    char input[32];
    char valid_inputs[24] = "bohdcsqnBOHDCSQ&|^~+-N<>";
    char fin_check_val;
    char modes[5] = "BOHD";
    int selected_mode = 3;
    short acc = 0;
    short op_input = 0;
    short op_output = 0;
    int shift_count = 0;

    printf("\n");
    char *menu = "Please select one of the following options:\n\n"
                 "B  Binary mode             &  AND with Accumulator           +  Add to Accumulator\n"
                 "O  Octal Mode              |  OR  with Acuumulator           -  Subtract from Accumulator\n"
                 "H  Hexidecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator\n"
                 "D  Decimal Mode            ~  Complement Accumulator\n\n"

                 "C  Clear Accumulator       <  Shift Accumulator Left\n"
                 "S  Set Accumulator         >  Shift Accumulator Right\n\n"

                 "Q  Quit\n\n"

                 "Option: ";

    print_acc(acc);
    
    do{
    printf("%s",menu);
    scanf("%s" , input);
    printf("%s\n",input);
        if (strlen(input)>1) // checks to make sure length of input is 1 character 
            printf("Invalid option: %s\n\n", input); 
        else
        {
            if (strchr(valid_inputs, input[0]) != NULL) // check to make sure it is a valid input
            {
                if( (input[0]>='a' && input[0]<='z')) 
                	fin_check_val = (char)toupper(input[0]); // if letter, make it capital
                else
                    fin_check_val = input[0]; //otherwise just transfer input value to checker

                if (strchr(valid_inputs, fin_check_val) != NULL)
                {
                    if (fin_check_val == 'Q')
                        status = 0;
                    else
                    {
                        switch(fin_check_val) {
                            case 'B' :
                                printf("Mode is Binary\n\n" );
                                selected_mode = 0;
                                print_acc(acc);
                                break;
                            case 'O' :
								printf("Mode is Octal\n\n" );
								selected_mode = 1;
                                print_acc(acc);
								break;
                            case 'H' :
                                printf("Mode is Hexadecimal\n\n" );
                                selected_mode = 2;
                                print_acc(acc);
                                break;
                            case 'D' :
                                printf("Mode is Decimal\n\n" );
                                selected_mode = 3;
                                print_acc(acc);
                                break;
                            case 'C' :
                                acc = 0;
                                printf("\n" );
                                print_acc(acc);
                                break;
                            case 'S' :
                                acc = get_operand((char)modes[selected_mode]);
                                printf("\n" );
                                print_acc(acc);
                                break;
                            case '&' :
                                op_input = get_operand((char)modes[selected_mode]);
                                op_output = ( (short)op_input & (short)acc);
                                printf("\n" );
                                print_acc(op_output);
                                break;
                            case '|' :
                                op_input = get_operand((char)modes[selected_mode]);
                                op_output = ( (short)op_input | (short)acc);
                                printf("\n" );
                                print_acc(op_output);
                                break;
                            case '^' :
                                op_input = get_operand((char)modes[selected_mode]);
                                op_output = ( (short)acc ^ (short)op_input) ;
                                printf("\n" );
                                print_acc(op_output);
                                break;
                            case '~' :
                                op_output = ( ~(short)acc)  ;
                                printf("\n" );
                                print_acc(op_output);
                                break;
                            case '<' :
                                shift_count = 0;
                                printf("Enter number of positions to left shift accumulator: ");
                                scanf("%d" , &shift_count);
                                op_output = ( (short)acc<<shift_count) ;
                                printf("\n" );
                                print_acc(op_output);
                                break;
                            case 'N' :
                                print_acc(-acc);
                            case '+' :
                                add(&acc, (char)modes[selected_mode]);
                                break;
                            case '-' :
                                subtract(&acc, (char)modes[selected_mode]);
                                break;




                        }
                    }
                }
                else
                    printf("Invalid option: %s\n\n", input); 
            }
            else
                printf("Invalid option: %s\n\n", input);
        }
    }while (status ==1);

    return 0;
}

int main()
{
    print_menu ();
    return 0;
}







































