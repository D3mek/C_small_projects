#include <stdio.h>
#include <math.h>

// lift a car 1.
float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    float r2 = (float)stick_length * (float)human_weight / ((float)human_weight + (float)car_weight);  // length of second half of stick for lift ex. car  
    // r2 = r * m1 / ( m1 + m2 ) !!!
    r2 = roundf(r2 * 100) / 100;  // r2 round on 2

    return r2;
}

// unit price for toilet paper 2.
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    float roll_price = pack_price / (float)rolls_count;  // price of one roll in pack 
    float piece_price = roll_price / (float)pieces_count;  // price of one piece in one roll of paper
    
    float pieces_price = roundf( (piece_price * 100) *100 ) / 100;  // take price one piece of paper and multiply it with 100 and round it on 2 
    return pieces_price;

}
// bank notes ATM 3.
int bank_notes(const int price){
    int full_price = price;  // variable for hold value of parameter price because its const.
    int counter = 0;  // counter for count how much money give
    int money[5] = {200,100,50,20,10};  // array which hold money values

    if( full_price % 10 == 0 ){  // if price is ex. 45 ATM cant give money because 45 % 10 != 0 !!!
        for(int i=0; i<=4; i++){  // loop for through array 
            while( full_price > money[i]-1 ){  // engine
                  full_price = full_price - money[i];
                  counter = counter + 1;
            }
        }
        return counter;  // return how much count
    } else {
        return -1;  // because ATM cant give this value of money
    }
}

// euler's totient function 4.
int euler(const int n){
   int num = n;
   float fi = n;
   for(int i=2; i<=n; i++){
       if( ( i % 2 != 0 || (i == 2 || i == 3) ) && ( i % 3 != 0 || (i == 2 || i == 3) ) ){
          if( num % i == 0 ){
             fi = fi * (1-(1.0/i)); 
             num = num / i;
             while( num % i == 0 ){
                   num = num / i;
             }
          }
       }
    }
    return fi;
}

// find missing number 5.
int find_missing_number(const int n, const int arr[]){
    int found;  // variable for check if e. is founded or not
 
    for(int i=0; i<=n; i++){  // make sequence if n=3, 1 e. missing so there must be 4 e.
        found = 0;  // declare not founded
        for(int j=0; j<=n; j++){  // check sequence with array e. 
            if( arr[j] == i ){  // if founded then e. must be in arr
               found = 1;  // founded e. -> true
            }
        }
        if( !found ){  // not founded, mean num in sequnce is not in arr
           return i;
        }
    }
    return -1;
}

// pascal's triangle 6.
unsigned long sum_squared(const int line){
    unsigned long sum = 0;
    unsigned long coefficient = 1;

    for(int i=0; i<=line; i++){  // loop through choosen line if line = 4 then 5 e. are in line
        sum += coefficient * coefficient;  // sum
        coefficient = coefficient * (line - i) / (i + 1);  // coefficient in line in row 4 = 1 4 6 4 1 ex.
    }
    return sum;  // return sum of line 
}

// min and max price 7.1
int array_min(const int input_array[], const int array_size){ // min
      int temp;  // for store e. for swap num
      int swap = 0;  // checker
      int n = array_size;  // size of arr
      int arr[n];  // arr for manipulation because with input_array you cant manipulate ex. swap numbers
      
      if(input_array == NULL){  // copy input_arr to 
        return -1;
      }

      for(int i=0; i<n; i++){  // copy input_arr to arr cause its const
          arr[i] = input_array[i];
      }

      for(int i=0; i<n-1; i++){  // sort arr with bubble sort alg.
          for(int j=0; j<n-i-1; j++){
              if( arr[j] > arr[j + 1] ){
                 swap = 1;
                 temp = arr[j];
                 arr[j] = arr[j + 1];
                 arr[j + 1] = temp;
              }
          }
          if( !swap ){  // swap = 0 mean arr its already in correct order
             return arr[0];
          }
      }
      return arr[0]; // return lowest num after sort it must be first in arr 
}
int array_max(const int input_array[], const int array_size){ // max 7.2
    int temp;  // for store e. for swap num.
    int swap = 0;  // checker
    int n = array_size;  // size of arr
    int arr[n];  // arr for manipulation

    if(input_array == NULL){  // check if arr is not null
      return -1;
    }

    for(int i=0; i<n; i++){  // copy input_arr to arr cause its const
        arr[i] = input_array[i];
    }

    for(int i=0; i<n-1; i++){  // sort arr with bubble sort alg.
        for(int j=0; j<n-i-1; j++){
            if( arr[j] > arr[j + 1] ){
               swap = 1;
               temp = arr[j];  
               arr[j] = arr[j + 1];  // swap numbrs /\ \/
               arr[j + 1] = temp;
            }
        }
        if ( !swap ){  // if swap = 0 that's mean arr is already in correct order, this save time of program
            return arr[n - 1];  // retunr max num in arr
        }
    }
    return arr[n - 1];  // return max num in arr that's mean it must be last
}

// factor counter 8.
int factorize_count(const int n){
    int count;  // count for diffrent prime numbers
    int num = n;  // store num from n
    for(int i=2; i<=n; i++){  // check through all numbrs to n
        if( ( i % 2 != 0 || (i == 2 || i == 3) ) && ( i % 3 != 0 || (i == 2 || i == 3) ) ){ // check if its prime
           if( num % i == 0 ){  // check if num can be divided by prime num
              count += 1;  // if can be divided count +1
              num = num / i;
              while( num % i == 0 ){  // if its more prime nums just go through them for ex. 2*2*2 = 1, 2*3*3 = 2
                    num = num / i;
              }
           }
        }   
    }
    return count;  // return counted different prime numbers
}

// marathon 9.
void podium(const int n, int arr[]){
     int num = n;  // store const n to int num
     int first;
     int second;
     int third;
     
     second = num / 3;
     second = second + 1;
     first = second + 1;
     third = num - second - first;
     
     arr[0] = second;
     arr[1] = first;
     arr[2] = third;
}

int main(void){
    printf("%.4f\n", lift_a_car(2, 80, 1400) );  //1. length of stick for lift ex. car
    
    printf("%.4f\n", unit_price(5.63, 20, 200) );  //2. price of 100 pieces of paper in one roll 
    
    printf("%d\n", bank_notes(370) );  //3. ATM
    
    printf("%d\n", euler(6) );  //4. euler's totient function

    int input_array[] = {9,1,7,13,3,14,5,2,6,11,12,4,15,10,8,16};
    printf("%d\n", find_missing_number(16, input_array) );  //5. find missing number

    printf("%lu\n", sum_squared(4) );  //6. pascal's triangle
    
    int input_array2[] = {1,2,3,4,5};
    printf("%d\n", array_min(input_array2, 5) );  //7.1 find min-price
    printf("%d\n", array_max(input_array2, 5) );  //7.2 find max-price
    printf("%d\n", array_max(NULL, 5) );

    printf("%d\n", factorize_count(1110) );  //8. factor counter

    int result_array[3];
    int material = 328;
    podium(material, result_array);  //9. marathon /\ \/
    for(int i=0; i<3; i++){
       printf("%d " , result_array[i]);
    }
    printf("\n");
    return 0;
}
