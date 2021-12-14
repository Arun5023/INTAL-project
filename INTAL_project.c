#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// we declare a 1001 element character array
#define n 1001

// declare INTAL
char *create_INTAL()
{
    char *intal = (char *)malloc(n * sizeof(char));
    int index = 0;
    for (index = 0; index < n - 1; index++)
    {
        intal[index] = '0';
    }

    intal[index] = '\0';

    return intal;
}

// find size of character array
int length(char *c)
{
    return strlen(c);
}

//function that accepts two INTALs as function parameters and returns 0 or -1 or 1 if both INTALs are equal or first INTAL is lesser than second INTAL or second INTAL is lesser than first INTAL respectively.
int compare_INTAL(char *first, char *second)
{
    //if length of intal_first > length of intal_second, return 1
    if (length(first) > length(second))
        return 1;
    //if length of intal_first < length of intal_second, return -1
    else if (length(first) < length(second))
        return -1;
    //equal length
    else
    {
        int i = 0;
        while (i < length(first))
        {
            if (first[i] > second[i])
                return 1;

            if (first[i] < second[i])
                return -1;

            i += 1;
        }
        //equal INTAL
        return 0;
    }
}

// swap INTAL
void swap(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

//function which adds two INTALs and returns their sum.
char *add_INTAL(char *str1, char *str2)
{
    // Before proceeding further, make sure length of str2 is larger.
    if (length(str1) > length(str2))
        swap(&str1, &str2);

    char *result = create_INTAL();
    int n1 = length(str1);
    int n2 = length(str2);
    strrev(str1);
    strrev(str2);
    int carry = 0;
    int i = 0;
    for (i = 0; i < n1; i++)
    {
        int sum = (str1[i] - '0') + (str2[i] - '0') + carry;
        result[i] = (sum % 10 + '0');
        carry = sum / 10;
    }
    int j = 0;
    for (j = n1; j < n2; j++)
    {
        int sum = (str2[j] - '0') + carry;
        result[j] = (sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry)
    {
        result[n2] = carry + '0';
        result[n2 + 1] = '\0';
    }
    else
        result[n2] = '\0';

    strrev(result);
    return result;
}

// function which subtracts two INTALs and returns their difference.
char *subtract_INTAL(char *str1, char *str2)
{

    if (compare_INTAL(str1, str2) == 0)
    {
        char *result = create_INTAL();
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if (compare_INTAL(str1, str2) == -1)
        swap(&str1, &str2);

    char *result = create_INTAL();
    int n1 = length(str1);
    int n2 = length(str2);
    strrev(str1);
    strrev(str2);

    int borrow = 0;
    int i = 0;
    for (i = 0; i < n2; i++)
    {
        int diff = (str1[i] - '0') - (str2[i] - '0') - borrow;
        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
            borrow = 0;

        result[i] = (diff + '0');
    }

    int j = 0;
    for (j = n2; j < n1; j++)
    {
        int diff = (str1[j] - '0') - borrow;
        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
            borrow = 0;

        result[j] = (diff + '0');
    }

    result[n1] = '\0';
    strrev(result);

    //The result INTAL must not contain any preceding zeros in the result, unless the result is zero in which case the INTAL can contain only 1 zero.
    char *ans = create_INTAL();
    i = 0;
    for (i = 0; result[i] != '\0'; i++)
    {
        if (result[i] != '0')
            break;
    }
    j = 0;
    int k = 0;
    for (j = i; result[j] != '\0'; j++)
    {
        ans[k] = result[j];
        k++;
    }

    ans[k] = '\0';
    return ans;
}

//function which multiplies two INTALs and returns their product.
//Since our INTALs support a maximum of 1000 digits, the sum of digits of both multipliers must not exceed 1000.
char *multiply_INTAL(char *str1, char *str2)
{
    if (length(str1) == 0 || length(str2) == 0)
    {
        printf(" WARNING ! , enter proper number");
    }
    if (str1[0] == '1' && length(str1) == 1)
    {
        return str2;
    }
    if (str2[0] == '1' && length(str2) == 1)
    {
        return str1;
    }
    if (str1[0] == '0' && length(str1) == 1)
    {
        char *result = create_INTAL();
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    if (str2[0] == '0' && length(str2) == 1)
    {
        char *result = create_INTAL();
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    char *result = create_INTAL();
    int l1 = length(str1);
    int l2 = length(str2);
    int i = 0, j = 0, ptr1 = 1;
    int sum, carry, ptr2;
    for (i = l2 - 1; i >= 0; i--)
    {
        sum = 0, carry = 0;
        ptr2 = l1 + l2 - ptr1;
        for (j = l1 - 1; j >= 0; j--)
        {
            sum = (str1[j] - '0') * (str2[i] - '0') + (result[ptr2] - '0') + carry;
            result[ptr2] = sum % 10 + '0';
            carry = sum / 10;
            --ptr2;
        }
        if (carry)
            result[ptr2] = carry + '0';
        ++ptr1;
    }
    result[l1 + l2] = '\0';

    //The result INTAL must not contain any preceding zeros in the result, unless the result is zero in which case the INTAL can contain only 1 zero.
    char *ans = create_INTAL();
    i = 0;
    for (i = 0; result[i] != '\0'; i++)
    {
        if (result[i] != '0')
            break;
    }
    j = 0;
    int k = 0;
    for (j = i; result[j] != '\0'; j++)
    {
        ans[k] = result[j];
        k++;
    }

    ans[k] = '\0';
    return ans;

}
 
// function which divide INTAL to long int and return quotient
char * division_INTAL(char* dividend,long int divisor,long int* remainder){
   
    if(dividend[0]=='0' && length(dividend)==1)
    {
        char* ans = create_INTAL();
        ans[0]='0';
        ans[1]='\0';
        return ans;
    }
    
    char* quotient = create_INTAL();
    long temp=0;
    int i=0,j=0;

    while(dividend[i]){
        
         temp = temp*10 + (dividend[i] -48);
         if(temp<divisor){
            
             quotient[j++] = 48;
            
         }
         else{
             quotient[j++] = (temp / divisor) + 48;;
             temp = temp % divisor;

         }
         i++;
    }

    quotient[j] = '\0';
    *remainder = temp;

    //The result INTAL must not contain any preceding zeros in the result
    char *ans = create_INTAL();
    i = 0;
    for (i = 0; quotient[i] != '\0'; i++)
    {
        if (quotient[i] != '0')
            break;
    }
    j = 0;
    int k = 0;
    for (j = i; quotient[j] != '\0'; j++)
    {
        ans[k] = quotient[j];
        k++;
    }

    ans[k] = '\0';
    return ans;
}

char *copy(char *str)
{
    int i = 0;
    char *ans = create_INTAL();
    for (i = 0; str[i] != '\0'; i++)
    {
        ans[i] = str[i];
    }
    ans[i] = '\0';
    return ans;
}
char *Fibonacci_INTAL(unsigned int x)
{
    char *a = (char *)malloc(2 * sizeof(char));
    a[0] = '0';
    a[1] = '\0';

    if (x == 0)
    {
        return a;
    }

    char *b = (char *)malloc(2 * sizeof(char));
    b[0] = '1';
    b[1] = '\0';

    if (x == 1)
    {
        free(a);
        return b;
    }
    char *c = create_INTAL();
    int i = 2;
    for (i = 2; i <= x; i++)
    {
        c = add_INTAL(a, b);
        free(a);
        a = b;
        a = strrev(a);
        b = c;
    }
    free(a);
    return b;
}

char *factorial_INTAL(unsigned int x)
{
    char *result = (char *)malloc(2 * sizeof(char));
    result[0] = '1';
    result[1] = '\0';

    if (x == 0 || x == 1)
        return result;

    char *num = (char *)malloc(2 * sizeof(char));
    num[0] = '1';
    num[1] = '\0';
    char *temp;
    int i = 0;
    for (i = 2; i <= x; i++)
    {
        temp = add_INTAL(num, "1");
        num = temp;
        temp = multiply_INTAL(num, result);
        result = temp;
    }
    return result;
}



int main()
{
    //Creating Two INTALs for comparing
    char *INTAL1 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL1, "7596");
    char *INTAL2 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL2, "5849");

    //comparing 2 INTALs
    if (compare_INTAL(INTAL1, INTAL2) == 1)
    {
        printf("1st INTAL is greater than 2nd\n");
    }
    else
    {
        if (compare_INTAL(INTAL1, INTAL2) == -1)
        {
            printf("2nd INTAL is greater than 1st\n");
        }
        else
        {
            printf("Both INTAL are same\n");
        }
    }

    free(INTAL1);
    free(INTAL2);

    //Creating Two INTALs for Addition
    INTAL1 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL1, "7596");
    INTAL2 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL2, "5849");

    //Addition of Two INTAls
    char *ans_addition = add_INTAL(INTAL1, INTAL2);
    printf("Addition of Two INTALs : ");
    int i = 0;
    for (i = 0; ans_addition[i] != '\0'; i++)
        printf("%c", ans_addition[i]);
    printf("\n");

    free(INTAL1);
    free(INTAL2);

    //Creating Two INTALs for substraction
    INTAL1 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL1, "7596");
    INTAL2 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL2, "5849");

    //Subtraction of Two INTALs
    char *ans_substraction = subtract_INTAL(INTAL1, INTAL2);
    printf("Subtraction of Two INTALs : ");
    i = 0;
    for (i = 0; ans_substraction[i] != '\0'; i++)
        printf("%c", ans_substraction[i]);
    printf("\n");

    free(INTAL1);
    free(INTAL2);

    //Creating Two INTALs for Multiplication
    INTAL1 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL1, "7596");
    INTAL2 = (char *)malloc(1001 * sizeof(char));
    strcpy(INTAL2, "5849");

    //Multiplication of Two INTALs
    char *ans_Multiplication = multiply_INTAL(INTAL1, INTAL2);
    printf("Multiplication of Two INTALs : ");
    i = 0;
    for (i = 0; ans_Multiplication[i] != '\0'; i++)
        printf("%c", ans_Multiplication[i]);
    printf("\n");

    free(INTAL1);
    free(INTAL2);
    
    //sample test case for division
    char*  dividend = (char *)malloc(1001 * sizeof(char));
    strcpy(dividend, "0");
    long int divisor = 25,remainder = 0;
    char * quotient= division_INTAL(dividend,divisor,&remainder);
    i = 0;
    printf("quotient : ");
    for (i = 0; quotient[i] != '\0'; i++)
        printf("%c", quotient[i]);
    printf("\n");
    printf("Remainder : %lu\n",remainder);

    int Number = 20;
    //fibonacci series
    char *ans_Fibonacci = Fibonacci_INTAL(Number);
    printf("%dth Fibonacci number is : ", Number);
    i = 0;
    for (i = 0; ans_Fibonacci[i] != '\0'; i++)
        printf("%c", ans_Fibonacci[i]);
    printf("\n");

    //Factorial of a given number
    char *ans_Factorial = factorial_INTAL(Number);
    printf("Factorial of %d is : ", Number);
    i = 0;
    for (i = 0; ans_Factorial[i] != '\0'; i++)
        printf("%c", ans_Factorial[i]);
    printf("\n");
    return 0;
}